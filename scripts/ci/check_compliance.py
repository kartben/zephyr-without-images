#!/usr/bin/env python3

# Copyright (c) 2018,2020 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

import collections
import sys
import subprocess
import re
import os
from email.utils import parseaddr
import logging
import argparse
from junitparser import TestCase, TestSuite, JUnitXml, Skipped, Error, Failure
import tempfile
import traceback
import magic
import shlex
from pathlib import Path

logger = None

# This ends up as None when we're not running in a Zephyr tree
ZEPHYR_BASE = os.environ.get('ZEPHYR_BASE')
if not ZEPHYR_BASE:
    # Let the user run this script as ./scripts/ci/check_compliance.py without
    #  making them set ZEPHYR_BASE.
    ZEPHYR_BASE = str(Path(__file__).resolve().parents[2])

    # Propagate this decision to child processes.
    os.environ['ZEPHYR_BASE'] = ZEPHYR_BASE

    print(f'ZEPHYR_BASE unset, using "{ZEPHYR_BASE}"')


def git(*args, cwd=None):
    # Helper for running a Git command. Returns the rstrip()ed stdout output.
    # Called like git("diff"). Exits with SystemError (raised by sys.exit()) on
    # errors. 'cwd' is the working directory to use (default: current
    # directory).

    git_cmd = ("git",) + args
    try:
        git_process = subprocess.Popen(
            git_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=cwd)
    except OSError as e:
        err(f"failed to run '{cmd2str(git_cmd)}': {e}")

    stdout, stderr = git_process.communicate()
    stdout = stdout.decode("utf-8")
    stderr = stderr.decode("utf-8")
    if git_process.returncode or stderr:
        err(f"""\
'{cmd2str(git_cmd)}' exited with status {git_process.returncode} and/or wrote
to stderr.

==stdout==
{stdout}
==stderr==
{stderr}""")

    return stdout.rstrip()


def get_shas(refspec):
    """
    Returns the list of Git SHAs for 'refspec'.

    :param refspec:
    :return:
    """
    return git('rev-list',
               '--max-count={}'.format(-1 if "." in refspec else 1),
               refspec).split()


class FmtdFailure(Failure):

    def __init__(self, severity, title, file, line, col=None, desc=""):
        self.severity = severity
        self.title = title
        self.file = file
        self.line = line
        self.col = col
        self.desc = desc
        description = f':{desc}' if desc else ''
        msg_body = desc or title

        txt = f'\n{title}{description}\nFile:{file}\nLine:{line}' + \
              (f'\nColumn:{col}' if col else '')
        msg = f'{file}:{line} {msg_body}'
        typ = severity.lower()

        super().__init__(msg, typ)

        self.text = txt


class ComplianceTest:
    """
    Base class for tests. Inheriting classes should have a run() method and set
    these class variables:

    name:
      Test name

    doc:
      Link to documentation related to what's being tested

    path_hint:
      The path the test runs itself in. This is just informative and used in
      the message that gets printed when running the test.

      The magic string "<git-top>" refers to the top-level repository
      directory. This avoids running 'git' to find the top-level directory
      before main() runs (class variable assignments run when the 'class ...'
      statement runs). That avoids swallowing errors, because main() reports
      them to GitHub.
    """
    def __init__(self):
        self.case = TestCase(type(self).name, "Guidelines")
        # This is necessary because Failure can be subclassed, but since it is
        # always restored form the element tree, the subclass is lost upon
        # restoring
        self.fmtd_failures = []

    def _result(self, res, text):
        res.text = text.rstrip()
        self.case.result += [res]

    def error(self, text, msg=None, type_="error"):
        """
        Signals a problem with running the test, with message 'msg'.

        Raises an exception internally, so you do not need to put a 'return'
        after error().
        """
        err = Error(msg or (type(self).name + " error"), type_)
        self._result(err, text)

        raise EndTest

    def skip(self, text, msg=None, type_="skip"):
        """
        Signals that the test should be skipped, with message 'msg'.

        Raises an exception internally, so you do not need to put a 'return'
        after skip().
        """
        skpd = Skipped(msg or (type(self).name + " skipped"), type_)
        self._result(skpd, text)

        raise EndTest

    def failure(self, text, msg=None, type_="failure"):
        """
        Signals that the test failed, with message 'msg'. Can be called many
        times within the same test to report multiple failures.
        """
        fail = Failure(msg or (type(self).name + " issues"), type_)
        self._result(fail, text)

    def fmtd_failure(self, severity, title, file, line, col=None, desc=""):
        """
        Signals that the test failed, and store the information in a formatted
        standardized manner. Can be called many times within the same test to
        report multiple failures.
        """
        fail = FmtdFailure(severity, title, file, line, col, desc)
        self._result(fail, fail.text)
        self.fmtd_failures.append(fail)


class EndTest(Exception):
    """
    Raised by ComplianceTest.error()/skip() to end the test.

    Tests can raise EndTest themselves to immediately end the test, e.g. from
    within a nested function call.
    """


class CheckPatch(ComplianceTest):
    """
    Runs checkpatch and reports found issues

    """
    name = "checkpatch"
    doc = "See https://docs.zephyrproject.org/latest/contribute/guidelines.html#coding-style for more details."
    path_hint = "<git-top>"

    def run(self):
        # Default to Zephyr's checkpatch if ZEPHYR_BASE is set
        checkpatch = os.path.join(ZEPHYR_BASE or GIT_TOP, 'scripts',
                                  'checkpatch.pl')
        if not os.path.exists(checkpatch):
            self.skip(checkpatch + " not found")

        # git diff's output doesn't depend on the current (sub)directory
        diff = subprocess.Popen(('git', 'diff', COMMIT_RANGE),
                                stdout=subprocess.PIPE)
        try:
            subprocess.check_output((checkpatch, '--mailback', '--no-tree', '-'),
                                    stdin=diff.stdout,
                                    stderr=subprocess.STDOUT,
                                    shell=True, cwd=GIT_TOP)

        except subprocess.CalledProcessError as ex:
            output = ex.output.decode("utf-8")
            regex = r'^\s*\S+:(\d+):\s*(ERROR|WARNING):(.+):(.+)(?:\n|\r\n?)+' \
                    r'^\s*#(\d+):\s*FILE:\s*(.+):(\d+):'

            matches = re.findall(regex, output, re.MULTILINE)
            for m in matches:
                self.fmtd_failure(m[1].lower(), m[2], m[5], m[6], col=None,
                        desc=m[3])

            # If the regex has not matched add the whole output as a failure
            if len(matches) == 0:
                self.failure(output)


class DevicetreeBindingsCheck(ComplianceTest):
    """
    Checks if we are introducing any unwanted properties in Devicetree Bindings.
    """
    name = "DevicetreeBindings"
    doc = "See https://docs.zephyrproject.org/latest/build/dts/bindings.html for more details."
    path_hint = ZEPHYR_BASE

    def run(self, full=True):
        dts_yaml = self.parse_dt_bindings()

        self.required_false_check(dts_yaml)

    def parse_dt_bindings(self):
        """
        Returns a list of dts/bindings/**/*.yaml files
        """
        if not ZEPHYR_BASE:
            self.skip("Not a Zephyr tree (ZEPHYR_BASE unset)")

        dt_bindings = []
        for file_name in git('diff', '--name-only', COMMIT_RANGE):
            if file_name.startswith('dts/bindings/') and file_name.endswith('.yaml'):
                dt_bindings.append(file_name)

        return dt_bindings

    def required_false_check(self, dt_bindings):
        for file_name in dt_bindings:
            try:
                with open(file_name) as file:
                    line_number = 0
                    for line in file:
                        line_number += 1
                        if 'required: false' in line:
                            self.fmtd_failure(
                                'warning', 'Devicetree Bindings', file_name,
                                line_number, col=None,
                                desc="'required: false' is redundant, please remove")
            except Exception:
                # error opening file (it was likely deleted by the commit)
                continue


class KconfigCheck(ComplianceTest):
    """
    Checks is we are introducing any new warnings/errors with Kconfig,
    for example using undefined Kconfig variables.
    """
    name = "Kconfig"
    doc = "See https://docs.zephyrproject.org/latest/guides/kconfig/index.html for more details."
    path_hint = ZEPHYR_BASE

    def run(self, full=True):
        kconf = self.parse_kconfig()

        self.check_top_menu_not_too_long(kconf)
        self.check_no_pointless_menuconfigs(kconf)
        self.check_no_undef_within_kconfig(kconf)
        self.check_no_redefined_in_defconfig(kconf)
        self.check_no_enable_in_boolean_prompt(kconf)
        if full:
            self.check_no_undef_outside_kconfig(kconf)

    def get_modules(self, modules_file):
        """
        Get a list of modules and put them in a file that is parsed by
        Kconfig

        This is needed to complete Kconfig sanity tests.

        """
        # Invoke the script directly using the Python executable since this is
        # not a module nor a pip-installed Python utility
        zephyr_module_path = os.path.join(ZEPHYR_BASE, "scripts",
                                          "zephyr_module.py")
        cmd = [sys.executable, zephyr_module_path,
               '--kconfig-out', modules_file]
        try:
            _ = subprocess.check_output(cmd, stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as ex:
            self.error(ex.output)

        modules_dir = ZEPHYR_BASE + '/modules'
        modules = [name for name in os.listdir(modules_dir) if
                   os.path.exists(os.path.join(modules_dir, name, 'Kconfig'))]

        with open(modules_file, 'r') as fp_module_file:
            content = fp_module_file.read()

        with open(modules_file, 'w') as fp_module_file:
            for module in modules:
                fp_module_file.write("ZEPHYR_{}_KCONFIG = {}\n".format(
                    re.sub('[^a-zA-Z0-9]', '_', module).upper(),
                    modules_dir + '/' + module + '/Kconfig'
                ))
            fp_module_file.write(content)

    def get_kconfig_dts(self, kconfig_dts_file):
        """
        Generate the Kconfig.dts using dts/bindings as the source.

        This is needed to complete Kconfig compliance tests.

        """
        # Invoke the script directly using the Python executable since this is
        # not a module nor a pip-installed Python utility
        zephyr_drv_kconfig_path = os.path.join(ZEPHYR_BASE, "scripts", "dts",
			                       "gen_driver_kconfig_dts.py")
        binding_path = os.path.join(ZEPHYR_BASE, "dts", "bindings")
        cmd = [sys.executable, zephyr_drv_kconfig_path,
               '--kconfig-out', kconfig_dts_file, '--bindings', binding_path]
        try:
            _ = subprocess.check_output(cmd, stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as ex:
            self.error(ex.output)


    def parse_kconfig(self):
        """
        Returns a kconfiglib.Kconfig object for the Kconfig files. We reuse
        this object for all tests to avoid having to reparse for each test.
        """
        if not ZEPHYR_BASE:
            self.skip("Not a Zephyr tree (ZEPHYR_BASE unset)")

        # Put the Kconfiglib path first to make sure no local Kconfiglib version is
        # used
        kconfig_path = os.path.join(ZEPHYR_BASE, "scripts", "kconfig")
        if not os.path.exists(kconfig_path):
            self.error(kconfig_path + " not found")

        sys.path.insert(0, kconfig_path)
        # Import globally so that e.g. kconfiglib.Symbol can be referenced in
        # tests
        global kconfiglib
        import kconfiglib

        # Look up Kconfig files relative to ZEPHYR_BASE
        os.environ["srctree"] = ZEPHYR_BASE

        # Parse the entire Kconfig tree, to make sure we see all symbols
        os.environ["SOC_DIR"] = "soc/"
        os.environ["ARCH_DIR"] = "arch/"
        os.environ["BOARD_DIR"] = "boards/*/*"
        os.environ["ARCH"] = "*"
        os.environ["KCONFIG_BINARY_DIR"] = tempfile.gettempdir()
        os.environ['DEVICETREE_CONF'] = "dummy"
        os.environ['TOOLCHAIN_HAS_NEWLIB'] = "y"

        # Older name for DEVICETREE_CONF, for compatibility with older Zephyr
        # versions that don't have the renaming
        os.environ["GENERATED_DTS_BOARD_CONF"] = "dummy"

        # For multi repo support
        self.get_modules(os.path.join(tempfile.gettempdir(), "Kconfig.modules"))

        # For Kconfig.dts support
        self.get_kconfig_dts(os.path.join(tempfile.gettempdir(), "Kconfig.dts"))

        # Tells Kconfiglib to generate warnings for all references to undefined
        # symbols within Kconfig files
        os.environ["KCONFIG_WARN_UNDEF"] = "y"

        try:
            # Note this will both print warnings to stderr _and_ return
            # them: so some warnings might get printed
            # twice. "warn_to_stderr=False" could unfortunately cause
            # some (other) warnings to never be printed.
            return kconfiglib.Kconfig()
        except kconfiglib.KconfigError as e:
            self.failure(str(e))
            raise EndTest

    def check_top_menu_not_too_long(self, kconf):
        """
        Checks that there aren't too many items in the top-level menu (which
        might be a sign that stuff accidentally got added there)
        """
        max_top_items = 50

        n_top_items = 0
        node = kconf.top_node.list
        while node:
            # Only count items with prompts. Other items will never be
            # shown in the menuconfig (outside show-all mode).
            if node.prompt:
                n_top_items += 1
            node = node.next

        if n_top_items > max_top_items:
            self.failure("""
Expected no more than {} potentially visible items (items with prompts) in the
top-level Kconfig menu, found {} items. If you're deliberately adding new
entries, then bump the 'max_top_items' variable in {}.
""".format(max_top_items, n_top_items, __file__))

    def check_no_redefined_in_defconfig(self, kconf):
        # Checks that no symbols are (re)defined in defconfigs.

        for node in kconf.node_iter():
            if "defconfig" in node.filename and (node.prompt or node.help):
                self.failure(f"""
Kconfig node '{node.item.name}' found with prompt or help in {node.filename}.
Options must not be defined in defconfig files.
""")
                continue

    def check_no_enable_in_boolean_prompt(self, kconf):
        # Checks that boolean's prompt does not start with "Enable...".

        for node in kconf.node_iter():
            # skip Kconfig nodes not in-tree (will present an absolute path)
            if os.path.isabs(node.filename):
                continue

            # 'kconfiglib' is global
            # pylint: disable=undefined-variable

            # only process boolean symbols with a prompt
            if (not isinstance(node.item, kconfiglib.Symbol) or
                node.item.type != kconfiglib.BOOL or
                not node.prompt or
                not node.prompt[0]):
                continue

            if re.match(r"^[Ee]nable.*", node.prompt[0]):
                self.failure(f"""
Boolean option '{node.item.name}' prompt must not start with 'Enable...'. Please
check Kconfig guidelines.
""")
                continue

    def check_no_pointless_menuconfigs(self, kconf):
        # Checks that there are no pointless 'menuconfig' symbols without
        # children in the Kconfig files

        bad_mconfs = []
        for node in kconf.node_iter():
            # 'kconfiglib' is global
            # pylint: disable=undefined-variable

            # Avoid flagging empty regular menus and choices, in case people do
            # something with 'osource' (could happen for 'menuconfig' symbols
            # too, though it's less likely)
            if node.is_menuconfig and not node.list and \
               isinstance(node.item, kconfiglib.Symbol):

                bad_mconfs.append(node)

        if bad_mconfs:
            self.failure("""\
Found pointless 'menuconfig' symbols without children. Use regular 'config'
symbols instead. See
https://docs.zephyrproject.org/latest/guides/kconfig/tips.html#menuconfig-symbols.

""" + "\n".join(f"{node.item.name:35} {node.filename}:{node.linenr}"
                for node in bad_mconfs))

    def check_no_undef_within_kconfig(self, kconf):
        """
        Checks that there are no references to undefined Kconfig symbols within
        the Kconfig files
        """
        undef_ref_warnings = "\n\n\n".join(warning for warning in kconf.warnings
                                           if "undefined symbol" in warning)

        if undef_ref_warnings:
            self.failure("Undefined Kconfig symbols:\n\n"
                             + undef_ref_warnings)

    def check_no_undef_outside_kconfig(self, kconf):
        """
        Checks that there are no references to undefined Kconfig symbols
        outside Kconfig files (any CONFIG_FOO where no FOO symbol exists)
        """
        # Grep for symbol references.
        #
        # Example output line for a reference to CONFIG_FOO at line 17 of
        # foo/bar.c:
        #
        #   foo/bar.c<null>17<null>#ifdef CONFIG_FOO
        #
        # 'git grep --only-matching' would get rid of the surrounding context
        # ('#ifdef '), but it was added fairly recently (second half of 2018),
        # so we extract the references from each line ourselves instead.
        #
        # The regex uses word boundaries (\b) to isolate the reference, and
        # negative lookahead to automatically whitelist the following:
        #
        #  - ##, for token pasting (CONFIG_FOO_##X)
        #
        #  - $, e.g. for CMake variable expansion (CONFIG_FOO_${VAR})
        #
        #  - @, e.g. for CMakes's configure_file() (CONFIG_FOO_@VAR@)
        #
        #  - {, e.g. for Python scripts ("CONFIG_FOO_{}_BAR".format(...)")
        #
        #  - *, meant for comments like '#endif /* CONFIG_FOO_* */

        defined_syms = get_defined_syms(kconf)

        # Maps each undefined symbol to a list <filename>:<linenr> strings
        undef_to_locs = collections.defaultdict(list)

        # Warning: Needs to work with both --perl-regexp and the 're' module
        regex = r"\bCONFIG_[A-Z0-9_]+\b(?!\s*##|[$@{*])"

        # Skip doc/releases, which often references removed symbols
        grep_stdout = git("grep", "--line-number", "-I", "--null",
                          "--perl-regexp", regex, "--", ":!/doc/releases",
                          cwd=Path(GIT_TOP))

        # splitlines() supports various line terminators
        for grep_line in grep_stdout.splitlines():
            path, lineno, line = grep_line.split("\0")

            # Extract symbol references (might be more than one) within the
            # line
            for sym_name in re.findall(regex, line):
                sym_name = sym_name[7:]  # Strip CONFIG_
                if sym_name not in defined_syms and \
                   sym_name not in UNDEF_KCONFIG_WHITELIST:

                    undef_to_locs[sym_name].append("{}:{}".format(path, lineno))

        if not undef_to_locs:
            return

        # String that describes all referenced but undefined Kconfig symbols,
        # in alphabetical order, along with the locations where they're
        # referenced. Example:
        #
        #   CONFIG_ALSO_MISSING    arch/xtensa/core/fatal.c:273
        #   CONFIG_MISSING         arch/xtensa/core/fatal.c:264, subsys/fb/cfb.c:20
        undef_desc = "\n".join(
            "CONFIG_{:35} {}".format(sym_name, ", ".join(locs))
            for sym_name, locs in sorted(undef_to_locs.items()))

        self.failure("""
Found references to undefined Kconfig symbols. If any of these are false
positives, then add them to UNDEF_KCONFIG_WHITELIST in {} in the ci-tools repo.

If the reference is for a comment like /* CONFIG_FOO_* */ (or
/* CONFIG_FOO_*_... */), then please use exactly that form (with the '*'). The
CI check knows not to flag it.

More generally, a reference followed by $, @, {{, *, or ## will never be
flagged.

{}""".format(os.path.basename(__file__), undef_desc))


def get_defined_syms(kconf):
    # Returns a set() with the names of all defined Kconfig symbols (with no
    # 'CONFIG_' prefix). This is complicated by samples and tests defining
    # their own Kconfig trees. For those, just grep for 'config FOO' to find
    # definitions. Doing it "properly" with Kconfiglib is still useful for the
    # main tree, because some symbols are defined using preprocessor macros.

    # Warning: Needs to work with both --perl-regexp and the 're' module.
    # (?:...) is a non-capturing group.
    regex = r"^\s*(?:menu)?config\s*([A-Z0-9_]+)\s*(?:#|$)"

    # Grep samples/ and tests/ for symbol definitions
    grep_stdout = git("grep", "-I", "-h", "--perl-regexp", regex, "--",
                      ":samples", ":tests", cwd=ZEPHYR_BASE)

    # Symbols from the main Kconfig tree + grepped definitions from samples and
    # tests
    return set([sym.name for sym in kconf.unique_defined_syms]
               + re.findall(regex, grep_stdout, re.MULTILINE))


# Many of these are symbols used as examples. Note that the list is sorted
# alphabetically, and skips the CONFIG_ prefix.
UNDEF_KCONFIG_WHITELIST = {
    "ALSO_MISSING",
    "APP_LINK_WITH_",
    "APP_LOG_LEVEL", # Application log level is not detected correctly as the
                     # option is defined using a template, so it can't be
                     # grepped
    "ARMCLANG_STD_LIBC",  # The ARMCLANG_STD_LIBC is defined in the toolchain
                          # Kconfig which is sourced based on Zephyr toolchain
			  # variant and therefore not visible to compliance.
    "BOOT_UPGRADE_ONLY", # Used in example adjusting MCUboot config, but symbol
                         # is defined in MCUboot itself.
    "CDC_ACM_PORT_NAME_",
    "CLOCK_STM32_SYSCLK_SRC_",
    "CMU",
    "BT_6LOWPAN",  # Defined in Linux, mentioned in docs
    "COUNTER_RTC_STM32_CLOCK_SRC",
    "CRC",  # Used in TI CC13x2 / CC26x2 SDK comment
    "DEEP_SLEEP",  # #defined by RV32M1 in ext/
    "DESCRIPTION",
    "ERR",
    "ESP_DIF_LIBRARY",  # Referenced in CMake comment
    "EXPERIMENTAL",
    "FFT",  # Used as an example in cmake/extensions.cmake
    "FLAG",  # Used as an example
    "FOO",
    "FOO_LOG_LEVEL",
    "FOO_SETTING_1",
    "FOO_SETTING_2",
    "LSM6DSO_INT_PIN",
    "MCUBOOT_LOG_LEVEL_WRN",        # Used in example adjusting MCUboot config,
    "MCUBOOT_DOWNGRADE_PREVENTION", # but symbols are defined in MCUboot itself.
    "MISSING",
    "MODULES",
    "MYFEATURE",
    "MY_DRIVER_0",
    "NORMAL_SLEEP",  # #defined by RV32M1 in ext/
    "OPT",
    "OPT_0",
    "PEDO_THS_MIN",
    "REG1",
    "REG2",
    "SAMPLE_MODULE_LOG_LEVEL",  # Used as an example in samples/subsys/logging
    "SAMPLE_MODULE_LOG_LEVEL_DBG",  # Used in tests/subsys/logging/log_api
    "LOG_BACKEND_MOCK_OUTPUT_DEFAULT", #Referenced in tests/subsys/logging/log_syst
    "LOG_BACKEND_MOCK_OUTPUT_SYST", #Referenced in testcase.yaml of log_syst test
    "SEL",
    "SHIFT",
    "SOC_WATCH",  # Issue 13749
    "SOME_BOOL",
    "SOME_INT",
    "SOME_OTHER_BOOL",
    "SOME_STRING",
    "SRAM2",  # Referenced in a comment in samples/application_development
    "STACK_SIZE",  # Used as an example in the Kconfig docs
    "STD_CPP",  # Referenced in CMake comment
    "TAGOIO_HTTP_POST_LOG_LEVEL",  # Used as in samples/net/cloud/tagoio
    "TEST1",
    "TYPE_BOOLEAN",
    "USB_CONSOLE",
    "USE_STDC_",
    "WHATEVER",
    "EXTRA_FIRMWARE_DIR", # Linux, in boards/xtensa/intel_adsp_cavs25/doc
    "HUGETLBFS",          # Linux, in boards/xtensa/intel_adsp_cavs25/doc
    "MODVERSIONS",        # Linux, in boards/xtensa/intel_adsp_cavs25/doc
    "SECURITY_LOADPIN",   # Linux, in boards/xtensa/intel_adsp_cavs25/doc
    "ZEPHYR_TRY_MASS_ERASE", # MCUBoot setting described in sysbuild documentation
    "ZTEST_FAIL_TEST_",  # regex in tests/ztest/fail/CMakeLists.txt
}

class KconfigBasicCheck(KconfigCheck):
    """
    Checks if we are introducing any new warnings/errors with Kconfig,
    for example using undefined Kconfig variables.
    This runs the basic Kconfig test, which is checking only for undefined
    references inside the Kconfig tree.
    """
    name = "KconfigBasic"
    doc = "See https://docs.zephyrproject.org/latest/guides/kconfig/index.html for more details."
    path_hint = ZEPHYR_BASE

    def run(self):
        super().run(full=False)


class Codeowners(ComplianceTest):
    """
    Check if added files have an owner.
    """
    name = "Codeowners"
    doc = "See https://help.github.com/articles/about-code-owners/ for more details."
    path_hint = "<git-top>"

    def ls_owned_files(self, codeowners):
        """Returns an OrderedDict mapping git patterns from the CODEOWNERS file
        to the corresponding list of files found on the filesystem.  It
        unfortunately does not seem possible to invoke git and re-use
        how 'git ignore' and/or 'git attributes' already implement this,
        we must re-invent it.
        """

        # TODO: filter out files not in "git ls-files" (e.g.,
        # twister-out) _if_ the overhead isn't too high for a clean tree.
        #
        # pathlib.match() doesn't support **, so it looks like we can't
        # recursively glob the output of ls-files directly, only real
        # files :-(

        pattern2files = collections.OrderedDict()
        top_path = Path(GIT_TOP)

        with open(codeowners, "r") as codeo:
            for lineno, line in enumerate(codeo, start=1):

                if line.startswith("#") or not line.strip():
                    continue

                match = re.match(r"^([^\s,]+)\s+[^\s]+", line)
                if not match:
                    self.failure(
                        "Invalid CODEOWNERS line %d\n\t%s" %
                        (lineno, line))
                    continue

                git_patrn = match.group(1)
                glob = self.git_pattern_to_glob(git_patrn)
                files = []
                for abs_path in top_path.glob(glob):
                    # comparing strings is much faster later
                    files.append(str(abs_path.relative_to(top_path)))

                if not files:
                    self.failure("Path '{}' not found in the tree but is listed in "
                                     "CODEOWNERS".format(git_patrn))

                pattern2files[git_patrn] = files

        return pattern2files

    def git_pattern_to_glob(self, git_pattern):
        """Appends and prepends '**[/*]' when needed. Result has neither a
        leading nor a trailing slash.
        """

        if git_pattern.startswith("/"):
            ret = git_pattern[1:]
        else:
            ret = "**/" + git_pattern

        if git_pattern.endswith("/"):
            ret = ret + "**/*"
        elif os.path.isdir(os.path.join(GIT_TOP, ret)):
            self.failure("Expected '/' after directory '{}' "
                             "in CODEOWNERS".format(ret))

        return ret

    def run(self):
        # TODO: testing an old self.commit range that doesn't end
        # with HEAD is most likely a mistake. Should warn, see
        # https://github.com/zephyrproject-rtos/ci-tools/pull/24
        codeowners = os.path.join(GIT_TOP, "CODEOWNERS")
        if not os.path.exists(codeowners):
            self.skip("CODEOWNERS not available in this repo")

        name_changes = git("diff", "--name-only", "--diff-filter=ARCD",
                           COMMIT_RANGE)

        owners_changes = git("diff", "--name-only", COMMIT_RANGE,
                             "--", codeowners)

        if not name_changes and not owners_changes:
            # TODO: 1. decouple basic and cheap CODEOWNERS syntax
            # validation from the expensive ls_owned_files() scanning of
            # the entire tree. 2. run the former always.
            return

        logger.info("If this takes too long then cleanup and try again")
        patrn2files = self.ls_owned_files(codeowners)

        # The way git finds Renames and Copies is not "exact science",
        # however if one is missed then it will always be reported as an
        # Addition instead.
        new_files = git("diff", "--name-only", "--diff-filter=ARC",
                        COMMIT_RANGE).splitlines()
        logger.debug("New files %s", new_files)

        # Convert to pathlib.Path string representation (e.g.,
        # backslashes 'dir1\dir2\' on Windows) to be consistent
        # with self.ls_owned_files()
        new_files = [str(Path(f)) for f in new_files]

        new_not_owned = []
        for newf in new_files:
            f_is_owned = False

            for git_pat, owned in patrn2files.items():
                logger.debug("Scanning %s for %s", git_pat, newf)

                if newf in owned:
                    logger.info("%s matches new file %s", git_pat, newf)
                    f_is_owned = True
                    # Unlike github, we don't care about finding any
                    # more specific owner.
                    break

            if not f_is_owned:
                new_not_owned.append(newf)

        if new_not_owned:
            self.failure("New files added that are not covered in "
                             "CODEOWNERS:\n\n" + "\n".join(new_not_owned) +
                             "\n\nPlease add one or more entries in the "
                             "CODEOWNERS file to cover those files")


class Nits(ComplianceTest):
    """
    Checks various nits in added/modified files. Doesn't check stuff that's
    already covered by e.g. checkpatch.pl and pylint.
    """
    name = "Nits"
    doc = "See https://docs.zephyrproject.org/latest/contribute/guidelines.html#coding-style for more details."
    path_hint = "<git-top>"

    def run(self):
        # Loop through added/modified files
        for fname in git("diff", "--name-only", "--diff-filter=d",
                         COMMIT_RANGE).splitlines():
            if "Kconfig" in fname:
                self.check_kconfig_header(fname)
                self.check_redundant_zephyr_source(fname)

            if fname.startswith("dts/bindings/"):
                self.check_redundant_document_separator(fname)

            if fname.endswith((".c", ".conf", ".cpp", ".dts", ".overlay",
                               ".h", ".ld", ".py", ".rst", ".txt", ".yaml",
                               ".yml")) or \
               "Kconfig" in fname or \
               "defconfig" in fname or \
               fname == "README":

                self.check_source_file(fname)

    def check_kconfig_header(self, fname):
        # Checks for a spammy copy-pasted header format

        with open(os.path.join(GIT_TOP, fname), encoding="utf-8") as f:
            contents = f.read()

        # 'Kconfig - yada yada' has a copy-pasted redundant filename at the
        # top. This probably means all of the header was copy-pasted.
        if re.match(r"\s*#\s*(K|k)config[\w.-]*\s*-", contents):
            self.failure("""
Please use this format for the header in '{}' (see
https://docs.zephyrproject.org/latest/guides/kconfig/index.html#header-comments-and-other-nits):

    # <Overview of symbols defined in the file, preferably in plain English>
    (Blank line)
    # Copyright (c) 2019 ...
    # SPDX-License-Identifier: <License>
    (Blank line)
    (Kconfig definitions)

Skip the "Kconfig - " part of the first line, since it's clear that the comment
is about Kconfig from context. The "# Kconfig - " is what triggers this
failure.
""".format(fname))

    def check_redundant_zephyr_source(self, fname):
        # Checks for 'source "$(ZEPHYR_BASE)/Kconfig[.zephyr]"', which can be
        # be simplified to 'source "Kconfig[.zephyr]"'

        with open(os.path.join(GIT_TOP, fname), encoding="utf-8") as f:
            # Look for e.g. rsource as well, for completeness
            match = re.search(
                r'^\s*(?:o|r|or)?source\s*"\$\(?ZEPHYR_BASE\)?/(Kconfig(?:\.zephyr)?)"',
                f.read(), re.MULTILINE)

            if match:
                self.failure("""
Redundant 'source "$(ZEPHYR_BASE)/{0}" in '{1}'. Just do 'source "{0}"'
instead. The $srctree environment variable already points to the Zephyr root,
and all 'source's are relative to it.""".format(match.group(1), fname))

    def check_redundant_document_separator(self, fname):
        # Looks for redundant '...' document separators in bindings

        with open(os.path.join(GIT_TOP, fname), encoding="utf-8") as f:
            if re.search(r"^\.\.\.", f.read(), re.MULTILINE):
                self.failure(f"""\
Redundant '...' document separator in {fname}. Binding YAML files are never
concatenated together, so no document separators are needed.""")

    def check_source_file(self, fname):
        # Generic nits related to various source files

        with open(os.path.join(GIT_TOP, fname), encoding="utf-8") as f:
            contents = f.read()

        if not contents.endswith("\n"):
            self.failure("Missing newline at end of '{}'. Check your text "
                             "editor settings.".format(fname))

        if contents.startswith("\n"):
            self.failure("Please remove blank lines at start of '{}'"
                             .format(fname))

        if contents.endswith("\n\n"):
            self.failure("Please remove blank lines at end of '{}'"
                             .format(fname))


class GitLint(ComplianceTest):
    """
    Runs gitlint on the commits and finds issues with style and syntax

    """
    name = "Gitlint"
    doc = "See https://docs.zephyrproject.org/latest/contribute/guidelines.html#commit-guidelines for more details"
    path_hint = "<git-top>"

    def run(self):
        # By default gitlint looks for .gitlint configuration only in
        # the current directory
        proc = subprocess.Popen('gitlint --commits ' + COMMIT_RANGE,
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                shell=True, cwd=GIT_TOP)

        msg = ""
        if proc.wait() != 0:
            msg = proc.stdout.read()

        if msg != "":
            self.failure(msg.decode("utf-8"))


class PyLint(ComplianceTest):
    """
    Runs pylint on all .py files, with a limited set of checks enabled. The
    configuration is in the pylintrc file.
    """
    name = "pylint"
    doc = "See https://www.pylint.org/ for more details"
    path_hint = "<git-top>"

    def run(self):
        # Path to pylint configuration file
        pylintrc = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                "pylintrc"))

        # List of files added/modified by the commit(s).
        files = git(
            "diff", "--name-only", "--diff-filter=d", COMMIT_RANGE, "--",
            # Skip to work around crash in pylint 2.2.2:
            # https://github.com/PyCQA/pylint/issues/2906
            ":!boards/xtensa/intel_s1000_crb/support/create_board_img.py") \
            .splitlines()

        # Filter out everything but Python files. Keep filenames
        # relative (to GIT_TOP) to stay farther from any command line
        # limit.
        py_files = filter_py(GIT_TOP, files)
        if not py_files:
            return

        pylintcmd = ["pylint", "--rcfile=" + pylintrc] + py_files
        logger.info(cmd2str(pylintcmd))
        try:
            subprocess.run(pylintcmd,
                           check=True,
                           stdout=subprocess.PIPE,
                           stderr=subprocess.STDOUT,
                           cwd=GIT_TOP)
        except subprocess.CalledProcessError as ex:
            output = ex.output.decode("utf-8")
            regex = r'^\s*(\S+):(\d+):(\d+):\s*([A-Z]\d{4}):\s*(.*)$'

            matches = re.findall(regex, output, re.MULTILINE)
            for m in matches:
                # https://pylint.pycqa.org/en/latest/user_guide/messages/messages_overview.html#
                severity = 'unknown'
                if m[3][0] in ('F', 'E'):
                    severity = 'error'
                elif m[3][0] in ('W','C', 'R', 'I'):
                    severity = 'warning'
                self.fmtd_failure(severity, m[3], m[0], m[1], col=m[2],
                        desc=m[4])

            # If the regex has not matched add the whole output as a failure
            if len(matches) == 0:
                self.failure(output)


def filter_py(root, fnames):
    # PyLint check helper. Returns all Python script filenames among the
    # filenames in 'fnames', relative to directory 'root'.
    #
    # Uses the python-magic library, so that we can detect Python
    # files that don't end in .py as well. python-magic is a frontend
    # to libmagic, which is also used by 'file'.
    #
    # The extra os.path.isfile() is necessary because git includes
    # submodule directories in its output.

    return [fname for fname in fnames
            if os.path.isfile(os.path.join(root, fname)) and
            (fname.endswith(".py") or
             magic.from_file(os.path.join(root, fname),
                             mime=True) == "text/x-python")]


class Identity(ComplianceTest):
    """
    Checks if Emails of author and signed-off messages are consistent.
    """
    name = "Identity"
    doc = "See https://docs.zephyrproject.org/latest/contribute/guidelines.html#commit-guidelines for more details"
    # git rev-list and git log don't depend on the current (sub)directory
    # unless explicited
    path_hint = "<git-top>"

    def run(self):
        for shaidx in get_shas(COMMIT_RANGE):
            commit = git("log", "--decorate=short", "-n 1", shaidx)
            signed = []
            author = ""
            sha = ""
            parsed_addr = None
            for line in commit.split("\n"):
                match = re.search(r"^commit\s([^\s]*)", line)
                if match:
                    sha = match.group(1)
                match = re.search(r"^Author:\s(.*)", line)
                if match:
                    author = match.group(1)
                    parsed_addr = parseaddr(author)
                match = re.search(r"signed-off-by:\s(.*)", line, re.IGNORECASE)
                if match:
                    signed.append(match.group(1))

            error1 = "%s: author email (%s) needs to match one of the signed-off-by entries." % (
                sha, author)
            error2 = "%s: author email (%s) does not follow the syntax: First Last <email>." % (
                sha, author)
            error3 = "%s: author email (%s) must be a real email and cannot end in @users.noreply.github.com" % (
                sha, author)
            failure = None
            if author not in signed:
                failure = error1

            if not parsed_addr or len(parsed_addr[0].split(" ")) < 2:
                if not failure:

                    failure = error2
                else:
                    failure = failure + "\n" + error2
            elif parsed_addr[1].endswith("@users.noreply.github.com"):
                failure = error3

            if failure:
                self.failure(failure)


def init_logs(cli_arg):
    # Initializes logging

    global logger

    level = os.environ.get('LOG_LEVEL', "WARN")

    console = logging.StreamHandler()
    console.setFormatter(logging.Formatter('%(levelname)-8s: %(message)s'))

    logger = logging.getLogger('')
    logger.addHandler(console)
    logger.setLevel(cli_arg or level)

    logger.info("Log init completed, level=%s",
                 logging.getLevelName(logger.getEffectiveLevel()))


def inheritors(klass):
    subclasses = set()
    work = [klass]
    while work:
        parent = work.pop()
        for child in parent.__subclasses__():
            if child not in subclasses:
                subclasses.add(child)
                work.append(child)
    return subclasses


def annotate(res):
    """
    https://docs.github.com/en/actions/using-workflows/workflow-commands-for-github-actions#about-workflow-commands
    """
    notice = f'::{res.severity} file={res.file},line={res.line}' + \
             (f',col={res.col}' if res.col else '') + \
             f',title={res.title}::{res.message}'
    print(notice)


def parse_args():

    default_range = 'HEAD~1..HEAD'
    parser = argparse.ArgumentParser(
        description="Check for coding style and documentation warnings.")
    parser.add_argument('-c', '--commits', default=default_range,
                        help=f'''Commit range in the form: a..[b], default is
                        {default_range}''')
    parser.add_argument('-o', '--output', default="compliance.xml",
                        help='''Name of outfile in JUnit format,
                        default is ./compliance.xml''')
    parser.add_argument('-l', '--list', action="store_true",
                        help="List all checks and exit")
    parser.add_argument("-v", "--loglevel", choices=['DEBUG', 'INFO', 'WARNING',
                                                     'ERROR', 'CRITICAL'],
                        help="python logging level")
    parser.add_argument('-m', '--module', action="append", default=[],
                        help="Checks to run. All checks by default.")
    parser.add_argument('-e', '--exclude-module', action="append", default=[],
                        help="Do not run the specified checks")
    parser.add_argument('-j', '--previous-run', default=None,
                        help='''Pre-load JUnit results in XML format
                        from a previous run and combine with new results.''')
    parser.add_argument('--annotate', action="store_true",
                        help="Print GitHub Actions-compatible annotations.")

    return parser.parse_args()

def _main(args):
    # The "real" main(), which is wrapped to catch exceptions and report them
    # to GitHub. Returns the number of test failures.

    # The absolute path of the top-level git directory. Initialize it here so
    # that issues running Git can be reported to GitHub.
    global GIT_TOP
    GIT_TOP = git("rev-parse", "--show-toplevel")

    # The commit range passed in --commit, e.g. "HEAD~3"
    global COMMIT_RANGE
    COMMIT_RANGE = args.commits

    init_logs(args.loglevel)

    logger.info(f'Running tests on commit range {COMMIT_RANGE}')

    if args.list:
        for testcase in inheritors(ComplianceTest):
            print(testcase.name)
        return 0

    # Load saved test results from an earlier run, if requested
    if args.previous_run:
        if not os.path.exists(args.previous_run):
            # This probably means that an earlier pass had an internal error
            # (the script is currently run multiple times by the ci-pipelines
            # repo). Since that earlier pass might've posted an error to
            # GitHub, avoid generating a GitHub comment here, by avoiding
            # sys.exit() (which gets caught in main()).
            print("error: '{}' not found".format(args.previous_run),
                  file=sys.stderr)
            return 1

        logging.info("Loading previous results from " + args.previous_run)
        for loaded_suite in JUnitXml.fromfile(args.previous_run):
            suite = loaded_suite
            break
    else:
        suite = TestSuite("Compliance")

    for testcase in inheritors(ComplianceTest):
        # "Modules" and "testcases" are the same thing. Better flags would have
        # been --tests and --exclude-tests or the like, but it's awkward to
        # change now.

        if args.module and testcase.name not in args.module:
            continue

        if testcase.name in args.exclude_module:
            print("Skipping " + testcase.name)
            continue

        test = testcase()
        try:
            print(f"Running {test.name:16} tests in "
                  f"{GIT_TOP if test.path_hint == '<git-top>' else test.path_hint} ...")
            test.run()
        except EndTest:
            pass

        # Annotate if required
        if args.annotate:
            for res in test.fmtd_failures:
                annotate(res)

        suite.add_testcase(test.case)

    xml = JUnitXml()
    xml.add_testsuite(suite)
    xml.update_statistics()
    xml.write(args.output, pretty=True)

    failed_cases = []
    name2doc = {testcase.name: testcase.doc
						for testcase in inheritors(ComplianceTest)}

    for case in suite:
        if case.result:
            if case.is_skipped:
                logging.warning("Skipped %s", case.name)
            else:
                failed_cases.append(case)
        else:
            # Some checks like codeowners can produce no .result
            logging.info("No JUnit result for %s", case.name)

    n_fails = len(failed_cases)

    if n_fails:
        print("{} checks failed".format(n_fails))
        for case in failed_cases:
            errmsg = ""
            with open(f"{case.name}.txt", "w") as f:
                docs = name2doc.get(case.name)
                f.write(f"{docs}\n")
                for res in case.result:
                    errmsg = res.text.strip()
                    logging.error("Test %s failed: \n%s", case.name, errmsg)
                    f.write('\n' + errmsg)

    print("\nComplete results in " + args.output)
    return n_fails


def main():
    args = parse_args()

    try:
        # pylint: disable=unused-import
        from lxml import etree
    except ImportError:
        print("\nERROR: Python module lxml not installed, unable to proceed")
        print("See https://github.com/weiwei/junitparser/issues/99")
        return 1

    try:
        n_fails = _main(args)
    except BaseException:
        # Catch BaseException instead of Exception to include stuff like
        # SystemExit (raised by sys.exit())
        print("Python exception in `{}`:\n\n"
              "```\n{}\n```".format(__file__, traceback.format_exc()))

        raise

    sys.exit(n_fails)


def cmd2str(cmd):
    # Formats the command-line arguments in the iterable 'cmd' into a string,
    # for error messages and the like

    return " ".join(shlex.quote(word) for word in cmd)


def err(msg):
    cmd = sys.argv[0]  # Empty if missing
    if cmd:
        cmd += ": "
    sys.exit(cmd + "error: " + msg)


if __name__ == "__main__":
    main()

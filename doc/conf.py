# -*- coding: utf-8 -*-
#
# Zephyr documentation build configuration file, created by
# sphinx-quickstart on Fri May  8 11:43:01 2015.
#
# This file is execfile()d with the current directory set to its
# containing dir.
#
# Note that not all possible configuration values are present in this
# autogenerated file.
#
# All configuration values have a default; values that are commented out
# serve to show the default.

import sys
import os
from subprocess import CalledProcessError, check_output, DEVNULL

if "ZEPHYR_BASE" not in os.environ:
    sys.exit("$ZEPHYR_BASE environment variable undefined.")
ZEPHYR_BASE = os.path.abspath(os.environ["ZEPHYR_BASE"])

if "ZEPHYR_BUILD" not in os.environ:
    sys.exit("$ZEPHYR_BUILD environment variable undefined.")
ZEPHYR_BUILD = os.path.abspath(os.environ["ZEPHYR_BUILD"])

# Add the 'extensions' directory to sys.path, to enable finding Sphinx
# extensions within.
sys.path.insert(0, os.path.join(ZEPHYR_BASE, 'doc', 'extensions'))

# Add the directory which contains the runners package as well,
# for autodoc directives on runners.xyz.
sys.path.insert(0, os.path.join(ZEPHYR_BASE, 'scripts', 'west_commands'))

west_found = False

try:
    desc = check_output(['west', 'list', '-f{abspath}', 'west'],
			stderr=DEVNULL,
			cwd=os.path.dirname(__file__))
    west_path = desc.decode(sys.getdefaultencoding()).strip()
    # Add west, to be able to pull in its API docs.
    sys.path.append(os.path.join(west_path, 'src'))
    west_found = True
except FileNotFoundError as e:
    # west not installed
    pass
except CalledProcessError as e:
    # west not able to list itself
    pass

# -- General configuration ------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'breathe', 'sphinx.ext.todo',
    'sphinx.ext.extlinks',
    'sphinx.ext.autodoc',
    'zephyr.application',
    'zephyr.html_redirects',
    'only.eager_only',
    'zephyr.link-roles'
]

# Only use SVG converter when it is really needed, e.g. LaTeX.
if tags.has("svgconvert"):
    extensions.append('sphinxcontrib.rsvgconverter')

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
# source_suffix = ['.rst', '.md']
source_suffix = '.rst'

# The encoding of source files.
#source_encoding = 'utf-8-sig'

# The master toctree document.
master_doc = 'index'

# General information about the project.
project = u'Zephyr Project'
copyright = u'2015-2019 Zephyr Project members and individual contributors'
author = u'The Zephyr Project'

# The following code tries to extract the information by reading the Makefile,
# when Sphinx is run directly (e.g. by Read the Docs).
try:
    version_major = None
    version_minor = None
    patchlevel = None
    extraversion = None
    for line in open(os.path.join(ZEPHYR_BASE, 'VERSION')):
        key, val = [x.strip() for x in line.split('=', 2)]
        if key == 'VERSION_MAJOR':
            version_major = val
        if key == 'VERSION_MINOR':
            version_minor = val
        elif key == 'PATCHLEVEL':
            patchlevel = val
        elif key == 'EXTRAVERSION':
            extraversion = val
        if version_major and version_minor and patchlevel and extraversion:
            break
except:
    pass
finally:
    if version_major and version_minor and patchlevel and extraversion is not None:
        version = release = version_major + '.' + version_minor + '.' + patchlevel
        if extraversion != '':
            version = release = version + '-' + extraversion
    else:
        sys.stderr.write('Warning: Could not extract kernel version\n')
        version = release = "unknown version"

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = None

# There are two options for replacing |today|: either, you set today to some
# non-false value, then it is used:
#today = ''
# Else, today_fmt is used as the format for a strftime call.
#today_fmt = '%B %d, %Y'

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
exclude_patterns = ['_build']
if not west_found:
    exclude_patterns.append('**/*west-apis*')
else:
    exclude_patterns.append('**/*west-not-found*')

# The reST default role (used for this markup: `text`) to use for all
# documents.

# This change will allow us to use bare back-tick notation to let
# Sphinx hunt for a reference, starting with normal "document"
# references such as :ref:, but also including :c: and :cpp: domains
# (potentially) helping with API (doxygen) references simply by using
# `name`

default_role = 'any'
# default_domain = 'cpp'

# If true, '()' will be appended to :func: etc. cross-reference text.
#add_function_parentheses = True

# If true, the current module name will be prepended to all description
# unit titles (such as .. function::).
#add_module_names = True

# If true, sectionauthor and moduleauthor directives will be shown in the
# output. They are ignored by default.
#show_authors = False

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = 'sphinx'

# Additional lexer for Pygments (syntax highlighting)
from lexer.DtsLexer import DtsLexer
from sphinx.highlighting import lexers
lexers['DTS'] = DtsLexer()

# A list of ignored prefixes for module index sorting.
#modindex_common_prefix = []

# If true, keep warnings as "system message" paragraphs in the built documents.
#keep_warnings = False

# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = False

rst_epilog = """
.. include:: /substitutions.txt
"""

# -- Options for HTML output ----------------------------------------------

import sphinx_rtd_theme
html_theme = "sphinx_rtd_theme"
html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

if tags.has('release'):
    is_release = True
    docs_title = 'Docs / %s' %(version)
else:
    is_release = False
    docs_title = 'Docs / Latest'

# The name for this set of Sphinx documents.  If None, it defaults to
# "<project> v<release> documentation".
html_title = "Zephyr Project Documentation"

# This value determines the text for the permalink; it defaults to "¶".
# Set it to None or the empty string to disable permalinks.
#html_add_permalinks = ""

# A shorter title for the navigation bar.  Default is the same as html_title.
#html_short_title = None

# The name of an image file (relative to this directory) to place at the top
# of the sidebar.
html_logo = 'images/Zephyr-Kite-logo.png'

# The name of an image file (within the static path) to use as favicon of the
# docs.  This file should be a Windows icon file (.ico) being 16x16 or 32x32
# pixels large.
html_favicon = 'images/zp_favicon.png'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['{}/doc/static'.format(ZEPHYR_BASE)]

# Add any extra paths that contain custom files (such as robots.txt or
# .htaccess) here, relative to this directory. These files are copied
# directly to the root of the documentation.
#html_extra_path = []

# If not '', a 'Last updated on:' timestamp is inserted at every page bottom,
# using the given strftime format.
html_last_updated_fmt = '%b %d, %Y'

# If true, SmartyPants will be used to convert quotes and dashes to
# typographically correct entities.
#html_use_smartypants =

# Custom sidebar templates, maps document names to template names.
#html_sidebars = {}

# Additional templates that should be rendered to pages, maps page names to
# template names.
#html_additional_pages = {}

# If false, no module index is generated.
html_domain_indices = False

# If false, no index is generated.
html_use_index = True

# If true, the index is split into individual pages for each letter.
html_split_index = True

# If true, links to the reST sources are added to the pages.
html_show_sourcelink = False

# If true, "Created using Sphinx" is shown in the HTML footer. Default is True.
html_show_sphinx = False

# If true, "(C) Copyright ..." is shown in the HTML footer. Default is True.
# html_show_copyright = tags.has('development')

# If true, license is shown in the HTML footer. Default is True.
html_show_license = True

# If true, an OpenSearch description file will be output, and all pages will
# contain a <link> tag referring to it.  The value of this option must be the
# base URL from which the finished HTML is served.
#html_use_opensearch = ''

# This is the file name suffix for HTML files (e.g. ".xhtml").
#html_file_suffix = None

# Language to be used for generating the HTML full-text search index.
# Sphinx supports the following languages:
#   'da', 'de', 'en', 'es', 'fi', 'fr', 'hu', 'it', 'ja'
#   'nl', 'no', 'pt', 'ro', 'ru', 'sv', 'tr'
#html_search_language = 'en'

sourcelink_suffix = '.txt'

# A dictionary with options for the search language support, empty by default.
# Now only 'ja' uses this config value
#html_search_options = {'type': 'default'}

# The name of a javascript file (relative to the configuration directory) that
# implements a search results scorer. If empty, the default will be used.
#html_search_scorer = 'scorer.js'

# Output file base name for HTML help builder.
htmlhelp_basename = 'zephyrdoc'


# Custom added feature to allow redirecting old URLs
#
# list of tuples (old_url, new_url) for pages to redirect
# (URLs should be relative to document root, only)
html_redirect_pages = [
        ('contribute/contribute_guidelines', 'contribute/index'),
        ('application/application', 'application/index.rst'),
        ('security/security', 'security/index'),
        ('boards/boards', 'boards/index'),
        ('samples/samples', 'samples/index'),
        ('releases/release-notes', 'releases/index'),
        ('getting_started/getting_starting', 'getting_started/index'),
        ('introduction/introducing_zephyr', 'introduction/index'),
        ('api/index', 'reference/index'),
        ('api/api', 'reference/index'),
        ('subsystems/subsystems', 'reference/index'),
        ('kernel/kernel', 'reference/kernel/index'),
		('boards/arc/arduino_101_sss/doc/board.html', 'boards/arc/arduino_101_sss/doc/index.html'),
		('boards/arc/em_starterkit/doc/board.html', 'boards/arc/em_starterkit/doc/index.html'),
		('boards/arc/nsim_em/doc/board.html', 'boards/arc/nsim_em/doc/index.html'),
		('boards/arm/96b_argonkey/doc/96b_argonkey.html', 'boards/arm/96b_argonkey/doc/index.html'),
		('boards/arm/96b_carbon/doc/96b_carbon.html', 'boards/arm/96b_carbon/doc/index.html'),
		('boards/arm/96b_carbon_nrf51/doc/96b_carbon_nrf51.html', 'boards/arm/96b_carbon_nrf51/doc/index.html'),
		('boards/arm/96b_neonkey/doc/96b_neonkey.html', 'boards/arm/96b_neonkey/doc/index.html'),
		('boards/arm/96b_nitrogen/doc/96b_nitrogen.html', 'boards/arm/96b_nitrogen/doc/index.html'),
		('boards/arm/adafruit_feather_m0_basic_proto/doc/adafruit_feather_m0_basic_proto.html', 'boards/arm/adafruit_feather_m0_basic_proto/doc/index.html'),
		('boards/arm/adafruit_trinket_m0/doc/adafruit_trinket_m0.html', 'boards/arm/adafruit_trinket_m0/doc/index.html'),
		('boards/arm/arduino_due/doc/board.html', 'boards/arm/arduino_due/doc/index.html'),
		('boards/arm/arduino_zero/doc/arduino_zero.html', 'boards/arm/arduino_zero/doc/index.html'),
		('boards/arm/atsamd20_xpro/doc/atsamd20_xpro.html', 'boards/arm/atsamd20_xpro/doc/index.html'),
		('boards/arm/bbc_microbit/doc/board.html', 'boards/arm/bbc_microbit/doc/index.html'),
		('boards/arm/cc2650_sensortag/doc/cc2650_sensortag.html', 'boards/arm/cc2650_sensortag/doc/index.html'),
		('boards/arm/cc3220sf_launchxl/doc/cc3220sf_launchxl.html', 'boards/arm/cc3220sf_launchxl/doc/index.html'),
		('boards/arm/colibri_imx7d_m4/doc/colibri_imx7d_m4.html', 'boards/arm/colibri_imx7d_m4/doc/index.html'),
		('boards/arm/curie_ble/doc/board.html', 'boards/arm/curie_ble/doc/index.html'),
		('boards/arm/disco_l475_iot1/doc/disco_l475_iot1.html', 'boards/arm/disco_l475_iot1/doc/index.html'),
		('boards/arm/dragino_lsn50/doc/dragino_lsn50.html', 'boards/arm/dragino_lsn50/doc/index.html'),
		('boards/arm/efm32wg_stk3800/doc/efm32wg_stk3800.html', 'boards/arm/efm32wg_stk3800/doc/index.html'),
		('boards/arm/efr32_slwstk6061a/doc/efr32_slwstk6061a.html', 'boards/arm/efr32_slwstk6061a/doc/index.html'),
		('boards/arm/frdm_k64f/doc/frdm_k64f.html', 'boards/arm/frdm_k64f/doc/index.html'),
		('boards/arm/frdm_kl25z/doc/frdm_kl25z.html', 'boards/arm/frdm_kl25z/doc/index.html'),
		('boards/arm/frdm_kw41z/doc/frdm_kw41z.html', 'boards/arm/frdm_kw41z/doc/index.html'),
		('boards/arm/hexiwear_k64/doc/hexiwear_k64.html', 'boards/arm/hexiwear_k64/doc/index.html'),
		('boards/arm/hexiwear_kw40z/doc/hexiwear_kw40z.html', 'boards/arm/hexiwear_kw40z/doc/index.html'),
		('boards/arm/lpcxpresso54114_m0/doc/lpcxpresso54114_m0.html', 'boards/arm/lpcxpresso54114_m0/doc/index.html'),
		('boards/arm/lpcxpresso54114_m4/doc/lpcxpresso54114.html', 'boards/arm/lpcxpresso54114_m4/doc/index.html'),
		('boards/arm/mimxrt1050_evk/doc/mimxrt1050_evk.html', 'boards/arm/mimxrt1050_evk/doc/index.html'),
		('boards/arm/mps2_an385/doc/mps2_an385.html', 'boards/arm/mps2_an385/doc/index.html'),
		('boards/arm/msp_exp432p401r_launchxl/doc/msp_exp432p401r_launchxl.html', 'boards/arm/msp_exp432p401r_launchxl/doc/index.html'),
		('boards/arm/nrf51_ble400/doc/nrf51_ble400.html', 'boards/arm/nrf51_ble400/doc/index.html'),
		('boards/arm/nrf51_blenano/doc/nrf51_blenano.html', 'boards/arm/nrf51_blenano/doc/index.html'),
		('boards/arm/nrf51_pca10028/doc/nrf51_pca10028.html', 'boards/arm/nrf51_pca10028/doc/index.html'),
		('boards/arm/nrf51_vbluno51/doc/nrf51_vbluno51.html', 'boards/arm/nrf51_vbluno51/doc/index.html'),
		('boards/arm/nrf52810_pca10040/doc/nrf52810_pca10040.html', 'boards/arm/nrf52810_pca10040/doc/index.html'),
		('boards/arm/nrf52840_pca10056/doc/nrf52840_pca10056.html', 'boards/arm/nrf52840_pca10056/doc/index.html'),
		('boards/arm/nrf52840_pca10059/doc/nrf52840_pca10059.html', 'boards/arm/nrf52840_pca10059/doc/index.html'),
		('boards/arm/nrf52_adafruit_feather/doc/nrf52_adafruit_feather.html', 'boards/arm/nrf52_adafruit_feather/doc/index.html'),
		('boards/arm/nrf52_blenano2/doc/nrf52_blenano2.html', 'boards/arm/nrf52_blenano2/doc/index.html'),
		('boards/arm/nrf52_pca10040/doc/nrf52_pca10040.html', 'boards/arm/nrf52_pca10040/doc/index.html'),
		('boards/arm/nrf52_pca20020/doc/nrf52_pca20020.html', 'boards/arm/nrf52_pca20020/doc/index.html'),
		('boards/arm/nrf52_vbluno52/doc/nrf52_vbluno52.html', 'boards/arm/nrf52_vbluno52/doc/index.html'),
		('boards/arm/nucleo_f030r8/doc/nucleof030r8.html', 'boards/arm/nucleo_f030r8/doc/index.html'),
		('boards/arm/nucleo_f070rb/doc/nucleof070rb.html', 'boards/arm/nucleo_f070rb/doc/index.html'),
		('boards/arm/nucleo_f091rc/doc/nucleof091rc.html', 'boards/arm/nucleo_f091rc/doc/index.html'),
		('boards/arm/nucleo_f103rb/doc/nucleof103rb.html', 'boards/arm/nucleo_f103rb/doc/index.html'),
		('boards/arm/nucleo_f207zg/doc/nucleo_f207zg.html', 'boards/arm/nucleo_f207zg/doc/index.html'),
		('boards/arm/nucleo_f334r8/doc/nucleof334r8.html', 'boards/arm/nucleo_f334r8/doc/index.html'),
		('boards/arm/nucleo_f401re/doc/nucleof401re.html', 'boards/arm/nucleo_f401re/doc/index.html'),
		('boards/arm/nucleo_f411re/doc/nucleof411re.html', 'boards/arm/nucleo_f411re/doc/index.html'),
		('boards/arm/nucleo_f412zg/doc/nucleof412zg.html', 'boards/arm/nucleo_f412zg/doc/index.html'),
		('boards/arm/nucleo_f413zh/doc/nucleof413zh.html', 'boards/arm/nucleo_f413zh/doc/index.html'),
		('boards/arm/nucleo_f429zi/doc/nucleof429zi.html', 'boards/arm/nucleo_f429zi/doc/index.html'),
		('boards/arm/nucleo_f446re/doc/nucleof446re.html', 'boards/arm/nucleo_f446re/doc/index.html'),
		('boards/arm/nucleo_l053r8/doc/nucleol053r8.html', 'boards/arm/nucleo_l053r8/doc/index.html'),
		('boards/arm/nucleo_l073rz/doc/nucleol073rz.html', 'boards/arm/nucleo_l073rz/doc/index.html'),
		('boards/arm/nucleo_l432kc/doc/nucleol432kc.html', 'boards/arm/nucleo_l432kc/doc/index.html'),
		('boards/arm/nucleo_l476rg/doc/nucleol476rg.html', 'boards/arm/nucleo_l476rg/doc/index.html'),
		('boards/arm/olimex_stm32_e407/doc/olimex_stm32_e407.html', 'boards/arm/olimex_stm32_e407/doc/index.html'),
		('boards/arm/olimex_stm32_h407/doc/olimex_stm32_h407.html', 'boards/arm/olimex_stm32_h407/doc/index.html'),
		('boards/arm/olimex_stm32_p405/doc/olimex_stm32_p405.html', 'boards/arm/olimex_stm32_p405/doc/index.html'),
		('boards/arm/olimexino_stm32/doc/olimexino_stm32.html', 'boards/arm/olimexino_stm32/doc/index.html'),
		('boards/arm/qemu_cortex_m3/doc/board.html', 'boards/arm/qemu_cortex_m3/doc/index.html'),
		('boards/arm/reel_board/doc/reel_board.html', 'boards/arm/reel_board/doc/index.html'),
		('boards/arm/sam4s_xplained/doc/sam4s_xplained.html', 'boards/arm/sam4s_xplained/doc/index.html'),
		('boards/arm/sam_e70_xplained/doc/sam_e70_xplained.html', 'boards/arm/sam_e70_xplained/doc/index.html'),
		('boards/arm/stm3210c_eval/doc/stm3210c_eval.html', 'boards/arm/stm3210c_eval/doc/index.html'),
		('boards/arm/stm32373c_eval/doc/stm32373c_eval.html', 'boards/arm/stm32373c_eval/doc/index.html'),
		('boards/arm/stm32_min_dev/doc/stm32_min_dev.html', 'boards/arm/stm32_min_dev/doc/index.html'),
		('boards/arm/stm32f072_eval/doc/stm32f072_eval.html', 'boards/arm/stm32f072_eval/doc/index.html'),
		('boards/arm/stm32f072b_disco/doc/stm32f072b_disco.html', 'boards/arm/stm32f072b_disco/doc/index.html'),
		('boards/arm/stm32f0_disco/doc/stm32f0_disco.html', 'boards/arm/stm32f0_disco/doc/index.html'),
		('boards/arm/stm32f3_disco/doc/stm32f3_disco.html', 'boards/arm/stm32f3_disco/doc/index.html'),
		('boards/arm/stm32f411e_disco/doc/stm32f411e_disco.html', 'boards/arm/stm32f411e_disco/doc/index.html'),
		('boards/arm/stm32f412g_disco/doc/stm32f412g_disco.html', 'boards/arm/stm32f412g_disco/doc/index.html'),
		('boards/arm/stm32f429i_disc1/doc/stm32f429i_disc1.html', 'boards/arm/stm32f429i_disc1/doc/index.html'),
		('boards/arm/stm32f469i_disco/doc/stm32f469i_disco.html', 'boards/arm/stm32f469i_disco/doc/index.html'),
		('boards/arm/stm32f4_disco/doc/stm32f4_disco.html', 'boards/arm/stm32f4_disco/doc/index.html'),
		('boards/arm/stm32f723e_disco/doc/stm32f723e_disco.html', 'boards/arm/stm32f723e_disco/doc/index.html'),
		('boards/arm/stm32f746g_disco/doc/stm32f746g_disco.html', 'boards/arm/stm32f746g_disco/doc/index.html'),
		('boards/arm/stm32f769i_disco/doc/stm32f769i_disco.html', 'boards/arm/stm32f769i_disco/doc/index.html'),
		('boards/arm/stm32l476g_disco/doc/stm32l476g_disco.html', 'boards/arm/stm32l476g_disco/doc/index.html'),
		('boards/arm/stm32l496g_disco/doc/stm32l496g_disco.html', 'boards/arm/stm32l496g_disco/doc/index.html'),
		('boards/arm/udoo_neo_full_m4/doc/udoo_neo_full.html', 'boards/arm/udoo_neo_full_m4/doc/index.html'),
		('boards/arm/usb_kw24d512/doc/usb_kw24d512.html', 'boards/arm/usb_kw24d512/doc/index.html'),
		('boards/arm/v2m_beetle/doc/v2m_beetle.html', 'boards/arm/v2m_beetle/doc/index.html'),
		('boards/arm/warp7_m4/doc/warp7_m4.html', 'boards/arm/warp7_m4/doc/index.html'),
		('boards/nios2/altera_max10/doc/board.html', 'boards/nios2/altera_max10/doc/index.html'),
		('boards/nios2/qemu_nios2/doc/board.html', 'boards/nios2/qemu_nios2/doc/index.html'),
		('boards/posix/native_posix/doc/board.html', 'boards/posix/native_posix/doc/index.html'),
		('boards/riscv32/hifive1/doc/hifive1.html', 'boards/riscv32/hifive1/doc/index.html'),
		('boards/riscv32/m2gl025_miv/doc/m2g1025_miv.html', 'boards/riscv32/m2gl025_miv/doc/index.html'),
		('boards/riscv32/qemu_riscv32/doc/board.html', 'boards/riscv32/qemu_riscv32/doc/index.html'),
		('boards/riscv32/zedboard_pulpino/doc/zedboard_pulpino.html', 'boards/riscv32/zedboard_pulpino/doc/index.html'),
		('boards/x86/arduino_101/doc/board.html', 'boards/x86/arduino_101/doc/index.html'),
		('boards/x86/galileo/doc/galileo.html', 'boards/x86/galileo/doc/index.html'),
		('boards/x86/minnowboard/doc/minnowboard.html', 'boards/x86/minnowboard/doc/index.html'),
		('boards/x86/qemu_x86/doc/board.html', 'boards/x86/qemu_x86/doc/index.html'),
		('boards/x86/quark_d2000_crb/doc/quark_d2000_crb.html', 'boards/x86/quark_d2000_crb/doc/index.html'),
		('boards/x86/tinytile/doc/board.html', 'boards/x86/tinytile/doc/index.html'),
		('boards/x86/up_squared/doc/up_squared.html', 'boards/x86/up_squared/doc/index.html'),
		('boards/x86/x86_jailhouse/doc/board.html', 'boards/x86/x86_jailhouse/doc/index.html'),
		('boards/xtensa/esp32/doc/esp32.html', 'boards/xtensa/esp32/doc/index.html'),
		('boards/xtensa/intel_s1000_crb/doc/intel_s1000.html', 'boards/xtensa/intel_s1000_crb/doc/index.html'),
		('boards/xtensa/qemu_xtensa/doc/board.html', 'boards/xtensa/qemu_xtensa/doc/index.html'),
		('boards/xtensa/xt-sim/doc/xt-sim.html', 'boards/xtensa/xt-sim/doc/index.html'),
        ]

# -- Options for LaTeX output ---------------------------------------------

latex_elements = {
# The paper size ('letterpaper' or 'a4paper').
#'papersize': 'letterpaper',

# The font size ('10pt', '11pt' or '12pt').
#'pointsize': '10pt',

# Additional stuff for the LaTeX preamble.
'preamble': r'\setcounter{tocdepth}{2}',

# Latex figure (float) alignment
#'figure_align': 'htbp',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
  (master_doc, 'zephyr.tex', u'Zephyr Project Documentation',
   u'many', 'manual'),
]

# The name of an image file (relative to this directory) to place at the top of
# the title page.
#latex_logo = None

# For "manual" documents, if this is true, then toplevel headings are parts,
# not chapters.
#latex_use_parts = False

# If true, show page references after internal links.
#latex_show_pagerefs = False

# If true, show URL addresses after external links.
#latex_show_urls = False

# Documents to append as an appendix to all manuals.
#latex_appendices = []

# If false, no module index is generated.
#latex_domain_indices = True

# -- Options for manual page output ---------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    (master_doc, 'zephyr', u'Zephyr Project Documentation',
     [author], 1)
]

# If true, show URL addresses after external links.
#man_show_urls = False


# -- Options for Texinfo output -------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
  (master_doc, 'zephyr', u'Zephyr Project Documentation',
   author, 'Zephyr', 'One line description of project.',
   'Miscellaneous'),
]

# Documents to append as an appendix to all manuals.
#texinfo_appendices = []

# If false, no module index is generated.
#texinfo_domain_indices = True

# How to display URL addresses: 'footnote', 'no', or 'inline'.
#texinfo_show_urls = 'footnote'

# If true, do not generate a @detailmenu in the "Top" node's menu.
#texinfo_no_detailmenu = False

breathe_projects = {
    "Zephyr": "{}/doxygen/xml".format(ZEPHYR_BUILD),
    "doc-examples": "{}/doxygen/xml".format(ZEPHYR_BUILD)
}
breathe_default_project = "Zephyr"

# Changing breathe configuration to force "c" domain doesn't work
# see https://github.com/michaeljones/breathe/issues/282
#breathe_domain_by_extension = {
#    "h" : "c",
#    "c" : "c",
#    }

# Qualifiers to a function are causing Sphihx/Breathe to warn about
# Error when parsing function declaration and more.  This is a list
# of strings that the parser additionally should accept as
# attributes.
cpp_id_attributes = ['__syscall', '__syscall_inline', '__deprecated',
    '__may_alias', '__used', '__unused', '__weak',
    '__DEPRECATED_MACRO', 'FUNC_NORETURN']

# docs_title is used in the breadcrumb title in the zephyr docs theme
html_context = {
    'show_license': html_show_license,
    'docs_title': docs_title,
    'is_release': is_release,
    'theme_logo_only': False,
    'current_version': version,
    'versions': ( ("latest", "/"),
                 ("1.14.0", "/1.14.0/"),
                 ("1.13.0", "/1.13.0/"),
                 ("1.12.0", "/1.12.0/"),
                 ("1.11.0", "/1.11.0/"),
                 ("1.10.0", "/1.10.0/"),
                )
}


extlinks = {'jira': ('https://jira.zephyrproject.org/browse/%s', ''),
            'github': ('https://github.com/zephyrproject-rtos/zephyr/issues/%s', '')
           }

# some configuration for linkcheck builder
#   noticed that we're getting false-positive link errors on JIRA, I suspect
#   because it's taking too long for the server to respond so bump up the
#   timeout (default=5) and turn off anchor checks (so only a HEAD request is
#   done - much faster) Leave the ignore commented in case we want to remove
#   jira link checks later...

linkcheck_timeout = 30
linkcheck_workers = 10
# linkcheck_ignore = [r'https://jira\.zephyrproject\.org/']
linkcheck_anchors = False

def setup(app):
    app.add_stylesheet("zephyr-custom.css")
    app.add_javascript("zephyr-custom.js")

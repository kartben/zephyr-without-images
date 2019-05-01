# Copyright (c) 2018 Foundries.io
#
# SPDX-License-Identifier: Apache-2.0

import argparse
import os

from west import log
from west.configuration import config
from zcmake import DEFAULT_CMAKE_GENERATOR, run_cmake, run_build, CMakeCache
from build_helpers import is_zephyr_build, find_build_dir, \
    BUILD_DIR_DESCRIPTION

from zephyr_ext_common import Forceable

_ARG_SEPARATOR = '--'

BUILD_USAGE = '''\
west build [-h] [-b BOARD] [-d BUILD_DIR]
           [-t TARGET] [-p {auto, always, never}] [-c] [--cmake-only]
           [-f] [source_dir] -- [cmake_opt [cmake_opt ...]]
'''

BUILD_DESCRIPTION = '''\
Convenience wrapper for building Zephyr applications.

This command attempts to do what you mean when run from a Zephyr
application source or a pre-existing build directory:

- When the build directory ('./build' by default, see below) exists and is
  already a Zephyr build directory, the source directory is obtained from the
  CMake cache, and that build directory is re-compiled.

- Otherwise, the source directory defaults to the current working
  directory, so running "west build" from a Zephyr application's
  source directory compiles it.

The source and build directories can be explicitly set with the
--source-dir and --build-dir options. The build directory defaults to
'build' if it is not auto-detected. The build directory is always
created if it does not exist.

The board to build for is taken from the CACHED_BOARD CMake cache
variable, --board option, BOARD environment variable, or build.board
configuration option, in decreasing order of precedence.

This command runs CMake to generate a build system if one is not
present in the build directory, then builds the application.
Subsequent builds try to avoid re-running CMake; you can force it
to run by setting --cmake.

To pass additional options to CMake, give them as extra arguments
after a '--'. For example, this sets an overlay config file:

west build [...] -- -DOVERLAY_CONFIG=some.conf

(Doing this forces a CMake run.)

positional arguments:
  source_dir            Explicitly set the source directory. If not given and
                        rebuilding an existing Zephyr build directory, this is
                        taken from the CMake cache. Otherwise, the current
                        directory is assumed.
  cmake_opt             Extra options to pass to CMake; implies -c
'''

def config_get(option, fallback):
    return config.get('build', option, fallback=fallback)

def config_getboolean(option, fallback):
    return config.getboolean('build', option, fallback=fallback)

class AlwaysIfMissing(argparse.Action):

    def __call__(self, parser, namespace, values, option_string=None):
        setattr(namespace, self.dest, values or 'always')

class Build(Forceable):

    def __init__(self):
        super(Build, self).__init__(
            'build',
            # Keep this in sync with the string in west-commands.yml.
            'compile a Zephyr application',
            BUILD_DESCRIPTION,
            accepts_unknown_args=True)

        self.source_dir = None
        '''Source directory for the build, or None on error.'''

        self.build_dir = None
        '''Final build directory used to run the build, or None on error.'''

        self.created_build_dir = False
        '''True if the build directory was created; False otherwise.'''

        self.run_cmake = False
        '''True if CMake was run; False otherwise.

        Note: this only describes CMake runs done by this command. The
        build system generated by CMake may also update itself due to
        internal logic.'''

        self.cmake_cache = None
        '''Final parsed CMake cache for the build, or None on error.'''

    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(
            self.name,
            help=self.help,
            formatter_class=argparse.RawDescriptionHelpFormatter,
            description=self.description,
            usage=BUILD_USAGE)

        # Remember to update scripts/west-completion.bash if you add or remove
        # flags

        parser.add_argument('-b', '--board', help='Board to build for')
        # Hidden option for backwards compatibility
        parser.add_argument('-s', '--source-dir', help=argparse.SUPPRESS)
        parser.add_argument('-d', '--build-dir',
                            help=BUILD_DIR_DESCRIPTION +
                            "The directory is created if it doesn't exist.")
        parser.add_argument('-t', '--target',
                            help='''Override the build system target (e.g.
                            'clean', 'pristine', etc.)''')
        parser.add_argument('-p', '--pristine', choices=['auto', 'always',
                            'never'], action=AlwaysIfMissing, nargs='?',
                            help='''Control whether the build folder is made
                            pristine before building if a build system is
                            present in the build dir. --pristine is the same as
                            --pristine=always. If set to auto, the build folder
                            will be made pristine only if required based on the
                            existing build system and the options provided.
                            This allows for reusing a build folder even if it
                            contains build files for a different board or
                            application.''')
        parser.add_argument('-c', '--cmake', action='store_true',
                            help='Force CMake to run')
        parser.add_argument('--cmake-only', action='store_true',
                            help="Just run CMake; don't build. Implies -c.")
        self.add_force_arg(parser)
        return parser

    def do_run(self, args, remainder):
        self.args = args        # Avoid having to pass them around
        log.dbg('args: {} remainder: {}'.format(args, remainder,
                                                level=log.VERBOSE_EXTREME))
        # Store legacy -s option locally
        source_dir = self.args.source_dir
        self._parse_remainder(remainder)
        if source_dir:
            if self.args.source_dir:
                log.die("source directory specified twice:({} and {})".format(
                                            source_dir, self.args.source_dir))
            self.args.source_dir = source_dir
        log.dbg('source_dir: {} cmake_opts: {}'.format(self.args.source_dir,
                                                       self.args.cmake_opts))
        self._sanity_precheck()
        self._setup_build_dir()

        if args.pristine is not None:
            pristine = args.pristine
        else:
            # Load the pristine={auto, always, never} configuration value
            pristine = config_get('pristine', 'never')
            if pristine not in ['auto', 'always', 'never']:
                log.wrn(
                    'treating unknown build.pristine value "{}" as "never"'.
                    format(pristine))
                pristine = 'never'
        self.auto_pristine = (pristine == 'auto')

        log.dbg('pristine: {} auto_pristine: {}'.format(pristine,
                                                        self.auto_pristine))
        if is_zephyr_build(self.build_dir):
            if pristine == 'always':
                self._run_pristine()
                self.run_cmake = True
            else:
                self._update_cache()
                if (self.args.cmake or self.args.cmake_opts or
                        self.args.cmake_only):
                    self.run_cmake = True
        else:
            self.run_cmake = True
        self._setup_source_dir()
        self._sanity_check()

        board, origin = self._find_board()
        self._run_cmake(board, origin, self.args.cmake_opts)
        if args.cmake_only:
            return

        self._sanity_check()
        self._update_cache()

        self._run_build(args.target)

    def _find_board(self):
        board, origin = None, None
        config_board = config_get('board', None)
        if self.cmake_cache:
            board, origin = (self.cmake_cache.get('CACHED_BOARD'),
                             'CMakeCache.txt')
        elif self.args.board:
            board, origin = self.args.board, 'command line'
        elif 'BOARD' in os.environ:
            board, origin = os.environ['BOARD'], 'env'
        elif config_board is not None:
            board, origin = config_board, 'configfile'
        return board, origin

    def _parse_remainder(self, remainder):
        self.args.source_dir = None
        self.args.cmake_opts = None
        try:
            # Only one source_dir is allowed, as the first positional arg
            if remainder[0] != _ARG_SEPARATOR:
                self.args.source_dir = remainder[0]
                remainder = remainder[1:]
            # Only the first argument separator is consumed, the rest are
            # passed on to CMake
            if remainder[0] == _ARG_SEPARATOR:
                remainder = remainder[1:]
            if len(remainder):
                self.args.cmake_opts = remainder
        except IndexError:
            return

    def _sanity_precheck(self):
        app = self.args.source_dir
        if app:
            self.check_force(
                os.path.isdir(app),
                'source directory {} does not exist'.format(app))
            self.check_force(
                'CMakeLists.txt' in os.listdir(app),
                "{} doesn't contain a CMakeLists.txt".format(app))

    def _update_cache(self):
        try:
            self.cmake_cache = CMakeCache.from_build_dir(self.build_dir)
        except FileNotFoundError:
            pass

    def _setup_build_dir(self):
        # Initialize build_dir and created_build_dir attributes.
        # If we created the build directory, we must run CMake.
        log.dbg('setting up build directory', level=log.VERBOSE_EXTREME)
        build_dir = find_build_dir(self.args.build_dir)

        if os.path.exists(build_dir):
            if not os.path.isdir(build_dir):
                log.die('build directory {} exists and is not a directory'.
                        format(build_dir))
        else:
            os.makedirs(build_dir, exist_ok=False)
            self.created_build_dir = True
            self.run_cmake = True

        self.build_dir = build_dir

    def _setup_source_dir(self):
        # Initialize source_dir attribute, either from command line argument,
        # implicitly from the build directory's CMake cache, or using the
        # default (current working directory).
        log.dbg('setting up source directory', level=log.VERBOSE_EXTREME)
        if self.args.source_dir:
            source_dir = self.args.source_dir
        elif self.cmake_cache:
            source_dir = self.cmake_cache.get('CMAKE_HOME_DIRECTORY')
            if not source_dir:
                # This really ought to be there. The build directory
                # must be corrupted somehow. Let's see what we can do.
                log.die('build directory', self.build_dir,
                        'CMake cache has no CMAKE_HOME_DIRECTORY;',
                        'please give a source_dir')
        else:
            source_dir = os.getcwd()
        self.source_dir = os.path.abspath(source_dir)

    def _sanity_check_source_dir(self):
        if self.source_dir == self.build_dir:
            # There's no forcing this.
            log.die('source and build directory {} cannot be the same; '
                    'use --build-dir {} to specify a build directory'.
                    format(self.source_dir, self.build_dir))

        srcrel = os.path.relpath(self.source_dir)
        self.check_force(
            not is_zephyr_build(self.source_dir),
            'it looks like {srcrel} is a build directory: '
            'did you mean --build-dir {srcrel} instead?'.
            format(srcrel=srcrel))
        self.check_force(
            'CMakeLists.txt' in os.listdir(self.source_dir),
            'source directory "{srcrel}" does not contain '
            'a CMakeLists.txt; is this really what you '
            'want to build? (Use -s SOURCE_DIR to specify '
            'the application source directory)'.
            format(srcrel=srcrel))

    def _sanity_check(self):
        # Sanity check the build configuration.
        # Side effect: may update cmake_cache attribute.
        log.dbg('sanity checking the build', level=log.VERBOSE_EXTREME)
        self._sanity_check_source_dir()

        if not self.cmake_cache:
            return          # That's all we can check without a cache.

        cached_app = self.cmake_cache.get('APPLICATION_SOURCE_DIR')
        log.dbg('APPLICATION_SOURCE_DIR:', cached_app,
                level=log.VERBOSE_EXTREME)
        source_abs = (os.path.abspath(self.args.source_dir)
                      if self.args.source_dir else None)
        cached_abs = os.path.abspath(cached_app) if cached_app else None

        log.dbg('pristine:', self.auto_pristine, level=log.VERBOSE_EXTREME)
        # If the build directory specifies a source app, make sure it's
        # consistent with --source-dir.
        apps_mismatched = (source_abs and cached_abs and
                           source_abs != cached_abs)
        self.check_force(
            not apps_mismatched or self.auto_pristine,
            'Build directory "{}" is for application "{}", but source '
            'directory "{}" was specified; please clean it, use --pristine, '
            'or use --build-dir to set another build directory'.
            format(self.build_dir, cached_abs, source_abs))
        if apps_mismatched:
            self.run_cmake = True  # If they insist, we need to re-run cmake.

        # If CACHED_BOARD is not defined, we need --board from the
        # command line.
        cached_board = self.cmake_cache.get('CACHED_BOARD')
        log.dbg('CACHED_BOARD:', cached_board, level=log.VERBOSE_EXTREME)
        # If app_mismatched and pristine are true we will run pristine on the
        # build, invalidating the cached board. Whenever we run pristine we
        # require the user to provide all the require inputs again.
        self.check_force((cached_board and
                          not (apps_mismatched and self.auto_pristine))
                         or self.args.board,
                         'Cached board not defined, please provide --board')

        # Check consistency between cached board and --board.
        boards_mismatched = (self.args.board and cached_board and
                             self.args.board != cached_board)
        self.check_force(
            not boards_mismatched or self.auto_pristine,
            'Build directory {} targets board {}, but board {} was specified. '
            '(Clean the directory, use --pristine, or use --build-dir to '
            'specify a different one.)'.
            format(self.build_dir, cached_board, self.args.board))

        if self.auto_pristine and (apps_mismatched or boards_mismatched):
            self._run_pristine()
            self.cmake_cache = None
            log.dbg('run_cmake:', True, level=log.VERBOSE_EXTREME)
            self.run_cmake = True

            # Tricky corner-case: The user has not specified a build folder but
            # there was one in the CMake cache. Since this is going to be
            # invalidated, reset to CWD and re-run the basic tests.
            if ((boards_mismatched and not apps_mismatched) and
                    (not source_abs and cached_abs)):
                self._setup_source_dir()
                self._sanity_check_source_dir()

    def _run_cmake(self, board, origin, cmake_opts):
        log.inf('source directory: {}'.format(self.source_dir), colorize=True)
        log.inf('build directory: {}{}'.
                format(self.build_dir,
                       ' (created)' if self.created_build_dir else ''),
                colorize=True)
        log.inf('BOARD:', ('{} (origin: {})'.format(board, origin) if board
                           else 'UNKNOWN'),
                colorize=True)

        if board is None and config_getboolean('board_warn', True):
            log.wrn('This looks like a fresh build and BOARD is unknown;',
                    "so it probably won't work. To fix, use",
                    '--board=<your-board>.')
            log.inf('Note: to silence the above message, run',
                    "'west config build.board_warn false'")

        if not self.run_cmake:
            log.dbg('not running cmake; build system is present')
            return

        if board is not None and origin != 'CMakeCache.txt':
            cmake_opts = ['-DBOARD={}'.format(board)]
        else:
            cmake_opts = []
        if self.args.cmake_opts:
            cmake_opts.extend(self.args.cmake_opts)

        # Invoke CMake from the current working directory using the
        # -S and -B options (officially introduced in CMake 3.13.0).
        # This is important because users expect invocations like this
        # to Just Work:
        #
        # west build -- -DOVERLAY_CONFIG=relative-path.conf
        final_cmake_args = ['-B{}'.format(self.build_dir),
                            '-S{}'.format(self.source_dir),
                            '-G{}'.format(config_get('generator',
                                                     DEFAULT_CMAKE_GENERATOR))]
        if cmake_opts:
            final_cmake_args.extend(cmake_opts)
        run_cmake(final_cmake_args)

    def _run_pristine(self):
        log.inf('Making build dir {} pristine'.format(self.build_dir))

        zb = os.environ.get('ZEPHYR_BASE')
        if not zb:
            log.die('Internal error: ZEPHYR_BASE not set in the environment, '
                    'and should have been by the main script')

        if not is_zephyr_build(self.build_dir):
            log.die('Refusing to run pristine on a folder that is not a '
                    'Zephyr build system')

        cmake_args = ['-P', '{}/cmake/pristine.cmake'.format(zb)]
        run_cmake(cmake_args, cwd=self.build_dir)

    def _run_build(self, target):
        extra_args = ['--target', target] if target else []
        run_build(self.build_dir, extra_args=extra_args)

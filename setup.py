"""
Block `setup.py` file.

You can execute this file directly from the command line by passing commands
keywords to python like so: `python setup.py [command]`.
Useful commands you are probably interested about:
  - `build`: build the package.
  - `install`: install the package (not reliable).
  - `--version`: get block's current version.
To know about block's `setup.py` commands run `python setup.py --help`.

All Block distributions are under MIT license.
"""

import os
import sys
import logging
import subprocess
import textwrap
import warnings

import builtins

import setuptools
from Cython.Build import cythonize

logging.basicConfig( level=logging.DEBUG )
logger = logging.getLogger( 'SETUP' )

# Python supported version checks. Keep right after stdlib imports to ensure to
# get a sensible error for older Python versions.
if sys.version_info[:2] < (3, 7):
    raise RuntimeError( "Python version >= 3.7 required." )

# Get module location in the system.
DIR = os.path.dirname( os.path.abspath( __file__ ) )


def parse_commands( argv = sys.argv, force = '--force' in sys.argv ):
    """
    Check the commands and respond appropriately. Disable broken commands.
    Return a boolean indicating whether to run the build or not.
    To force unsupported commands pass `force=True`, by default check if `--force`
    is passed as parameter of `python setup.py`.

    Info Commands, Other Commands ––> False
    Supported Commands ––> True
    Help ––> Print help string
    Install ––> Print warning and True
    Unsupported Commands ––> Print help string and raise Error (if not `force` in sys.argv)
    """
    args = argv[1]

    if not args:
        # User forgot to give an argument probably, let setuptools handle that.
        return True

    # `setup.py` info commands.
    info_commands = ['--help-commands', '--name', '--version', '-V',
                     '--fullname', '--author', '--author-email',
                     '--maintainer', '--maintainer-email', '--contact',
                     '--contact-email', '--url', '--license', '--description',
                     '--long-description', '--platforms', '--classifiers',
                     '--keywords', '--provides', '--requires', '--obsoletes',
                     'version']

    # If an info command is passed then return `False`.
    for command in info_commands:
        if command == args:
            return False

    # Note that 'alias', 'saveopts' and 'setopt' commands also seem to work
    # fine as they are, but are usually used together with one of the commands
    # below and not standalone. Hence they're not added to `build_commands`.
    # Also, 'install' isn't added to `supported_commands` just because it is handled later.
    supported_commands = ['develop', 'sdist', 'build', 'build_ext', 'build_py',
                     'build_clib', 'build_scripts', 'bdist_wheel', 'bdist_rpm',
                     'bdist_wininst', 'bdist_msi', 'bdist_mpkg', 'build_src',
                     'bdist_egg']

    # If an build command is passed then return `True`.
    for command in supported_commands:
        if command == args:
            return True

    # The following commands are supported, but there is the needing to show more
    # useful messages to the user.

    if 'install' == args:
        print(textwrap.dedent("""
            Note: if you need reliable uninstall behavior, then install
            with pip instead of using `setup.py install`:
              - `pip install .`             (from a git repository or downloaded source release)
            """))
        return True

    if '--help' == args or '-h' == args:
        print(textwrap.dedent("""
            Block-specific help
            –––––––––––––––––––––––
            To install Block from here with reliable uninstall, it's recomended
            to use `pip install .`.
            If you are sure that you have run into a bug, please report it at
            "https://github.com/giuppox/block/issues".
            Setuptools commands help
            –––––––––––––––––––––––
            """))
        return False

    # The following commands aren't supported by block's `setup.py`. They can
    # only be executed when the user explicitly adds a --force command-line argument.
    unsupported_commands = dict(
        test="""
            `setup.py test` is not supported. Use one of the following
            instead:
              - `>>> import block as bk
                 >>> bk.test()`             (run test from within an interpreter)
            """,
        clean="""
            `setup.py clean` is not supported, use one of the following instead:
              - `git clean -xdf`            (cleans all files)
              - `git clean -Xdf`            (cleans all versioned files, doesn't touch
                                             files that aren't checked into the git
                                             repository)
            """,
        upload="""
            `setup.py upload` is not supported, because it's insecure.
            Instead, build what you want to upload and upload those files
            with `twine upload -s <filename>` instead.
            """
    )
    for command in ('upload_docs', 'easy_install', 'check', 'register',
                    'bdist_dumb', 'bdist', 'build_sphinx', 'flake8',
                    'nosetests', 'install_data', 'install_headers',
                    'install_lib', 'install_scripts'):
        unsupported_commands[command] = "\n`setup.py {}` is not supported\n".format( command )

    # If a command from `unsupported_commands` is passed then raise error.
    for command in unsupported_commands.keys():
        if command == args:
            if not force:
                print( textwrap.dedent( unsupported_commands[command] ) +
                    "\nAdd `--force` to your command to use it anyway if you "
                    "must (unsupported).\n" )
                sys.exit( -1 )
            else:
                return False

    # Commands that don't print info, but also don't need the module building.
    other_commands = ['egg_info', 'install_egg_info', 'rotate', 'dist_info']

    # If one command present in `other_commands` is passed then return `False`
    # (no need for module building).
    for command in other_commands:
        if command == args:
            return False

    # If the function hasn't recognized what `setup.py` command was given and `force==False`
    # then raise `RuntimeError`.
    if force:
        return False
    raise RuntimeError( "Unrecognized command: {}".format( args ) )


def setup():
    """ Run the Setup of the package. """
    # Get current working directory.
    old_path = os.getcwd()
    # Change working directory to `DIR`.
    os.chdir( DIR )
    sys.path.insert( 0, DIR )

    if parse_commands() and 'sdist' not in sys.argv:
        # Compile package unless the user wants to generate a 'sdist'.
        pass

    # Setup the package.
    setuptools.setup()

    del sys.path[0]
    os.chdir( old_path )
    return


if __name__ == '__main__':
    setup()

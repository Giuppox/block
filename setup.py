"""Block `setup.py` file.

You can execute this file directly from the command line by passing commands
keywords to python like so: `python setup.py [command]`.

Useful commands you are probably interested about:
  - `setup.py build`: build the package.
  - `setup.py install`: install the package (not reliable).
  - `setup.py --version`: get block's current version.

To know about block's `setup.py` commands run `python setup.py --help`.

All Block distributions are under MIT license.
"""

import os
import sys
import subprocess
import logging
import textwrap
import builtins

from setuptools import setup, Extension
from setuptools.config import read_configuration
from Cython.Build import cythonize


logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger('SETUP')


# Python supported version checks. Keep right after stdlib imports to ensure to
# get a sensible error for older Python versions.
if sys.version_info[:2] < (3, 7):
    raise RuntimeError("Python version >= 3.7 required.")


# Get module location in the system.
DIR = os.path.dirname(os.path.abspath(__file__))


# This is a bit hackish: Set a global variable so that the main block `__init__.py`
# can detect if it is being loaded by the setup routine, to avoid attempting
# to load components that aren't built yet.
builtins.__BLOCK_SETUP__ = True


def check_submodules():
    """Verify that the submodules are checked out and clean
    use `git submodule update --init`; on failure.

    Raises
    ------
    Raises `ValueError` if a submodule specified in `.gitmodules` doesn't
    exists, while raises `ValueError` if a submodule is not clean.
    """

    # Check whether the directory is a git repository or not.
    if not os.path.exists('.git'):
        return
    # Look for `.gitmodules` file to get submodules names.
    with open('.gitmodules') as f:
        for line in f:
            if 'path' in line:
                p = line.split('=')[-1].strip()
                # Check whether the sybnodyle exists or not.
                if not os.path.exists(p):
                    raise ValueError('Submodule {} missing'.format(p))

    proc = subprocess.Popen(['git', 'submodule', 'status'],
                            stdout=subprocess.PIPE)
    status, _ = proc.communicate()
    status = status.decode("ascii", "replace")
    for line in status.splitlines():
        if line.startswith('-') or line.startswith('+'):
            raise ValueError('Submodule not clean: {}'.format(line))


def parse_commands():
    """Check the commands and respond appropriately. Disable broken commands.

    Parse commands passed as command line arguments `python setup.py <command>`.
    For passed info commands (e.g. '--version', `--license`) don't run the build,
    the same for unsupported commands (e.g. `--clean`, '--bdist'), that are
    actually supported by setuptools, but that are considered not usefull to
    the package or unsecure.
    For supported commands the package should be builded (e.g. `build`, `develop`).

    Returns
    -------
    Return a boolean indicating whether to run the build or not.

    Raises
    ------
    Raises `RuntimeError` in the case the command-line-passed command is not
    recognized, while raises `SystemExit` if an unsupported command is found.
    """

    # Check for '--force' flag to know whether to run the setup in force mode or not.
    force = '--force' in sys.argv
    # Remove '--force' flag from `sys.argv`, so that setuptools doesn't throws
    # errors (unrecognised flag).
    if force:
        sys.argv.remove('--force')

    try:
        args = sys.argv[1:]
    except IndexError as e:
        # User probably forgot to pass an argument, let setuptools handle that.
        return False

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
        if command in args:
            return False

    # Note that 'alias', 'saveopts' and 'setopt' commands also seem to work
    # fine as they are, but are usually used together with one of the commands
    # below and not standalone. Hence they're not added to `build_commands`.
    # Also, 'install' isn't added to `supported_commands` just because it is handled later.
    supported_commands = ['develop', 'build', 'build_ext', 'build_py',
                          'build_clib', 'build_scripts', 'bdist_wheel', 'bdist_rpm',
                          'bdist_wininst', 'bdist_msi', 'bdist_mpkg', 'build_src',
                          'bdist_egg']

    # If an build command is passed then return `True`.
    for command in supported_commands:
        if command in args:
            return True

    # The following commands are supported, but there is the needing to show more
    # useful messages to the user.

    if 'install' in args:
        print(textwrap.dedent("""
            Note: if you need reliable uninstall behavior, then install
            with pip instead of using `setup.py install`:
              - `pip install .`             (from a git repository or downloaded source release)
            """))
        return True

    if '--help' in args or '-h' in args:
        print(textwrap.dedent("""
            Block-specific help
            –––––––––––––––––––––––
            To install Block from here with reliable uninstall, it's recomended
            to use `pip install .`.
            If you are sure that you have run into a bug, please report it at
            "https://github.com/giuppox/block/issues".

            Setuptools commands help
            ––––––––––––––––––––––––
            """))
        return False

    # The following commands aren't supported by block's `setup.py`. They can
    # only be executed when the user explicitly adds a --force command-line argument.
    unsupported_commands = dict(
        test="""
            `setup.py test` is not supported. Use one of the following
            instead:
              - ```python
                >>> import block as bk
                >>> bk.test()
                ```                         (run test from within an interpreter)
            """,
        clean="""
            `setup.py clean` is not supported, use one of the following instead:
              - `git clean -xdf`            (cleans all files)
              - `git clean -Xdf `           (cleans all versioned files, doesn't touch
                                             files that aren't checked into the git
                                             repository)
            """,
        upload="""
            `setup.py upload` is not supported, because it's insecure.
            Instead, build what you want to upload and upload those files
            with one of the following instead:
              - `twine upload -s <filename>` instead.
            """
    )
    for command in ('upload_docs', 'easy_install', 'check', 'register',
                    'bdist_dumb', 'bdist', 'build_sphinx', 'flake8',
                    'nosetests', 'install_data', 'install_headers',
                    'install_lib', 'install_scripts'):
        unsupported_commands[command] = "\n`setup.py {}` is not supported\n".format(command)

    # If a command from `unsupported_commands` is passed then raise error.
    for command in unsupported_commands.keys():
        if command in args:
            if not force:
                print(textwrap.dedent(unsupported_commands[command])
                    + "\nAdd `--force` to your command to use it anyway if you must (unsupported).\n"
                    )
                sys.exit(-1)
            else:
                return False

    # Commands that don't print info, but also don't need the module building.
    other_commands = ['egg_info', 'install_egg_info', 'rotate', 'dist_info', 'sdist']

    # If one command present in `other_commands` is passed then return `False`
    # (no need for module building).
    for command in other_commands:
        if command in args:
            return False

    # If the function hasn't recognized what `setup.py` command was given, raise `RuntimeError`.
    raise RuntimeError("Command `setup.py {}` is unrecognised".format(' '.join(args)))


def setup_package():
    """Run the Setup of the package."""

    # Get current working directory.
    old_path = os.getcwd()
    # Change working directory to `DIR`.
    os.chdir(DIR)
    sys.path.insert(0, DIR)

    # Check whether to run the build or not.
    run_build = parse_commands()

    if run_build:
        # If a the user wants to generate a sdist check for the consistency of
        # package's submodules.
        check_submodules()

    # Define extensions to compile.
    if run_build:
        extensions = cythonize([
            Extension('block.core.dtypes.dtypes', ['block/core/dtypes/dtypes.c'])
            ])
    else:
        extensions = None

    # Setup the package.
    setup(
        ext_modules=extensions
        )


    del sys.path[0]
    os.chdir(old_path)
    return


if __name__ == '__main__':
    setup_package()
    # This may avoid problems where block is installed via `*_requires` by
    # setuptools, the global namespace isn't reset properly, and then block is
    # imported later (which will then fail to load block extension modules).
    del builtins.__BLOCK_SETUP__

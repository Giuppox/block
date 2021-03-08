
import sys
import os
import shutil
from block_utils import (
    PATH as DIR, __version__ as VERSION, __name__ as NAME,
    __author__ as AUTHOR, __email__ as EMAIL, __description__ as DESCRIPTION,
    __license__ as LICENSE
)
import logging
from distutils.ccompiler import new_compiler
from distutils.core import setup, Extension

logging.basicConfig( level=logging.DEBUG )
LOGGER = logging.getLogger( 'SETUP' )

# Set platform constants.
PYVERSION = sys.version_info
PLATFORM = sys.platform
SUPPORTED_PLATFORMS = ['win32', 'linux', 'linux2', 'darwin']

# Define `block/block` and `block/block/build` paths.
BLOCK_DIR = os.path.join( DIR, 'block' )
BUILD_DIR = os.path.join( BLOCK_DIR, 'build' )

def clean():
    """
    Clean build directory (removing the entire `BUILD` tree).
    """
    # Check if `BUILD_DIR` exists.
    if os.path.exists( BUILD_DIR ):
        # Remove the entire `BUILD` tree.
        shutil.rmtree( BUILD_DIR )

def build():
    """
    Compile library into `BUILD` directory.
    """
    # Clean build directory.
    clean()
    # Create directory `./block/build`.
    try:
        os.makedirs( BUILD_DIR )
    except OSError as exception:
        # Raise Error whether `./block` isn't a valid path.
        if not exception.errno == errno.EEXIST:
            raise
    try:
        # Create distutils C compiler.
        CC = new_compiler()
        # Pass include directory.
        CC.add_include_dir( BLOCK_DIR )
        # Compile core.
        objects = CC.compile([ os.path.join( BLOCK_DIR, 'core.c' ) ], output_dir=BUILD_DIR )
        # Link shared libraries.
        CC.link_shared_lib( objects, "core", output_dir=BUILD_DIR )
    except Exception as e:
        clean()
        raise e

if 'install' in sys.argv or 'build' in sys.argv:
    # If `install` or `build` are passed as parameters then
    # compile the library.
    build()
elif 'clean' in sys.argv:
    # If `clean` is passed as parameter clean build – Delete
    # `./block/build`.
    clean()

# Open and store content of `README.md` into `README`.
README = 'README.md'
try:
    with open( os.path.join( DIR, README ), 'r' ) as readme:
        README = readme.read()
except IOError:
    README = ''

setup(
    name=NAME,
    version=VERSION,
    description=DESCRIPTION,
    long_description=README,
    author=AUTHOR,
    author_email=EMAIL,
    license=LICENSE,
    platforms=SUPPORTED_PLATFORMS,
)

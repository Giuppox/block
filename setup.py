import sys, os

from block_utils import (
    LIBPATH as DIR,
    __version__ as VERSION,
    __name__ as NAME,
    __author__ as AUTHOR,
    __email__ as EMAIL,
    __description__ as README,
    __license__ as LICENSE
)

import errno

from distutils.core import setup, Extension
from distutils.ccompiler import new_compiler

# Cd current working directory.
os.chdir( DIR )

BUILD = './block/build'     # Build files directory path.
CORE = './block/core.c'     # Core file path.

# Create directory `./block/build`.
try:
    os.makedirs( BUILD )
except OSError as exception:
    # Raise Error whether `./block` isn't a valid path.
    if exception.errno != errno.EEXIST:
        raise

# Create distutils C compiler.
C = new_compiler()
C.add_include_dir( './block' )
objects = C.compile([ CORE ], output_dir=BUILD)
C.link_shared_lib( objects, "core", output_dir=BUILD )

setup(
    name=NAME,
    version=VERSION,
    description='Block python library',
    long_description=README,
    author=AUTHOR,
    author_email=EMAIL,
    license=LICENSE
)

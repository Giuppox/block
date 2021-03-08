
# Block library name.
__name__ = 'block'

# Me!
__author__ = 'Giulio Procopio'

# The current version of the library.
__version__ = '1.0.0'
V = tuple( __version__.split( '.' ) )

# The email of the author.
__email__ = 'giulioprocopioo@gmail.com'

# The description of the library.
import os                                                        # Import os python module.
LIBPATH = f"{os.path.dirname( __file__ )}/"                      # Get library absolute path.
__description__ = open( f'{LIBPATH}README.md', 'r' ).read()      # Open `block/README.md` and read its content.

# The license of the library.
__license__ = 'MIT'

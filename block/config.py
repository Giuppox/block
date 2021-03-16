"""Get package metadata using importlib.
Exposes:
NAME: str, VERSION: str, location: str.
"""
import builtins
from pkg_resources import get_distribution

pkg = get_distribution( 'block' )

# Package location in the system.
LOCATION: builtins.str  = pkg.location

# Package name and version.
NAME: builtins.str = pkg.project_name
VERSION: builtins.str = pkg.version

del pkg

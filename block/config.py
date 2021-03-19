"""Get package metadata using importlib.

Exposes:
    NAME (str): the name of the package
    VERSION (tuple[str]): the version of the package
"""
from typing import Tuple
from pkg_resources import get_distribution

pkg = get_distribution('block')

# Package name and version.
NAME: str = pkg.project_name
VERSION: Tuple[str] = tuple(pkg.version.split('.'))

del pkg

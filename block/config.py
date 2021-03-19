"""Get package metadata using importlib.

Exposes:
    NAME (str): the name of the package
    VERSION (tuple[str]): the version of the package
"""
from typing import Tuple
try:
    from importlib import metadata
except ImportError:
    # Running on pre-3.8 Python; use importlib-metadata package.
    import importlib_metadata as metadata

# Package name and version.
NAME: str = 'block'
VERSION: Tuple[str] = tuple(
    metadata.version(NAME).split('.')
    )

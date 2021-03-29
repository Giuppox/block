"""Get package metadata using importlib.

Exposes:
    `NAME` (str): the name of the package
    `VERSION` (tuple[str]): the version of the package
"""
__all__ = ['NAME', 'VERSION']

try:
    from importlib import metadata
except ImportError:
    # Running on pre-3.8 Python; use importlib-metadata package.
    import importlib_metadata as metadata

# Package name and version.
try:
    NAME: str = 'block'
    VERSION: str = metadata.version(NAME)
except Exception as e:
    NAME, VERSION = None, None

"""Block is a python package for scientific computing with Python."""
__all__ = [
    'tools', 'dtypes'
    ]

from .config import (
    NAME as __name__, VERSION as __version__
    )
from . import tools
from . import dtypes

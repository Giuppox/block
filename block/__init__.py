# Expose package metadata.
from .config import (
    NAME as __name__, VERSION as __version__
)
__version__ = '.'.join(__version__)

from .tools import types

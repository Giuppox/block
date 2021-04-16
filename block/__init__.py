"""
Block
=====
Block is a powerfull and easy-to-use python package for Software Development
and Scientific Engineering. It provides:

 - N-dimensional Tensor builtin object.
 - Python C fixed data types wrappers.
 - Random Numbers and Tensor handling capabilities.

Get started
-----------
To get started just type ``import block as blk`` in the python console and
``blk.test()`` to test the installation. See block official documentation
for more info.

Example
-------
Block's Hello World! Create two block tensors (``blk.tensor``) and sum them.
```python
>>> import block as blk
>>> x, y = blk.tensor([1, 2, 3], [3, 2, 1])
>>> x + y
Tensor[4, 4, 4]
```

Attributes
----------
``core`` (module)

To see submodules specific documentation run ``help(submodule)`` or
``submodule.__doc__``

"""
import sys

# First detect if this is being called as part of the block setup
# procedure itself in a reliable manner.
try:
    __BLOCK_SETUP__
except NameError:
    __BLOCK_SETUP__ = False

if __BLOCK_SETUP__:
    sys.stderr.write('Running from block source directory.\n')
else:

    from . import core

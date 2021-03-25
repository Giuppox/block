"""Block types handling utility tools

Exposes:
    `checktype`: Runtime type hints checking decorator.
    `sametype`: Type equality checker.
    `ellipsis`: The ellipsis datatype.
    `NoneType`: None type.
"""

from typing import get_type_hints, get_origin, get_args, Union, Any
from inspect import isclass, isfunction, ismethod

# Expose ellipsis datatype (it should be implemented in python 3.10, but defining
# it here allows better ellipsis handling in python >3.10 versions too).
ellipsis = type(...)

# Expose None type.
NoneType = type(None)


def sametype(t, T):
    """Check if the two passed datatypes are the same type; or that at least one
    is comparable to the other (like `int` and `numbers.Number`).

    Parameters:
        `t` and `T` (types): The two types to check.

    Returns:
        A boolean indicating whether `t` and `T` are comparable or not.
    """

    # If `T` is `typing.Any` always return `True`.
    if T == Any:
        return True

    # Convert `typing.Union` to `tuple[...]`.
    if get_origin(T) == Union:
        T = tuple(get_args(T))

    # Check whether both `t` and `T` are classes or not.
    arguments_order = { 't': '1', 'T': '2' }
    for arg in (t, T):
        if not (isclass(arg)
                or (isinstance(arg, tuple) and not False in [isclass(k) for k in arg])):
            raise TypeError('Expected argument {} to be a class, but found "{}"'.format(
                arguments_order[[k for k,v in locals().items() if v == arg][0]], arg
                ))

    # Check if one is subclass of the other.
    if issubclass(t, T):
        return True

    # If the function hasn't returned `True` until here then return `False`.
    return False


def checktypes(fn):
    """Check type hints of the passed function `fn` on runtime.

    Parameters:
        `fn` (function): A function or a class on which to apply the type checking.

    Returns:
        The decorated function.
    """

    # Get `fn` type hints.
    hints = get_type_hints(fn)

    def wrapper(*args, **kwargs):
        """Decorator wrapper for handled function `fn`"""

        # Get `fn` arguments.
        all_args = kwargs.copy()
        all_args.update(dict(zip(fn.__code__.co_varnames, args)))

        # Check function args types where passed correctly.
        for argument, argument_type in ((i, type(j)) for i, j in all_args.items()):
            if argument in hints:
                if not sametype(argument_type, hints[argument]):
                    raise TypeError(
                        'Expected type of "{}" to be {}, but found {}'.format(
                            argument, hints[argument], argument_type
                            )
                        )

        # Get return of the function.
        result = fn(*args, **kwargs)

        # Check the return type of `fn` is correct.
        if 'return' in hints:
            if not sametype(type(result), hints['return']):
                raise TypeError(
                    'Expected return type to be {}, but found {}'.format(
                        type(result), hints['return']
                        )
                    )

        return result

    # Set major `fn` utility attributes from the decorated function to the
    # decorator, such as `__name__` (otherwise `wrapper` will be displayed,
    # instead of the proper name of the decorated function itself).
    for prop in ('__name__', '__doc__'):
        setattr(wrapper, prop, getattr(fn, prop))

    return wrapper

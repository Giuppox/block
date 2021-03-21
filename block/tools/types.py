"""Block types handling utility tools"""

from typing import get_type_hints

def checktypes( fn ):
    """Check type hints of pass function `fn` on runtime.

    Parameters:
        `fn`: A function or a class on which to apply the type checking.

    Returns:
        The decorated function.
    """

    print("`checktypes` isn't stable yet, you should definitely avoid using this!")

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
                if not issubclass(argument_type, hints[argument]):
                    raise TypeError(
                        'Expected type of "{}" to be {}, but found {}'.format(
                            argument, argument_type, hints[argument]
                            )
                        )

        # Get return of the function.
        result = fn(*args, **kwargs)

        # Check the return type of `fn` is correct.
        if 'return' in hints:
            if not type(result) == hints['return']:
                raise TypeError(
                    'Expected result type to be {}, but found {}'.format(
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

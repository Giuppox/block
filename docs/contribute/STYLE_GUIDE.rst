Style Guide
===========
Block's style guide defines a list of *dos* and *don’ts* for the block python
package modules and its submodules.
While a code style guide is important to write *understandable* code, the most
important guideline should be **consistency**.

    *"Any fool can write code that a computer can understand. Good programmers
    write code that humans can understand."* – Martin Fowler

Two good reasons to break a particular rule:

1. When applying the rule would make the code less readable, even for someone
   who is used to reading code that follows the rules.
2. To be consistent with surrounding code that also breaks it (maybe for
   historic reasons) – although this is also an opportunity to clean up someone
   else’s mess.

C detailed description
======================
The Block C coding conventions are based on Python
`PEP 7 – Style Guide for C <https://www.python.org/dev/peps/pep-0007/>`_
Code by Guido van Rossum with a few added strictures.

Dialect
-------
* Use *C99* (that is, the standard defined by ISO/IEC 9899:1999).
* Don’t use GCC extensions (for instance, don’t write multi-line strings
  without trailing backslashes).
* All function declarations and definitions must use full prototypes (that is,
  specify the types of all arguments).
* No compiler warnings with major compilers (gcc, VC++, a few others).

Code layout
-----------
* Use 4-space indents and no tabs at all.
* No line should be longer than 80 characters. If this and the previous rule
  together don’t give you enough room to code, your code is too complicated –
  consider using subroutines.
* No line should end in whitespace. If you think you need significant trailing
  whitespace, think again; somebody’s editor might delete it as a matter of
  routine.
* Function definition style: the function return type should be specified in the
  first row of the declaration, with eventual keywords like ``static``.
  In the second row should be specified the function name and arguments

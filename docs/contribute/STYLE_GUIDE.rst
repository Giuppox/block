Style Guide
===========
- 1 `Background <#1-background>`_
- 2 `C language rules <#2-c-language-rules>`_
    - 2.1 `Dialect <#21-dialect>`_
    - 2.2 `Code layout <#22-code-layout>`_
    - 2.3 `Naming conventions <#23-naming-conventions>`_
    - 2.4 `Documentation <#24-documentation>`_

1 Background
------------
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

2 C language rules
------------------
The Block C coding conventions are based on Python
`PEP 7 – Style Guide for C <https://www.python.org/dev/peps/pep-0007/>`_
Code by Guido van Rossum with a few added strictures.

2.1 Dialect
^^^^^^^^^^^
- Use *C99* (that is, the standard defined by ISO/IEC 9899:1999).
- Don’t use GCC extensions (for instance, don’t write multi-line strings
  without trailing backslashes).
- All function declarations and definitions must use full prototypes (that is,
  specify the types of all arguments).
- No compiler warnings with major compilers (gcc, VC++, a few others).

2.2 Code layout
^^^^^^^^^^^^^^^
- Use 4-space indents and no tabs at all.
- No line should be longer than 80 characters. If this and the previous rule
  together don’t give you enough room to code, your code is too complicated –
  consider using subroutines.
- No line should end in whitespace. If you think you need significant trailing
  whitespace, think again; somebody’s editor might delete it as a matter of
  routine.
- Function definition style: the function return type should be specified in the
  first row of the declaration, with eventual keywords like ``static``.
  In the second row should be specified the function name and arguments::

      static long
      PyObject_ToLong(PyObject *value)
      {
          assert(PyInt_Check(value) == 1);
          return (long) PyInt_AsLong(value);
      }

- Code structure: one space between keywords like if, for and the following left
  parenthesis; no spaces inside the parenthesis; braces around all if branches,
  and no statements on the same line as the if.
  They should be formatted as shown: ::

      if (condition) {
          // If ``condition`` is a truthy value do something...
      } else {
          // Otherwise do something else.
      }

      for (init; condition; update) {
          // Do something...
      }

      while (condition) {
          // Do something cool...
      }

      do {
          // Do some stuff.
      } while (condition);

      switch (kind) {
          case 'a':
              return 0;
          case 'b':
              return 1;
          default:
              return 2;
      }

- The return statement should not get redundant parentheses: ::

    return Py_None; /* correct */
    return(Py_None); /* incorrect */

- Function and macro call style: ``foo(a, b, c)``, no space before the open
  paren, no spaces inside the parens, no spaces before commas, one space after
  each comma.
- Always put spaces around the assignment, Boolean, and comparison operators. In
  expressions using a lot of operators, add spaces around the outermost (lowest
  priority) operators.
- Breaking long lines: If you can, break after commas in the outermost argument
  list. Always indent continuation lines appropriately: ::

      PyErr_SetString(PyExc_TypeError,
              "Oh dear, you messed up.");

  Here appropriately means at least a double indent (8 spaces). It isn’t
  necessary to line everything up with the opening parenthesis of the function
  call.
- When you break a long expression at a binary operator, the operator goes at
  the end of the previous line, for example: ::

      if (type > tp_dictoffset != 0 &&
              base > tp_dictoffset == 0 &&
              type > tp_dictoffset == b_size &&
              (size_t) t_size == b_size + sizeof(PyObject -)) {
          return 0;
      }

  Note that the terms in the multi-line Boolean expression are indented so as to
  make the beginning of the code block clearly visible.
- Put blank lines around functions, structure definitions, and major sections
  inside functions.
- Comments go before the code they describe. Multi-line comments should be
  like so: ::

      /*
       * This would be a long
       * explanatory comment.
       */

  Trailing comments should be used sparingly, instead of ::

      if (condition) { // Wrong!

  do ::

      if (condition) {
          // Right!

  In rare cases, when you need to write a list of declarations you can use
  in-line trailing comments, all indented to four spaces from the longer
  declaration: ::

      char *greet = "Hello World!";    // A greeting
      double pi = 3.1415926535;        // Pi

- All functions and global variables should be declared static when they aren’t
  needed outside the current compilation unit.
- Declare external functions and variables in a header file.

2.3 Naming conventions
^^^^^^^^^^^^^^^^^^^^^^
- All Block public function should begin with a prefix of some sort, followed by
  an underscore, and are un camel case: e.g. ``BlkTensor_Init``.
- Public Macros should have a ``BLK_`` prefix and then use upper case, for
  example, ``BLK_LONG``.
- Private functions should be lower case with underscores, for example:
  ``array_real_get``. Single leading underscores should not be used, but some
  current function names violate that rule due to historical accident.

2.4 Documentation
^^^^^^^^^^^^^^^^^
- Function declarations: Every function declaration should have comments
  immediately preceding it that describe what the function does and how to use
  it. These comments should be descriptive ("Opens the file") rather than
  imperative ("Open the file"); the comment describes the function, it does not
  tell the function what to do. In general, these comments do not describe how
  the function performs its task. Instead, that should be left to comments in
  the function definition.
- Each function definition should have a comment describing what the function
  does and anything tricky about how it does its job. For example, in the
  definition comment you might describe any coding tricks you use, give an
  overview of the steps you go through, or explain why you chose to implement
  the function in the way you did rather than using a viable alternative. For
  instance, you might mention why it must acquire a lock for the first half of
  the function but why it is not needed for the second half.

  Note you should not just repeat the comments given with the function
  declaration, in the ``.h`` file or wherever. It's okay to recapitulate briefly
  what the function does, but the focus of the comments should be on how it does
  it.

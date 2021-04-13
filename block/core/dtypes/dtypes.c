#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "types.h"
#include "dtypes.h"


// Undefine `INTEGERS`, `FLOATINGPOINTS` and `COMPLEX` macros to avoid
// conflicts when block is eventually included as header.
#undef INTEGERS
#undef FLOATINGPOINTS
#undef COMPLEX

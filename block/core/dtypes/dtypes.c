#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "types.h"
#include "dtypes.h"

// We temporarily avoid implementing complexes for developing purposes.


// Defines deallocation method macro.
#define DEALLOC(DTYPE, NAME)                          \
    static void                                       \
    NAME##_dealloc(NAME##_object *self)               \
    {                                                 \
        Py_TYPE(self)->tp_free((PyObject *) self);    \
    }
BLK_INTEGERS(DEALLOC)
BLK_FLOATINGPOINTS(DEALLOC)
#undef DEALLOC


// Defines `__new__` method macro.
#define NEW(DTYPE, NAME)                                              \
    static PyObject *                                                 \
    NAME##_new(PyTypeObject *type, PyObject *args, PyObject *kwds)    \
    {                                                                 \
        NAME##_object *self;                                          \
        self = (NAME##_object *) type->tp_alloc(type, 0);             \
        if (self != NULL) {                                           \
            self->value = (DTYPE) 0;                                  \
        }                                                             \
        return (PyObject *) self;                                     \
    }
BLK_INTEGERS(NEW)
BLK_FLOATINGPOINTS(NEW)
#undef NEW


// Defines `__init__` method macro.
#define INIT(DTYPE, NAME)                                               \
    static int                                                          \
    NAME##_init(NAME##_object *self, PyObject *args, PyObject *kwds)    \
    {                                                                   \
        if (!PyArg_ParseTuple(args, "d", &self->value)) {               \
            return -1;                                                  \
        }                                                               \
        return 0;                                                       \
    }
BLK_INTEGERS(INIT)
BLK_FLOATINGPOINTS(INIT)
#undef INIT

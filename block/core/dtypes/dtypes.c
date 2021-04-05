#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "dtypes.h"


static void
BLK_double_dealloc(BLK_double_object *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *
BLK_double_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    BLK_double_object *self;
    self = (BLK_double_object *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->value = (double)0.;
    }
    return (PyObject *) self;
}

static int
BLK_double_init(BLK_double_object *self, PyObject *args, PyObject *kwds)
{
    if (!PyArg_ParseTuple(args, "d", &self->value)) {
        return -1;
    }
    return 0;
}

static PyObject *
BLK_double_repr(BLK_double_object *self, PyObject *Py_UNUSED(ignored))
{
    int size = sizeof(self->value);
    char repr[size];
    snprintf(repr, size, "%f", self->value);
    return PyUnicode_FromStringAndSize(repr, (Py_ssize_t)size);
}

static PyObject *
BLK_double_add(PyObject *self, PyObject *other)
{
    double a, b;
    return NULL;
}


static PyMethodDef BLK_double_methods[] = {
    {NULL}
};

static PyNumberMethods BLK_double_number = {
    BLK_double_add,              // nb_add
    0,                           // nb_subtract
    0,                           // nb_multiply
    0,                           // nb_remainder
    0,                           // nb_divmod
    0,                           // nb_power
    0,                           // nb_negative
    0,                           // nb_positive
    0,                           // nb_absolute
    0,                           // nb_bool
    0,                           // nb_invert
    0,                           // nb_lshift
    0,                           // nb_rshift
    0,                           // nb_and
    0,                           // nb_xor
    0,                           // nb_or
    0,                           // nb_int
    0,                           // nb_reserved
    0,                           // nb_float
    0,                           // nb_inplace_add
    0,                           // nb_inplace_subtract
    0,                           // nb_inplace_multiply
    0,                           // nb_inplace_remainder
    0,                           // nb_inplace_power
    0,                           // nb_inplace_lshift
    0,                           // nb_inplace_rshift
    0,                           // nb_inplace_and
    0,                           // nb_inplace_xor
    0,                           // nb_inplace_or
    0,                           // nb_floor_divide
    0,                           // nb_true_divide
    0,                           // nb_inplace_floor_divide
    0,                           // nb_inplace_true_divide
};

static PyTypeObject BLK_double = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "dtypes.double",
    sizeof(BLK_double_object),
    0,
    (destructor)
        BLK_double_dealloc,      // tp_dealloc
    0,                           // tp_vectorcall_offset
    0,                           // tp_getattr
    0,                           // tp_setattr
    0,                           // tp_as_async
    (reprfunc)BLK_double_repr,   // tp_repr
    &BLK_double_number,          // tp_as_number
    0,                           // tp_as_sequence
    0,                           // tp_as_mapping
    0,                           // tp_hash
    0,                           // tp_call
    0,                           // tp_str
    PyObject_GenericGetAttr,     // tp_getattro
    0,                           // tp_setattro
    0,                           // tp_as_buffer
    Py_TPFLAGS_DEFAULT
        | Py_TPFLAGS_BASETYPE,   // tp_flags
    0,                           // tp_doc
    0,                           // tp_traverse
    0,                           // tp_clear
    0,                           // tp_richcompare
    0,                           // tp_weaklistoffset
    0,                           // tp_iter
    0,                           // tp_iternext
    BLK_double_methods,          // tp_methods
    0,                           // tp_members
    0,                           // tp_getset
    0,                           // tp_base
    0,                           // tp_dict
    0,                           // tp_descr_get
    0,                           // tp_descr_set
    0,                           // tp_dictoffset
    BLK_double_init,             // tp_init
    0,                           // tp_alloc
    BLK_double_new               // tp_new
};


static PyModuleDef dtypesmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "dtypes",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_dtypes(void)
{
    PyObject *m;

    if (PyType_Ready(&BLK_double) < 0) {
      return NULL;
    }

    m = PyModule_Create(&dtypesmodule);
    if (m == NULL) {
      return NULL;
    }

    Py_INCREF(&BLK_double);
    if (PyModule_AddObject(m, "double", (PyObject *) &BLK_double) < 0) {
        Py_DECREF(&BLK_double);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <Python.h>

static PyObject *test( PyObject *self ) {
  printf( "Hello World from Block!\n" );
  int success = 1;
  return PyLong_FromLong( success );
}

static PyMethodDef testMethods[] = {
  {"test", test, METH_VARARGS, NULL},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef testModule = {
  PyModuleDef_HEAD_INIT,
  "test",
  NULL,
  -1,
  testMethods
};

PyMODINIT_FUNC PyInit_module( void ) {
  return PyModule_Create( &testModule );
}

#ifndef BLOCK_CORE_DTYPES_DTYPES_H
#define BLOCK_CORE_DTYPES_DTYPES_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    PyObject_HEAD
    double value;
} BLK_double_object;

#ifdef __cplusplus
}
#endif
#endif

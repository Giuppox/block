#ifndef BLOCK_CORE_DTYPES_DTYPES_H
#define BLOCK_CORE_DTYPES_DTYPES_H

// Define block data types struct objects. Of the kind:
// ```C
// typedef struct {
//    PyObject_HEAD
//    dtype value;
// } blk_dtype_object;
// ```
#define OBJ(dtype, name)      \
    typedef struct {          \
        PyObject_HEAD         \
        dtype value;          \
    } name##_object;
BLK_INTEGERS(OBJ)
BLK_FLOATINGPOINTS(OBJ)
#undef OBJ

#endif

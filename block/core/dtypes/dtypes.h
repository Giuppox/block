#ifndef BLOCK_CORE_DTYPES_DTYPES_H
#define BLOCK_CORE_DTYPES_DTYPES_H

// Define block data types struct objects. Of the kind:
// ```C
// typedef struct {
//    PyObject_HEAD
//    dtype value;
// } blk_dtype_object;
// ```
#define OBJECT(DTYPE, NAME)    \
    typedef struct {           \
        PyObject_HEAD          \
        DTYPE value;           \
    } NAME##_object;
BLK_INTEGERS(OBJECT)
BLK_FLOATINGPOINTS(OBJECT)
#undef OBJECT

#endif

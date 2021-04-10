#ifndef BLOCK_CORE_DTYPES_DTYPES_H
#define BLOCK_CORE_DTYPES_DTYPES_H
#ifdef __cplusplus
extern "C" {
#endif


// Define macros for integers data types.
#define INTEGERS(M)               \
    M(signed char, CHAR)          \
    M(unsigned char, UCHAR)       \
    M(int, INT)                   \
    M(unsigned int, UINT)         \
    M(short, SHORT)               \
    M(unsigned short, USHORT)     \
    M(long, LONG)                 \
    M(unsigned long, ULONG)

// Define macros for floating points data types.
#define FLOATING_POINTS(M)        \
    M(float, FLOAT)               \
    M(double, DOUBLE)             \
    M(long double, LONGDOUBLE)

// Define macros for complex floating points data types.
#define COMPLEX(M)                                \
    M(float _Complex, FLOATCOMPLEX)               \
    M(double _Complex, DOUBLECOMPLEX)             \
    M(long double _Complex, LONGDOUBLECOMPLEX)

// Define dtypes object macro definition. Doing `DTYPE(int, INT)` is
// equivalent of doing:
// ```C
// typedef struct {
//     int value;
// } BLK_INT_object;
// ```
#define DTYPE(dtype, name)                  \
    typedef struct {                        \
        dtype value;                        \
    } BLK_##name##_object;

INTEGERS(DTYPE);
FLOATING_POINTS(DTYPE);
COMPLEX(DTYPE);


#ifdef __cplusplus
}
#endif
#endif

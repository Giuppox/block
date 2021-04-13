#ifndef BLOCK_CORE_DTYPES_TYPES_H
#define BLOCK_CORE_DTYPES_TYPES_H

// The following two macro definitions can be used to apply a
// macro over each C data type of that type. Just like:
// ```C
// #define TEST(type, name) type name##_TEST;
// BLK_FLOATINGPOINTS(TEST)
// ```

// Define integers data types definitions.
#define BLK_INTEGERS(M)                     \
    M(signed char, blk_char)                \
    M(unsigned char, blk_uchar)             \
    M(int, blk_int)                         \
    M(unsigned int, blk_uint)               \
    M(short, blk_short)                     \
    M(unsigned short, blk_ushort)           \
    M(long, blk_long)                       \
    M(unsigned long, blk_ulong)             \
    M(long long, blk_longlong)              \
    M(unsigned long long, blk_ulonglong)

// Define floating points data types definitions.
#define BLK_FLOATINGPOINTS(M)         \
    M(float, blk_float)               \
    M(double, blk_double)             \
    M(long double, blk_longdouble)

// Define complex floating points data types definitions.
#define BLK_COMPLEX(M)                                \
    M(float _Complex, blk_floatcomplex)               \
    M(double _Complex, blk_doublecomplex)             \
    M(long double _Complex, blk_longdoublecomplex)

#endif

#ifndef BLOCK_CORE_DTYPES_SCALARTYPES_H
#define BLOCK_CORE_DTYPES_SCALARTYPES_H

// The following two macro definitions can be used to apply a
// macro over each C data type of that type. Just like:
// ```C
// #define TEST(type, name) type name##_TEST;
// FLOATING_POINTS(TEST)
// ```

// Define integers data types definitions.
#define INTEGERS(M)                     \
    M(char, CHAR_)                      \
    M(signed char, CHAR)                \
    M(unsigned char, UCHAR)             \
    M(int, INT)                         \
    M(unsigned int, UINT)               \
    M(short, SHORT)                     \
    M(unsigned short, USHORT)           \
    M(long, LONG)                       \
    M(unsigned long, ULONG)             \
    M(long long, LONGLONG)              \
    M(unsigned long long, ULONGLONG)

// Define floating points data types definitions.
#define FLOATING_POINTS(M)        \
    M(float, FLOAT)               \
    M(double, DOUBLE)             \
    M(long double, LONGDOUBLE)

// Define complex floating points data types definitions.
#define COMPLEX(M)                                \
    M(float _Complex, FLOATCOMPLEX)               \
    M(double _Complex, DOUBLECOMPLEX)             \
    M(long double _Complex, LONGDOUBLECOMPLEX)

#endif

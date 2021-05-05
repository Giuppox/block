#ifndef BLOCK_CORE_COMMON_ERRNO_H
#define BLOCK_CORE_COMMON_ERRNO_H

/*
 * Declarations for block error codes, plus some utility functions for error
 * checking and throwing.
 * Including this header, block public functions (that return an errno) should
 * be in the form:
 * ```C
 * // Add example...
 * ```
 */

typedef char * string;

/*
 * Declare block error codes. Note that when needed you should create new error
 * codes instead of using the generic `Error` Exception.
 *
 * `Pass`: Success!
 * `Error`: A generic exception, should just be used when the problem cannot be
 *          represented easily by more specific exceptions, though in this case
 *          creating a new error code would be the better option.
 * `NotImplementedError`: The requested feature has not been implemented yet,
 *                        though it has been planed to develop it in future or
 *                        is under development.
 * `DeprecationError`: The requested feature has been deprecated and is not
 *                     avaiable in the current block version.
 * `OverflowError`: This error should be thown when there is an overflow
 *                  problem, that could be due, for example, to type
 *                  conversions, such as from a `char *` containing a `long` to
 *                  an `int`.
 */
#define ERRNO(M)              \
    M(Pass)                   \
    M(Error)                  \
    M(NotImplementedError)    \
    M(DeprecationError)       \
    M(OverflowError)

// Declare `BlkErrNo_Type` enumeration for error codes
#define ENUM(M) M,
typedef enum {
    ERRNO(ENUM)
} BlkErrNo_Type;
#undef ENUM

// Declare block error codes as string, so that they can be used for printing
// error messages.
#define STRING(M) #M,
const char *BlkErrNo_Type_Strings[] = {
    ERRNO(STRING)
};
#undef STRING


// Declare block `BlkErrNo` struct, that should be the return type of all block
// public functions (that must return an errno).
typedef struct BlkErrNo BlkErrNo;
struct BlkErrNo {
    BlkErrNo_Type type;
    string (*repr)(BlkErrNo *, char *);
    const char *file;
    unsigned int line, column;
};

// Define `BlkErrNo` creation function.
BlkErrNo *BlkErrNo_New(
    BlkErrNo_Type type, string (*repr)(BlkErrNo *, char *),
    const char *file, unsigned int line, unsigned int column);

// Get prefix of error code, in the form `filepath:row:col type`.
// Define a generic representation function for error codes.
char *BlkErrNo_Prefix(BlkErrNo *self, char *str);

// Define default `repr` functions for error codes (`BlkErrNo_Type`).
#define STR(M) char *BlkErrNo_Repr_##M(BlkErrNo *self, char *str);
ERRNO(STR)
#undef STR

// Remove `ERRNO` macro to avoid conflicts.
#undef ERRNO

#endif

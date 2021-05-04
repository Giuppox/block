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
#define ERRNO_ENUM(ENUM) ENUM,
typedef enum {
    ERRNO(ERRNO_ENUM)
} BlkErrNo_Type;
#undef ERRNO_ENUM

// Declare block error codes as string, so that they can be used for printing
// error messages.
#define ERRNO_STRING(STRING) #STRING,
const char *BlkErrNo_TypeStrings[] = {
    ERRNO(ERRNO_STRING)
};
#undef ERRNO_STRING

#undef ERRNO


// Declare block `BlkErrNo` struct, that should be the return type of all block
// public functions (that must return an errno).
typedef struct BlkErrNo BlkErrNo;
struct BlkErrNo {
    BlkErrNo_Type type;
    void (*str)(BlkErrNo *, char *);
    const char *file;
    unsigned int line;
};

// Define `BlkErrNo` creation function.
BlkErrNo *BlkErrNo_New(
    BlkErrNo_Type type, void (*str)(BlkErrNo *, char *),
    const char *file, unsigned int line);


// Define default `errno_str` function for `Pass` errno (`BlkErrNo_Type`).
void BlkErrNo_Pass(BlkErrNo *self, char *str);


#endif

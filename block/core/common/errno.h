#ifndef BLOCK_CORE_COMMON_ERRNO_H
#define BLOCK_CORE_COMMON_ERRNO_H

/*
 * Declarations for block error codes, plus some utility functions for error
 * checking and throwing.
 * Including this header, block public functions (that return an errno) should
 * be in the form:
 * ```C
 * BlkErrNo *sum(int *a, int b) {
 *     *a += b;
 *     return (BlkErrNo) BlkErrNo_New(Pass, __FILE__, __LINE__, 0, NULL);
 * }
 * ```
 */

// Define maximum length of sample lengths in error messages.
#ifndef BLK_ERRNO_LINE_SIZE
#define BLK_ERRNO_LINE_SIZE 80
#endif

// Specify whether to raise error on `Pass` throwing or not.
#ifndef BLK_THROW_PASS
#define BLK_THROW_PASS 0
#else
#define BLK_THROW_PASS 1
#endif

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
#define ERRNO(M) \
    M(Pass) \
    M(Error) \
    M(NotImplementedError) \
    M(DeprecationError) \
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
    char *(*repr)(BlkErrNo *, char **, char *);
    const char *file;
    unsigned int line, column;
    void (*throw)(BlkErrNo *, char *);
};

/*
 * `BlkErrNo` creation function.
 *
 * Parameters
 * ----------
 * `BlkErrNo_Type type`: the type of the error number.
 * `char *file`: a string containing the path of the file where the exception
 *               occours.
 * `const int line`,
 * `const int column`: the line and the column where the exception occours. Note
 *                     that if the error is not related to a specific line or
 *                     column you can use `0` value to specify a whole section.
 * `char *(*repr)(BlkErrNo *, char **, char *)`: the representation function of
 *                                               the exception. If the passed
 *                                               value is `NULL` use default one
 *                                               `BlkErrNo_Repr`.
 */
BlkErrNo *BlkErrNo_New(BlkErrNo_Type type, const char *file, unsigned int line,
    unsigned int column, char *(*repr)(BlkErrNo *, char **, char *));

// Defines default `repr` function for error codes (`BlkErrNo_Type`).
char *BlkErrNo_Repr(BlkErrNo *self, char **str, char *content);

// Defines exception throwing, that should be a "method" of `BlkErrNo`.
void BlkErrNo_Throw(BlkErrNo *self, char *content);

#define THROW(e, content) \
    BlkErrNo *errno = BlkErrNo_New(e, __FILE__, __LINE__, 0, NULL); \
    errno->throw(errno, content); \

// Remove `ERRNO` macro to avoid conflicts.
#undef ERRNO

#endif

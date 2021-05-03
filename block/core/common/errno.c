/*
 * Implements block helper error codes that should be used (at least) as return
 * type for all block core functions.
 */

/*
#define PY_SSIZE_T_CLEAN
#include <Python.h>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errno.h"

// Implement `BlkErrNo_New` function, for creating new `BlkErrNo` block error
// codes.
BlkErrNo *BlkErrNo_New(
    BlkErrNo_Type type, void (*str)(BlkErrNo *, char *), char *file, unsigned int line) {

    // Allocate errno's memory using `malloc`.
    BlkErrNo *errno = malloc(sizeof(BlkErrNo));
    if (errno == NULL) {
        return NULL;
    }

    // Gets `file` path length so that its memory can be allocated correctly.
    int file_size = (strlen(file)+1) * sizeof(char);

    #define ALLOCATE(NAME, SIZE, VALUE)    \
        errno->NAME = malloc(SIZE);        \
        if (errno->NAME == NULL) {         \
            free(errno);                   \
            return NULL;                   \
        }                                  \
        errno->NAME = VALUE;
    ALLOCATE(type, sizeof(BlkErrNo_Type), &type);
    ALLOCATE(file, file_size, file);
    ALLOCATE(line, sizeof(unsigned int), &line);
    ALLOCATE(str, )
    #undef ALLOCATE

    errno->str = str;

    return errno;

}

// Implement `BlkErrNo_Pass`.
void BlkErrNo_Pass(BlkErrNo *self, char *str) {

}

int main() {
    BlkErrNo *errno = BlkErrNo_New(DeprecationError, *BlkErrNo_Pass, "src.c", 192);
    char *x;
    errno->str(errno, x);
    printf("%i\n", *errno->line);
}

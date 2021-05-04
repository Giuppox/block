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
    BlkErrNo_Type type, void (*str)(BlkErrNo *, char *),
    const char *file, unsigned int line) {

    // Allocate errno's memory using `malloc`.
    BlkErrNo *errno = (BlkErrNo *) malloc(sizeof(BlkErrNo));
    if (errno == NULL) {
        return NULL;
    }

    #define PROP(NAME, VALUE) errno->NAME = VALUE;
    PROP(type, type);
    PROP(file, file);
    PROP(line, line);
    PROP(str, str);
    #undef PROP

    return errno;

}

// Implement `BlkErrNo_Pass`.
void BlkErrNo_Pass(BlkErrNo *self, char *str) {
    sprintf(str, "%s:%i Pass", self->file, self->line);
}

int main(void) {
    BlkErrNo *errno = BlkErrNo_New(DeprecationError, *BlkErrNo_Pass, "errno.c", 192);
    char *x;
    errno->str(errno, x);
    printf("%s\n", x);
}

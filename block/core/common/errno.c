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
    BlkErrNo_Type type, string (*repr)(BlkErrNo *, char *),
    const char *file, unsigned int line, unsigned int column) {

    // Allocate errno's memory using `malloc`.
    BlkErrNo *errno = (BlkErrNo *) malloc(sizeof(BlkErrNo));
    if (errno == NULL) {
        return NULL;
    }

    #define PROP(NAME, VALUE) errno->NAME = VALUE;
    PROP(type, type)
    PROP(file, file)
    PROP(line, line)
    PROP(column, column)
    PROP(repr, repr)
    #undef PROP

    return errno;

}

// Implements `BlkErrNo_Prefix`.
char *BlkErrNo_Prefix(BlkErrNo *self, char *str) {
    char *fmt = "%s:%i:%i %s";
    int size = snprintf(NULL, 0, fmt, self->file, self->line, self->column,
        BlkErrNo_Type_Strings[self->type]) + 1;
    str = malloc(size);
    if (str == NULL) {
        free(str);
        return NULL;
    }
    snprintf(str, size, fmt, self->file, self->line, self->column,
        BlkErrNo_Type_Strings[self->type]);
    return str;
}

// Implement `BlkErrNo_Repr_Pass`.


int main(void) {
    BlkErrNo *errno = BlkErrNo_New(Pass, *BlkErrNo_Prefix, "errno.c", 192, 0);
    char *x;
    errno->repr(errno, x);
    printf("%s\n", x);
}

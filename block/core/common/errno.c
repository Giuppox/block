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
BlkErrNo *BlkErrNo_New(BlkErrNo_Type type, const char *file, unsigned int line,
    unsigned int column, char *(*repr)(BlkErrNo *, char **, char *)) {

    // If `NULL` is passed instead of a representation function uses
    // `BlkErrNo_Repr` as default.
    if (repr == NULL) {
        repr = BlkErrNo_Repr;
    }

    // Allocate errno's memory using `malloc`.
    BlkErrNo *errno = (BlkErrNo *) malloc(sizeof(BlkErrNo));
    if (errno == NULL) {
        return NULL;
    }

    // Add properties to `errno`.
    #define PROP(NAME, VALUE) errno->NAME = VALUE;
    PROP(type, type)
    PROP(file, file)
    PROP(line, line)
    PROP(column, column)
    PROP(repr, repr)
    PROP(throw, &BlkErrNo_Throw)
    #undef PROP

    return errno;

}

// Implements `BlkErrNo_Repr`.
#define PARAMS self->file, self->line, self->column, \
    BlkErrNo_Type_Strings[self->type], content, line_content
char *BlkErrNo_Repr(BlkErrNo *self, char **str, char *content) {

    // Read line `self->line` of file `self->file`.
    FILE *file;
    if ((file = fopen(self->file, "r")) == NULL) {
        return NULL;
    }
    char line_content[BLK_ERRNO_LINE_SIZE];
    for (int i = 0; i <= self->line;
        fgets(line_content, sizeof(line_content), file), i++);
    fclose(file);

    // Define format string for the error message.
    char *fmt = "%s:%i:%i %s: %s\n%s";
    // Get size of the final resultant string.
    int size = snprintf(NULL, 0, fmt, PARAMS) + 1;

    *str = malloc(size);
    if (*str == NULL) {
        return NULL;
    }

    // Both set `str` value and return it.
    snprintf(*str, size, fmt, PARAMS);
    return *str;

}
#undef PARAMS

// Implements `BlkErrNo_Throw`.
void BlkErrNo_Throw(BlkErrNo *self, char *content) {
    char *repr;
    self->repr(self, &repr, content);
    if (self->type != Pass || BLK_THROW_PASS) {
        printf("%s\n", repr);
        exit(1);
    }
}

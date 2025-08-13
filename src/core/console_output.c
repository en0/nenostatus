#include <stdio.h>

#include "core.h"


/**
 * Print status to console.
 * @param self The OutputStrategy instance.
 * @param status A char ptr to the status line to print.
 */
static void print_status(OutputStrategy *self, const char *status) {
    printf("%s\n", status);
}


OutputStrategy new_console_output() {
    return (OutputStrategy){.set_status = print_status};
}

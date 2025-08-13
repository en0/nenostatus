#include <stdio.h>
#include <string.h>

#include "core.h"
#include "fixtures.h"


static void test_double_output_set_status(OutputStrategy *self, const char *status) {
    TestDoubleOutputStrategy *s = (TestDoubleOutputStrategy *)&self;
    s->call_count++;
    snprintf(s->output, MAX_STATUS_SIZE, "%i: %s", s->call_count, status);
}

TestDoubleOutputStrategy new_test_double_output() {
    return (TestDoubleOutputStrategy){
        .base.set_status = test_double_output_set_status,
        .call_count = 0
    };
}

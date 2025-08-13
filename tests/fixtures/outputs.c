#include <stdio.h>

#include "core.h"
#include "fixtures.h"


static void test_double_output_set_status(OutputStrategy *self, const char *status) {
    TestDoubleOutputStrategy *s = (TestDoubleOutputStrategy *)self;
    s->call_count = 1;
    snprintf(s->output, MAX_STATUS_SIZE, "%s", status);
}

static void test_double_output_reset(TestDoubleOutputStrategy *self) {
    self->call_count = 0;
}

TestDoubleOutputStrategy new_test_double_output() {
    return (TestDoubleOutputStrategy){
        .base.set_status = test_double_output_set_status,
        .reset = test_double_output_reset,
        .call_count = 0,
        .output[0] = '\0',
    };
}

#include <stdio.h>

#include "core.h"
#include "fixtures.h"


static void test_double_collector_run(MetricCollector *self) {
    TestDoubleCollector *s = (TestDoubleCollector *)self;
    s->call_count ++;
    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%s %i", self->name, s->call_count);
}

static void test_double_collector_reset(TestDoubleCollector *self) {
    self->base.set_interval(&self->base, 1);
    self->call_count = 0;
}

TestDoubleCollector new_test_double_colector(const char *name) {
    TestDoubleCollector ret = {.reset = test_double_collector_reset};
    initialize_collector_base(&ret.base, name, 1, test_double_collector_run);
    return ret;
}


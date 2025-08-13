#include <stdio.h>

#include "core.h"
#include "fixtures.h"


static void test_double_collector_run(MetricCollector *self) {
    TestDoubleCollector *s = (TestDoubleCollector *)&self;
    s->call_count ++;
    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%s %i", self->name, s->call_count);
}

TestDoubleCollector new_test_double_colector(const char *name) {
    return (TestDoubleCollector){
        .base.name = name,
        .base.interval = {0, 60},
        .base.update = test_double_collector_run,
        .call_count = 0
    };
}


#ifndef UNITTEST_FIXTURES_H
#define UNITTEST_FIXTURES_H

#include "core.h"

typedef struct TestDoubleCollector TestDoubleCollector;
struct TestDoubleCollector {
    MetricCollector base;
    void (*reset)(TestDoubleCollector *self);
    int call_count;
};
TestDoubleCollector new_test_double_colector(const char *name);

typedef struct TestDoubleOutputStrategy TestDoubleOutputStrategy;
struct TestDoubleOutputStrategy {
    OutputStrategy base;
    void (*reset)(TestDoubleOutputStrategy *self);
    int call_count;
    char output[MAX_STATUS_SIZE];
};
TestDoubleOutputStrategy new_test_double_output();
#endif

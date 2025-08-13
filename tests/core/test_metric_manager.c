#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>

#include "core.h"
#include "fixtures.h"


static MetricManager unit;
static TestDoubleOutputStrategy output;
static TestDoubleCollector d1;
static TestDoubleCollector d2;
static TestDoubleCollector d3;
static MetricCollector *collectors[] = {
    (MetricCollector *)&d1,
    (MetricCollector *)&d2,
    (MetricCollector *)&d3,
};

static int setup() {
    output = new_test_double_output();
    d1 = new_test_double_colector("d1");
    d2 = new_test_double_colector("d2");
    d3 = new_test_double_colector("d3");
    unit = new_metric_manager((OutputStrategy *)&output, collectors, 3);
    return 0;
}

static int teardown() {
    return 0;
}

static void test_metric_manager_calls_output() {
    output.reset(&output);
    unit.update(&unit);
    CU_ASSERT_STRING_EQUAL(output.output, "d1 1 | d2 1 | d3 1");
    CU_ASSERT_EQUAL(output.call_count, 1);
}

static void test_metric_manager_calls_collector_on_every_cycle() {
    d1.reset(&d1);
    d1.base.set_interval(&d1.base, 1);
    for (int i = 0; i < 20; i++)
        unit.update(&unit);
    CU_ASSERT_EQUAL(d1.call_count, 20);
}

static void test_metric_manager_calls_collector_on_every_other_cycle() {
    d1.reset(&d1);
    d1.base.set_interval(&d1.base, 2);
    for (int i = 0; i < 20; i++)
        unit.update(&unit);
    CU_ASSERT_EQUAL(d1.call_count, 10);
}

static void test_metric_manager_calls_collector_only_once() {
    d1.reset(&d1);
    d1.base.set_interval(&d1.base, 0);
    for (int i = 0; i < 20; i++)
        unit.update(&unit);
    CU_ASSERT_EQUAL(d1.call_count, 1);
}

static void test_metric_manager_never_calls_collector() {
    d1.reset(&d1);
    d1.base.set_interval(&d1.base, -1);
    for (int i = 0; i < 20; i++)
        unit.update(&unit);
    CU_ASSERT_EQUAL(d1.call_count, 0);
}

void core_metric_manager_test_suite() {
	CU_pSuite suite = CU_add_suite("core/metric_manager Test Suite", setup, teardown);
	CU_ADD_TEST(suite, test_metric_manager_calls_output);
    CU_ADD_TEST(suite, test_metric_manager_calls_collector_on_every_cycle);
    CU_ADD_TEST(suite, test_metric_manager_calls_collector_on_every_other_cycle);
    CU_ADD_TEST(suite, test_metric_manager_calls_collector_only_once);
	CU_ADD_TEST(suite, test_metric_manager_never_calls_collector);
}

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "core.h"
#include "fixtures.h"


MetricManager unit;
TestDoubleOutputStrategy output;
TestDoubleCollector d1;
TestDoubleCollector d2;
TestDoubleCollector d3;
MetricCollector *collectors[] = {
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

static void test_metric_manager() {
    // TODO: We need to add the the abiility to set the number of times the manager updates.
    // 0 could be forever, n > 0 will indicate how many updates are called.
    // for (uint i = 0; i < n; i++) # I don't know how to do this. will have to think
}

void core_metric_manager_test_suite() {
	CU_pSuite suite = CU_add_suite("core/metric_manager Test Suite", setup, teardown);
}

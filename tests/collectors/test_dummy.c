#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "collectors/dummy.h"
#include "core.h"


static void test_dummy_defaults() {
    DummyCollector c = new_dummy_collector("dummy", 1);
    CU_ASSERT_EQUAL(c.base.name, "dummy");
    CU_ASSERT_EQUAL(c.base.interval[0], 0);
    CU_ASSERT_EQUAL(c.base.interval[1], 60);
    CU_ASSERT_EQUAL(c.v, 1);
}

static void test_dummy_update() {
    DummyCollector c = new_dummy_collector("dummy", 1);
    c.base.update((MetricCollector *)&c);
    CU_ASSERT_STRING_EQUAL(c.base.status, "dummy says 1")
}

void collector_dummy_test_suite() {
	CU_pSuite suite = CU_add_suite("collector/dummy Test Suite", 0, 0);
	CU_add_test(suite, "[new_dummy_collector returns valid instance.]", test_dummy_defaults);
	CU_add_test(suite, "[test_dummy_update updates status]", test_dummy_update);
}

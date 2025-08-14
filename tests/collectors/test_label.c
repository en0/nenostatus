#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "core.h"
#include "collectors/label.h"


static void test_label_defaults() {
    MetricCollector c = new_label("dummy");
    CU_ASSERT_EQUAL(c.interval[0], -1);
    CU_ASSERT_EQUAL(c.interval[1], -1);
    CU_ASSERT_STRING_EQUAL(c.name, "Label");
    CU_ASSERT_STRING_EQUAL(c.status, "dummy")
}

void collector_label_test_suite() {
	CU_pSuite suite = CU_add_suite("collector/label", 0, 0);
	CU_ADD_TEST(suite, test_label_defaults);
}

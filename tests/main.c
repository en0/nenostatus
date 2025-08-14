#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void cli_test_suite();
void collector_label_test_suite();
void core_metric_manager_test_suite();
void collector_battery_test_suite();

int main() {
	CU_initialize_registry();

	// Call the test suite functions to register tests
	cli_test_suite();
    collector_label_test_suite();
    core_metric_manager_test_suite();
    collector_battery_test_suite();

	// Run all tests
	CU_basic_run_tests();
	CU_cleanup_registry();
	return 0;
}

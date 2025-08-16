#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void cli_test_suite();
void collector_label_test_suite();
void core_metric_manager_test_suite();
void collector_battery_test_suite();
void core_util_test_suite();

int main() {
	CU_initialize_registry();

    // CLI Tests
	cli_test_suite();

    // Core Tests
    core_metric_manager_test_suite();
    core_util_test_suite();

    // Collector Tests
    collector_label_test_suite();
    collector_battery_test_suite();

	// Run all tests
	CU_basic_run_tests();
	CU_cleanup_registry();
	return 0;
}

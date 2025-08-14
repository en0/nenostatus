#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "collectors/battery.h"


static void test_battery_defaults() {
    BatteryCollector unit = new_battery_collector("/sys/class/power_supply/BAT0");
    CU_ASSERT_STRING_EQUAL("/sys/class/power_supply/BAT0/present", unit.present_path);
    CU_ASSERT_STRING_EQUAL("/sys/class/power_supply/BAT0/energy_full", unit.energy_full_path);
    CU_ASSERT_STRING_EQUAL("/sys/class/power_supply/BAT0/energy_now", unit.energy_now_path);
    CU_ASSERT_STRING_EQUAL("/sys/class/power_supply/BAT0/status", unit.status_path);
    CU_ASSERT_EQUAL(unit.base.interval[0], 30);
    CU_ASSERT_EQUAL(unit.base.interval[1], 30);

    unit.base.update((MetricCollector *)&unit);
    printf(">>>%s<<<", unit.base.status);
}

void collector_battery_test_suite() {
	CU_pSuite suite = CU_add_suite("collector/battery", 0, 0);
	CU_ADD_TEST(suite, test_battery_defaults);
}

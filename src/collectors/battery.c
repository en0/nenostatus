/**
 * alarm                Sets a threshold for battery alarms.
 * energy_now           Current energy level of the battery in microWatt-hours.
 * present              Indicates if the battery is present (1) or not (0).
 * type Type of         battery (e.g., Li-ion).
 * cycle_count          Number of charge cycles the battery has gone through.
 * manufacturer         Name of the battery manufacturer.
 * serial_number        Serial number of the battery.
 * status               Current status (Charging, Discharging, Full).
 * voltage_min_design   Minimum design voltage of the battery.
 * energy_full          Full energy capacity of the battery.
 * power_now            Current power consumption in microWatts.
 * voltage_now          Current voltage of the battery.
 */

#include "collectors/battery.h"
#include "core.h"
#include <stdio.h>

#define ICON_MISSING "󱟨"

const char *ICONS_CHARGING[] = {
    "󰢜", "󰂆", "󰂇", "󰂈", "󰢝",
    "󰂉", "󰢞", "󰂊", "󰂋", "󰂅",
};

const char *ICONS_DISCHARGING[] = {
    "󰁺", "󰁻", "󰁼", "󰁽", "󰁾",
    "󰁿", "󰂀", "󰂁", "󰂂", "󰁹",
};

const char *ICONS_FULL[] = {
    "󱟢", "󱟢", "󱟢", "󱟢", "󱟢",
    "󱟢", "󱟢", "󱟢", "󱟢", "󱟢",
};

const char *ICONS_UNKNOWN[] = {
    "󰂑", "󰂑", "󰂑", "󰂑", "󰂑",
    "󰂑", "󰂑", "󰂑", "󰂑", "󰂑",
};

/**
 * Check if the hardware is present and installed.
 */
static bool is_present(BatteryCollector *self) {

    int present, rc;

    // Open file, exit if error.
    FILE *fp = fopen(self->present_path, "r");
    if (fp == NULL) return false;

    // Read value, exit if error
    rc = fscanf(fp, "%d", &present);
    fclose(fp);
    if (rc != 1) return false;

    return present == 1;
}

/**
 * get the correct icon-set depending on the charginig status.
 */
static const char **get_icons_set(BatteryCollector *self) {

    char status[2];
    int rc;

    // Open file, exit if failure to open.
    FILE *fp = fopen(self->status_path, "r");
    if (fp == NULL) return ICONS_UNKNOWN;

    // Read in file, exit if failure to read.
    rc = fscanf(fp, "%1s", status);
    fclose(fp);
    if (rc != 1) return ICONS_UNKNOWN;

    // Return the icon set depending on the status.
    switch (status[0]) {
        case 'C':
            return ICONS_CHARGING;
        case 'D':
            return ICONS_DISCHARGING;
        case 'F':
            return ICONS_FULL;
        default:
            return ICONS_UNKNOWN;
    }
}

/**
 * Compute the battery percentage. -1 indicates an error
 */
static int get_battery_percent(BatteryCollector *self) {
    FILE *fp;
    double full, now;
    int rc = 0;

    // Open full energy file, exit on error.
    fp = fopen(self->energy_full_path, "r");
    if (fp == NULL) return -1;

    // Read in the full energy value. Exit on error or zero.
    rc = fscanf(fp, "%lf", &full);
    fclose(fp);
    if (rc != 1 || full == 0) return -1;

    // Open current energy file. exit on error.
    fp = fopen(self->energy_now_path, "r");
    if (fp == NULL) return -1;

    // Read the now-energy vaule. Exit on error.
    rc = fscanf(fp, "%lf", &now);
    fclose(fp);
    if (rc != 1) return -1;

    // Compute and return an integer representation of the battery percentage.
    return (int)((now / full) * 100);
}

/**
 * Update the battery data and set the status.
 */
static void update(MetricCollector *self) {
    BatteryCollector *s = (BatteryCollector *)self;

    if (!is_present(s)) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, ICON_MISSING);
        return;
    }

    int value = get_battery_percent(s);
    int index = iclamp(value / 10, 0, 9);
    const char **icons = get_icons_set(s);

    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%s %i%%", icons[index], value);
}

BatteryCollector new_battery_collector(const char *hw_path) {
    BatteryCollector ret = {0};
    initialize_collector_base(&ret.base, "Battery", 30, update);
    snprintf((char *)ret.present_path, BATTERY_PATH_BUFFER_SIZE, "%s/present", hw_path);
    snprintf((char *)ret.energy_full_path, BATTERY_PATH_BUFFER_SIZE, "%s/energy_full", hw_path);
    snprintf((char *)ret.energy_now_path, BATTERY_PATH_BUFFER_SIZE, "%s/energy_now", hw_path);
    snprintf((char *)ret.status_path, BATTERY_PATH_BUFFER_SIZE, "%s/status", hw_path);
    return ret;
}

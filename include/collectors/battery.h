#ifndef COLLECTORS_BATTERY_H
#define COLLECTORS_BATTERY_H

#include "core.h"

#define BATTERY_PATH_BUFFER_SIZE 128

/**
 * BatteryCollector Structure
 *
 * This structure represents a battery metric collector that is responsible for
 * gathering battery-related metrics from the system. It extends the base
 * MetricCollector structure to include specific functionality for battery
 * monitoring.
 */
typedef struct {
    MetricCollector base;
    const char energy_now_path[BATTERY_PATH_BUFFER_SIZE];
    const char energy_full_path[BATTERY_PATH_BUFFER_SIZE];
    const char present_path[BATTERY_PATH_BUFFER_SIZE];
    const char alarm_path[BATTERY_PATH_BUFFER_SIZE];
    const char status_path[BATTERY_PATH_BUFFER_SIZE];
} BatteryCollector;

BatteryCollector new_battery_collector(const char *hw_path);

#endif

#ifndef COLLECTORS_BATTERY_H
#define COLLECTORS_BATTERY_H

#include "core.h"

#define BATTERY_PATH_BUFFER_SIZE 128

/**
 * BatteryCollector Structure
 *
 * This structure represents a metric collector specifically designed for gathering
 * battery-related metrics from the system. It extends the base functionality of the
 * MetricCollector by providing paths to various battery information files, allowing
 * for comprehensive monitoring of battery status and energy levels.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors,
 *   including the update mechanism and status management.
 *
 * - const char energy_now_path[BATTERY_PATH_BUFFER_SIZE]:
 *   A string representing the path to the file that contains the current energy level
 *   of the battery. This path is used to read the real-time energy status.
 *
 * - const char energy_full_path[BATTERY_PATH_BUFFER_SIZE]:
 *   A string representing the path to the file that contains the full energy capacity
 *   of the battery. This information is essential for calculating the percentage of
 *   battery life remaining.
 *
 * - const char present_path[BATTERY_PATH_BUFFER_SIZE]:
 *   A string representing the path to the file that indicates whether the battery is
 *   present in the system. This helps in determining the availability of battery metrics.
 *
 * - const char status_path[BATTERY_PATH_BUFFER_SIZE]:
 *   A string representing the path to the file that contains the current status of the
 *   battery (e.g., charging, discharging, full). This information is vital for understanding
 *   the operational state of the battery.
 */
typedef struct {
    MetricCollector base;
    const char energy_now_path[BATTERY_PATH_BUFFER_SIZE];
    const char energy_full_path[BATTERY_PATH_BUFFER_SIZE];
    const char present_path[BATTERY_PATH_BUFFER_SIZE];
    const char status_path[BATTERY_PATH_BUFFER_SIZE];
    bool alarmed;
} BatteryCollector;

/**
 * new_battery_collector Function
 *
 * This function creates and initializes a new instance of a BatteryCollector,
 * which is responsible for collecting battery-related metrics from the specified
 * hardware path. The collector is designed to interface with the system's battery
 * information, allowing for real-time monitoring of battery status.
 *
 * Parameters:
 *
 * - const char *hw_path:
 *   A string representing the hardware path to the battery information. This path
 *   is used by the collector to access the relevant data from the system, ensuring
 *   accurate and up-to-date battery metrics.
 *
 * Returns:
 *
 * - A BatteryCollector instance that is initialized with the provided hardware path.
 *   The caller is responsible for managing the lifecycle of the returned collector.
 */
BatteryCollector new_battery_collector(const char *hw_path);

#endif

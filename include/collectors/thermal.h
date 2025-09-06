#ifndef COLLECTORS_THERMAL_H
#define COLLECTORS_THERMAL_H

#include "core.h"

/**
 * ThermalCollector Structure
 *
 * This structure represents a thermal metric collector that is responsible for
 * gathering temperature-related metrics from the system. It extends the base
 * MetricCollector structure to include specific functionality for thermal
 * monitoring.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric
 *   collectors, including the update method and status management.
 *
 * - const char *hw_path:
 *   A pointer to a string representing the hardware path for the thermal
 *   sensor information. This path is used to access the temperature data
 *   and other related metrics from the system.
 */
typedef struct {
    MetricCollector base;
    const char *hw_path;
    bool alarmed;
} ThermalCollector;

/**
 * Function to create a new ThermalCollector.
 *
 * This function creates and initializes a new instance of a ThermalCollector,
 * which is responsible for monitoring and reporting the temperature readings
 * from a specified hardware path.
 *
 * Parameters:
 *
 * - const int interval:
 *   The interval, in seconds, at which this component should be updated.
 *
 * - const char *hw_path:
 *   A string representing the path to the hardware sensor to monitor. This path
 *   should point to a valid thermal zone in the system, typically located in
 *   the /sys/class/thermal directory.
 *
 * Returns:
 *
 * - A ThermalCollector instance that is initialized with the provided hardware path.
 *   The caller is responsible for managing the lifecycle of the returned collector.
 */

ThermalCollector new_thermal_collector(const int interval, const char *hw_path);

#endif

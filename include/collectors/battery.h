#ifndef COLLECTORS_BATTERY_H
#define COLLECTORS_BATTERY_H

#include "core.h"

/**
 * BatteryCollector Structure
 *
 * This structure represents a battery metric collector that is responsible for
 * gathering battery-related metrics from the system. It extends the base
 * MetricCollector structure to include specific functionality for battery
 * monitoring.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric
 *   collectors, including the update method and status management.
 *
 * - const char *base_path:
 *   A pointer to a string representing the hardware path for the battery
 *   information. This path is used to access the battery status and other
 *   related metrics from the system.
 */
typedef struct {
    MetricCollector base;
    const char *base_path;
} BatteryCollector;

#endif

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
 * - const char *base_path:
 *   A pointer to a string representing the hardware path for the thermal
 *   sensor information. This path is used to access the temperature data
 *   and other related metrics from the system.
 */
typedef struct {
    MetricCollector base;
    const char *base_path;
} ThermalCollector;

#endif

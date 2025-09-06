#ifndef MEMORY_USAGE_H
#define MEMORY_USAGE_H

#include "core.h"

/**
 * MemoryUsageCollector Structure
 *
 * This structure represents a metric collector that retrieves and displays
 * memory utilization metrics, including total, used, and free memory.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors,
 *   including the update mechanism and status management.
 */
typedef struct {
    MetricCollector base;
} MemoryUsageCollector;

/**
 * Function to create a new MemoryUsageCollector.
 *
 * Parameters:
 *
 * - const int interval:
 *   The interval, in seconds, at which this component should be updated.
 *
 * This function creates a metric collector that retrieves and displays
 * memory utilization metrics.
 */
MemoryUsageCollector new_memory_usage_collector(const int interval);

#endif // MEMORY_USAGE_H

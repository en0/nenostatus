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
 * This function creates a metric collector that retrieves and displays
 * memory utilization metrics.
 */
MemoryUsageCollector new_memory_usage_collector(void);

#endif // MEMORY_USAGE_H

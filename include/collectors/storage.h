#ifndef STORAGE_H
#define STORAGE_H

#include "core.h"

/**
 * StorageCollector Structure
 *
 * This structure represents a metric collector that retrieves and displays
 * the storage utilization percentage of a specified path. It extends the
 * base functionality of the MetricCollector to provide specific behavior
 * for storage utilization collection.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors,
 *   including the update mechanism and status management.
 *
 * - const char *path:
 *   A string representing the path for which the storage utilization will be collected.
 */
typedef struct {
    MetricCollector base;
    const char *path;
} StorageCollector;

/**
 * Function to create a new StorageCollector.
 *
 * This function creates and initializes a new instance of a StorageCollector,
 * which is responsible for collecting and displaying the storage utilization
 * percentage of a specified path.
 *
 * Parameters:
 *
 * - const char *path:
 *   A string representing the path to monitor.
 *
 * Returns:
 *
 * - A StorageCollector instance that is initialized with the provided path.
 *   The caller is responsible for managing the lifecycle of the returned collector.
 */
StorageCollector new_storage_collector(const char *path);

#endif // STORAGE_H

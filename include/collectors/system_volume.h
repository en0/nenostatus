#ifndef SYSTEM_VOLUME_H
#define SYSTEM_VOLUME_H

#include "core.h"

/**
 * SystemVolumeCollector Structure
 *
 * This structure represents a metric collector that retrieves and displays
 * the current system volume and mute state. It extends the base functionality
 * of the MetricCollector to provide specific behavior for volume collection.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors,
 *   including the update mechanism and status management.
 *
 * - const char *mixer_name:
 *   A string representing the name of the mixer to monitor for volume and mute state.
 *
 * - const char *element_name:
 *   A string representing the name of the mixer element to monitor for volume and mute state.
 */
typedef struct {
    MetricCollector base;
    const char *mixer_name;
    const char *element_name;
} SystemVolumeCollector;

/**
 * Function to create a new SystemVolumeCollector.
 *
 * This function creates and initializes a new instance of a SystemVolumeCollector,
 * which is responsible for collecting and displaying the current system volume
 * and mute state.
 *
 * Parameters:
 *
 * - const char *mixer_name:
 *   A string representing the name of the mixer to monitor.
 *
 * - const char *element_name:
 *   A string representing the name of the mixer element to monitor.
 *
 * Returns:
 *
 * - A SystemVolumeCollector instance that is initialized with the provided mixer and element names.
 *   The caller is responsible for managing the lifecycle of the returned collector.
 */
SystemVolumeCollector new_system_volume_collector(const char *mixer_name, const char *element_name);

#endif // SYSTEM_VOLUME_H

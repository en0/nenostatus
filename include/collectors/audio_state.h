#ifndef AUDIO_STATE_H
#define AUDIO_STATE_H

#include "core.h"

/**
 * AudioStateCollector Structure
 *
 * This structure represents a metric collector that retrieves and displays
 * the current state of the audio subsystem. It extends the base functionality
 * of the MetricCollector to provide specific behavior for audio state collection.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors,
 *   including the update mechanism and status management.
 *
 * - const char *mixer_name:
 *   A string representing the name of the mixer to monitor for mute state.
 *
 * - const char *output_name
 *   A string representing the name of the mixer element to monitor for mute state as output.
 *
 * - const char *input_name
 *   A string representing the name of the mixer element to monitor for mute state as input.
 */
typedef struct {
    MetricCollector base;
    const char *mixer_name;
    const char *output_name;
    const char *input_name;
} AudioStateCollector;

/**
 * Function to create a new AudioStateCollector.
 *
 * This function creates and initializes a new instance of a AudioStateCollector,
 * which is responsible for collecting and displaying the current state of the
 * audio subsystem.
 *
 * Parameters:
 *
 * - const char *mixer_name:
 *   A string representing the name of the mixer to monitor.
 *
 * - const char *output_name:
 *   A string representing the name of the mixer element to monitor as output.
 *
 * - const char *input_name:
 *   A string representing the name of the mixer element to monitor as input.
 *
 * Returns:
 *
 * - A AudioStateCollector instance that is initialized with the provided mixer and element names.
 *   The caller is responsible for managing the lifecycle of the returned collector.
 */
AudioStateCollector new_audio_state_collector(const char *mixer_name, const char *output_name, const char *input_name);

#endif // AUDIO_STATE_H

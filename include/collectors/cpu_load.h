#ifndef CPU_LOAD_H
#define CPU_LOAD_H

#include "core.h"
#include <stdint.h>

#define MAX_CPU_CORES 64

/**
 * CPULoadCollector Structure
 *
 * This structure represents a metric collector that retrieves and displays
 * the current CPU load for each core. It extends the base functionality of
 * the MetricCollector to provide specific behavior for CPU load collection.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors,
 *   including the update mechanism and status management.
 *
 * - int metrics[MAX_CPU_CORES]:
 *   An array of integers storing the last measurement collected for each CPU core.
 *
 * - uint64_t lastClockTime:
 *   A long long value that holds the wall-time of the last metric collection step.
 *   this value is used to calcualte the cpu load.
 *
 * - int user_hz:
 *   An integer defining the unit of values stored in the metrics array.
 *   calcualte the cpu load.
 */
typedef struct {
    MetricCollector base;
    long metrics[MAX_CPU_CORES];
    uint64_t lastClockTime;
    int user_hz;
} CPULoadCollector;

/**
 * Function to create a new CPULoadCollector.
 *
 * This function creates and initializes a new instance of a CPULoadCollector,
 * which is responsible for collecting and displaying the current CPU load for each core.
 *
 * Returns:
 *
 * - A CPULoadCollector instance that is initialized with the provided core count.
 *   The caller is responsible for managing the lifecycle of the returned collector.
 */
CPULoadCollector new_cpu_load_collector();

#endif // CPU_LOAD_H

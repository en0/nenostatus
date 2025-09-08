#ifndef __SHELL_H__
#define __SHELL_H__

#include "core.h"

/**
 * ShellCollector Structure
 *
 * This structure represents a metric collector specifically designed for running
 * a shell script or external program.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors,
 *   including the update mechanism and status management.
 *
 * - const char *path:
 *   The path of the script to execute.
 */
typedef struct {
    MetricCollector base;
    const char *path;
} ShellCollector;

/**
 * new_shell_collector Function
 *
 * This function creates and initializes a new instance of a ShellCollector,
 * which is responsible for collecting metrics from a shell script or external
 * program.
 *
 * Parameters:
 *
 * - const char *path:
 *   A string representing the path to the script or external program.
 *
 * Returns:
 *
 * - A ShellCollector instance that is initialized with the provided path.
 *   The caller is responsible for managing the lifecycle of the returned
 * collector.
 */
ShellCollector new_shell_collector(const char *path);

#endif

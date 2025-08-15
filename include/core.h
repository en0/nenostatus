#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <X11/Xlib.h>

#define MAX_COLLECTOR_STATUS_SIZE 255
#define MAX_COLLECTORS 64
#define MAX_STATUS_SIZE (MAX_COLLECTOR_STATUS_SIZE * MAX_COLLECTORS)


 /**
 * MetricCollector Structure
 *
 * This structure represents a metric collector that is responsible for gathering
 * specific metrics from the system. Each collector can be enabled or disabled,
 * and it contains functionality to update its status and store the result.
 *
 * Members:
 *
 * - void (*update)(MetricCollector *self):
 *   A function pointer to the update function that is responsible for collecting
 *   the metric data and writing the status string to the `status` buffer.
 *
 * - char status[MAX_COLLECTOR_STATUS_SIZE]:
 *   A buffer where the `update()` function writes the status string representing
 *   the current value of the metric being collected. This string can be used for
 *   display or logging purposes.
 *
 * - int interval[2]:
 *   An array of two integers representing the update intervals. The first element
 *   (i) is the current interval counter, which increments with each update call.
 *   The second element (j) is the interval at which the update is triggered. After
 *   the `update()` function is called, the current interval (i) will be reset.
 *
 * - const char *name:
 *   A name for the MetricCollector. This is set by MetricCollector implementations
 *   to help with trouble shooting.
 */
typedef struct MetricCollector MetricCollector;
struct MetricCollector {
    void (*update)(MetricCollector *self);
    void (*set_interval)(MetricCollector *self, int seconds);
    char status[MAX_COLLECTOR_STATUS_SIZE];
    int interval[2];
    const char *name;
};

/**
 * OutputStrategy Structure
 *
 * This structure represents an output strategy for displaying collected metrics.
 * It provides a mechanism to set the status of the output, allowing for different
 * implementations to define how and where the metrics are presented.
 *
 * Members:
 *
 * - void (*set_status)(OutputStrategy *self, const char *status):
 *   A function pointer to the method responsible for updating the output status.
 *   This function takes the current status string as input and determines how to
 *   display it, whether to the console or to a window manager.
 */
typedef struct OutputStrategy OutputStrategy;
struct OutputStrategy {
    void (*set_status)(OutputStrategy *self, const char *status);
};

/**
 * new_console_output Function
 *
 * This function creates and initializes a new instance of an OutputStrategy that
 * prints collected metrics to the standard output (stdout). This is useful for
 * simple console-based applications where metrics need to be displayed in real-time.
 *
 * Returns:
 *
 * - An OutputStrategy instance configured to output metrics to the console.
 *   The caller is responsible for managing the lifecycle of the returned strategy,
 *   including any necessary cleanup.
 */
OutputStrategy new_console_output();

/**
 * new_xsetroot_output Function
 *
 * This function creates and initializes a new instance of an OutputStrategy that
 * sets the name of the X display root window. This is particularly useful for window
 * managers like dwm that utilize the root window name in their status bar, allowing
 * for dynamic updates of the displayed metrics.
 *
 * Returns:
 *
 * - An OutputStrategy instance configured to update the X display root window name
 *   with the collected metrics. The caller is responsible for managing the lifecycle
 *   of the returned strategy, including any necessary cleanup.
 */
OutputStrategy new_xsetroot_output();

/**
 * MetricManager Structure
 *
 * This structure represents a service that orchestrates the collection of metrics
 * from multiple metric collectors and manages the output of these metrics to a
 * specified output strategy. The MetricManager is responsible for tracking the
 * update schedule of each collector, ensuring they are updated at the appropriate
 * intervals, and sending the status to the output only when necessary.
 *
 * Members:
 *
 * - void (*update)(MetricManager *self):
 *   A function pointer to the method responsible for updating all registered
 *   collectors. This method checks each collector's schedule and invokes their
 *   update functions as needed, consolidating the results for output.
 *
 * - OutputStrategy *output_strategy:
 *   A pointer to the OutputStrategy instance that defines how the collected metrics
 *   will be displayed. This allows for flexibility in output methods, such as
 *   console output or window manager integration.
 *
 * - MetricCollector **collectors:
 *   An array of pointers to MetricCollector instances that are being managed by
 *   the MetricManager. This allows the manager to coordinate updates and status
 *   reporting for all registered collectors.
 *
 * - int collector_count:
 *   An integer representing the total number of collectors being managed. This
 *   is used to iterate through the collectors during updates and status reporting.
 *
 * - char status[MAX_STATUS_SIZE]:
 *   A buffer where the current status string is stored. This string represents
 *   the consolidated output of the metrics collected and is used for display
 *   purposes.
 */
typedef struct MetricManager MetricManager;
struct MetricManager{
    void (*update)(MetricManager *self);
    OutputStrategy *output_strategy;
    MetricCollector **collectors;
    int collector_count;
    char status[MAX_STATUS_SIZE];
};

/**
 * new_metric_manager Function
 *
 * This function creates and initializes a new instance of a MetricManager,
 * which orchestrates the collection of metrics from the provided collectors
 * and manages their output to the specified output strategy. The MetricManager
 * ensures that each collector is updated at the appropriate intervals and
 * consolidates the status for output only when necessary.
 *
 * Parameters:
 *
 * - OutputStrategy *output_strategy:
 *   A pointer to the OutputStrategy instance that will be used for displaying
 *   the collected metrics.
 *
 * - MetricCollector **collectors:
 *   An array of pointers to MetricCollector instances that the MetricManager
 *   will manage.
 *
 * - int count:
 *   The total number of collectors in the provided array.
 *
 * Returns:
 *
 * - A MetricManager instance that is initialized with the specified output strategy
 *   and collectors. The caller is responsible for managing the lifecycle of the
 *   returned manager, including any necessary cleanup.
 */
MetricManager new_metric_manager(OutputStrategy *output_strategy, MetricCollector **collectors, int count);


/**
 * initialize_collector_base Function
 *
 * This function initializes the base information for a metric collector. It should
 * be called during the construction of a new collector to set up essential properties
 * such as the collector's name, update interval, and the update function. This ensures
 * that the collector is properly configured before it begins operation.
 *
 * Parameters:
 *
 * - MetricCollector *self:
 *   A pointer to the MetricCollector instance that is being initialized. This instance
 *   will have its base properties set according to the provided parameters.
 *
 * - const char *name:
 *   A string representing the name of the collector. This name is used for identification
 *   and troubleshooting purposes.
 *
 * - int seconds:
 *   An integer representing the update interval in seconds. This value determines how
 *   frequently the collector's update function will be called.
 *
 * - void (*update)(MetricCollector *self):
 *   A function pointer to the update function that will be responsible for collecting
 *   the metric data. This function will be invoked at the specified intervals to gather
 *   and process the relevant metrics.
 */
void initialize_collector_base(MetricCollector *self, const char *name, int seconds, void (*update)(MetricCollector *self));

#endif

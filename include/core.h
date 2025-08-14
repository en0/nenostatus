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
 * This structure defines an interface for output strategies used by the
 * MetricManager to handle the output of metric statuses. It allows for
 * flexibility in how metrics are presented, enabling different output
 * methods to be implemented.
 *
 * Members:
 *
 * - void (*set_status)(OutputStrategy *self, const char *status):
 *   A function pointer to the method responsible for setting the status
 *   string. This function takes a pointer to the `OutputStrategy` instance
 *   and the status string to be output. This design allows for various
 *   output strategies to maintain internal state, such as writing to a file
 *   or managing rolling logs.
 */
typedef struct OutputStrategy OutputStrategy;
struct OutputStrategy {
    void (*set_status)(OutputStrategy *self, const char *status); };

/**
 * MetricManager Structure
 *
 * This structure manages the collection of metrics from various metric
 * collectors. It coordinates the execution of updates and handles the
 * output of the collected metrics through the specified output strategy.
 *
 * Members:
 *
 * - void (*run)(MetricManager *self):
 *   A function pointer to the method that starts the metric collection
 *   process. This function will enter a loop, calling the update methods
 *   of the registered collectors and using the output strategy to display
 *   or log the collected metrics.
 *
 * - OutputStrategy *output_strategy:
 *   A pointer to the output strategy being used by the MetricManager.
 *   This allows the manager to output the collected metrics in various ways,
 *   independing on the implementation of the output strategy.
 *
 * - MetricCollector *collectors:
 *   A pointer to an array of metric collectors managed by the MetricManager.
 *   This array holds the collectors that will be updated and whose statuses
 *   will be output.
 *
 * - int collector_count:
 *   An integer representing the number of metric collectors currently managed
 *   by the MetricManager. This count is used to iterate over the collectors
 *   during the update process.
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
 * Creates a new output strategy
 *
 * @return A ConsoleOutputStrategy instance.
 */
OutputStrategy new_console_output();
OutputStrategy new_xsetroot_output();

/**
 * Creates a new MetricManager
 *
 * @return A MetricManager instance.
 */
MetricManager new_metric_manager(OutputStrategy *output_strategy, MetricCollector **collectors, int count);


/**
 * Initialize a collector.
 *
 * This function should be called during the construction of a new collector.
 *
 * void new_custom_collector(...) {
 *   MyCustomCollector ret = {.custom_variable = 1};
 *   initialize_collector_base(&ret.base, "My Collector", 10, my_update);
 * }
 */
void initialize_collector_base(MetricCollector *self, const char *name, int seconds, void (*update)(MetricCollector *self));

#endif

#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

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
 * - void (*update)(MetricCollector *self):
 *   A function pointer to the update function that will be responsible for collecting
 *   the metric data. This function will be invoked at the specified intervals to gather
 *   and process the relevant metrics.
 */
void initialize_collector_base(MetricCollector *self, void (*update)(MetricCollector *self));

/**
 * append_to_buffer Function
 *
 * This function appends a formatted string to a specified buffer while managing
 * the current offset. It allows for flexible string formatting using variadic
 * arguments, making it suitable for constructing messages or logs dynamically.
 * The function ensures that the buffer does not overflow by checking the available
 * space before writing. It should be used whenever there is a need to build
 * strings incrementally in a safe manner.
 *
 * Parameters:
 *
 * - char *buffer:
 *   A pointer to the character array (buffer) where the formatted string will be
 *   appended. This buffer should be large enough to hold the resulting string.
 *
 * - size_t buffer_size:
 *   The total size of the buffer in bytes. This value is used to prevent buffer
 *   overflow during the append operation.
 *
 * - size_t *offset:
 *   A pointer to a size_t variable that keeps track of the current position in the
 *   buffer. This value will be updated by the function to reflect the new offset
 *   after the string is appended.
 *
 * - const char *format:
 *   A format string that specifies how to format the subsequent variadic arguments.
 *   This string follows the same conventions as the format string used in printf.
 *
 * - ...:
 *   A variable number of arguments that will be formatted according to the format
 *   string. These arguments can be of various types, allowing for flexible string
 *   construction.
 *
 * Returns:
 * - int:
 *   The number of characters written to the buffer, or -1 if an error occurs.
 *   Possible error cases include:
 *   - If the buffer is full and cannot accommodate the new string.
 *   - If the formatted string exceeds the available space in the buffer, resulting
 *     in a truncated write.
 *   - If a formatting error occurs during the string construction.
 *   In all error cases, the value of offset will remain unchanged and may be
 *   considered undefined.
 */
int append_to_buffer(char *buffer, size_t buffer_size, size_t *offset, const char *format, ...);

/**
 * render_bar Function
 *
 * This function generates a visual progress bar representation based on the
 * specified value and maximum value. The resulting bar is constructed using
 * Unicode characters, which take up 3 bytes each. To accommodate this, the
 * width of the bar is set to be 3 times smaller than the provided buffer size
 * minus 1, ensuring that there is space for a null terminator at the end of
 * the string. It is recommended that the buffer size be a multiple of 3 plus 1
 * (e.g., buffer[31]) to ensure proper alignment and avoid overflow.
 *
 * Parameters:
 *
 * - char *buffer:
 *   A pointer to the character array (buffer) where the progress bar will be
 *   rendered. This buffer should be large enough to hold the resulting bar
 *   representation, including the null terminator.
 *
 * - size_t buffer_size:
 *   The total size of the buffer in bytes. This value is used to determine the
 *   maximum width of the progress bar and to prevent buffer overflow during
 *   the rendering operation. The buffer size should be a multiple of 3 plus 1.
 *
 * - double value:
 *   The current value representing the progress. This value should be less than
 *   or equal to max_value to ensure accurate rendering of the progress bar.
 *
 * - double max_value:
 *   The maximum value that represents 100% completion. The progress bar will
 *   be filled proportionally based on the ratio of value to max_value.
 *
 * Returns:
 * - void:
 *   This function does not return a value. It directly modifies the contents
 *   of the provided buffer to reflect the rendered progress bar.
 *
 * Note:
 * - The function does not perform error checking on the input parameters. It is
 *   the caller's responsibility to ensure that the buffer is appropriately sized
 *   and that the values for value and max_value are valid.
 */
void render_bar(char *buffer, size_t buffer_size, double value, double max_value);


/**
 * iclamp function
 *
 * This function clamps a given interger value into a specified range.  If a value
 * is below the minimum value, the minimum is returned. If a value is above the
 * maximum value, the maximum value is returned. If the value falls within the
 * given range, the value is returned.
 *
 * Parameters:
 *
 * - int value:
 *   The value to clamp.
 *
 * - int min:
 *   The minimum value of the range.
 *
 * - int max:
 *   The maximium value of the range.
 *
 * - Returns:
 *   - int:
 *     If value is less than min, min. Else, if the value is greater than max, max.
 *     Else, value.
 */
static inline int iclamp(int value, int min, int max) {
    const int i = value < min ? min : value;
    return i > max ? max : i;
}

/**
 * notify_low function
 *
 * This function sends a low-priority notification to the user. The notification
 * includes an icon, a title, and a message. If the icon is NULL or 0, a default
 * icon will be used. The notification is sent using the system() call.
 *
 * Parameters:
 *
 * - const char *icon:
 *   The icon to display with the notification. If NULL or 0, a default icon is used.
 *
 * - const char *title:
 *   The title of the notification.
 *
 * - const char *message:
 *   The message content of the notification.
 *
 * - Returns:
 *   - void:
 *     This function does not return a value.
 */
void notify_low(const char *icon, const char *title, const char *message);

/**
 * notify_normal function
 *
 * This function sends a normal-priority notification to the user. The notification
 * includes an icon, a title, and a message. If the icon is NULL or 0, a default
 * icon will be used. The notification is sent using the system() call.
 *
 * Parameters:
 *
 * - const char *icon:
 *   The icon to display with the notification. If NULL or 0, a default icon is used.
 *
 * - const char *title:
 *   The title of the notification.
 *
 * - const char *message:
 *   The message content of the notification.
 *
 * - Returns:
 *   - void:
 *     This function does not return a value.
 */
void notify_normal(const char *icon, const char *title, const char *message);

/**
 * notify_critical function
 *
 * This function sends a critical-priority notification to the user. The notification
 * includes an icon, a title, and a message. If the icon is NULL or 0, a default
 * icon will be used. The notification is sent using the system() call.
 *
 * Parameters:
 *
 * - const char *icon:
 *   The icon to display with the notification. If NULL or 0, a default icon is used.
 *
 * - const char *title:
 *   The title of the notification.
 *
 * - const char *message:
 *   The message content of the notification.
 *
 * - Returns:
 *   - void:
 *     This function does not return a value.
 */
void notify_critical(const char *icon, const char *title, const char *message);

 /**
 * MetricCollector periodic
 *
 * This function will apply a periodic interval to a metric collector such that it is only called
 * every 'interval' seconds.
 *
 * Parameters:
 *
 * - MetricCollector* collector
 *   A pointer to a MetricCollector to which the schedule will be applied.
 *
 * - const int interval:
 *   An integer that specifies the interval, in seconds, at which this collector should be updated.
 *
 * Returns:
 *   The same pointer as passed in as the MetricCollector.
 */
MetricCollector *periodic(MetricCollector* collector, const int interval);

 /**
 * MetricCollector onsignal
 *
 * This function will setup a signal handler that, when signaled, will trigger an update to the
 * given collector.
 *
 * Parameters:
 *
 * - MetricCollector* collector
 *   A pointer to a MetricCollector to which the schedule will be applied.
 *
 * - const int rtsig:
 *   An integer between SIGRTMIN and SIGRTMAX that identifies the value of the signal handler
 *   associated with this metric collector. Be sure that this value is unique to all other
 *   collectors.
 *
 * Returns:
 *   The same pointer as passed in as the MetricCollector.
 */
MetricCollector *onsignal(MetricCollector* collector, const int rtsig);

#endif

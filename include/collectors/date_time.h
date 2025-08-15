#ifndef COLLECTORS_TIME_H
#define COLLECTORS_TIME_H

#include "core.h"

/**
 * DateTimeCollector Structure
 *
 * This structure represents a specialized metric collector that is designed to
 * gather date and time. This collector allows you to specify the output format
 * and the timezone. You can have more than one of these components.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors.
 *   This includes the update mechanism and status management.
 *
 * - const char *strfmt:
 *   A string format specifier used to define how the time metrics should be formatted
 *   when collected. This allows for customization of the output representation of time.
 *   Example: "%I:%M %p" -> "04:32 PM"
 *
 * - const char *tzone:
 *   A string representing the timezone in which the time metrics are collected. This
 *   ensures that the collected time data is relevant to the specified timezone,
 *   facilitating accurate time reporting and analysis.
 *   Example: "America/Los_Angeles"
 */
typedef struct {
    MetricCollector base;
    const char *strfmt;
    const char *tzone;
} DateTimeCollector ;

/**
 * new_date_time_collector_tz Function
 *
 * This function creates and initializes a new instance of a DateTimeCollector,
 * which is responsible for collecting and formatting date and time metrics.
 * The collector is configured with a specified string format and timezone,
 * allowing for customized output of the collected time data.
 *
 * Parameters:
 *
 * - const char *strfmt:
 *   A string format specifier that defines how the date and time metrics should
 *   be formatted. This format will be used when generating the output for the
 *   collected metrics.
 *   Example: "%I:%M %p" -> "04:32 PM"
 *
 * - const char *tzone:
 *   A string representing the timezone in which the date and time metrics will
 *   be collected. This ensures that the metrics are relevant to the specified
 *   timezone, facilitating accurate time reporting.
 *   Example: "America/Los_Angeles"
 *
 * Returns:
 *
 * - A DateTimeCollector instance that is initialized with the provided format
 *   and timezone. The caller is responsible for managing the lifecycle of the
 *   returned collector.
 */
DateTimeCollector new_date_time_colector_tz(const char *strfmt, const char *tzone);

/**
 * new_date_time_collector Function
 *
 * This function creates and initializes a new instance of a DateTimeCollector,
 * which is responsible for collecting and formatting date and time metrics.
 * The collector is configured with a specified string format allowing for
 * customized output of the collected time data.
 *
 * Parameters:
 *
 * - const char *strfmt:
 *   A string format specifier that defines how the date and time metrics should
 *   be formatted. This format will be used when generating the output for the
 *   collected metrics.
 *   Example: "%I:%M %p" -> "04:32 PM"
 *
 * Returns:
 *
 * - A DateTimeCollector instance that is initialized with the provided format.
 *   The caller is responsible for managing the lifecycle of the returned
 *   collector.
 */
DateTimeCollector new_date_time_colector(const char *strfmt);

#endif

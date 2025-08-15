#ifndef COLLECTORS_DUMMY_H
#define COLLECTORS_DUMMY_H

#include "core.h"

/**
 * new_label Function
 *
 * This function creates and initializes a new instance of a simple label collector,
 * which is used for adding labels, spaces, and separators between other metric collectors.
 * Unlike other collectors, the update function is never called for this label, as its
 * primary purpose is to provide a visual or organizational aid in the output of metrics.
 *
 * Parameters:
 *
 * - const char *value:
 *   A string representing the label's value. This value will be displayed as part of
 *   the metric output, serving as a descriptive or decorative element to enhance
 *   readability and organization.
 *
 * Returns:
 *
 * - A MetricCollector instance that is initialized as a label with the provided value.
 *   The caller is responsible for managing the lifecycle of the returned collector.
 */
MetricCollector new_label(const char *value);

#endif

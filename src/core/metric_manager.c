#include <stdbool.h>
#include <stdio.h>

#include "core.h"


static void update(MetricManager *self) {

    OutputStrategy *op = self->output_strategy;

    int offset = 0;
    self->status[0] = '\0';

    for (int i = 0; i < self->collector_count; i++) {

        MetricCollector *mc = self->collectors[i];

        /**
         * Conditionally update the collector depending on the interval.
         *
         * interval = a, b
         * a is the scheduled interval
         * b is the current interval.
         *
         * if b = -1, update will never be called and b will never change.
         * else if a = 0 and b = 0, update once. then be is set to -1
         * else if a equals b, we trigger an update and reset b to 1
         * else, we move the interval forward by incrementing b
         */

        if (mc->interval[1] == -1) {
            // update never called.
        } else if (mc->interval[0] == mc->interval[1]) {
            mc->update(mc);
            mc->interval[1] = mc->interval[0] > 0 ? 1 : -1;
        } else {
            mc->interval[1]++;
        }

        /**
         * Append to the output status
         * Keep track of the offset for the next collector.
         */
        offset += snprintf(
            self->status + offset,
            sizeof(self->status) - offset,
            "%s",
            mc->status
        );
    }
    op->set_status(op, self->status);
}


MetricManager new_metric_manager(OutputStrategy *output_strategy, MetricCollector **collectors, int count) {
    return (MetricManager){
        .update = update,
        .output_strategy = output_strategy,
        .collectors = collectors,
        .collector_count = count,
    };
}

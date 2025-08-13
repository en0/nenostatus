#include <stdbool.h>
#include <stdio.h>

#include "core.h"

static void run_step(MetricManager *self) {
    int offset = 0;
    self->status[0] = '\0';
    for (int i = 0; i < self->collector_count; i++) {
        MetricCollector *mc = self->collectors[i];
        mc->update(mc);
        offset += snprintf(
            self->status + offset,
            sizeof(self->status) - offset,
            "%s%s",
            i == 0 ? "" : self->sep,
            mc->status
        );
    }
}

static void run(MetricManager *self) {
    OutputStrategy *op = self->output_strategy;
    while(true) {
        run_step(self);
        op->set_status(op, self->status);
    }
}

MetricManager new_metric_manager(OutputStrategy *output_strategy, MetricCollector **collectors, int count) {
    return (MetricManager){
        .run = run,
        .sep = " | ",
        .output_strategy = output_strategy,
        .collectors = collectors,
        .collector_count = count,
    };
}

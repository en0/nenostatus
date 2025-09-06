#include "core.h"

static inline void set_collector_interval(MetricCollector *self, int seconds) {
    self->interval[0] = seconds;
    self->interval[1] = seconds;
}

void initialize_collector_base(MetricCollector *self, int seconds, void (*update)(MetricCollector *self)) {
    self->status[0] = '\0';
    self->update = update;
    set_collector_interval(self, seconds);
}

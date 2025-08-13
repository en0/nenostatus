#include "core.h"


static void set_collector_interval(MetricCollector *self, int seconds) {
    self->interval[0] = seconds;
    self->interval[1] = seconds;
}

void initialize_collector_base(MetricCollector *self, const char *name, int seconds, void (*update)(MetricCollector *self)) {
    self->name = name;
    self->status[0] = '\0';
    self->update = update;
    self->set_interval = set_collector_interval;
    set_collector_interval(self, seconds);
}

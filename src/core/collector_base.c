#include "core.h"

void initialize_collector_base(MetricCollector *self, void (*update)(MetricCollector *self)) {
    self->status[0] = '\0';
    self->update = update;
    periodic(self, -1);
}

#include <stdio.h>

#include "collectors/dummy.h"


static void update(MetricCollector *self) {
    DummyCollector *s = (DummyCollector *)self;
    sprintf(self->status, "%s says %i", self->name, s->v);
}

// DummyCollector new_dummy_collector(const char *name, int v) {
//     return (DummyCollector){
//         .base.name = name,
//         .base.interval = {0, 60},
//         .base.update = update,
//         .v = v,
//     };
// }

DummyCollector new_dummy_collector(const char *name, int v) {
    DummyCollector ret = {.v = v};
    initialize_collector_base(&ret.base, name, 60, update);
    return ret;
}

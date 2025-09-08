#include <stdio.h>

#include "core.h"


MetricCollector new_label(const char *value) {
    MetricCollector ret = {0};
    initialize_collector_base(&ret, 0);
    sprintf(ret.status, "%s", value);
    return ret;
}

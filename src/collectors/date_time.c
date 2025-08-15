#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "collectors/date_time.h"
#include "core.h"


static void update(MetricCollector *self) {

    DateTimeCollector *s = (DateTimeCollector *)self;

    time_t raw_time;
    struct tm *time_info;

    if (s->tzone != NULL)
        setenv("TZ", s->tzone, 1);

    time(&raw_time);
    time_info = localtime(&raw_time);

    if (time_info == NULL) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "time module error");
    } else {
        strftime(self->status, MAX_COLLECTOR_STATUS_SIZE, s->strfmt, time_info);
    }
}

DateTimeCollector new_date_time_colector_tz(const char *strfmt, const char *tzone) {
    DateTimeCollector ret = {.strfmt = strfmt, .tzone = tzone};
    initialize_collector_base(&ret.base, "Date Time Collector", 30, update);
    return ret;
}

DateTimeCollector new_date_time_colector(const char *strfmt) {
    DateTimeCollector ret = {.strfmt = strfmt, .tzone = NULL};
    initialize_collector_base(&ret.base, "Date Time Collector", 30, update);
    return ret;
}

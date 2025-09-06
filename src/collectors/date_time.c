#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "collectors/date_time.h"
#include "core.h"


static void update(MetricCollector *self) {

    DateTimeCollector *s = (DateTimeCollector *)self;

    time_t raw_time;
    struct tm *time_info;

    time(&raw_time);
    time_info = localtime(&raw_time);

    if (time_info == NULL) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
    } else {
        strftime(self->status, MAX_COLLECTOR_STATUS_SIZE, s->strfmt, time_info);
    }
}

DateTimeCollector new_date_time_colector_tz(const int interval, const char *strfmt, const char *tzone) {
    DateTimeCollector ret = {.strfmt = strfmt};
    initialize_collector_base(&ret.base, interval, update);
    setenv("TZ", tzone, 1);
    tzset();
    return ret;
}

DateTimeCollector new_date_time_colector(const int interval, const char *strfmt) {
    DateTimeCollector ret = {.strfmt = strfmt};
    initialize_collector_base(&ret.base, interval, update);
    return ret;
}

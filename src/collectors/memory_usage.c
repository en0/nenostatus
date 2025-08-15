#include <stdio.h>
#include <sys/sysinfo.h>

#include "collectors/memory_usage.h"
#include "core.h"

#define MEMORY_BAR_WIDTH 30

static void update(MetricCollector *self) {

    struct sysinfo memInfo;

    if (sysinfo(&memInfo) != 0) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    long total_memory = memInfo.totalram;
    long free_memory = memInfo.freeram;
    long used_memory = total_memory - free_memory;


    // Convert bytes to megabytes for easier readability
    // total_memory /= (1024 * 1024);
    // free_memory /= (1024 * 1024);
    // used_memory /= (1024 * 1024);

    // snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "Memory: %ld MB used, %ld MB free, %ld MB total",
    //          used_memory, free_memory, total_memory);

    char buffer[MEMORY_BAR_WIDTH + 1] = {'\0'};

    int d = (used_memory * MEMORY_BAR_WIDTH) / (double)total_memory;
    for (int i = 0; i < MEMORY_BAR_WIDTH; i++) {
        if (i < d)
            buffer[i] = '=';
        else
            buffer[i] = '-';
    }

    // Uses these chars...
    // ""
    // Why is this off from what 'free' shows?
    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "  %lf GB [%s]", used_memory / (1024.0*1024.0*1024.0), buffer);
}

MemoryUsageCollector new_memory_usage_collector(void) {
    MemoryUsageCollector ret;
    initialize_collector_base(&ret.base, "Memory Usage Collector", 30, update);
    return ret;
}

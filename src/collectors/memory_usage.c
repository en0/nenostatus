#include <math.h>
#include <stdio.h>
#include <sys/sysinfo.h>

#include "collectors/memory_usage.h"
#include "core.h"

#define MEMORY_BAR_WIDTH 15


static void update(MetricCollector *self) {

    char utilization_bar[MEMORY_BAR_WIDTH*3+1] = {0};
    long memTotal, memFree, memBuffers, memCached, memAvailable, memUsed;

    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    fscanf(fp, "MemTotal: %ld kB\n", &memTotal);
    fscanf(fp, "MemFree: %ld kB\n", &memFree);
    fscanf(fp, "MemAvailable: %ld kB\n", &memAvailable);
    fscanf(fp, "Buffers: %ld kB\n", &memBuffers);
    fscanf(fp, "Cached: %ld kB\n", &memCached);
    fclose(fp);

    memUsed = memTotal - memFree - memBuffers - memCached;

    render_bar(utilization_bar, sizeof(utilization_bar), memUsed, memTotal);
    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, " %.2f GB %s", memUsed/(1024.0*1024.0), utilization_bar);
}

MemoryUsageCollector new_memory_usage_collector(void) {
    MemoryUsageCollector ret;
    initialize_collector_base(&ret.base, "Memory Usage Collector", 10, update);
    return ret;
}

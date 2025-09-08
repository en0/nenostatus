#include <stdio.h>
#include <sys/sysinfo.h>

#include "collectors/memory_usage.h"
#include "core.h"

static const char *ICON_SET[] = { "󰫃", "󰫄", "󰫅", "󰫆", "󰫇", "󰫈", };
#define ICON_SET_SIZE ((sizeof(ICON_SET)/sizeof(ICON_SET[0]))-1)

static void update(MetricCollector *self) {

    long memTotal, memFree, memBuffers, memCached, memAvailable, memUsed;
    int icon_index;

    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR: File not found");
        return;
    }

    int rc = fscanf(
        fp, "MemTotal: %ld kB\nMemFree: %ld kB\nMemAvailable: %ld kB\nBuffers: %ld kB\nCached: %ld kB\n",
        &memTotal, &memFree, &memAvailable, &memBuffers, &memCached
    );

    fclose(fp);

    if (rc != 5) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    memUsed = memTotal - memFree - memBuffers - memCached;
    icon_index = iclamp((ICON_SET_SIZE * memUsed) / memTotal, 0, ICON_SET_SIZE - 1);

    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%.2f GB %s", memUsed/(1024.0*1024.0), ICON_SET[icon_index]);
}

MemoryUsageCollector new_memory_usage_collector() {
    MemoryUsageCollector ret;
    initialize_collector_base(&ret.base, update);
    return ret;
}

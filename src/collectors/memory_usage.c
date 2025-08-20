#include <stdio.h>
#include <sys/sysinfo.h>

#include "collectors/memory_usage.h"
#include "core.h"


//static const char *ICON_SET[] = { "󰪞", "󰪟", "󰪠", "󰪡", "󰪢", "󰪣", "󰪤", "󰪥" };
static const char *ICON_SET[] = { "󰫃", "󰫄", "󰫅", "󰫆", "󰫇", "󰫈", };
#define ICON_SET_SIZE ((sizeof(ICON_SET)/sizeof(ICON_SET[0]))-1)

static void update(MetricCollector *self) {

    long memTotal, memFree, memBuffers, memCached, memAvailable, memUsed;
    int icon_index;

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
    icon_index = (ICON_SET_SIZE * memUsed) / memTotal;

    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, " %.2f GB %s", memUsed/(1024.0*1024.0), ICON_SET[icon_index]);
}

MemoryUsageCollector new_memory_usage_collector(void) {
    MemoryUsageCollector ret;
    initialize_collector_base(&ret.base, "Memory Usage Collector", 10, update);
    return ret;
}

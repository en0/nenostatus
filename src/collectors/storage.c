#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/statvfs.h>

#include "core.h"
#include "collectors/storage.h"

static void update(MetricCollector *self) {
    StorageCollector *s = (StorageCollector *)self;
    struct statvfs stat;

    if (statvfs(s->path, &stat) != 0) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    // Calculate the storage utilization percentage
    unsigned long total = stat.f_blocks * stat.f_frsize;
    unsigned long free = stat.f_bfree * stat.f_frsize;
    unsigned long used = total - free;
    double utilization = (double)used / total * 100.0;

    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%.0f%%", round(utilization));
}

StorageCollector new_storage_collector(const char *path) {
    StorageCollector ret = {.path = path};
    initialize_collector_base(&ret.base, update);
    return ret;
}

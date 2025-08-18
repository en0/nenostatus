#include <bits/time.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "collectors/cpu_load.h"
#include "core.h"


const static char *ICON_SET[] = {
    "▁", "▂", "▃", "▄",
    "▅", "▆", "▇", "█",
};


static uint64_t get_nanoseconds() {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (tp.tv_sec * 1000000000) + tp.tv_nsec;
}

static inline int iclamp(int value, int min, int max) {
    const int i = value < min ? min : value;
    return i > max ? max : i;
}


static void update(MetricCollector *self) {
    CPULoadCollector *s = (CPULoadCollector *)self;
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    char graph_buffer[(MAX_CPU_CORES*3)+1] = {0};
    uint64_t total_nsec = get_nanoseconds();
    uint64_t elapsed_time = total_nsec - s->lastClockTime;
    s->lastClockTime = total_nsec;

    int core, rc;
    long user, nice, system, garbage;
    uint64_t core_load_ns;
    size_t offset = 0;

    rc = fscanf(
        fp,
        "cpu %li %li %li %li %li %li %li %li %li %li\n",
        &garbage, &garbage, &garbage, &garbage, &garbage,
        &garbage, &garbage, &garbage, &garbage, &garbage
    );
    if (rc != 10) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        fclose(fp);
        return;
    }

    double total_cpu_load = 0;
    for(int i = 0; i < MAX_CPU_CORES; i++) {
        rc = fscanf(
            fp,
            "cpu%i %li %li %li %li %li %li %li %li %li %li\n",
            &core, &user, &nice, &system, &garbage, &garbage,
            &garbage, &garbage, &garbage, &garbage, &garbage
        );
        if (rc != 11) break;

        // Convert cpu load from ticks to nanoseconds.
        core_load_ns = ((user + nice + system) - s->metrics[core]) * (1e9 / s->user_hz);

        // Get the index for the icon set and append the icon to the graph_buffer.
        int d = iclamp(ceil((7 * core_load_ns) / (double)elapsed_time), 0, 7);
        append_to_buffer(graph_buffer, MAX_COLLECTOR_STATUS_SIZE, &offset, "%s", ICON_SET[d]);

        // Store the metric for this core for the next calculation
        s->metrics[core] = (user + nice + system);

        // Keep a total of the cpu load so we can compute a system-wide average.
        total_cpu_load += (core_load_ns / (double)elapsed_time);
    }

    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, " %.0lf%% %s", (total_cpu_load / (core+1)* 100), graph_buffer);
    fclose(fp);
}

CPULoadCollector new_cpu_load_collector() {
    CPULoadCollector ret = {0};
    initialize_collector_base(&ret.base, "CPU Load", 1, update);
    ret.user_hz = sysconf(_SC_CLK_TCK);
    return ret;
}

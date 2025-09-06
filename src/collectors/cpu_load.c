#include <bits/time.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "collectors/cpu_load.h"
#include "core.h"

// The graph uses unicode characters so each core will need 3 chars worth
// of space. In addition the space for each core's visualization, we need
// one additional char to hold the null terminator.
#define GRAPH_BUFFER_SIZE ((MAX_CPU_CORES * 3) + 1)

// Icon set used to visualize the load for each core.
#define ICON_SET_SIZE 3
const static char *ICON_SET[] = {
    "𜺀", "𜺄", "𜺅",
    "𜺈", "𜺌", "𜺍",
    "𜺊", "𜺎", "𜺏",
};

static inline uint64_t get_elapsed_time(CPULoadCollector *collector) {
    struct timespec tp;
    if (clock_gettime(CLOCK_MONOTONIC, &tp) == -1) return 0;
    uint64_t clock_time_ns = (tp.tv_sec * 1000000000) + tp.tv_nsec;
    uint64_t elapsed_time_ns = clock_time_ns - collector->lastClockTime;
    collector->lastClockTime = clock_time_ns;
    return elapsed_time_ns;
}

static inline int get_core_ticks(FILE *fp, uint64_t *core_time) {

    int core_id, read_count;
    long user_time, nice_time, system_time, _;

    if (ftell(fp) == 0) {
        // Read past the first line - it's not useful to us.
        read_count = fscanf(
            fp, "cpu %li %li %li %li %li %li %li %li %li %li\n",
            &_, &_, &_, &_, &_, &_, &_, &_, &_, &_
        );
    }

    read_count = fscanf(
        fp, "cpu%i %li %li %li %li %li %li %li %li %li %li\n",
        &core_id, &user_time, &nice_time, &system_time,
        &_, &_, &_, &_, &_, &_, &_
    );

    if (read_count != 11)
        return -1;

    *core_time = user_time + nice_time + system_time;
    return core_id;
}

static void update(MetricCollector *self) {

    CPULoadCollector *s = (CPULoadCollector *)self;

    // Buffer used to store the visualized output of each CPU core and an
    // offset used to keep track during append operations.
    char graph_buffer[GRAPH_BUFFER_SIZE] = {0};
    size_t graph_buffer_offset = 0;

    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    uint64_t elapsed_time = get_elapsed_time(s);

    uint64_t core_ticks, core_time_ns;
    double total_cpu_load = 0;
    int core_id;
    int x, y;

    for(core_id = 0; core_id < MAX_CPU_CORES; core_id++) {

        // Collect the core_ticks for the next core.
        if (get_core_ticks(fp, &core_ticks) == -1) break;

        // Compute the tick delta and convert to nanoseconds. Store for next update.
        core_time_ns = (core_ticks - s->metrics[core_id]) * (1e9 / s->user_hz);
        s->metrics[core_id] = core_ticks;

        // Get the index for the icon set and append the icon to the graph_buffer.
        if (core_id % 2 == 0) {
            x = iclamp(ceil(((ICON_SET_SIZE - 1) * core_time_ns) / (double)elapsed_time), 0, (ICON_SET_SIZE - 1));
        } else {
            y = iclamp(ceil(((ICON_SET_SIZE - 1) * core_time_ns) / (double)elapsed_time), 0, (ICON_SET_SIZE - 1));
            append_to_buffer(graph_buffer, MAX_COLLECTOR_STATUS_SIZE, &graph_buffer_offset, "%s", ICON_SET[(y * ICON_SET_SIZE) + x]);
        }

        // Keep a total of the cpu load so we can compute a system-wide average.
        total_cpu_load += (core_time_ns / (double)elapsed_time);
    }

    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "%.0lf%% %s", (total_cpu_load / core_id* 100), graph_buffer);
    fclose(fp);
}

CPULoadCollector new_cpu_load_collector(const int interval) {
    CPULoadCollector ret = {0};
    initialize_collector_base(&ret.base, interval, update);
    ret.user_hz = sysconf(_SC_CLK_TCK);
    return ret;
}

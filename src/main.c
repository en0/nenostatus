#include "cli.h"
#include "core.h"
#include "collectors/cpu_load.h"
#include "collectors/date_time.h"
#include "collectors/label.h"
#include "collectors/memory_usage.h"


int main(int argc, char *argv[]) {

    MetricCollector sep = new_label("  ");

    DateTimeCollector date_time_local = new_date_time_colector(10, "%a %b %d %I:%M %p %Y");
    MemoryUsageCollector mem = new_memory_usage_collector(10);
    CPULoadCollector cpu = new_cpu_load_collector(1);

    MetricCollector *collectors[] = {
        (MetricCollector *)&cpu,
        (MetricCollector *)&sep,
        (MetricCollector *)&mem,
        (MetricCollector *)&sep,
        (MetricCollector *)&date_time_local,
    };

    ArgumentParser ap = new_cli_arg_parser();
    CommandLine cli = new_cli(stdout, stderr, &ap, collectors, sizeof(collectors)/sizeof(MetricCollector *));
    return cli.run(&cli, argc, argv);
}

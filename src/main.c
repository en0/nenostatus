#include <signal.h>

#include "cli.h"
#include "core.h"
#include "collectors/cpu_load.h"
#include "collectors/date_time.h"
#include "collectors/label.h"
#include "collectors/memory_usage.h"
#include "collectors/shell.h"

#define SCRIPT(p) new_shell_collector("~/.bin/status/" #p)
#define RTSIG(p) (SIGRTMIN+p)

int main(int argc, char *argv[]) {

    MetricCollector sep = new_label("  ");

    DateTimeCollector date_time_local = new_date_time_colector( "%a %b %d %I:%M %p %Y");
    MemoryUsageCollector mem = new_memory_usage_collector();
    CPULoadCollector cpu = new_cpu_load_collector();
    ShellCollector sound = SCRIPT("audio");

    MetricCollector *collectors[] = {
        onsignal(&sound.base, RTSIG(0)),      &sep,
        periodic(&cpu.base, 1),               &sep,
        periodic(&mem.base, 10),              &sep,
        periodic(&date_time_local.base, 10),//&sep,
    };

    ArgumentParser ap = new_cli_arg_parser();
    CommandLine cli = new_cli(stdout, stderr, &ap, collectors, sizeof(collectors)/sizeof(MetricCollector *));
    return cli.run(&cli, argc, argv);
}

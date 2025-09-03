#include "cli.h"
#include "collectors/audio_state.h"
#include "core.h"
#include "collectors/battery.h"
#include "collectors/cpu_load.h"
#include "collectors/date_time.h"
#include "collectors/label.h"
#include "collectors/memory_usage.h"
#include "collectors/thermal.h"


int main(int argc, char *argv[]) {

    MetricCollector sep = new_label("  ");
    MetricCollector space = new_label(" ");

    BatteryCollector bat0 = new_battery_collector("/sys/class/power_supply/BAT0");
    DateTimeCollector date_time_local = new_date_time_colector("%a %b %e %I:%M %p %Y");
    MemoryUsageCollector mem = new_memory_usage_collector();
    AudioStateCollector astate = new_audio_state_collector("default", "Master", "Capture");
    CPULoadCollector cpu = new_cpu_load_collector();
    ThermalCollector temp = new_thermal_collector("/sys/class/thermal/thermal_zone10/temp");

    MetricCollector *collectors[] = {
        (MetricCollector *)&space,
        (MetricCollector *)&astate,
        (MetricCollector *)&sep,
        (MetricCollector *)&cpu,
        (MetricCollector *)&sep,
        (MetricCollector *)&mem,
        (MetricCollector *)&sep,
        (MetricCollector *)&temp,
        (MetricCollector *)&sep,
        (MetricCollector *)&bat0,
        (MetricCollector *)&sep,
        (MetricCollector *)&date_time_local,
        (MetricCollector *)&space,

    };

    ArgumentParser ap = new_cli_arg_parser();
    CommandLine cli = new_cli(stdout, stderr, &ap, collectors, sizeof(collectors)/sizeof(MetricCollector *));
    return cli.run(&cli, argc, argv);
}

#include "cli.h"
#include "collectors/cpu_load.h"
#include "collectors/storage.h"
#include "collectors/system_volume.h"
#include "collectors/thermal.h"
#include "core.h"
#include "collectors/ip_address.h"
#include "collectors/date_time.h"
#include "collectors/label.h"
#include "collectors/battery.h"
#include "collectors/memory_usage.h"


int main(int argc, char *argv[]) {

    MetricCollector sep = new_label("  ");
    MetricCollector space = new_label(" ");

    BatteryCollector bat0 = new_battery_collector("/sys/class/power_supply/BAT0");
    DateTimeCollector date_time_local = new_date_time_colector("%a %b %e %I:%M %p %Y");
    IPAddressCollector wlp7s0 = new_ip_address_collector("wlp9s0");
    MemoryUsageCollector mem = new_memory_usage_collector();
    StorageCollector disk = new_storage_collector("/");
    SystemVolumeCollector avol = new_system_volume_collector("default", "Master");
    CPULoadCollector cpu = new_cpu_load_collector();
    ThermalCollector temp = new_thermal_collector("/sys/class/thermal/thermal_zone10/temp");

    MetricCollector *collectors[] = {
        (MetricCollector *)&space,
        (MetricCollector *)&avol,
        (MetricCollector *)&sep,
        (MetricCollector *)&wlp7s0,
        (MetricCollector *)&sep,
        (MetricCollector *)&disk,
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

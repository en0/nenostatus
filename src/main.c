#include "cli.h"
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
    IPAddressCollector wlp7s0 = new_ip_address_collector("wlp7s0");
    MemoryUsageCollector mem = new_memory_usage_collector();

    MetricCollector *collectors[] = {
        (MetricCollector *)&space,
        (MetricCollector *)&wlp7s0,
        (MetricCollector *)&sep,
        (MetricCollector *)&mem,
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

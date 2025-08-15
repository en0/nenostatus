#include "cli.h"
#include "collectors/date_time.h"
#include "core.h"
#include "collectors/label.h"
#include "collectors/battery.h"


int main(int argc, char *argv[]) {

    MetricCollector sep = new_label("  ");
    MetricCollector space = new_label(" ");

    BatteryCollector bat0 = new_battery_collector("/sys/class/power_supply/BAT0");
    DateTimeCollector date_time = new_date_time_colector("%a %b %e %I:%M %p %Y");

    MetricCollector *collectors[] = {
        (MetricCollector *)&space,
        (MetricCollector *)&bat0,
        (MetricCollector *)&sep,
        (MetricCollector *)&date_time,
        (MetricCollector *)&space,
    };

    ArgumentParser ap = new_cli_arg_parser();
    CommandLine cli = new_cli(stdout, stderr, &ap, collectors, sizeof(collectors)/sizeof(MetricCollector *));
    return cli.run(&cli, argc, argv);
}

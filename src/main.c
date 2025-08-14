#include "cli.h"
#include "core.h"
#include "collectors/label.h"


int main(int argc, char *argv[]) {

    MetricCollector cpu_load = new_label("cpu: 100%");
    MetricCollector memory = new_label("mem: 50%");
    MetricCollector temp = new_label("temp: 75c");

    MetricCollector *collectors[] = {
        (MetricCollector *)&cpu_load,
        (MetricCollector *)&memory,
        (MetricCollector *)&temp,
    };

    ArgumentParser ap = new_cli_arg_parser();
    CommandLine cli = new_cli(stdout, stderr, &ap, collectors, sizeof(collectors)/sizeof(MetricCollector *));
    return cli.run(&cli, argc, argv);
}

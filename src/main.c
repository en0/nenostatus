#include "cli.h"
#include "collectors/dummy.h"
#include "core.h"


int main(int argc, char *argv[]) {

    DummyCollector cpu_load = new_dummy_collector("cpu", 1);
    DummyCollector memory = new_dummy_collector("mem", 1);
    DummyCollector temp = new_dummy_collector("temp", 1);

    cpu_load.base.set_interval(&cpu_load.base, 2);
    memory.base.set_interval(&memory.base, 3);
    temp.base.set_interval(&temp.base, 4);

    MetricCollector *collectors[] = {
        (MetricCollector *)&cpu_load,
        (MetricCollector *)&memory,
        (MetricCollector *)&temp,
    };

    ArgumentParser ap = new_cli_arg_parser();
    CommandLine cli = new_cli(stdout, stderr, &ap, collectors, sizeof(collectors)/sizeof(MetricCollector *));
    return cli.run(&cli, argc, argv);
}

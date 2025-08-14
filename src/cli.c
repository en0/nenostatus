#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli.h"
#include "core.h"


static CliArgs parse_args(int argc, char* argv[]) {
    CliArgs ret = {0};
    for (int i = 1; i < argc; i++) {
        if (strcmp("--help", argv[i]) == 0)
            ret.show_help = true;
        else if (strcmp("-h", argv[i]) == 0)
            ret.show_help = true;
        else if (strcmp("--stdout", argv[i]) == 0)
            ret.use_stdout = true;
        else {
            ret.unknown_arg_index = i;
            break;
        }
    }
    return ret;
}

static void show_help(char *prog, FILE *file) {
    fprintf(file,
        "Usage:\n"
        "  %s [options]\n\n"
        "OPTIONS\n"
        "  -h --help        Show list of command-line options.\n"
        "  --stdout         Print status line to stdout.\n",
        prog
    );
}


ArgumentParser new_cli_arg_parser() {
    return (ArgumentParser){
        .parse = parse_args,
        .show_help = show_help,
    };
}


static int run(CommandLine *self, int argc, char *argv[]) {

    CliArgs opts = self->parser->parse(argc, argv);

    if (opts.show_help) {
        self->parser->show_help(argv[0], self->out);
        return EXIT_SUCCESS;
    }

    else if (opts.unknown_arg_index > 0) {
        fprintf(stderr, "Unknown argument: %s\n\n", argv[opts.unknown_arg_index]);
        self->parser->show_help(argv[0], self->err);
        return EXIT_INVALID_ARG;
    }

    OutputStrategy op = opts.use_stdout ? new_console_output() : new_xsetroot_output();
    MetricManager mc = new_metric_manager(&op, self->collectors, self->count);
    for (;;sleep(1)) mc.update(&mc);

	return EXIT_SUCCESS;
}


CommandLine new_cli(FILE *out, FILE *err, ArgumentParser *parser, MetricCollector **collectors, int count) {
    return (CommandLine){
        .out = out,
        .err = err,
        .parser = parser,
        .run = run,
        .collectors = collectors,
        .count = count
    };
}

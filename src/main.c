#include "cli.h"

#define EXIT_INVALID_ARG -1


int main(int argc, char *argv[]) {
    ArgumentParser ap = new_cli_arg_parser();
    CommandLine cli = new_cli(stdout, stderr, &ap);
    return cli.run(&cli, argc, argv);
}

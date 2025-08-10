#ifndef CLI_H
#define CLI_H

#define EXIT_INVALID_ARG -1

#include <stdbool.h>
#include <stdio.h>


/**
 * Flags for commandline options.
 */
typedef struct {
	bool show_help;
    int unknown_arg_index;
	bool use_stdout;
} CliArgs;


/**
 * ArgumentParser provides a parser for commandline options as well as a help
 * function.
 */
typedef struct ArgumentParser ArgumentParser;
struct ArgumentParser {
    CliArgs (*parse)(int argc, char *argv[]);
    void (*show_help)(char *prog, FILE *out);
};

/**
 * Create a ArgumentParser.
 */
ArgumentParser new_cli_arg_parser();


/**
 * CommandLine runs the cli interface.
 */
typedef struct CommandLine CommandLine;
struct CommandLine {
    FILE *out;
    FILE *err;
    ArgumentParser *parser;
    int (*run)(CommandLine *self, int argc, char *argv[]);
};


/**
 * Create a new CommandLine interface
 * @param out The file to use as stdout.
 * @param err The file to use as stderr.
 * @param parser the agrument parser to use.
 */
CommandLine new_cli(FILE *out, FILE *err, ArgumentParser *parser);

#endif

#ifndef CLI_H
#define CLI_H

#include "core.h"
#define EXIT_INVALID_ARG -1

#include <stdbool.h>
#include <stdio.h>


 /**
 * CliArgs Structure
 *
 * This structure represents the flags for command-line options. It holds information
 * about the user's input and the state of various command-line arguments.
 *
 * Members:
 *
 * - bool show_help:
 *   A boolean flag indicating whether the help message should be displayed. This is
 *   typically set when the user requests help via a command-line option.
 *
 * - int unknown_arg_index:
 *   An integer representing the index of the first unknown argument encountered in
 *   the command-line input. This can be used to identify and handle unexpected
 *   arguments gracefully.
 *
 * - bool use_stdout:
 *   A boolean flag indicating whether the output should be directed to standard output
 *   (stdout). This allows the program to determine the appropriate output stream based
 *   on user preferences or command-line options.
 */
typedef struct {
	bool show_help;
    int unknown_arg_index;
	bool use_stdout;
} CliArgs;


/**
 * ArgumentParser Structure
 *
 * This structure provides a parser for command-line options and includes a function
 * for displaying help information. It encapsulates the logic for parsing user input
 * and managing command-line arguments.
 *
 * Members:
 *
 * - CliArgs (*parse)(int argc, char *argv[]):
 *   A function pointer to the method responsible for parsing command-line arguments.
 *   This function takes the argument count and array as input and returns a CliArgs
 *   structure containing the parsed options.
 *
 * - void (*show_help)(char *prog, FILE *out):
 *   A function pointer to the method that displays the help message. This function
 *   takes the program name and an output stream as parameters, allowing it to print
 *   the help information to the specified output.
 */
typedef struct ArgumentParser ArgumentParser;
struct ArgumentParser {
    CliArgs (*parse)(int argc, char *argv[]);
    void (*show_help)(char *prog, FILE *out);
};

 /**
 * new_cli_arg_parser Function
 *
 * This function creates and initializes a new instance of an ArgumentParser,
 * which is responsible for parsing command-line options and providing help
 * functionality. The parser can be used to interpret user input and manage
 * command-line arguments effectively.
 *
 * Returns:
 *
 * - An ArgumentParser instance that is ready to parse command-line options.
 *   The caller is responsible for managing the lifecycle of the returned parser,
 *   including any necessary cleanup.
 */
ArgumentParser new_cli_arg_parser();


/**
 * CommandLine Structure
 *
 * This structure represents the command-line interface (CLI) for the application.
 * It manages the output streams, the argument parser, and the metric collectors,
 * providing a cohesive interface for running the CLI and processing user input.
 *
 * Members:
 *
 * - FILE *out:
 *   A pointer to the file stream used for standard output. This is where the
 *   application will print its output messages.
 *
 * - FILE *err:
 *   A pointer to the file stream used for standard error. This is where error
 *   messages and warnings will be printed.
 *
 * - ArgumentParser *parser:
 *   A pointer to the ArgumentParser instance that will be used to parse command-line
 *   options and manage user input.
 *
 * - MetricCollector **collectors:
 *   An array of pointers to MetricCollector instances that are available for use
 *   within the command-line interface.
 *
 * - int count:
 *   An integer representing the total number of collectors available. This is used
 *   to iterate through the collectors during execution.
 *
 * - int (*run)(CommandLine *self, int argc, char *argv[]):
 *   A function pointer to the method responsible for running the command-line interface.
 *   This function takes the CommandLine instance, argument count, and argument array
 *   as parameters, processing user input and executing the appropriate actions.
 */
typedef struct CommandLine CommandLine;
struct CommandLine {
    FILE *out;
    FILE *err;
    ArgumentParser *parser;
    MetricCollector **collectors;
    int count;
    int (*run)(CommandLine *self, int argc, char *argv[]);
};


/**
 * new_cli Function
 *
 * This function creates and initializes a new CommandLine interface, which manages
 * the interaction between the user and the application. It sets up the output streams,
 * argument parser, and available metric collectors, providing a cohesive environment
 * for running the CLI.
 *
 * Parameters:
 *
 * - FILE *out:
 *   The file stream to use as standard output for the command-line interface.
 *
 * - FILE *err:
 *   The file stream to use as standard error for the command-line interface.
 *
 * - ArgumentParser *parser:
 *   A pointer to the ArgumentParser instance that will be used for parsing command-line
 *   options.
 *
 * - MetricCollector **collectors:
 *   An array of pointers to MetricCollector instances that are available for use
 *   within the command-line interface.
 *
 * - int count:
 *   The total number of collectors in the provided array.
 *
 * Returns:
 *
 * - A CommandLine instance that is initialized with the specified output streams,
 *   argument parser, and collectors. The caller is responsible for managing the
 *   lifecycle of the returned command-line interface, including any necessary cleanup.
 */
CommandLine new_cli(FILE *out, FILE *err, ArgumentParser *parser, MetricCollector **collectors, int count);

#endif

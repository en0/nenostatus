#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <stdio.h>

#include "cli.h"

ArgumentParser ap;

int setup(void) {
    ap = new_cli_arg_parser();
    return 0;
}

int teardown(void) {
    return 0;
}

static void test_parse_args_defaults() {
    // Test that no arguments produce default options.
    char *argv[] = {"unittest"};
    CliArgs opts = ap.parse(1, argv);
    CU_ASSERT_EQUAL(opts.show_help, false);
    CU_ASSERT_EQUAL(opts.use_stdout, false);
    CU_ASSERT_EQUAL(opts.unknown_arg_index, 0);
}

static void test_parse_args_show_help() {
    // Test that --help arg produces cli options with show_help set to true.
    char *argv[] = {"unittest", "--help"};
    CliArgs opts = ap.parse(2, argv);
    CU_ASSERT_EQUAL(opts.show_help, true);
    CU_ASSERT_EQUAL(opts.use_stdout, false);
    CU_ASSERT_EQUAL(opts.unknown_arg_index, 0);
}

static void test_parse_args_use_stdout() {
    // Test that --stdout arg produces cli options with use_stdout set to true.
    char *argv[] = {"unittest", "--stdout"};
    CliArgs opts = ap.parse(2, argv);
    CU_ASSERT_EQUAL(opts.show_help, false);
    CU_ASSERT_EQUAL(opts.use_stdout, true);
    CU_ASSERT_EQUAL(opts.unknown_arg_index, 0);
}

static void test_parse_args_use_stdout_show_help() {
    // Test that --stdout and --help args produces cli options with use_stdout and
    // show_help set to true.
    char *argv[] = {"unittest", "--help", "--stdout"};
    CliArgs opts = ap.parse(3, argv);
    CU_ASSERT_EQUAL(opts.show_help, true);
    CU_ASSERT_EQUAL(opts.use_stdout, true);
    CU_ASSERT_EQUAL(opts.unknown_arg_index, 0);
}

static void test_parse_args_unknown_arg_index() {
    // Test unkonwn args set unknown_arg_index to the index of the unknown argument.
    char *argv[] = {"unittest", "--help", "--stdout", "--foo"};
    CliArgs opts = ap.parse(4, argv);
    CU_ASSERT_EQUAL(opts.unknown_arg_index, 3);
}

static void test_parse_args_stops_on_first_unknown() {
    // Test unkonwn args set unknown_arg_index to the index of the first unknown argument.
    char *argv[] = {"unittest", "--bar", "--stdout", "--foo"};
    CliArgs opts = ap.parse(4, argv);
    CU_ASSERT_EQUAL(opts.unknown_arg_index, 1);
}

static void test_show_help() {
    // Verify show_help prints expected output.
    char buffer[256];
    FILE *output = fmemopen(buffer, sizeof(buffer), "w");
    ap.show_help("unittest", output);
    fclose(output);
    CU_ASSERT_STRING_EQUAL(buffer,
        "Usage:\n"
        "  unittest [options]\n\n"
        "OPTIONS\n"
        "  -h --help        Show list of command-line options.\n"
        "  --stdout         Print status line to stdout.\n"
    );
}

void cli_test_suite() {
	CU_pSuite suite = CU_add_suite("core/cli Test Suite", setup, teardown);

    // parse_args
	CU_add_test(suite, "[parse_args()]", test_parse_args_defaults);
	CU_add_test(suite, "[parse_args(--help)]", test_parse_args_show_help);
	CU_add_test(suite, "[parse_args(--stdout)]", test_parse_args_use_stdout);
	CU_add_test(suite, "[parse_args(--help, --stdout)]", test_parse_args_use_stdout_show_help);
	CU_add_test(suite, "[parse_args(--help, --stdout, --foo)]", test_parse_args_unknown_arg_index);
	CU_add_test(suite, "[parse_args(--bar ,--stdout, --foo)]", test_parse_args_stops_on_first_unknown);

    // show_help
    CU_add_test(suite, "[show_help (unittest, OUT)]", test_show_help);
}

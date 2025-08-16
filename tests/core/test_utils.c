#include "core.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>


static void test_append_to_buffer() {
    char buffer[64] = {0};
    size_t offset = 0;
    int result = append_to_buffer(buffer, 64, &offset, "%s", "Hello");
    CU_ASSERT_STRING_EQUAL(buffer, "Hello");
    CU_ASSERT_EQUAL(result, 5);
    CU_ASSERT_EQUAL(offset, 5);
}

static void test_append_to_buffer_twice() {
    char buffer[64] = {0};
    size_t offset = 0;
    int result = 0;
    result += append_to_buffer(buffer, 64, &offset, "%s", "Hello");
    result += append_to_buffer(buffer, 64, &offset, "%s", ", world!");
    CU_ASSERT_STRING_EQUAL(buffer, "Hello, world!");
    CU_ASSERT_EQUAL(result, 13);
    CU_ASSERT_EQUAL(offset, 13);
}

static void test_append_to_buffer_exceed_limit() {
    char buffer[10] = {0};
    size_t offset = 0;
    int result = 0;
    result = append_to_buffer(buffer, 10, &offset, "%s", "Hello");
    result = append_to_buffer(buffer, 10, &offset, "%s", ", world!");
    CU_ASSERT_STRING_EQUAL(buffer, "Hello, wo");
    CU_ASSERT_EQUAL(result, -1);
    CU_ASSERT_EQUAL(offset, 5); // because offset is not set on the error.
}


void core_util_test_suite() {
	CU_pSuite suite = CU_add_suite("core/util", 0, 0);
	CU_ADD_TEST(suite, test_append_to_buffer);
    CU_ADD_TEST(suite, test_append_to_buffer_twice);
    CU_ADD_TEST(suite, test_append_to_buffer_exceed_limit);
}

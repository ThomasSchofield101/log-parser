#include "unity.h"

int main(void) {
    UNITY_BEGIN();
    
    // test_log_entry.c
    RUN_TEST(test_log_entry_from_line_info);
    RUN_TEST(test_log_entry_from_line_warn);
    RUN_TEST(test_log_entry_from_line_error);
    RUN_TEST(test_log_entry_from_line_unknown);
    RUN_TEST(test_log_entry_from_line_truncated_message);
    RUN_TEST(test_log_entry_from_line_empty_message);
    RUN_TEST(test_log_entry_from_line_invalid_format);
    RUN_TEST(test_log_entry_from_line_long_message);
    RUN_TEST(test_log_entry_from_line_edge_cases);

    return UNITY_END();
}


include "unity.h"
include "log_entry.h"

void test_log_entry_from_line_info(void) {
    
    char* line = "1622547800 INFO This is an info message";
    LogEntry entry = log_entry_from_line(line);

    TEST_ASSERT_EQUAL(1622547800, entry.timestamp);
    TEST_ASSERT_EQUAL(LOG_INFO, entry.level);
    TEST_ASSERT_EQUAL_STRING("This is an info message", entry.message);
}

void test_log_entry_from_line_warn(void) {
    
    char* line = "1622547801 WARN This is a warning message";
    LogEntry entry = log_entry_from_line(line);

    TEST_ASSERT_EQUAL(1622547801, entry.timestamp);
    TEST_ASSERT_EQUAL(LOG_WARN, entry.level);
    TEST_ASSERT_EQUAL_STRING("This is a warning message", entry.message);
}

void test_log_entry_from_line_error(void) {

    char* line = "1622547802 ERROR This is an error message";
    LogEntry entry = log_entry_from_line(line);

    TEST_ASSERT_EQUAL(1622547802, entry.timestamp);
    TEST_ASSERT_EQUAL(LOG_ERROR, entry.level);
    TEST_ASSERT_EQUAL_STRING("This is an error message", entry.message);
}

void test_log_entry_from_line_unknown(void) {
    
    char* line = "1622547803 UNKNOWN This is an unknown level message";
    LogEntry entry = log_entry_from_line(line);

    TEST_ASSERT_EQUAL(1622547803, entry.timestamp);
    TEST_ASSERT_EQUAL(LOG_UNKNOWN, entry.level);
    TEST_ASSERT_EQUAL_STRING("This is an unknown level message", entry.message);
}

void test_log_entry_from_line_truncated_message(void) {

    char* line = "1622547804 INFO This message is way too long and should be truncated at some point because it exceeds the maximum length allowed for a log entry message in our system which is set to 511 characters. Let's keep adding more text to ensure we exceed that limit and see how the function handles it. We will continue to add more text until we are sure that we have gone well beyond the limit of 511 characters. This should be enough to test the truncation functionality of our log entry parser, as long as i keep extending it until i hit over 511 characters which i should have by now.";
    TEST_ASSERT_TRUE(strlen(line) > 511); // Ensure the line is longer than 511 characters
    LogEntry entry = log_entry_from_line(line);

    TEST_ASSERT_EQUAL(1622547804, entry.timestamp);
    TEST_ASSERT_EQUAL(LOG_INFO, entry.level);
    TEST_ASSERT_EQUAL(511, strlen(entry.message)); // The message should be truncated to 511 characters
}

void test_log_entry_from_line_empty_message(void) {

    char* line = "1622547805 INFO ";
    LogEntry entry = log_entry_from_line(line);

    TEST_ASSERT_EQUAL(1622547805, entry.timestamp);
    TEST_ASSERT_EQUAL(LOG_INFO, entry.level);
    TEST_ASSERT_EQUAL_STRING("", entry.message); // The message should be empty

}

void test_log_entry_from_line_invalid_format(void) {

    char* line = "This is an invalid log entry format";
    LogEntry entry = log_entry_from_line(line);

    // Since the format is invalid, we expect the timestamp to be 0 and level to be LOG_UNKNOWN
    TEST_ASSERT_EQUAL(0, entry.timestamp);
    TEST_ASSERT_EQUAL(LOG_UNKNOWN, entry.level);
    TEST_ASSERT_EQUAL_STRING("", entry.message); // The message should be empty

}

void test_log_entry_from_line_long_message(void) {

    char* line = "1622547806 INFO This is a long message that should be fully captured by the log entry parser. It contains multiple sentences and should be handled correctly without any truncation or loss of information. The parser should be able to handle messages of this length without any issues, as long as they do not exceed the maximum allowed length for a log entry message in our system.";
    LogEntry entry = log_entry_from_line(line);

    TEST_ASSERT_EQUAL(1622547806, entry.timestamp);
    TEST_ASSERT_EQUAL(LOG_INFO, entry.level);
    TEST_ASSERT_EQUAL_STRING("This is a long message that should be fully captured by the log entry parser. It contains multiple sentences and should be handled correctly without any truncation or loss of information. The parser should be able to handle messages of this length without any issues, as long as they do not exceed the maximum allowed length for a log entry message in our system.", entry.message);

}
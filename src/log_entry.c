#include <string.h>

#include "log_entry.h"

LogEntry log_entry_from_line(const char *line) {
    LogEntry entry;
    
    long timestamp;
    char level_str[16];
    char message[512];

    sscanf(line, "%ld %15s %511[^\n]", &timestamp, level_str, message);

    entry.timestamp = timestamp;

    if (strcmp(level_str, "INFO") == 0) {
        entry.level = LOG_INFO;
    } else if (strcmp(level_str, "WARN") == 0) {
        entry.level = LOG_WARN;
    } else if (strcmp(level_str, "ERROR") == 0) {
        entry.level = LOG_ERROR;
    } else {
        entry.level = LOG_UNKNOWN; // Default to UNKNOWN if unknown
    }
    
    strncpy(entry.message, message, sizeof(entry.message) - 1);
    entry.message[sizeof(entry.message) - 1] = '\0'; // Ensure null-termination after truncation

    return entry;
}
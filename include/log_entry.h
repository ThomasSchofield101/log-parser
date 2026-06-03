#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

/**
* @brief Enumeration for possible log levels used throughout logging system.
 */
typedef enum {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_UNKNOWN
} LogLevel;

/**
* @brief Represents a single log entry in the system.
*
* Contains severity level, timestamp and message payload.
*/
typedef struct {
    LogLevel level; // log level (INFO, WARN, ERROR)
    long timestamp; // log message text
    char message[512]; // epoch time in seconds
} LogEntry;

/**
* @brief Parses a single line from the log file and constructs a LogEntry.
* @param line The line to parse.
* @return A LogEntry containing the parsed information.
*/
LogEntry log_entry_from_line(const char *line);

#endif // LOG_ENTRY_H
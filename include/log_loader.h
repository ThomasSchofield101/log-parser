#ifndef LOG_LOADER_H
#define LOG_LOADER_H

#include "log_entry.h"

/**
* @brief Parses a log file and processes each line.
* @param filename The path to the log file to parse.
* @param out_count A pointer to an integer where the number of log entries will be stored.
* @return An array of LogEntry structures containing the parsed log entries, or NULL on failure
*/
LogEntry* load_log_file(const char *filename, int *out_count);

/**
* @brief Reallocates the log entries array to accommodate more entries.
* @param entries The current array of log entries.
* @param new_size Inputs the current size of the entries array and stores the new size after reallocation.
* @return A pointer to the reallocated array of log entries, or NULL on failure.
 */
LogEntry* realloc_entries(LogEntry *entries, size_t *new_size);

#endif // LOG_LOADER_H
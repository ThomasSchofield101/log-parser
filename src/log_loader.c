#include <stdio.h>
#include <stdlib.h>

#include "log_loader.h"
#include "log_entry.h"

LogEntry* load_log_file (const char *filename, int *out_count) {
    if (filename == NULL) {
        fprintf(stderr, "Error: filename cannot be NULL\n");
        return NULL; // Handle null filename by returning NULL
    }

    if (out_count == NULL) {
        fprintf(stderr, "Error: out_count cannot be NULL\n");
        return NULL; // Handle null out_count by returning NULL
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        goto cleanup; // Handle file open failure by cleaning up and exiting
    }

    LogEntry *entries = NULL; 
    size_t entries_size = 64;
    entries = malloc(sizeof(LogEntry) * entries_size);
    if (!entries) {
        fprintf(stderr, "Error: could not allocate memory for log entries\n");
        goto cleanup; // Handle malloc failure by cleaning up and exiting
    }
    size_t entries_index = 0; 

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        LogEntry entry = log_entry_from_line(line);
        if (entries_index >= entries_size) {
            LogEntry *new_entries = realloc_entries(entries, &entries_size);
            if (!new_entries) {
                goto cleanup; // Handle realloc failure by cleaning up and exiting
            }
            entries = new_entries;
            entries[entries_index++] = entry;
        }
        else {
            entries[entries_index++] = entry;
        }
    }
    goto cleanup;

    cleanup:
        if (file)  fclose(file);

        if (entries && entries_index > 0) {
            *out_count = entries_index;
            return entries;
        } else if (entries && entries_index == 0) {
            fprintf(stderr, "Log file empty: %s\n", filename);
            *out_count = 0;
            return entries; // Return allocated array even if empty, caller can free it
        }
        else {
            *out_count = 0;
            return NULL;
        }
        
}

LogEntry* realloc_entries(LogEntry *entries, size_t *new_size) {
    *new_size *= 2; // Double the size for the new allocation
    LogEntry *new_entries = realloc(entries, *new_size * sizeof(LogEntry));
    if (new_entries == NULL) {
        fprintf(stderr, "Error: could not reallocate memory for log entries\n");
        return NULL;
    }
    return new_entries;
}



#include <stdio.h>

#include "log_loader.h"
#include "log_entry.h"

void parse_file (const char *filename) {
    if (filename == NULL) {
        fprintf(stderr, "Error: filename cannot be NULL\n");
        return;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        return;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        LogEntry entry = log_entry_from_line(line);
        // add to dynamic array
    }
    fclose(file);
}

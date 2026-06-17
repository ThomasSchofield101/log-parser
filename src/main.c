#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>

#include "log_entry.h"
#include "log_loader.h"

void print_usage(void) {
    fprintf(stderr, "Usage: logparser [OPTIONS] <logfile>\n");
    fprintf(stderr, " --level   LEVEL     Filter by log level (INFO, WARN, ERROR)\n");
    fprintf(stderr, " --keyword TEXT    Filter by keyword in message\n");
    fprintf(stderr, " --output  FILE     Write results to file\n");
}

void string_to_upper(char* string){
    for (; *string; string++){
            *string = toupper((unsigned char)*string);
    }
}

LogLevel parse_level(char* level){
    string_to_upper(level);
    if (strcmp(level, "INFO") == 0) return LOG_INFO;
    else if (strcmp(level, "WARN") == 0) return LOG_WARN;
    else if (strcmp(level, "ERROR") == 0) return LOG_ERROR;
    
    fprintf(stderr, "Error: Invalid level '%s'. Must be INFO, WARN, or ERROR.\n", level);
    return LOG_UNKNOWN;
}

char* level_to_string(LogLevel level){
    if (level == LOG_INFO) return "INFO";
    else if (level == LOG_WARN) return "WARN";
    else if (level == LOG_ERROR) return "ERROR";
    return "UNKNOWN";
}

int main (int argc, char *argv[]) {
    LogLevel level = LOG_UNKNOWN;
    char* keyword = NULL;
    char* output_file = NULL;
    FILE* file_ptr = NULL;

    struct option long_options[] = {
        {"level", required_argument, 0, 'l'},
        {"keyword", required_argument, 0, 'k'},
        {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };
    int opt;
    while ((opt = getopt_long(argc, argv, "l:k:o:", long_options, NULL)) != -1){
        switch (opt) {
            case 'l':
                level = parse_level(optarg);
                if (level == LOG_UNKNOWN) {
                    fprintf(stderr, "Error: invalid value for level.\n");
                    print_usage();
                    return 1;
                }
                break;
            case 'k':
                keyword = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case '?':
                print_usage();
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: No log file specified.\n");
        print_usage();
        return 1;
    }

    char* logfile = argv[optind];

    int count = 0;
    LogEntry* entries = load_log_file(logfile, &count);

    if (!entries) {
        fprintf(stderr, "Error: log file empty.\n");
        return 1;
    }

    if (output_file){
        file_ptr = fopen(output_file, "a");
        if (!file_ptr){
            fprintf(stderr, "Error: output file could not be opened.\n");
            return 1;
        }
    }

    for (int i = 0; i < count; i++){
        LogEntry* entry = &entries[i];

        if (level != LOG_UNKNOWN && entry->level != level) continue;
        if (keyword && strstr(entry->message, keyword) == NULL) continue;

        if (file_ptr) {
            fprintf(file_ptr, "%ld %s %s\n", entry->timestamp, level_to_string(entry->level), entry->message);
            
        } else {
            printf("%ld %s %s\n", entry->timestamp, level_to_string(entry->level), entry->message);
        }
    }
    
    if (file_ptr) fclose(file_ptr);
    free (entries);
    return 0;
}

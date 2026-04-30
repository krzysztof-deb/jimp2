#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

typedef struct {
    char* input_file;
    char* output_file;
    char* algorithm;
    char* format;
    bool verbose;
} AppConfig;

void print_help();
void parse_args(int argc, char* argv[], AppConfig* config);

#endif
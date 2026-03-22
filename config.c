#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

void print_help() {
    printf("Uzycie: graph_layout [opcje]\n");
    printf("Opcje:\n");
    printf("  -i <plik>      Plik wejsciowy zawierajacy graf\n");
    printf("  -o <plik>      Plik wyjsciowy z wynikami\n");
    printf("  -a <algorytm>  Wybor algorytmu (np. 'fr' lub 'tutte')\n");
    printf("  -f <format>    Format zapisu wynikow ('txt' lub 'bin')\n");
    printf("  -h             Wyswietlenie pomocy\n");
    printf("  -V             Tryb verbose\n");
}
void parse_args(int argc, char* argv[], AppConfig* config) {
    config->input_file = NULL;
    config->output_file = NULL;
    config->algorithm = "fr";
    config->format = "txt";
    config->verbose = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                config->input_file = argv[++i];
            }
            else {
                fprintf(stderr, "Error: brak argumentu dla opcji -i\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                config->output_file = argv[++i];
            }
            else {
                fprintf(stderr, "Error: brak argumentu dla opcji -o\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "-a") == 0) {
            if (i + 1 < argc) {
                config->algorithm = argv[++i];
            }
            else {
                fprintf(stderr, "Error: brak argumentu dla opcji -a\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                config->format = argv[++i];
            }
            else {
                fprintf(stderr, "Error: brak argumentu dla opcji -f\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(argv[i], "-V") == 0) {
            config->verbose = true;
        }
        else if (strcmp(argv[i], "-h") == 0) {
            print_help();
            exit(EXIT_SUCCESS);
        }
        else {
            fprintf(stderr, "Error: invalid arguments\n");
            exit(EXIT_FAILURE);
        }
    }
}
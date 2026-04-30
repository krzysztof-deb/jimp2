#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "reingold.h"
#include "tutte.h"
#include "config.h"
#include "planarnosc.h"







int main(int argc, char* argv[]) {
    AppConfig config;
    parse_args(argc, argv, &config);

    if (!config.input_file) {
        fprintf(stderr, "Error: input file not found\n");
        return EXIT_FAILURE;
    }

    Graph* g = create_graph();

    if (config.verbose) printf("Wczytywanie grafu z %s...\n", config.input_file);
    if (!read_graph(config.input_file, g)) {
        free_graph(g);
        return EXIT_FAILURE;
    }

    if (config.verbose) printf("Wczytano %d krawedzi i %d wierzcholkow.\n", g->num_edges, g->num_vertices);

    if (strcmp(config.algorithm, "fr") == 0) {
        if (config.verbose) printf("Uruchamianie algorytmu Fruchterman-Reingold...\n");
        layout_fruchterman_reingold(g);
    }
    else if (strcmp(config.algorithm, "tutte") == 0) {
        if (config.verbose) printf("Uruchamianie algorytmu Tutte embedding...\n");
        layout_tutte_embedding(g);
    }
    else {
        fprintf(stderr, "Error: unknown algorithm\n");
        free_graph(g);
        return EXIT_FAILURE;
    }

    if (is_planar(g)){
        if (config.output_file) {
            if (config.verbose) printf("Zapisywanie wynikow do %s (format: %s)...\n", config.output_file, config.format);
            if (strcmp(config.format, "bin") == 0) {
                save_graph_bin(config.output_file, g);
            }
            else {
                save_graph_txt(config.output_file, g);
            }
        }
    }
    else {
        fprintf(stderr, "Error: graph isn't plannary\n");
        free_graph(g);
        return EXIT_FAILURE;
    }

    free_graph(g);

    if (config.verbose) printf("Zakonczono pomyslnie.\n");
    return EXIT_SUCCESS;
}
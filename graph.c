#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph* create_graph() {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->num_edges = 0;
    g->max_edges = 10;
    g->edges = (Edge*)malloc(g->max_edges * sizeof(Edge));
    
    g->num_vertices = 0;
    g->max_vertices = 10;
    g->vertices = (Vertex*)malloc(g->max_vertices * sizeof(Vertex));
    return g;
}

void free_graph(Graph *g) {
    if (g) {
        free(g->edges);
        free(g->vertices);
        free(g);
    }
}

int add_vertex_if_missing(Graph *g, int vertex_id) {
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->vertices[i].id == vertex_id) return i;
    }
    
    if (g->num_vertices >= g->max_vertices) {
        g->max_vertices *= 2;
        g->vertices = (Vertex*)realloc(g->vertices, g->max_vertices * sizeof(Vertex));
    }
    
    g->vertices[g->num_vertices].id = vertex_id;
    g->vertices[g->num_vertices].x = 0.0;
    g->vertices[g->num_vertices].y = 0.0;
    g->num_vertices++;
    
    return g->num_vertices - 1;
}

bool read_graph(const char *filename, Graph *g) {
    if (!filename) {
        fprintf(stderr, "Error: input file not found\n");
        return false;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: input file not found\n");
        return false;
    }

    char edge_name[256];
    int u, v;
    double weight;

    while (fscanf(file, "%255s %d %d %lf", edge_name, &u, &v, &weight) == 4) {
        if (g->num_edges >= g->max_edges) {
            g->max_edges *= 2;
            g->edges = (Edge*)realloc(g->edges, g->max_edges * sizeof(Edge));
        }
        
        strcpy(g->edges[g->num_edges].name, edge_name);
        g->edges[g->num_edges].u = u;
        g->edges[g->num_edges].v = v;
        g->edges[g->num_edges].weight = weight;
        g->num_edges++;

        add_vertex_if_missing(g, u);
        add_vertex_if_missing(g, v);
    }

    if (!feof(file)) {
        fprintf(stderr, "Error: invalid input file format\n");
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

bool save_graph_txt(const char *filename, Graph *g) {
    FILE *file = fopen(filename, "w");
    if (!file) return false;

    for (int i = 0; i < g->num_vertices; i++) {
        fprintf(file, "%d %.6f %.6f\n", g->vertices[i].id, g->vertices[i].x, g->vertices[i].y);
    }
    
    fclose(file);
    return true;
}

bool save_graph_bin(const char *filename, Graph *g) {
    FILE *file = fopen(filename, "wb");
    if (!file) return false;

    for (int i = 0; i < g->num_vertices; i++) {
        fwrite(&g->vertices[i].id, sizeof(int), 1, file);
        fwrite(&g->vertices[i].x, sizeof(double), 1, file);
        fwrite(&g->vertices[i].y, sizeof(double), 1, file);
    }
    
    fclose(file);
    return true;
}
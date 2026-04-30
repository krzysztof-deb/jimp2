#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct {
    char name[256];
    int u;
    int v;
    double weight;
} Edge;

typedef struct {
    int id;
    double x;
    double y;
} Vertex;

typedef struct {
    Edge *edges;
    int num_edges;
    int max_edges;
    
    Vertex *vertices;
    int num_vertices;
    int max_vertices;
} Graph;


Graph* create_graph();
void free_graph(Graph *g);
int add_vertex_if_missing(Graph *g, int vertex_id);
bool read_graph(const char *filename, Graph *g);
bool save_graph_txt(const char *filename, Graph *g);
bool save_graph_bin(const char *filename, Graph *g);

#endif 
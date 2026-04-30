#include <math.h>
#include "tutte.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool layout_tutte_embedding(Graph* g) {
    int V = g->num_vertices;
    if (V < 3) return true;

    int boundary_count = 3;

    double radius = 50.0;
    double center_x = 50.0;
    double center_y = 50.0;

    for (int i = 0; i < boundary_count; i++) {
        double angle = 2.0 * M_PI * i / boundary_count;
        g->vertices[i].x = center_x + radius * cos(angle);
        g->vertices[i].y = center_y + radius * sin(angle);
    }

    for (int i = boundary_count; i < V; i++) {
        g->vertices[i].x = center_x;
        g->vertices[i].y = center_y;
    }

    int max_iterations = 2000;
    double tolerance = 0.0001;

    for (int iter = 0; iter < max_iterations; iter++) {
        double max_movement = 0.0;

        for (int i = boundary_count; i < V; i++) {
            int v_id = g->vertices[i].id;
            double sum_x = 0.0;
            double sum_y = 0.0;
            int degree = 0;

            for (int e = 0; e < g->num_edges; e++) {
                int neighbor_id = -1;
                if (g->edges[e].u == v_id) neighbor_id = g->edges[e].v;
                else if (g->edges[e].v == v_id) neighbor_id = g->edges[e].u;

                if (neighbor_id != -1) {
                    for (int j = 0; j < V; j++) {
                        if (g->vertices[j].id == neighbor_id) {
                            sum_x += g->vertices[j].x;
                            sum_y += g->vertices[j].y;
                            degree++;
                            break;
                        }
                    }
                }
            }

            if (degree > 0) {
                double new_x = sum_x / degree;
                double new_y = sum_y / degree;

                double dx = new_x - g->vertices[i].x;
                double dy = new_y - g->vertices[i].y;
                double dist = sqrt(dx * dx + dy * dy);
                if (dist > max_movement) {
                    max_movement = dist;
                }

                g->vertices[i].x = new_x;
                g->vertices[i].y = new_y;
            }
        }

        if (max_movement < tolerance) {
            break;
        }
    }

    return true;
}
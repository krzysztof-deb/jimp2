#include <stdlib.h>
#include <math.h>
#include "reingold.h"

bool layout_fruchterman_reingold(Graph *g) {
    int V = g->num_vertices;
    if (V <= 1) return true;

    double W = 100.0;
    double L = 100.0; 
    double area = W * L;
    double k = sqrt(area / V);
    
    int iterations = 100;
    double temp = W / 10.0; 
    double dt = temp / iterations; 

    double *disp_x = (double*)calloc(V, sizeof(double));
    double *disp_y = (double*)calloc(V, sizeof(double));

    for (int i = 0; i < V; i++) {
        g->vertices[i].x = (double)(rand() % (int)W);
        g->vertices[i].y = (double)(rand() % (int)L);
    }

    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < V; i++) {
            disp_x[i] = 0.0;
            disp_y[i] = 0.0;
        }

        for (int v = 0; v < V; v++) {
            for (int u = 0; u < V; u++) {
                if (v != u) {
                    double dx = g->vertices[v].x - g->vertices[u].x;
                    double dy = g->vertices[v].y - g->vertices[u].y;
                    double delta = sqrt(dx * dx + dy * dy);
                    
                    if (delta > 0.00001) {
                        double rep_force = (k * k) / delta; 
                        disp_x[v] += (dx / delta) * rep_force;
                        disp_y[v] += (dy / delta) * rep_force;
                    }
                }
            }
        }

        for (int e = 0; e < g->num_edges; e++) {
            int u_id = g->edges[e].u;
            int v_id = g->edges[e].v;
            
            int u_idx = -1, v_idx = -1;
            for (int i = 0; i < V; i++) {
                if (g->vertices[i].id == u_id) u_idx = i;
                if (g->vertices[i].id == v_id) v_idx = i;
            }

            if (u_idx != -1 && v_idx != -1 && u_idx != v_idx) {
                double dx = g->vertices[v_idx].x - g->vertices[u_idx].x;
                double dy = g->vertices[v_idx].y - g->vertices[u_idx].y;
                double delta = sqrt(dx * dx + dy * dy);
                
                if (delta > 0.00001) {
                    double attr_force = (delta * delta) / k; 
                    
                    attr_force *= g->edges[e].weight;

                    double disp_x_e = (dx / delta) * attr_force;
                    double disp_y_e = (dy / delta) * attr_force;

                    disp_x[v_idx] -= disp_x_e;
                    disp_y[v_idx] -= disp_y_e;
                    disp_x[u_idx] += disp_x_e;
                    disp_y[u_idx] += disp_y_e;
                }
            }
        }

        for (int v = 0; v < V; v++) {
            double disp_len = sqrt(disp_x[v] * disp_x[v] + disp_y[v] * disp_y[v]);
            
            if (disp_len > 0.00001) {
                double limited_disp = fmin(disp_len, temp); 
                g->vertices[v].x += (disp_x[v] / disp_len) * limited_disp;
                g->vertices[v].y += (disp_y[v] / disp_len) * limited_disp;
            }
            
            g->vertices[v].x = fmax(0.0, fmin(W, g->vertices[v].x));
            g->vertices[v].y = fmax(0.0, fmin(L, g->vertices[v].y));
        }

        temp -= dt;
        if (temp < 0) temp = 0;
    }

    free(disp_x);
    free(disp_y);
    return true;
}
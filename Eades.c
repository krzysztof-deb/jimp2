#include <stdio.h>
#include <math.h>

typedef struct {
    double x, y;
    double fx, fy;
} Node;


#define C_REP 2.0  
#define C_SPR 0.1  
#define L 1.0      
#define DT 0.1     

void compute_forces(Node nodes[], int adj[][2], int num_nodes, int num_edges) {
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i == j) continue;
            double dx = nodes[i].x - nodes[j].x;
            double dy = nodes[i].y - nodes[j].y;
            double d2 = dx*dx + dy*dy + 1e-9; 
            double force = C_REP / d2;
            nodes[i].fx += (dx / sqrt(d2)) * force;
            nodes[i].fy += (dy / sqrt(d2)) * force;
        }
    }

    for (int i = 0; i < num_edges; i++) {
        int u = adj[i][0];
        int v = adj[i][1];
        double dx = nodes[v].x - nodes[u].x;
        double dy = nodes[v].y - nodes[u].y;
        double d = sqrt(dx*dx + dy*dy) + 1e-9;
        double force = C_SPR * log(d / L); 
        nodes[u].fx += dx * force;
        nodes[u].fy += dy * force;
        nodes[v].fx -= dx * force;
        nodes[v].fy -= dy * force;
    }

    for (int i = 0; i < num_nodes; i++) {
        nodes[i].x += DT * nodes[i].fx;
        nodes[i].y += DT * nodes[i].fy;
        nodes[i].fx = nodes[i].fy = 0;
    }
}
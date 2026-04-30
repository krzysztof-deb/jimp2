#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "planarnosc.h"

#define EPS 1e-9

int find_vertex(Graph* g, int id) {
	for (int i = 0; i < g->num_vertices; i++) {
		if (g->vertices[i].id == id)
			return i;
	}
	return -1;
}

int orientation(double x1, double y1, double x2, double y2, double x3, double y3) {
	double val = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
	if (fabs(val) < EPS) return 0; 
	return (val > 0) ? 1 : 2;      
}

int onSegment(double x1, double y1, double x2, double y2, double x3, double y3) {
	if (x2 <= (x1 > x3 ? x1 : x3) && x2 >= (x1 < x3 ? x1 : x3) &&
		y2 <= (y1 > y3 ? y1 : y3) && y2 >= (y1 < y3 ? y1 : y3))
		return 1;
	return 0;
}

	int czyPrzecinaja(double xA, double yA, double xB, double yB, double xC, double yC, double xD, double yD) {
		int o1 = orientation(xA, yA, xB, yB, xC, yC);
		int o2 = orientation(xA, yA, xB, yB, xD, yD);
		int o3 = orientation(xC, yC, xD, yD, xA, yA);
		int o4 = orientation(xC, yC, xD, yD, xB, yB);
		if (o1 != o2 && o3 != o4)
			return 1;
		if (o1 == 0 && onSegment(xA, yA, xC, yC, xB, yB)) 
			return 1;
		if (o2 == 0 && onSegment(xA, yA, xD, yD, xB, yB)) 
			return 1;
		if (o3 == 0 && onSegment(xC, yC, xA, yA, xD, yD)) 
			return 1;
		if (o4 == 0 && onSegment(xC, yC, xB, yB, xD, yD)) 
			return 1;

		return 0;
	}
bool is_planar(Graph* g) {
	if (g->num_vertices < 3)
		return true;
	if (g->num_edges > 3 * g->num_vertices - 6)
		return false;

	for (int i = 0; i < g->num_edges - 1; i++){
		int idxA = find_vertex(g, g->edges[i].u);
		int idxB = find_vertex(g, g->edges[i].v);
		double xA = g->vertices[idxA].x;
		double yA = g->vertices[idxA].y;
		double xB = g->vertices[idxB].x;
		double yB = g->vertices[idxB].y;

		for (int j = i + 1; j < g->num_edges ; j++) {
			int idxC = find_vertex(g, g->edges[j].u);
			int idxD = find_vertex(g, g->edges[j].v);
			double xC = g->vertices[idxC].x;
			double yC = g->vertices[idxC].y;
			double xD = g->vertices[idxD].x;
			double yD = g->vertices[idxD].y;
			if (idxA == idxC || idxA == idxD || idxB==idxC || idxB==idxD )
				continue;
			if (czyPrzecinaja(xA, yA, xB, yB, xC, yC, xD, yD) == 1)
				return false;
		}
	}
	return true;
}
#ifndef PLANARNOSC_H
#define PLANARNOSC_H

#include <stdbool.h>
#include "graph.h" 


bool layout_tutte_embedding(Graph* g);
int find_vertex(Graph* g, int id);
int orientation(double x1, double y1, double x2, double y2, double x3, double y3);
int onSegment(double x1, double y1, double x2, double y2, double x3, double y3);
int czyPrzecinaja(double xA, double yA, double xB, double yB, double xC, double yC, double xD, double yD);
bool is_planar(Graph* g);

#endif 
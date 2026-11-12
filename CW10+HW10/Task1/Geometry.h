#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdbool.h>

typedef struct {
    double x;
    double y;
} Vertex;

typedef struct {
    Vertex v1;
    Vertex v2;
} Rectangle;

bool input_vertex(Vertex *v);
void print_vertex(const Vertex *v);
bool input_rectangle(Rectangle *rect);
void print_rectangle(const Rectangle *rect);

#endif
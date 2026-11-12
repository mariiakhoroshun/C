#include "Geometry.h"
#include <stdio.h>

bool input_vertex(Vertex *v) {
    if (v == NULL) {
        return false;
    }
    if (scanf("%lf %lf", &v->x, &v->y) != 2) {
        return false;
    }
    return true;
}

void print_vertex(const Vertex *v) {
    if (v == NULL) {
        return;
    }
    printf("(%.2f, %.2f)", v->x, v->y);
}

bool input_rectangle(Rectangle *rect) {
    if (rect == NULL) {
        return false;
    }
    printf("Enter first vertex (x1 y1, e.g. 0 0): ");
    if (!input_vertex(&rect->v1)) {
        return false;
    }
    printf("Enter opposite vertex (x2 y2, e.g. 4 3): ");
    if (!input_vertex(&rect->v2)) {
        return false;
    }
    if (rect->v1.x == rect->v2.x || rect->v1.y == rect->v2.y) {
        return false;
    }
    return true;
}

void print_rectangle(const Rectangle *rect) {
    if (rect == NULL) {
        return;
    }
    printf("Rectangle vertices: ");
    print_vertex(&rect->v1);
    printf(" and ");
    print_vertex(&rect->v2);
    printf("\n");
}
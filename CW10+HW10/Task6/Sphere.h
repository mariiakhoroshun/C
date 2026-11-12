#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

typedef struct {
    Point3D center;
    double radius_sq;
} Sphere;

bool input_point3d(Point3D *p);
void print_point3d(const Point3D *p);
bool input_sphere(Sphere *s);
void print_sphere(const Sphere *s);

#endif
#include "Sphere.h"
#include <stdio.h>

bool input_point3d(Point3D *p) {
    if (p == NULL) {
        return false;
    }
    if (scanf("%lf %lf %lf", &p->x, &p->y, &p->z) != 3) {
        return false;
    }
    return true;
}

void print_point3d(const Point3D *p) {
    if (p == NULL) {
        return;
    }
    printf("(%.2f, %.2f, %.2f)", p->x, p->y, p->z);
}

static void print_term(char var, double shift) {
    if (shift == 0.0) {
        printf("%c^2", var);
    } else if (shift > 0.0) {
        printf("(%c - %.2f)^2", var, shift);
    } else {
        printf("(%c + %.2f)^2", var, -shift);
    }
}

bool input_sphere(Sphere *s) {
    if (s == NULL) {
        return false;
    }
    double r;
    printf("Enter center coordinates (x y z, e.g. 1 -2 0): ");
    if (!input_point3d(&s->center)) {
        return false;
    }
    printf("Enter radius r (r > 0, e.g. 3): ");
    if (scanf("%lf", &r) != 1 || r <= 0.0) {
        return false;
    }
    s->radius_sq = r * r;
    return true;
}

void print_sphere(const Sphere *s) {
    if (s == NULL) {
        return;
    }
    printf("Sphere center: ");
    print_point3d(&s->center);
    printf("\nSphere equation: ");
    print_term('x', s->center.x);
    printf(" + ");
    print_term('y', s->center.y);
    printf(" + ");
    print_term('z', s->center.z);
    printf(" = %.2f\n", s->radius_sq);
}
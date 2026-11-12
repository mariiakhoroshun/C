#include <stdio.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

typedef struct {
    Point3D center;
    double radius_sq;
} Sphere;

int input_point3d(Point3D *p) {
    if (scanf("%lf %lf %lf", &p->x, &p->y, &p->z) != 3) {
        return 0;
    }
    return 1;
}

void output_point3d(Point3D p) {
    printf("(%.2f, %.2f, %.2f)", p.x, p.y, p.z);
}

int input_sphere(Sphere *s) {
    double r;
    printf("Enter center coordinates (x y z): ");
    if (!input_point3d(&s->center)) {
        return 0;
    }
    printf("Enter radius r: ");
    if (scanf("%lf", &r) != 1 || r <= 0.0) {
        return 0;
    }
    s->radius_sq = r * r;
    return 1;
}

void print_term(char var, double shift) {
    if (shift == 0.0) {
        printf("%c^2", var);
    } else if (shift > 0.0) {
        printf("(%c - %.2f)^2", var, shift);
    } else {
        printf("(%c + %.2f)^2", var, -shift);
    }
}

void output_sphere(Sphere s) {
    printf("\nSphere equation: ");
    print_term('x', s.center.x);
    printf(" + ");
    print_term('y', s.center.y);
    printf(" + ");
    print_term('z', s.center.z);
    printf(" = %.2f\n", s.radius_sq);
}

int main(void) {
    Sphere s;

    if (!input_sphere(&s)) {
        printf("Invalid sphere input.\n");
        return 1;
    }

    output_sphere(s);

    return 0;
}
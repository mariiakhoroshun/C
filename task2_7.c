#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

double segment_length(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    double cx, cy;
    double rx1, ry1;
    double rx2, ry2;

    printf("Input coordinates of the center of the ellipse (x y): ");
    scanf("%lf %lf", &cx, &cy);

    printf("Input coordinates of the end of the first radius (x y): ");
    scanf("%lf %lf", &rx1, &ry1);

    printf("Input coordinates of the end of the second radius (x y): ");
    scanf("%lf %lf", &rx2, &ry2);

    double a = segment_length(cx, cy, rx1, ry1);
    double b = segment_length(cx, cy, rx2, ry2);

    double area = M_PI * a * b;

    printf("\nArea of the ellipse: %g\n", area);

    return 0;
}
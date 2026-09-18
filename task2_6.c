#include <stdio.h>
#include <math.h>

double segment_length(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double triangle_area(double a, double b, double c) {
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main() {
    double ax, ay, bx, by, cx, cy;

    printf("Input coordinates of point A:\n");
    scanf("%lf %lf", &ax, &ay);
    
    printf("\nInput coordinates of point B:\n");
    scanf("%lf %lf", &bx, &by);
    
    printf("\nInput coordinates of point C:\n");
    scanf("%lf %lf", &cx, &cy);

    double ab = segment_length(ax, ay, bx, by);
    double bc = segment_length(bx, by, cx, cy);
    double ca = segment_length(cx, cy, ax, ay);

    double area = triangle_area(ab, bc, ca);  
    printf("\nArea of the triangle: %g\n", area);
    return 0;
}
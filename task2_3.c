#include <stdio.h>
#include <math.h>

double half_perimeter(double a, double b, double c) {
    return (a + b + c) / 2;
}

double area_heron(double a, double b, double c) {
    double s = half_perimeter(a, b, c);
    return sqrt(s * (s - a) * (s - b) * (s - c));
}


int main() {
    double a, b, c;
    printf("Enter the lengths of the sides of a triangle: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    double area = area_heron(a, b, c);
    printf("The area of the triangle is: %g\n", area);
    return 0;
}
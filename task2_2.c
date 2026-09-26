#include <stdio.h>
#include <math.h>

double square(double x) {
    return x * x;
}

double hypotenuse_squared(double a, double b) {
    return square(a) + square(b);
}

double hypotenuse(double a, double b) {
    return sqrt(hypotenuse_squared(a, b));
}


int main() {
    double a, b;
    printf("Enter the lengths of the two sides of a right triangle: ");
    scanf("%lf %lf", &a, &b);
    double c = hypotenuse(a, b);
    printf("The length of the hypotenuse is: %g %g \n", c, hypot(a, b));
    return 0;
}
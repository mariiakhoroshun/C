#include <stdio.h>

double square(double x) {
    return x * x;
}

double Rosenbrock2d(double x, double y) {
    return 100.0 * square(square(x) - y) + square(x - 1.0);
}

int main(void) {
    printf("Rosenbrock2d(1.0, 1.0)  = %g\n", Rosenbrock2d(1.0, 1.0));
    printf("Rosenbrock2d(0.0, 0.0)  = %g\n", Rosenbrock2d(0.0, 0.0));
    printf("Rosenbrock2d(-1.0, 1.0) = %g\n", Rosenbrock2d(-1.0, 1.0));
    
    double x, y;
    printf("\nEnter x and y: ");
    if (scanf("%lf %lf", &x, &y) == 2) {
        printf("Rosenbrock2d(%g, %g) = %g\n", x, y, Rosenbrock2d(x, y));
    }

    return 0;
}
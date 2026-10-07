#include <stdio.h>
#include <math.h>

double poly_a(double x, unsigned n) {
    double sum = 1.0;
    double term = 1.0;
    for (unsigned k = 1; k <= n; k++) {
        term *= x;
        sum += term;
    }
    return sum;
}

double poly_b(double x, double y, unsigned n) {
    double sum = 1.0;
    double t = x * x * y;
    double term = 1.0;
    for (unsigned k = 1; k <= n; k++) {
        term *= t;
        sum += term;
    }
    return sum;
}

int main() {
    double x_a = 2.0;
    unsigned n_a = 3;
    double result_a = poly_a(x_a, n_a);
    printf("a) Result for x = %.2lf, n = %u: %.2lf\n", x_a, n_a, result_a);

    double x_b = 1.0;
    double y_b = 2.0;
    unsigned n_b = 4;
    double result_b = poly_b(x_b, y_b, n_b);
    printf("b) Result for x = %.2lf, y = %.2lf, n = %u: %.2lf\n", x_b, y_b, n_b, result_b);

    return 0;
}
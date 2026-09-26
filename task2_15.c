#include <stdio.h>

double polynomial_a(double x, double y) {
    double sum = x + y;
    return sum * sum * sum;
}

double polynomial_b(double x, double y) {
    double p = x * y;
    double p2 = p * p;
    return p2 * (1.0 + p + p2);
}

int main(void) {
    double x, y;
    printf("Input x and y: ");
    scanf("%lf %lf", &x, &y);
    printf("a) f(%g, %g) = %g\n", x, y, polynomial_a(x, y));
    printf("b) f(%g, %g) = %g\n", x, y, polynomial_b(x, y));
    return 0;
}
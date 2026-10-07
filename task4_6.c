#include <stdio.h>
#include <math.h>

double rec_sqrt_a(unsigned n) {
    double y = 0.0;
    for (unsigned k = 1; k <= n; k++) {
        y = sqrt(2.0 + y);
    }
    return y;
}

double rec_sqrt_b(unsigned n) {
    double y = 0.0;
    for (unsigned k = n; k >= 1; k--) {
        y = sqrt(3.0 * k + y);
    }
    return y;
}

int main() {
    unsigned n;
    printf("Enter a value for n: ");
    scanf("%u", &n);

    double result_a = rec_sqrt_a(n);
    double result_b = rec_sqrt_b(n);

    printf("a) Result (%u roots) = %lf\n", n, result_a);
    printf("b) Result (%u roots) = %lf\n", n, result_b);

    return 0;
}
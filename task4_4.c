#include <stdio.h>

double compute_sum(double x, unsigned n) {
    double sum = 0.0;
    double power_x = 1.0;
    for (unsigned i = 1; i <= n; i++) {
        power_x *= x;
        sum += i * power_x;
    }
    return sum;
}

int main() {
    double x;
    unsigned n;

    printf("Enter a value for x: ");
    scanf("%lf", &x);
    printf("Enter a value for n: ");
    scanf("%u", &n);

    double result = compute_sum(x, n);
    printf("Result = %lf\n", result);

    return 0;
}
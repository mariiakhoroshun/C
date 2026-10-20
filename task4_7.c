#include <stdio.h>

double exp_taylor(double x, unsigned n) {
    double sum = 1.0;
    double term = 1.0;

    for (unsigned i = 1; i <= n; i++) {
        term *= x / i;
        sum += term;
    }

    return sum;
}

int main() {
    double x;
    unsigned n;

    printf("Enter a value for x (|x| < 1): ");
    scanf("%lf", &x);
    
    printf("Enter a value for n (n >= 0): ");
    scanf("%u", &n);

    double result = exp_taylor(x, n);
    printf("Result = %lf\n", result);

    return 0;
}
#include <stdio.h>

double calc_expression_g(double x, unsigned int n) {
    double sum = n;
    
    for (int i = n - 1; i >= 1; i--) {
        sum = sum * x + i;
    }
    
    return sum;
}

int main() {
    double x;
    unsigned int n;

    printf("Enter a value for x: ");
    scanf("%lf", &x);

    printf("Enter a value for n (n >= 1): ");
    scanf("%u", &n);

    if (n < 1) {
        printf("Invalid input. n must be a natural number (n >= 1).\n");
        return 1;
    }

    double result = calc_expression_g(x, n);

    printf("Result = %lf\n", result);

    return 0;
}
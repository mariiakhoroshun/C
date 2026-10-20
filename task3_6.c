#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    printf("Enter three floating-point numbers: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    printf("Maximum by absolute value: %.2lf\n", fmax(fmax(fabs(a), fabs(b)), fabs(c)));
    printf("Minimum by absolute value: %.2lf\n", fmin(fmin(fabs(a), fabs(b)), fabs(c)));

    return 0;
}
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

int main() {
    float num1 = 1e-4f;
    float num2 = 24.33e5f;

    double num3 = M_PI;
    double num4 = M_E;

    long double num5 = sqrtl(5.0L);
    long double num6 = logl(100.0L);

    printf("10^-4   = %.2f\n", num1);
    printf("24.33E5 = %.2f\n", num2);
    printf("pi      = %.2lf\n", num3);
    printf("e       = %.2lf\n", num4);
    printf("sqrt(5) = %.2Lf\n", num5);
    printf("ln(100) = %.2Lf\n", num6);

    return 0;
}
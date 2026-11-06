#include <stdio.h>
#include <math.h>

//l
int main(void) {
    double x, eps;
    printf("Enter x (|x| < 1) and accuracy eps (eps > 0): ");
    scanf("%lf %lf", &x, &eps);

    if (fabs(x) >= 1.0 || eps <= 0.0) {
        printf("Error: |x| < 1 and eps > 0 are required.\n");
        return 1;
    }

    double S = 0.0;
    double a = 1.0;
    int k = 1;

    while (fabs(a) >= eps) {
        S = S + a;
        k++;
        a = -a * (2.0 * k - 3.0) / (2.0 * k - 2.0) * x;
    }

    double exact = 1.0 / sqrt(1.0 + x);

    printf("Approximate sum S = %.10f\n", S);
    printf("Exact value y     = %.10f\n", exact);
    printf("Error             = %.10e\n", fabs(S - exact));

    return 0;
}
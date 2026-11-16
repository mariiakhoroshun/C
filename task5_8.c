#include <stdio.h>
#include <math.h>

double taylor_exp(double x, double eps) {
    double sum = 0.0;
    double a = 1.0;
    int k = 1;

    while (fabs(a) >= eps) {
        sum += a;
        a = a * x / k;
        k++;
    }
    return sum;
}

double taylor_phi_exact(double x, double eps) {
    double sum = 0.0;
    double a = x;
    int k = 1;

    while (fabs(a) >= eps) {
        sum += a;
        a = -a * x * x * (2 * k - 1) / ((2 * k + 1) * k);
        k++;
    }
    return sum;
}

double taylor_phi_printed(double x, double eps) {
    double sum = 0.0;
    double a = x;
    int k = 1;

    while (fabs(a) >= eps) {
        sum += a;
        if (k == 1) {
            a = -a * x * x / 3.0;
        } else {
            a = -a * x * x / ((2.0 * k + 1.0) * (2.0 * k - 2.0));
        }
        k++;
    }
    return sum;
}

int main(void) {
    double x, eps;
    printf("Enter x and positive accuracy eps: ");
    scanf("%lf %lf", &x, &eps);

    double res_exp = taylor_exp(x, eps);
    double std_exp = exp(x);

    double res_phi_exact = taylor_phi_exact(x, eps);
    double res_phi_printed = taylor_phi_printed(x, eps);
    double std_phi = 0.5 * sqrt(3.14159265358979323846) * erf(x);

    printf("\n--- Part a) e^x ---\n");
    printf("Taylor series: %.10f\n", res_exp);
    printf("math.h exp:    %.10f\n", std_exp);
    printf("Difference:    %.10e\n", fabs(res_exp - std_exp));

    printf("\n--- Part b) Phi(x) ---\n");
    printf("Taylor series (exact integral): %.10f\n", res_phi_exact);
    printf("Taylor series (as printed):     %.10f\n", res_phi_printed);
    printf("math.h erf(x) value:            %.10f\n", std_phi);

    return 0;
}
#include <stdio.h>

double calc_arithmetic_mean(double a, double b, double c) {
    return (a + b + c) / 3.0;
}

double calc_harmonic_mean(double a, double b, double c) {
    double sum_of_inverses = (1.0 / a) + (1.0 / b) + (1.0 / c);
    return 3.0 / sum_of_inverses;
}

int main() {
    double a, b, c;
    printf("Enter values in the exact format 'A=xxx.xxx, B=xxExxx C=xxx.xxxx':\n");
    if (scanf("A=%lf, B=%lf C=%lf", &a, &b, &c) != 3) {
        printf("Input error!\n");
        return 1;
    }

    double am = calc_arithmetic_mean(a, b, c);

    printf("\nArithmetic Mean:\n");
    printf("  Fixed-point format: %f\n", am);
    printf("  Scientific format:  %e\n\n", am);
    printf("Harmonic Mean:\n");
    if (a == 0.0 || b == 0.0 || c == 0.0) {
        printf("  Cannot be calculated (one of the values is zero).\n");
    } else {
        double sum_of_inverses = (1.0 / a) + (1.0 / b) + (1.0 / c);
        if (sum_of_inverses == 0.0) {
            printf("  Cannot be calculated (sum of inverses is zero).\n");
        } else {
            double hm = calc_harmonic_mean(a, b, c);
            printf("  Fixed-point format: %f\n", hm);
            printf("  Scientific format:  %e\n", hm);
        }
    }
    return 0;
}
#include <stdio.h>

int main(void) {
    int n;
    printf("Enter a natural number n: ");
    scanf("%d", &n);

    double P_a = 1.0;
    double b_a = 1.0;
    for (int k = 1; k <= n; k++) {
        b_a = b_a / k;
        double a_k = 1.0 + b_a;
        P_a = P_a * a_k;
    }

    double P_b = 1.0;
    double b_b = 0.5;
    for (int k = 1; k <= n; k++) {
        if (k > 1) {
            b_b = -b_b / 2.0;
        }
        double a_k = 1.0 + b_b * k * k;
        P_b = P_b * a_k;
    }

    printf("a) Product P_n = %.10f\n", P_a);
    printf("b) Product P_n = %.10f\n", P_b);

    return 0;
}
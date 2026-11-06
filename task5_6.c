#include <stdio.h>

int main(void) {
    int n;
    double b;

    printf("Enter a natural number n and a real number b (b != 0): ");
    scanf("%d %lf", &n, &b);

    double b_a = b;
    for (int k = 1; k <= n; k++) {
        b_a = b + 1.0 / b_a;
    }

    double b_b = 4.0 * n + 2.0;
    for (int k = 1; k <= n; k++) {
        b_b = 4.0 * (n - k) + 2.0 + 1.0 / b_b;
    }

    double b_c = 2.0;
    for (int k = 1; k <= 2 * n - 1; k++) {
        if (k % 2 != 0) {
            b_c = 1.0 + 1.0 / b_c;
        } else {
            b_c = 2.0 + 1.0 / b_c;
        }
    }

    printf("a) b_n = %.10f\n", b_a);
    printf("b) lambda_n = %.10f\n", b_b);
    printf("c) x_{2n} = %.10f\n", b_c);

    return 0;
}
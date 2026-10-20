#include <stdio.h>

double calc_subfactorial(int n) {
    if (n == 0) {
        return 1.0;
    }
    double y = 1.0;
    for (int i = 1; i <= n; i++) {
        double sign = (i % 2 == 0) ? 1.0 : -1.0;
        y = i * y + sign;
    }
    
    return y;
}

int main() {
    int n;
    printf("Enter a value for n (n < 25): ");
    scanf("%d", &n);
    if (n < 0 || n >= 25) {
        printf("Invalid input. n must be between 0 and 24.\n");
        return 1;
    }
    double result = calc_subfactorial(n);
    printf("Subfactorial !%d = %.0lf\n", n, result);
    return 0;
}
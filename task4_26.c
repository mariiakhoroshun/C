#include <stdio.h>
#include <stdlib.h>

int calc_gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

int main() {
    int n, m;

    printf("Enter numerator (integer n): ");
    scanf("%d", &n);

    printf("Enter denominator (natural number m > 0): ");
    scanf("%d", &m);

    if (m <= 0) {
        printf("Invalid input. Denominator m must be a natural number (m > 0).\n");
        return 1;
    }

    int gcd = calc_gcd(n, m);
    
    if (n == 0) {
        n = 0;
        m = 1;
    } else {
        n = n / gcd;
        m = m / gcd;
    }

    printf("Simplified fraction: %d/%d\n", n, m);

    return 0;
}
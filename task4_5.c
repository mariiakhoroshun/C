#include <stdio.h>

unsigned long long double_factorial(unsigned n) {
    unsigned long long result = 1;
    unsigned start = (n % 2 == 0) ? 2 : 1;
    for (unsigned i = start; i <= n; i += 2) {
        result *= i;
    }
    return result;
}

int main() {
    unsigned n;
    printf("Enter a value for n: ");
    scanf("%u", &n);
    unsigned long long res = double_factorial(n);
    printf("%u!! = %llu\n", n, res);
    return 0;
}
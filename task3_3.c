#include <stdio.h>

int main() {
    // a)
    int a_int, b_int, c_int;

    printf("Task a) Enter three numbers separated by commas (abs < 2^10): ");
    if (scanf("%d ,%d ,%d", &a_int, &b_int, &c_int) == 3) {
        int product_int = a_int * b_int * c_int;
        printf("Result (int): %d\n\n", product_int);
    }

    // b)
    long long a_ll, b_ll, c_ll;

    printf("Task b) Enter three numbers separated by commas (abs < 2^21): ");
    if (scanf("%lld ,%lld ,%lld", &a_ll, &b_ll, &c_ll) == 3) {
        long long product_ll = a_ll * b_ll * c_ll;
        printf("Result (long long): %lld\n", product_ll);
    }

    return 0;
}

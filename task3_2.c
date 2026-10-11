#include <stdio.h>

void print_combinations(unsigned n) {
    printf("Combinations of digits in %u:\n", n);
    unsigned units = n % 10;
    unsigned tens = (n / 10) % 10;
    unsigned hundreds = (n / 100) % 10;
    printf("%u%u%u\n", hundreds, tens, units);
    printf("%u%u%u\n", hundreds, units, tens);
    printf("%u%u%u\n", tens, hundreds, units);
    printf("%u%u%u\n", tens, units, hundreds);
    printf("%u%u%u\n", units, hundreds, tens);
    printf("%u%u%u\n", units, tens, hundreds);
}

int main() {
    unsigned x;
    printf("Enter a 3-digit positive integer: ");
    scanf("%u", &x);
    unsigned units = x % 10;
    unsigned tens = (x / 10) % 10;
    unsigned hundreds = (x / 100) % 10;
    if (units != tens && tens != hundreds) {
        print_combinations(x);
    } else {
        printf("The digits are not distinct.\n");
    }
    return 0;
}
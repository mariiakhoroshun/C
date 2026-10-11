#include <stdio.h>

unsigned sum_of_digits(unsigned n) {
    unsigned sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

unsigned reverse_digits(unsigned n) {
    unsigned reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return reversed;
}

int main() {
    unsigned x;
    printf("Enter a 3-digit positive integer: ");
    scanf("%u", &x);
    unsigned units = x%10;
    unsigned tens = (x/10)%10;
    unsigned hundreds = x/100;
    printf("Units digit, Tens digit, Hundreds digit: %u, %u, %u\n", units, tens, hundreds);
    printf("Sum of digits: %u\n", sum_of_digits(x));
    printf("Reversed number: %u\n", reverse_digits(x));

    return 0;
}
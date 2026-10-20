#include <stdio.h>

unsigned next_power_of_2(unsigned n) {
    unsigned power = 1;   
    while (power <= n) {
        power *= 2;
    }
    return power;
}

int main() {
    unsigned n;
    printf("Enter a value for n: ");
    scanf("%u", &n);

    unsigned result = next_power_of_2(n);
    printf("Result = %u\n", result);

    return 0;
}
#include <stdio.h>
#include <stdint.h>

uint16_t multiply8to16(uint8_t a, uint8_t b) {
    return (uint16_t)a * b;
}

int main(void) {
    uint8_t x, y;
    printf("Enter two 8-bit unsigned integers (0-255): ");
    scanf("%hhu %hhu", &x, &y);

    uint16_t result = multiply8to16(x, y);

    printf("Result: %u\n", result);

    return 0;
}
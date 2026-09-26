#include <stdio.h>

int main() {
    double num1, num2;
    double difference, product;

    printf("Input first real number: ");
    scanf("%lf", &num1);

    printf("\nInput second real number: ");
    scanf("%lf", &num2);

    difference = num1 - num2;
    product = num1 * num2;

    printf("Difference: %f\n", difference);
    printf("Product: %f\n", product);

    return 0;
}
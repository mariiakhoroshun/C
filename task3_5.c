#include <stdio.h>

int main() {
    double a, b;
    printf("Enter two floating-point numbers: ");
    scanf("%lf %lf", &a, &b);
    if (a==b) {
        printf("The numbers are equal.\n");
    } else if (a > b) {
        printf("The first number is greater than the second. The second number is less than the first.\n");
    } else {
        printf("The first number is less than the second. The second number is greater than the first.\n");
    }
    return 0;
}
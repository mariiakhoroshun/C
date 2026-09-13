#include <stdio.h>

int main() {
    float x;
    printf("Value of x: ");
    scanf("%f", &x);

    float y = x*x*x;
    y=y*y*y;
    printf("Value of y: %f\n", y);
}


#include <stdio.h>
#include <math.h>

int main() {
    double x;
    printf("Input real x:");
    scanf("%lf", &x);

    int x_int = (int)x; // Get the integer part of x
    printf("Integer part: %d", x_int);
    
    double fractional_part = x - x_int; // Get the fractional part of x
    printf("\nFractional part: %lf", fabs(fractional_part));

    int x_floor = floor(x); // Get the floor value of x
    printf("\nFloor of x: %d", x_floor);

    int x_ceil = ceil(x); // Get the ceiling value of x
    printf("\nCeiling of x: %d", x_ceil);

    int x_round = round(x); // Get the rounded value of x
    printf("\nRounded value of x: %d", x_round);
}
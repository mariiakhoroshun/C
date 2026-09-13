#include <stdio.h>

double avg(double a, double b) {
    return (a + b) / 2.0;
}

double harmonic(double a, double b) {
    return 2.0 / (1.0 / a + 1.0 / b);
}

int main() {
    double x,y;
    printf("Input real x,y:");
    scanf("%lf %lf",&x,&y);
    printf("Difference of x and y: %lf\n", x - y);
    printf("Multiplication of x and y: %lf\n", x * y);
    printf("Average of x and y: %lf\n", avg(x, y));
    if (x == 0.0 || y == 0.0) {
        printf("Harmonic of x and y: Cannot be calculated (zero value entered).\n");
    } else {
        double sum_of_inverses = (1.0 / x) + (1.0 / y);
        if (sum_of_inverses == 0.0) {
            printf("Harmonic of x and y: Cannot be calculated (sum of inverses is zero).\n");
        } else {
            printf("Harmonic of x and y: %lf\n", harmonic(x, y));
        }
    }
    
    return 0;
}
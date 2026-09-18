#include <stdio.h>

double calculate_g(double x) {
    double x2 = x * x;         
    double x3 = x2 * x;        
    double x6 = x3 * x3;       
    double x9 = x6 * x3;      
    return x9 + x3 + 1.0;
}

int main(void) {
    double x;
    printf("Input x: ");
    scanf("%lf", &x);
    printf("y = %lf\n", calculate_g(x));
    return 0;
}
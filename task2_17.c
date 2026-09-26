#include <stdio.h>
#include <math.h>

double sigmweight(double x) {
    return x / (1.0 + exp(-x));
}

double sigmweight_derivative(double x) {
    double sig = 1.0 / (1.0 + exp(-x));
    return sig + x * sig * (1.0 - sig);
}

int main() {
    double x; 
    printf("Input value of x: ");
    scanf("%lf", &x);
    printf("f(%g)  = %g\n", x, sigmweight(x));
    printf("f'(%g) = %g\n", x, sigmweight_derivative(x));
    
    return 0;
}
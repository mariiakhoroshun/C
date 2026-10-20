#include <stdio.h>
#include <math.h>

double rec_sinus(double x, unsigned n) {
    double y = x;
    for (unsigned k = 1; k <= n; k++) {
        y = sin(y);
    }
    return y;
}

int main(){
    double x;
    unsigned n;
    printf("Enter a value for x: ");
    scanf("%lf", &x);
    printf("Enter a value for n: ");
    scanf("%u", &n);

    double result = rec_sinus(x, n);
    printf("rec_sinus(%lf, %u) = %lf\n", x, n, result);
}
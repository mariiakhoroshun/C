#include <stdio.h>
#include <math.h>

int main() {
    double x, y;
    printf("Input real number x: ");
    scanf("%lf", &x);

    y=cosh(x);
    printf("cosh(%lf) = %lf\n", x, y);
}

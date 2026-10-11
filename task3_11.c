#include <stdio.h>
#include <math.h>

// а) f(x) = |x|
double func_a(double x) {
    return fabs(x);
}

// б) f(x) = ||x| - 1| - 1
double func_b(double x) {
    return fabs(fabs(x) - 1.0) - 1.0;
}

// в) f(x) = sign(x)
int func_v(double x) {
    if (x > 0.0) {
        return 1;
    } else if (x < 0.0) {
        return -1;
    } else {
        return 0;
    }
}

// г) f(x) = sin(|x|)
double func_g(double x) {
    return sin(fabs(x));
}

int main(void) {
    double x;

    printf("Enter x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("\nResults:\n");
    printf("a) f(x) = |x|            = %.4lf\n", func_a(x));
    printf("b) f(x) = ||x| - 1| - 1  = %.4lf\n", func_b(x));
    printf("v) f(x) = sign(x)        = %d\n", func_v(x));
    printf("g) f(x) = sin(|x|)       = %.4lf\n", func_g(x));

    return 0;
}
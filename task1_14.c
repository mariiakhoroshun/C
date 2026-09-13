#include <stdio.h>

double calc_distance(double a, double t) {
    return (a * t * t) / 2.0;
}

double calc_time(double v, double a) {
    return v / a;
}

int main() {
    double a, t, v;

    printf("Enter acceleration (a): ");
    scanf("%lf", &a);
    printf("Enter travel time (t): ");
    scanf("%lf", &t);
    printf("Enter target velocity (v): ");
    scanf("%lf", &v);

    printf("Distance traveled in time %.2lf: %.2lf\n", t, calc_distance(a, t));

    if (a != 0) {
        printf("Time to reach velocity %.2lf: %.2lf\n", v, calc_time(v, a));
    } else {
        if (v == 0) {
            printf("The body already has a velocity of 0 (no acceleration).\n");
        } else {
            printf("The body will never reach velocity %.2lf (zero acceleration).\n", v);
        }
    }

    return 0;
}
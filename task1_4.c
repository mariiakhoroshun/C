#include <stdio.h>
#include <math.h>

int main() {
    double m1, m2, r, F;
    printf("Enter mass m1 and m2, and distance r: ");
    scanf("%lf %lf %lf", &m1, &m2, &r);
    const double G = 6.67430e-11;
    F = G * (m1 * m2) / (r * r);
    printf("The gravitational force F is: %.9Lf or %Le\n", F, F);
    return 0;
}

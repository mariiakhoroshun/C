#include <stdio.h>
#include <math.h>

void solve_quadratic(double a, double b, double c) {
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("Infinite number of roots.\n");
            } else {
                printf("No roots.\n");
            }
        } else {
            double root = -c / b;
            printf("1 root: %.4lf\n", root);
        }
        return;
    }

    double d = b * b - 4 * a * c;

    if (d < 0) {
        printf("0 roots (D < 0).\n");
    } else if (d == 0) {
        double root = -b / (2 * a);
        printf("1 root: %.4lf\n", root);
    } else {
        double root1 = (-b + sqrt(d)) / (2 * a);
        double root2 = (-b - sqrt(d)) / (2 * a);
        printf("2 roots: %.4lf and %.4lf\n", root1, root2);
    }
}

void solve_biquadratic(double a, double b, double c) {
    if (a == 0) {
        // Рівняння стає b*x^2 + c = 0
        solve_quadratic(b, 0, c);
        return;
    }

    double d = b * b - 4 * a * c;

    if (d < 0) {
        printf("0 roots (D < 0).\n");
    } else if (d == 0) {
        double t = -b / (2 * a);

        if (t < 0) {
            printf("0 real roots (t < 0).\n");
        } else if (t == 0) {
            printf("1 root: 0.0000\n");
        } else {
            printf("2 roots: %.4lf and %.4lf\n", sqrt(t), -sqrt(t));
        }
    } else {
        double t1 = (-b + sqrt(d)) / (2 * a);
        double t2 = (-b - sqrt(d)) / (2 * a);

        // Перевіряємо скільки коренів t є невід'ємними
        if (t1 < 0 && t2 < 0) {
            printf("0 real roots.\n");
        } else if (t1 > 0 && t2 > 0) {
            printf("4 roots: %.4lf, %.4lf, %.4lf, %.4lf\n", 
                   sqrt(t1), -sqrt(t1), sqrt(t2), -sqrt(t2));
        } else if (t1 > 0 && t2 < 0) {
            printf("2 roots: %.4lf and %.4lf\n", sqrt(t1), -sqrt(t1));
        } else if (t2 > 0 && t1 < 0) {
            printf("2 roots: %.4lf and %.4lf\n", sqrt(t2), -sqrt(t2));
        } else if (t1 == 0 && t2 > 0) {
            printf("3 roots: 0.0000, %.4lf, %.4lf\n", sqrt(t2), -sqrt(t2));
        } else if (t2 == 0 && t1 > 0) {
            printf("3 roots: 0.0000, %.4lf, %.4lf\n", sqrt(t1), -sqrt(t1));
        } else if (t1 == 0 && t2 < 0) {
            printf("1 root: 0.0000\n");
        } else if (t2 == 0 && t1 < 0) {
            printf("1 root: 0.0000\n");
        }
    }
}

int main(void) {
    double a, b, c;

    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }

    printf("\na) Quadratic equation:\n");
    solve_quadratic(a, b, c);

    printf("\nb) Biquadratic equation:\n");
    solve_biquadratic(a, b, c);

    return 0;
}
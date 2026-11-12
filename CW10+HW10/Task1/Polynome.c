#include "Polynome.h"
#include <stdio.h>
#include <stdlib.h>

bool input_polynome(Polynome *p) {
    if (p == NULL) {
        return false;
    }
    p->coeffs = NULL;
    p->degree = 0;

    printf("Enter polynomial degree (integer n >= 0, e.g. 2): ");
    if (scanf("%d", &p->degree) != 1 || p->degree < 0) {
        return false;
    }

    p->coeffs = (double *)malloc((size_t)(p->degree + 1) * sizeof(double));
    if (p->coeffs == NULL) {
        return false;
    }

    printf("Enter %d real coefficients (a_0 a_1 ... a_%d separated by space): ",
           p->degree + 1, p->degree);
    for (int i = 0; i <= p->degree; i++) {
        if (scanf("%lf", &p->coeffs[i]) != 1) {
            free(p->coeffs);
            p->coeffs = NULL;
            p->degree = 0;
            return false;
        }
    }
    return true;
}

void print_polynome(const Polynome *p) {
    if (p == NULL || p->coeffs == NULL) {
        return;
    }
    printf("P(x) = ");
    for (int i = 0; i <= p->degree; i++) {
        if (i == 0) {
            printf("%.2f", p->coeffs[i]);
        } else if (p->coeffs[i] >= 0.0) {
            printf(" + %.2f*x^%d", p->coeffs[i], i);
        } else {
            printf(" - %.2f*x^%d", -p->coeffs[i], i);
        }
    }
    printf("\n");
}

void free_polynome(Polynome *p) {
    if (p == NULL) {
        return;
    }
    free(p->coeffs);
    p->coeffs = NULL;
    p->degree = 0;
}
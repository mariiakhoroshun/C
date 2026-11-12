#ifndef POLYNOME_H
#define POLYNOME_H

#include <stdbool.h>

typedef struct {
    int degree;
    double *coeffs;
} Polynome;

bool input_polynome(Polynome *p);
void print_polynome(const Polynome *p);
void free_polynome(Polynome *p);

#endif
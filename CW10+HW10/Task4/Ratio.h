#ifndef RATIO_H
#define RATIO_H

#include <stdbool.h>

typedef struct {
    int numerator;
    unsigned int denominator;
} Rational;

bool input_rational(Rational *r);
void print_rational(Rational r);
Rational reduce_rational(Rational r);
Rational add_rational(Rational a, Rational b);
Rational multiply_rational(Rational a, Rational b);
int compare_rational(Rational a, Rational b);
void print_comparison(Rational a, Rational b, int cmp);

#endif
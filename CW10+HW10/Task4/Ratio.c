#include "Ratio.h"
#include <stdio.h>

static unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool input_rational(Rational *r) {
    if (r == NULL) {
        return false;
    }
    long long den;
    if (scanf("%d %lld", &r->numerator, &den) != 2 || den <= 0) {
        return false;
    }
    r->denominator = (unsigned int)den;
    return true;
}

void print_rational(Rational r) {
    printf("%d/%u", r.numerator, r.denominator);
}

Rational reduce_rational(Rational r) {
    if (r.denominator == 0) {
        return r;
    }
    if (r.numerator == 0) {
        r.denominator = 1;
        return r;
    }
    unsigned long long abs_num = (r.numerator < 0)
        ? (unsigned long long)(-(long long)r.numerator)
        : (unsigned long long)r.numerator;
    unsigned long long divisor = gcd(abs_num, r.denominator);
    r.numerator /= (int)divisor;
    r.denominator /= (unsigned int)divisor;
    return r;
}

Rational add_rational(Rational a, Rational b) {
    long long num = (long long)a.numerator * (long long)b.denominator +
                    (long long)b.numerator * (long long)a.denominator;
    unsigned long long den = (unsigned long long)a.denominator * (unsigned long long)b.denominator;
    unsigned long long abs_num = (num < 0) ? (unsigned long long)(-num) : (unsigned long long)num;
    unsigned long long divisor = gcd(abs_num, den);
    Rational res;
    res.numerator = (int)(num / (long long)divisor);
    res.denominator = (unsigned int)(den / divisor);
    return res;
}

Rational multiply_rational(Rational a, Rational b) {
    long long num = (long long)a.numerator * (long long)b.numerator;
    unsigned long long den = (unsigned long long)a.denominator * (unsigned long long)b.denominator;
    unsigned long long abs_num = (num < 0) ? (unsigned long long)(-num) : (unsigned long long)num;
    unsigned long long divisor = gcd(abs_num, den);
    Rational res;
    res.numerator = (int)(num / (long long)divisor);
    res.denominator = (unsigned int)(den / divisor);
    return res;
}

int compare_rational(Rational a, Rational b) {
    long long left = (long long)a.numerator * (long long)b.denominator;
    long long right = (long long)b.numerator * (long long)a.denominator;
    if (left < right) {
        return -1;
    }
    if (left > right) {
        return 1;
    }
    return 0;
}

void print_comparison(Rational a, Rational b, int cmp) {
    print_rational(a);
    if (cmp < 0) {
        printf(" < ");
    } else if (cmp > 0) {
        printf(" > ");
    } else {
        printf(" == ");
    }
    print_rational(b);
    printf("\n");
}
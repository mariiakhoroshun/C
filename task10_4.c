#include <stdio.h>

typedef struct {
    int numerator;
    unsigned int denominator;
} Rational;

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int input_rational(Rational *r) {
    long long den;
    if (scanf("%d %lld", &r->numerator, &den) != 2 || den <= 0) {
        return 0;
    }
    r->denominator = (unsigned int)den;
    return 1;
}

void output_rational(Rational r) {
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

void output_comparison(Rational a, Rational b, int cmp) {
    output_rational(a);
    if (cmp < 0) {
        printf(" < ");
    } else if (cmp > 0) {
        printf(" > ");
    } else {
        printf(" == ");
    }
    output_rational(b);
    printf("\n");
}

int main(void) {
    Rational r1, r2;

    printf("Enter first rational number (numerator denominator): ");
    if (!input_rational(&r1)) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter second rational number (numerator denominator): ");
    if (!input_rational(&r2)) {
        printf("Invalid input.\n");
        return 1;
    }

    Rational reduced1 = reduce_rational(r1);
    Rational reduced2 = reduce_rational(r2);
    printf("First reduced: ");
    output_rational(reduced1);
    printf("\nSecond reduced: ");
    output_rational(reduced2);
    printf("\n");

    Rational sum = add_rational(r1, r2);
    printf("Sum: ");
    output_rational(sum);
    printf("\n");

    Rational prod = multiply_rational(r1, r2);
    printf("Product: ");
    output_rational(prod);
    printf("\n");

    int cmp = compare_rational(r1, r2);
    printf("Comparison: ");
    output_comparison(r1, r2, cmp);

    return 0;
}
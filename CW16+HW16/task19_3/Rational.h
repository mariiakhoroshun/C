#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

namespace task19_3 {

class Rational {
private:
    int nominator;
    unsigned int denominator;

    static unsigned long long gcd_ull(unsigned long long a, unsigned long long b);
    static Rational from_ll(long long nom, long long denom);
    void reduce();

public:
    Rational();
    Rational(int nom, int denom = 1);

    int get_nominator() const;
    unsigned int get_denominator() const;

    Rational operator+() const;
    Rational operator-() const;

    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);

    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;
    bool operator<(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator>=(const Rational& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Rational& r);
    friend std::istream& operator>>(std::istream& in, Rational& r);
};

}

#endif
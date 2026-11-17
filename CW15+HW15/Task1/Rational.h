#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
private:
    int nominator;
    unsigned int denominator;

    unsigned int gcd(unsigned int a, unsigned int b) const;
    void reduce();

public:
    Rational();
    Rational(int nom, int denom);

    void set_nominator(int nom);
    bool set_denominator(int denom);

    int get_nominator() const;
    unsigned int get_denominator() const;
    double to_double() const;

    bool input();
    void print() const;

    Rational add(const Rational& other) const;
    Rational multiply(const Rational& other) const;

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

#endif
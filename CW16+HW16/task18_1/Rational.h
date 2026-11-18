#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

namespace task1 {

class Rational {
private:
    int nominator;
    unsigned int denominator;

    unsigned int gcd(unsigned int a, unsigned int b) const;
    void reduce();

public:
    Rational();
    Rational(int nom, int denom);

    int get_nominator() const;
    unsigned int get_denominator() const;

    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;
    bool operator<(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator>=(const Rational& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Rational& r);
    friend std::istream& operator>>(std::istream& in, Rational& r);
};

template <typename T1, typename T2>
auto get_max(const T1& a, const T2& b) -> decltype((a > b) ? a : b) {
    return (a > b) ? a : b;
}

const char* get_max(const char* a, const char* b);

}

#endif
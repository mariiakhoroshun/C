#include "Rational.h"
#include <cstring>

namespace task1 {

unsigned int Rational::gcd(unsigned int a, unsigned int b) const {
    while (b != 0) {
        unsigned int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void Rational::reduce() {
    if (nominator == 0) {
        denominator = 1;
        return;
    }
    unsigned int abs_nom = nominator < 0
        ? static_cast<unsigned int>(-static_cast<long long>(nominator))
        : static_cast<unsigned int>(nominator);
    unsigned int divisor = gcd(abs_nom, denominator);
    nominator /= static_cast<int>(divisor);
    denominator /= divisor;
}

Rational::Rational() : nominator(0), denominator(1) {}

Rational::Rational(int nom, int denom) {
    if (denom == 0) {
        nominator = 0;
        denominator = 1;
    } else if (denom < 0) {
        nominator = -nom;
        denominator = static_cast<unsigned int>(-static_cast<long long>(denom));
    } else {
        nominator = nom;
        denominator = static_cast<unsigned int>(denom);
    }
    reduce();
}

int Rational::get_nominator() const {
    return nominator;
}

unsigned int Rational::get_denominator() const {
    return denominator;
}

bool Rational::operator==(const Rational& other) const {
    return nominator == other.nominator && denominator == other.denominator;
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

bool Rational::operator<(const Rational& other) const {
    return static_cast<long long>(nominator) * other.denominator <
           static_cast<long long>(other.nominator) * denominator;
}

bool Rational::operator<=(const Rational& other) const {
    return !(*this > other);
}

bool Rational::operator>(const Rational& other) const {
    return static_cast<long long>(nominator) * other.denominator >
           static_cast<long long>(other.nominator) * denominator;
}

bool Rational::operator>=(const Rational& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& out, const Rational& r) {
    out << r.nominator << "/" << r.denominator;
    return out;
}

std::istream& operator>>(std::istream& in, Rational& r) {
    int nom = 0;
    int denom = 1;
    if (!(in >> nom >> denom)) {
        return in;
    }
    if (denom == 0) {
        in.setstate(std::ios::failbit);
        return in;
    }
    r = Rational(nom, denom);
    return in;
}

const char* get_max(const char* a, const char* b) {
    return (std::strcmp(a, b) > 0) ? a : b;
}

}
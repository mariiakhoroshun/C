#include "Rational.h"
#include <stdexcept>

namespace task19_3 {

unsigned long long Rational::gcd_ull(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

Rational Rational::from_ll(long long nom, long long denom) {
    if (denom == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    if (nom == 0) {
        return Rational(0, 1);
    }
    if (denom < 0) {
        nom = -nom;
        denom = -denom;
    }
    unsigned long long abs_nom = (nom < 0)
        ? static_cast<unsigned long long>(-nom)
        : static_cast<unsigned long long>(nom);
    unsigned long long abs_denom = static_cast<unsigned long long>(denom);
    unsigned long long g = gcd_ull(abs_nom, abs_denom);
    return Rational(static_cast<int>(nom / static_cast<long long>(g)),
                    static_cast<int>(denom / static_cast<long long>(g)));
}

void Rational::reduce() {
    if (nominator == 0) {
        denominator = 1;
        return;
    }
    unsigned long long abs_nom = (nominator < 0)
        ? static_cast<unsigned long long>(-static_cast<long long>(nominator))
        : static_cast<unsigned long long>(nominator);
    unsigned long long g = gcd_ull(abs_nom, denominator);
    nominator /= static_cast<int>(g);
    denominator /= static_cast<unsigned int>(g);
}

Rational::Rational() : nominator(0), denominator(1) {}

Rational::Rational(int nom, int denom) {
    if (denom == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    if (denom < 0) {
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

Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    return Rational(-nominator, static_cast<int>(denominator));
}

Rational Rational::operator+(const Rational& other) const {
    long long num = static_cast<long long>(nominator) * other.denominator +
                    static_cast<long long>(other.nominator) * denominator;
    long long den = static_cast<long long>(denominator) * other.denominator;
    return from_ll(num, den);
}

Rational Rational::operator-(const Rational& other) const {
    long long num = static_cast<long long>(nominator) * other.denominator -
                    static_cast<long long>(other.nominator) * denominator;
    long long den = static_cast<long long>(denominator) * other.denominator;
    return from_ll(num, den);
}

Rational Rational::operator*(const Rational& other) const {
    long long num = static_cast<long long>(nominator) * other.nominator;
    long long den = static_cast<long long>(denominator) * other.denominator;
    return from_ll(num, den);
}

Rational Rational::operator/(const Rational& other) const {
    if (other.nominator == 0) {
        throw std::invalid_argument("Division by zero rational");
    }
    long long num = static_cast<long long>(nominator) * other.denominator;
    long long den = static_cast<long long>(denominator) * other.nominator;
    return from_ll(num, den);
}

Rational& Rational::operator+=(const Rational& other) {
    *this = *this + other;
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    *this = *this - other;
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    *this = *this * other;
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    *this = *this / other;
    return *this;
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
    if (!(in >> nom)) {
        return in;
    }
    in >> std::ws;
    if (in.peek() == '/') {
        in.get();
    }
    if (!(in >> denom)) {
        return in;
    }
    if (denom == 0) {
        in.setstate(std::ios::failbit);
        return in;
    }
    r = Rational(nom, denom);
    return in;
}

}
#include "Rational.h"

unsigned int Rational::gcd(unsigned int a, unsigned int b) const {
    while (b != 0) {
        unsigned int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void Rational::reduce() {
    if (denominator == 0) {
        denominator = 1;
    }
    if (nominator == 0) {
        denominator = 1;
        return;
    }
    unsigned int abs_nom = (nominator < 0)
        ? static_cast<unsigned int>(-static_cast<long long>(nominator))
        : static_cast<unsigned int>(nominator);
    unsigned int d = gcd(abs_nom, denominator);
    nominator /= static_cast<int>(d);
    denominator /= d;
}

Rational::Rational() : nominator(1), denominator(1) {}

Rational::Rational(int nom, int denom) {
    if (denom == 0) {
        nominator = nom;
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

void Rational::set_nominator(int nom) {
    nominator = nom;
    reduce();
}

bool Rational::set_denominator(int denom) {
    if (denom <= 0) {
        return false;
    }
    denominator = static_cast<unsigned int>(denom);
    reduce();
    return true;
}

int Rational::get_nominator() const {
    return nominator;
}

unsigned int Rational::get_denominator() const {
    return denominator;
}

double Rational::to_double() const {
    return static_cast<double>(nominator) / static_cast<double>(denominator);
}

bool Rational::input() {
    int nom = 0;
    int denom = 0;
    if (!(std::cin >> nom)) {
        return false;
    }
    std::cin >> std::ws;
    if (std::cin.peek() == '/') {
        std::cin.get();
    }
    if (!(std::cin >> denom)) {
        return false;
    }
    if (denom == 0) {
        return false;
    }
    if (denom < 0) {
        nom = -nom;
        denom = -denom;
    }
    nominator = nom;
    denominator = static_cast<unsigned int>(denom);
    reduce();
    return true;
}

void Rational::print() const {
    std::cout << nominator << "/" << denominator;
}

Rational Rational::add(const Rational& other) const {
    long long num = static_cast<long long>(nominator) * static_cast<long long>(other.denominator)
                  + static_cast<long long>(other.nominator) * static_cast<long long>(denominator);
    long long den = static_cast<long long>(denominator) * static_cast<long long>(other.denominator);
    return Rational(static_cast<int>(num), static_cast<int>(den));
}

Rational Rational::multiply(const Rational& other) const {
    long long num = static_cast<long long>(nominator) * static_cast<long long>(other.nominator);
    long long den = static_cast<long long>(denominator) * static_cast<long long>(other.denominator);
    return Rational(static_cast<int>(num), static_cast<int>(den));
}

Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    return Rational(-nominator, static_cast<int>(denominator));
}

Rational Rational::operator+(const Rational& other) const {
    return add(other);
}

Rational Rational::operator-(const Rational& other) const {
    long long num = static_cast<long long>(nominator) * static_cast<long long>(other.denominator)
                  - static_cast<long long>(other.nominator) * static_cast<long long>(denominator);
    long long den = static_cast<long long>(denominator) * static_cast<long long>(other.denominator);
    return Rational(static_cast<int>(num), static_cast<int>(den));
}

Rational Rational::operator*(const Rational& other) const {
    return multiply(other);
}

Rational Rational::operator/(const Rational& other) const {
    if (other.nominator == 0) {
        return Rational(0, 1);
    }
    long long num = static_cast<long long>(nominator) * static_cast<long long>(other.denominator);
    long long den = static_cast<long long>(denominator) * static_cast<long long>(other.nominator);
    if (den < 0) {
        num = -num;
        den = -den;
    }
    return Rational(static_cast<int>(num), static_cast<int>(den));
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
    return static_cast<long long>(nominator) * static_cast<long long>(other.denominator)
         < static_cast<long long>(other.nominator) * static_cast<long long>(denominator);
}

bool Rational::operator<=(const Rational& other) const {
    return *this < other || *this == other;
}

bool Rational::operator>(const Rational& other) const {
    return other < *this;
}

bool Rational::operator>=(const Rational& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& out, const Rational& r) {
    out << r.nominator << "/" << r.denominator;
    return out;
}

std::istream& operator>>(std::istream& in, Rational& r) {
    if (!r.input()) {
        in.setstate(std::ios::failbit);
    }
    return in;
}
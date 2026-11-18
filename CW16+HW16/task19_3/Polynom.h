#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <list>
#include <vector>

namespace task19_3 {

template <typename T>
class Polynom {
private:
    std::list<T> coeffs;

    void normalize() {
        while (coeffs.size() > 1 && coeffs.back() == T()) {
            coeffs.pop_back();
        }
        if (coeffs.empty()) {
            coeffs.push_back(T());
        }
    }

public:
    Polynom() {
        coeffs.push_back(T());
    }

    explicit Polynom(const std::list<T>& coefficients) : coeffs(coefficients) {
        normalize();
    }

    int degree() const {
        return static_cast<int>(coeffs.size()) - 1;
    }

    const std::list<T>& get_coefficients() const {
        return coeffs;
    }

    bool input(std::istream& in = std::cin) {
        int deg = 0;
        if (!(in >> deg) || deg < 0) {
            return false;
        }
        std::list<T> temp;
        for (int i = 0; i <= deg; ++i) {
            T val = T();
            if (!(in >> val)) {
                return false;
            }
            temp.push_back(val);
        }
        coeffs = temp;
        normalize();
        return true;
    }

    void print(std::ostream& out = std::cout) const {
        bool first = true;
        int deg = 0;
        for (typename std::list<T>::const_iterator it = coeffs.begin(); it != coeffs.end(); ++it, ++deg) {
            if (*it == T() && coeffs.size() > 1) {
                continue;
            }
            if (!first) {
                out << " + ";
            }
            out << *it;
            if (deg > 0) {
                out << "*x^" << deg;
            }
            first = false;
        }
        if (first) {
            out << T();
        }
    }

    Polynom<T> add(const Polynom<T>& other) const {
        std::list<T> res;
        typename std::list<T>::const_iterator it1 = coeffs.begin();
        typename std::list<T>::const_iterator it2 = other.coeffs.begin();

        while (it1 != coeffs.end() && it2 != other.coeffs.end()) {
            res.push_back(*it1 + *it2);
            ++it1;
            ++it2;
        }
        while (it1 != coeffs.end()) {
            res.push_back(*it1);
            ++it1;
        }
        while (it2 != other.coeffs.end()) {
            res.push_back(*it2);
            ++it2;
        }
        return Polynom<T>(res);
    }

    Polynom<T> multiply(const Polynom<T>& other) const {
        std::size_t res_size = coeffs.size() + other.coeffs.size() - 1;
        std::vector<T> prod(res_size, T());

        std::size_t i = 0;
        for (typename std::list<T>::const_iterator it1 = coeffs.begin(); it1 != coeffs.end(); ++it1, ++i) {
            std::size_t j = 0;
            for (typename std::list<T>::const_iterator it2 = other.coeffs.begin(); it2 != other.coeffs.end(); ++it2, ++j) {
                prod[i + j] += (*it1) * (*it2);
            }
        }

        std::list<T> res;
        for (std::size_t k = 0; k < prod.size(); ++k) {
            res.push_back(prod[k]);
        }
        return Polynom<T>(res);
    }

    T evaluate(const T& x) const {
        T result = T();
        for (typename std::list<T>::const_reverse_iterator rit = coeffs.rbegin(); rit != coeffs.rend(); ++rit) {
            result = result * x + (*rit);
        }
        return result;
    }

    Polynom<T> operator+(const Polynom<T>& other) const {
        return add(other);
    }

    Polynom<T> operator*(const Polynom<T>& other) const {
        return multiply(other);
    }

    T operator()(const T& x) const {
        return evaluate(x);
    }

    bool operator==(const Polynom<T>& other) const {
        return coeffs == other.coeffs;
    }

    bool operator!=(const Polynom<T>& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& out, const Polynom<T>& p) {
        p.print(out);
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Polynom<T>& p) {
        if (!p.input(in)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
};

}

#endif
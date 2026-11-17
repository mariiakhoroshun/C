#include "Polynomial.h"
#include <fstream>
#include <cmath>

Polynomial::Polynomial() : n(0), coeffs(nullptr) {}

Polynomial::Polynomial(int count) : n(0), coeffs(nullptr) {
    if (count > 0) {
        n = count;
        coeffs = new double[n];
        for (int i = 0; i < n; i++) {
            coeffs[i] = 0.0;
        }
    }
}

Polynomial::Polynomial(int count, const double* values) : n(0), coeffs(nullptr) {
    if (count > 0 && values != nullptr) {
        n = count;
        coeffs = new double[n];
        for (int i = 0; i < n; i++) {
            coeffs[i] = values[i];
        }
    }
}

Polynomial::Polynomial(const Polynomial& other) : n(other.n), coeffs(nullptr) {
    if (n > 0 && other.coeffs != nullptr) {
        coeffs = new double[n];
        for (int i = 0; i < n; i++) {
            coeffs[i] = other.coeffs[i];
        }
    }
}

Polynomial::~Polynomial() {
    delete[] coeffs;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this == &other) {
        return *this;
    }

    double* new_coeffs = nullptr;
    if (other.n > 0 && other.coeffs != nullptr) {
        new_coeffs = new double[other.n];
        for (int i = 0; i < other.n; i++) {
            new_coeffs[i] = other.coeffs[i];
        }
    }

    delete[] coeffs;
    n = other.n;
    coeffs = new_coeffs;
    return *this;
}

int Polynomial::size() const {
    return n;
}

bool Polynomial::fill_from_array(const double* values, int count) {
    if (count <= 0 || values == nullptr) {
        return false;
    }
    double* new_coeffs = new double[count];
    for (int i = 0; i < count; i++) {
        new_coeffs[i] = values[i];
    }
    delete[] coeffs;
    n = count;
    coeffs = new_coeffs;
    return true;
}

bool Polynomial::fill_from_console() {
    if (n <= 0 || coeffs == nullptr) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (!(std::cin >> coeffs[i])) {
            return false;
        }
    }
    return true;
}

bool Polynomial::set_coefficient(int index, double value) {
    if (index < 0 || index >= n || coeffs == nullptr) {
        return false;
    }
    coeffs[index] = value;
    return true;
}

double Polynomial::get_coefficient(int index) const {
    if (index < 0 || index >= n || coeffs == nullptr) {
        return 0.0;
    }
    return coeffs[index];
}

void Polynomial::print() const {
    if (n <= 0 || coeffs == nullptr) {
        std::cout << "0";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            std::cout << coeffs[i];
        } else if (coeffs[i] >= 0.0) {
            std::cout << " + " << coeffs[i] << "*x^" << i;
        } else {
            std::cout << " - " << -coeffs[i] << "*x^" << i;
        }
    }
}

double& Polynomial::operator[](int index) {
    return coeffs[index];
}

double Polynomial::operator[](int index) const {
    return coeffs[index];
}

bool Polynomial::operator==(const Polynomial& other) const {
    if (n != other.n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (std::fabs(coeffs[i] - other.coeffs[i]) >= 1e-9) {
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Polynomial& p) {
    if (p.n <= 0 || p.coeffs == nullptr) {
        out << "0";
        return out;
    }
    for (int i = 0; i < p.n; i++) {
        if (i == 0) {
            out << p.coeffs[i];
        } else if (p.coeffs[i] >= 0.0) {
            out << " + " << p.coeffs[i] << "*x^" << i;
        } else {
            out << " - " << -p.coeffs[i] << "*x^" << i;
        }
    }
    return out;
}

std::istream& operator>>(std::istream& in, Polynomial& p) {
    int count = 0;
    if (!(in >> count) || count <= 0) {
        in.setstate(std::ios::failbit);
        return in;
    }
    double* new_coeffs = new double[count];
    for (int i = 0; i < count; i++) {
        if (!(in >> new_coeffs[i])) {
            delete[] new_coeffs;
            in.setstate(std::ios::failbit);
            return in;
        }
    }
    delete[] p.coeffs;
    p.n = count;
    p.coeffs = new_coeffs;
    return in;
}

bool write_to_binary(const std::string& filename, const Polynomial& p) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout.is_open()) {
        return false;
    }
    fout.write(reinterpret_cast<const char*>(&p.n), sizeof(p.n));
    if (p.n > 0 && p.coeffs != nullptr) {
        fout.write(
            reinterpret_cast<const char*>(p.coeffs),
            static_cast<std::streamsize>(p.n) * sizeof(double)
        );
    }
    return fout.good();
}

bool read_from_binary(const std::string& filename, Polynomial& p) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin.is_open()) {
        return false;
    }
    int count = 0;
    if (!fin.read(reinterpret_cast<char*>(&count), sizeof(count)) || count < 0) {
        return false;
    }
    double* new_coeffs = nullptr;
    if (count > 0) {
        new_coeffs = new double[count];
        if (!fin.read(
                reinterpret_cast<char*>(new_coeffs),
                static_cast<std::streamsize>(count) * sizeof(double)
            )) {
            delete[] new_coeffs;
            return false;
        }
    }
    delete[] p.coeffs;
    p.n = count;
    p.coeffs = new_coeffs;
    return true;
}
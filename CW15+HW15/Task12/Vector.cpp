#include "Vector.h"
#include <fstream>
#include <cmath>

Vector::Vector() : n(0), data(nullptr) {}

Vector::Vector(int count) : n(0), data(nullptr) {
    if (count > 0) {
        n = count;
        data = new double[n];
        for (int i = 0; i < n; i++) {
            data[i] = 0.0;
        }
    }
}

Vector::Vector(int count, const double* values) : n(0), data(nullptr) {
    if (count > 0 && values != nullptr) {
        n = count;
        data = new double[n];
        for (int i = 0; i < n; i++) {
            data[i] = values[i];
        }
    }
}

Vector::Vector(const Vector& other) : n(other.n), data(nullptr) {
    if (n > 0 && other.data != nullptr) {
        data = new double[n];
        for (int i = 0; i < n; i++) {
            data[i] = other.data[i];
        }
    }
}

Vector::~Vector() {
    delete[] data;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    double* new_data = nullptr;
    if (other.n > 0 && other.data != nullptr) {
        new_data = new double[other.n];
        for (int i = 0; i < other.n; i++) {
            new_data[i] = other.data[i];
        }
    }

    delete[] data;
    n = other.n;
    data = new_data;
    return *this;
}

int Vector::size() const {
    return n;
}

bool Vector::fill_from_array(const double* values, int count) {
    if (count <= 0 || values == nullptr) {
        return false;
    }
    double* new_data = new double[count];
    for (int i = 0; i < count; i++) {
        new_data[i] = values[i];
    }
    delete[] data;
    n = count;
    data = new_data;
    return true;
}

bool Vector::fill_from_console() {
    if (n <= 0 || data == nullptr) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (!(std::cin >> data[i])) {
            return false;
        }
    }
    return true;
}

bool Vector::set_element(int index, double value) {
    if (index < 0 || index >= n || data == nullptr) {
        return false;
    }
    data[index] = value;
    return true;
}

double Vector::get_element(int index) const {
    if (index < 0 || index >= n || data == nullptr) {
        return 0.0;
    }
    return data[index];
}

void Vector::print() const {
    std::cout << "(";
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << data[i];
    }
    std::cout << ")";
}

bool Vector::read_from_file(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        return false;
    }
    int count = 0;
    if (!(fin >> count) || count <= 0) {
        return false;
    }
    double* new_data = new double[count];
    for (int i = 0; i < count; i++) {
        if (!(fin >> new_data[i])) {
            delete[] new_data;
            return false;
        }
    }
    delete[] data;
    n = count;
    data = new_data;
    return true;
}

bool Vector::write_to_file(const std::string& filename) const {
    if (n <= 0 || data == nullptr) {
        return false;
    }
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }
    fout << n << "\n";
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            fout << " ";
        }
        fout << data[i];
    }
    fout << "\n";
    return fout.good();
}

bool Vector::dot_product(const Vector& other, double& result, std::string& error_msg) const {
    if (n <= 0 || other.n <= 0 || data == nullptr || other.data == nullptr) {
        error_msg = "Dot product is impossible: vectors must have positive dimension (N > 0).";
        return false;
    }
    if (n != other.n) {
        error_msg = "Dot product is impossible: vector dimensions do not match ("
                  + std::to_string(n) + " != " + std::to_string(other.n) + ").";
        return false;
    }
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i] * other.data[i];
    }
    result = sum;
    return true;
}

bool Vector::cross_product(const Vector& other, Vector& result, std::string& error_msg) const {
    if (n != other.n) {
        error_msg = "Cross product is impossible: vector dimensions differ ("
                  + std::to_string(n) + " != " + std::to_string(other.n)
                  + "), and cross product is defined only for 3D vectors.";
        return false;
    }
    if (n != 3 || data == nullptr || other.data == nullptr) {
        error_msg = "Cross product is impossible: standard vector product is defined only for 3D vectors (got dimension "
                  + std::to_string(n) + ").";
        return false;
    }
    double c[3];
    c[0] = data[1] * other.data[2] - data[2] * other.data[1];
    c[1] = data[2] * other.data[0] - data[0] * other.data[2];
    c[2] = data[0] * other.data[1] - data[1] * other.data[0];
    result = Vector(3, c);
    return true;
}

double& Vector::operator[](int index) {
    return data[index];
}

double Vector::operator[](int index) const {
    return data[index];
}

bool Vector::operator==(const Vector& other) const {
    if (n != other.n) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (std::fabs(data[i] - other.data[i]) >= 1e-9) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << "(";
    for (int i = 0; i < v.n; i++) {
        if (i > 0) {
            out << ", ";
        }
        out << v.data[i];
    }
    out << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Vector& v) {
    int count = 0;
    if (!(in >> count) || count <= 0) {
        in.setstate(std::ios::failbit);
        return in;
    }
    double* new_data = new double[count];
    for (int i = 0; i < count; i++) {
        if (!(in >> new_data[i])) {
            delete[] new_data;
            in.setstate(std::ios::failbit);
            return in;
        }
    }
    delete[] v.data;
    v.n = count;
    v.data = new_data;
    return in;
}
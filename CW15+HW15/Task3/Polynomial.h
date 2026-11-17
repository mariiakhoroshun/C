#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <string>

class Polynomial {
private:
    int n;
    double* coeffs;

public:
    Polynomial();
    explicit Polynomial(int count);
    Polynomial(int count, const double* values);
    Polynomial(const Polynomial& other);
    ~Polynomial();

    Polynomial& operator=(const Polynomial& other);

    int size() const;

    bool fill_from_array(const double* values, int count);
    bool fill_from_console();
    bool set_coefficient(int index, double value);
    double get_coefficient(int index) const;

    void print() const;

    double& operator[](int index);
    double operator[](int index) const;

    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Polynomial& p);
    friend std::istream& operator>>(std::istream& in, Polynomial& p);

    friend bool write_to_binary(const std::string& filename, const Polynomial& p);
    friend bool read_from_binary(const std::string& filename, Polynomial& p);
};

#endif
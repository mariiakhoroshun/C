#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <string>

class Vector {
private:
    int n;
    double* data;

public:
    Vector();
    explicit Vector(int count);
    Vector(int count, const double* values);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    int size() const;

    bool fill_from_array(const double* values, int count);
    bool fill_from_console();
    bool set_element(int index, double value);
    double get_element(int index) const;

    void print() const;
    bool read_from_file(const std::string& filename);
    bool write_to_file(const std::string& filename) const;

    bool dot_product(const Vector& other, double& result, std::string& error_msg) const;
    bool cross_product(const Vector& other, Vector& result, std::string& error_msg) const;

    double& operator[](int index);
    double operator[](int index) const;

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Vector& v);
    friend std::istream& operator>>(std::istream& in, Vector& v);
};

#endif
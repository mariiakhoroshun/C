#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include "Polynomial.h"

void test_polynomial() {
    bool ok = true;

    Polynomial p_sized(3);
    if (p_sized.size() != 3 || std::fabs(p_sized.get_coefficient(1)) >= 1e-9) {
        ok = false;
    }

    double init_vals[3] = { 1.5, -2.0, 4.0 };
    Polynomial p_init(3, init_vals);
    if (p_init.size() != 3 || std::fabs(p_init.get_coefficient(2) - 4.0) >= 1e-9) {
        ok = false;
    }

    if (!p_init.set_coefficient(1, 3.5) || std::fabs(p_init.get_coefficient(1) - 3.5) >= 1e-9) {
        ok = false;
    }
    if (p_init.set_coefficient(5, 10.0)) {
        ok = false;
    }

    Polynomial p_copy(p_init);
    p_copy.set_coefficient(0, 99.0);
    if (std::fabs(p_init.get_coefficient(0) - 1.5) >= 1e-9) {
        ok = false;
    }

    Polynomial p_assigned;
    p_assigned = p_init;
    p_assigned = p_assigned;
    p_assigned.set_coefficient(2, -7.0);
    if (std::fabs(p_init.get_coefficient(2) - 4.0) >= 1e-9) {
        ok = false;
    }

    const std::string temp_file = "temp_poly_test.bin";
    Polynomial p_loaded;
    if (!write_to_binary(temp_file, p_init) ||
        !read_from_binary(temp_file, p_loaded) ||
        p_loaded != p_init) {
        ok = false;
    }
    std::remove(temp_file.c_str());

    std::cout << (ok ? "[TESTS PASSED]\n\n" : "[TESTS FAILED]\n\n");
}

int main() {
    test_polynomial();

    int n = 0;
    std::cout << "Enter number of polynomial coefficients N (positive integer): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid N.\n";
        return 1;
    }

    Polynomial p(n);
    std::cout << "Enter " << n << " real coefficients (a_0, a_1, ..., a_" << (n - 1) << "): ";
    if (!p.fill_from_console()) {
        std::cout << "Invalid coefficients input.\n";
        return 1;
    }

    std::cout << "Polynomial P(x) = ";
    p.print();
    std::cout << "\n";

    int idx = 0;
    double new_val = 0.0;
    std::cout << "Enter coefficient index to update (0 to " << (n - 1) << ") and new value: ";
    if (!(std::cin >> idx >> new_val) || !p.set_coefficient(idx, new_val)) {
        std::cout << "Invalid index or value.\n";
        return 1;
    }
    std::cout << "Updated P(x) = " << p << "\n";

    Polynomial p_copy(p);
    Polynomial p_assigned;
    p_assigned = p;
    std::cout << "Copy constructor P_copy(x) = " << p_copy << "\n";
    std::cout << "Assignment operator P_assigned(x) = " << p_assigned << "\n\n";

    std::string filename;
    std::cout << "Enter binary file name to save polynomial (e.g. poly.bin): ";
    if (!(std::cin >> filename) || filename.empty()) {
        std::cout << "Invalid file name.\n";
        return 1;
    }

    if (!write_to_binary(filename, p)) {
        std::cout << "Error writing polynomial to binary file.\n";
        return 1;
    }
    std::cout << "Polynomial saved to binary file '" << filename << "'.\n";

    Polynomial p_from_file;
    if (!read_from_binary(filename, p_from_file)) {
        std::cout << "Error reading polynomial from binary file.\n";
        return 1;
    }
    std::cout << "Polynomial loaded from binary file: P_file(x) = " << p_from_file << "\n";

    return 0;
}
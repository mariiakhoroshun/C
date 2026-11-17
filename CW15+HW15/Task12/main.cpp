#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include "Vector.h"

bool read_dynamic_array(double*& arr, int& count) {
    if (!(std::cin >> count) || count <= 0) {
        return false;
    }
    arr = new double[count];
    for (int i = 0; i < count; i++) {
        if (!(std::cin >> arr[i])) {
            delete[] arr;
            arr = nullptr;
            return false;
        }
    }
    return true;
}

void test_vector() {
    bool ok = true;

    Vector v_empty(3);
    if (v_empty.size() != 3 || std::fabs(v_empty.get_element(0)) >= 1e-9) {
        ok = false;
    }
    if (!v_empty.set_element(1, 5.5) || std::fabs(v_empty.get_element(1) - 5.5) >= 1e-9) {
        ok = false;
    }
    if (v_empty.set_element(4, 1.0)) {
        ok = false;
    }

    double a_vals[3] = { 1.0, 0.0, 0.0 };
    double b_vals[3] = { 0.0, 1.0, 0.0 };
    double c_vals[2] = { 2.0, 3.0 };

    Vector va(3, a_vals);
    Vector vb(3, b_vals);
    Vector vc(2, c_vals);

    Vector va_copy(va);
    va_copy.set_element(0, 9.0);
    if (std::fabs(va.get_element(0) - 1.0) >= 1e-9) {
        ok = false;
    }

    double dot_res = 0.0;
    std::string err;
    if (!va.dot_product(vb, dot_res, err) || std::fabs(dot_res) >= 1e-9) {
        ok = false;
    }
    if (va.dot_product(vc, dot_res, err)) {
        ok = false;
    }

    Vector cross_res;
    double expected_z[3] = { 0.0, 0.0, 1.0 };
    if (!va.cross_product(vb, cross_res, err) || cross_res != Vector(3, expected_z)) {
        ok = false;
    }
    if (vc.cross_product(vc, cross_res, err)) {
        ok = false;
    }

    const std::string temp_file = "temp_vec_test.txt";
    Vector v_loaded;
    if (!va.write_to_file(temp_file) || !v_loaded.read_from_file(temp_file) || v_loaded != va) {
        ok = false;
    }
    std::remove(temp_file.c_str());

    std::cout << (ok ? "[TESTS PASSED]\n\n" : "[TESTS FAILED]\n\n");
}

int main() {
    test_vector();

    double* raw_a = nullptr;
    int m = 0;
    std::cout << "Enter dimension m of first vector followed by m real numbers (e.g. 3 1 2 3): ";
    if (!read_dynamic_array(raw_a, m)) {
        std::cout << "Invalid input for first vector.\n";
        return 1;
    }

    double* raw_b = nullptr;
    int n = 0;
    std::cout << "Enter dimension n of second vector followed by n real numbers (e.g. 3 4 5 6): ";
    if (!read_dynamic_array(raw_b, n)) {
        std::cout << "Invalid input for second vector.\n";
        delete[] raw_a;
        return 1;
    }

    Vector v1(m, raw_a);
    Vector v2(n, raw_b);
    delete[] raw_a;
    delete[] raw_b;

    std::cout << "First vector v1 = ";
    v1.print();
    std::cout << "\nSecond vector v2 = ";
    v2.print();
    std::cout << "\n\n";

    std::string file1;
    std::string file2;
    std::cout << "Enter file name to save v1 (e.g. vec1.txt): ";
    if (!(std::cin >> file1) || file1.empty()) {
        std::cout << "Invalid file name.\n";
        return 1;
    }
    std::cout << "Enter file name to save v2 (e.g. vec2.txt): ";
    if (!(std::cin >> file2) || file2.empty()) {
        std::cout << "Invalid file name.\n";
        return 1;
    }

    if (!v1.write_to_file(file1) || !v2.write_to_file(file2)) {
        std::cout << "Error writing vectors to files.\n";
        return 1;
    }

    Vector v1_from_file;
    Vector v2_from_file;
    if (!v1_from_file.read_from_file(file1) || !v2_from_file.read_from_file(file2)) {
        std::cout << "Error reading vectors from files.\n";
        return 1;
    }

    std::cout << "\nVectors loaded from files:\n";
    std::cout << "v1_file = " << v1_from_file << "\n";
    std::cout << "v2_file = " << v2_from_file << "\n\n";

    double dot_val = 0.0;
    std::string dot_err;
    if (v1_from_file.dot_product(v2_from_file, dot_val, dot_err)) {
        std::cout << "Dot product (v1 . v2) = " << dot_val << "\n";
    } else {
        std::cout << dot_err << "\n";
    }

    Vector cross_vec;
    std::string cross_err;
    if (v1_from_file.cross_product(v2_from_file, cross_vec, cross_err)) {
        std::cout << "Cross product (v1 x v2) = " << cross_vec << "\n";
    } else {
        std::cout << cross_err << "\n";
    }

    return 0;
}
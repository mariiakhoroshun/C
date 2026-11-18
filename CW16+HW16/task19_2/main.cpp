#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cmath>

namespace task19_2 {

bool input_vector(int d, std::vector<double>& vec, std::istream& in = std::cin) {
    if (d <= 0) {
        return false;
    }
    vec.resize(d);
    for (int i = 0; i < d; ++i) {
        if (!(in >> vec[i])) {
            return false;
        }
    }
    return true;
}

bool input_vectors(int n, int d, std::vector<std::vector<double>>& vectors, std::istream& in = std::cin) {
    if (n <= 0 || d <= 0) {
        return false;
    }
    vectors.resize(n);
    for (int i = 0; i < n; ++i) {
        if (!input_vector(d, vectors[i], in)) {
            return false;
        }
    }
    return true;
}

double vector_norm(const std::vector<double>& vec) {
    double sum_sq = 0.0;
    for (std::size_t i = 0; i < vec.size(); ++i) {
        sum_sq += vec[i] * vec[i];
    }
    return std::sqrt(sum_sq);
}

double sum_of_norms(const std::vector<std::vector<double>>& vectors) {
    double total = 0.0;
    for (std::size_t i = 0; i < vectors.size(); ++i) {
        total += vector_norm(vectors[i]);
    }
    return total;
}

void print_vector(const std::vector<double>& vec, std::ostream& out = std::cout) {
    out << "(";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i + 1 < vec.size()) {
            out << ", ";
        }
    }
    out << ")";
}

}

void test_vector_norms() {
    std::vector<double> v1 = {3.0, 4.0};
    std::vector<double> v2 = {0.0, 0.0};
    std::vector<std::vector<double>> set1 = {v1, v2};
    bool t1 = (std::fabs(task19_2::vector_norm(v1) - 5.0) < 1e-9 &&
               std::fabs(task19_2::sum_of_norms(set1) - 5.0) < 1e-9);

    std::vector<double> v3 = {1.0, 2.0, 2.0};
    std::vector<double> v4 = {-2.0, -3.0, 6.0};
    std::vector<std::vector<double>> set2 = {v3, v4};
    bool t2 = (std::fabs(task19_2::vector_norm(v3) - 3.0) < 1e-9 &&
               std::fabs(task19_2::vector_norm(v4) - 7.0) < 1e-9 &&
               std::fabs(task19_2::sum_of_norms(set2) - 10.0) < 1e-9);

    std::istringstream iss("1.0 2.0 2.0 -2.0 -3.0 6.0");
    std::vector<std::vector<double>> parsed_set;
    bool input_ok = task19_2::input_vectors(2, 3, parsed_set, iss);
    bool t3 = (input_ok && std::fabs(task19_2::sum_of_norms(parsed_set) - 10.0) < 1e-9);

    std::vector<double> v5 = {-4.5};
    std::vector<std::vector<double>> set3 = {v5};
    bool t4 = (std::fabs(task19_2::sum_of_norms(set3) - 4.5) < 1e-9);

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (2D vectors): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (3D vectors with negatives): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (input_vectors stream parsing): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (1D vector): " << (t4 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_vector_norms();

    int d = 0;
    std::cout << "Enter vector dimension d (e.g. 3): ";
    if (!(std::cin >> d) || d <= 0) {
        std::cout << "Invalid dimension." << std::endl;
        return 1;
    }

    int n = 0;
    std::cout << "Enter number of vectors n (e.g. 2): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid number of vectors." << std::endl;
        return 1;
    }

    std::vector<std::vector<double>> vectors(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "Enter " << d << " coordinates for vector #" << (i + 1)
                  << " separated by space (e.g. 1.0 2.0 2.0): ";
        if (!task19_2::input_vector(d, vectors[i])) {
            std::cout << "Invalid vector coordinates." << std::endl;
            return 1;
        }
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\nEntered vectors and norms:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "v" << (i + 1) << " = ";
        task19_2::print_vector(vectors[i]);
        std::cout << ", norm = " << task19_2::vector_norm(vectors[i]) << std::endl;
    }
    std::cout << "Sum of vector norms: " << task19_2::sum_of_norms(vectors) << std::endl;

    return 0;
}
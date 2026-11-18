#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <utility>
#include <stdexcept>
#include <cmath>

namespace task19_4 {

bool input_matrix(int n, int m, std::vector<std::list<double>>& matrix, std::istream& in = std::cin) {
    if (n <= 0 || n >= 100 || m <= 0 || m >= 100) {
        return false;
    }
    matrix.clear();
    matrix.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double val = 0.0;
            if (!(in >> val)) {
                return false;
            }
            matrix[i].push_back(val);
        }
    }
    return true;
}

double row_max(const std::list<double>& row) {
    if (row.empty()) {
        throw std::invalid_argument("Matrix row cannot be empty");
    }
    std::list<double>::const_iterator it = row.begin();
    double max_val = *it;
    ++it;
    for (; it != row.end(); ++it) {
        if (*it > max_val) {
            max_val = *it;
        }
    }
    return max_val;
}

void sort_rows_by_max_desc(std::vector<std::list<double>>& matrix) {
    std::size_t n = matrix.size();
    if (n <= 1) {
        return;
    }

    std::vector<double> max_values(n);
    for (std::size_t i = 0; i < n; ++i) {
        max_values[i] = row_max(matrix[i]);
    }

    for (std::size_t i = 1; i < n; ++i) {
        std::size_t j = i;
        while (j > 0 && max_values[j - 1] < max_values[j]) {
            std::swap(max_values[j - 1], max_values[j]);
            std::swap(matrix[j - 1], matrix[j]);
            --j;
        }
    }
}

void print_matrix(const std::vector<std::list<double>>& matrix, std::ostream& out = std::cout) {
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::list<double>::const_iterator it = matrix[i].begin(); it != matrix[i].end(); ++it) {
            if (it != matrix[i].begin()) {
                out << " ";
            }
            out << *it;
        }
        out << "   (max = " << row_max(matrix[i]) << ")" << std::endl;
    }
}

}

void test_matrix_sort() {
    std::vector<std::list<double>> m1 = {
        {1.0, 5.0, 2.0},
        {9.0, 3.0, 4.0},
        {2.0, 7.0, 6.0}
    };
    task19_4::sort_rows_by_max_desc(m1);
    bool t1 = (std::fabs(task19_4::row_max(m1[0]) - 9.0) < 1e-9 &&
               std::fabs(task19_4::row_max(m1[1]) - 7.0) < 1e-9 &&
               std::fabs(task19_4::row_max(m1[2]) - 5.0) < 1e-9);

    std::vector<std::list<double>> m2 = {
        {-10.0, -5.0},
        {-2.0, -8.0},
        {-7.0, -6.0}
    };
    task19_4::sort_rows_by_max_desc(m2);
    bool t2 = (std::fabs(task19_4::row_max(m2[0]) + 2.0) < 1e-9 &&
               std::fabs(task19_4::row_max(m2[1]) + 5.0) < 1e-9 &&
               std::fabs(task19_4::row_max(m2[2]) + 6.0) < 1e-9);

    std::vector<std::list<double>> m3 = {
        {1.0, 4.0},
        {3.0, 4.0}
    };
    task19_4::sort_rows_by_max_desc(m3);
    bool t3 = (std::fabs(m3[0].front() - 1.0) < 1e-9 &&
               std::fabs(m3[1].front() - 3.0) < 1e-9);

    std::istringstream iss("10 20 30 5");
    std::vector<std::list<double>> m4;
    bool input_ok = task19_4::input_matrix(2, 2, m4, iss);
    task19_4::sort_rows_by_max_desc(m4);
    bool t4 = (input_ok &&
               std::fabs(task19_4::row_max(m4[0]) - 30.0) < 1e-9 &&
               std::fabs(task19_4::row_max(m4[1]) - 20.0) < 1e-9);

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (positive matrix rows): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (negative matrix rows): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (equal row maxima stability): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (stream input and sort): " << (t4 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_matrix_sort();

    int n = 0;
    int m = 0;
    std::cout << "Enter natural numbers n and m (1 <= n, m < 100, e.g. 3 3): ";
    if (!(std::cin >> n >> m) || n <= 0 || n >= 100 || m <= 0 || m >= 100) {
        std::cout << "Invalid matrix dimensions." << std::endl;
        return 1;
    }

    std::vector<std::list<double>> matrix;
    std::cout << "Enter " << n << "x" << m << " matrix elements row by row (e.g. 1 5 2 9 3 4 2 7 6):" << std::endl;
    if (!task19_4::input_matrix(n, m, matrix)) {
        std::cout << "Invalid matrix element input." << std::endl;
        return 1;
    }

    std::cout << "\nOriginal matrix:" << std::endl;
    task19_4::print_matrix(matrix);

    task19_4::sort_rows_by_max_desc(matrix);

    std::cout << "\nMatrix with rows sorted by descending row maximum:" << std::endl;
    task19_4::print_matrix(matrix);

    return 0;
}
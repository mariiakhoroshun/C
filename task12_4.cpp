#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

bool input_int_array(int *m, int n) {
    for (int i = 0; i < n; i++) {
        if (!(std::cin >> m[i])) {
            return false;
        }
    }
    return true;
}

bool is_whitespace(int ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v' || ch == '\f';
}

int read_real_array_from_file(const char *filename, double *x, int n) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (!(fin >> x[i])) {
            return -1;
        }
        int next_ch = fin.peek();
        if (next_ch != EOF && !is_whitespace(next_ch)) {
            return -1;
        }
    }
    return 1;
}

bool compute_powers(const double *x, const int *m, double *result, int n) {
    for (int i = 0; i < n; i++) {
        result[i] = std::pow(x[i], m[i]);
        if (!std::isfinite(result[i])) {
            return false;
        }
    }
    return true;
}

bool write_real_array_to_file(const char *filename, const double *result, int n) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }
    fout << std::fixed << std::setprecision(6);
    for (int i = 0; i < n; i++) {
        fout << result[i];
        if (i < n - 1) {
            fout << " ";
        }
    }
    fout << std::endl;
    return fout.good();
}

int main() {
    int n = 0;
    std::cout << "Enter natural number n (e.g. 3): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input: n must be a natural number." << std::endl;
        return 1;
    }

    int *m = new int[n];
    double *x = new double[n];
    double *result = new double[n];

    std::cout << "Enter " << n << " integers m_i (e.g. 2 -1 3): ";
    if (!input_int_array(m, n)) {
        std::cout << "Invalid input for integer array m." << std::endl;
        delete[] m;
        delete[] x;
        delete[] result;
        return 1;
    }

    char in_filename[256];
    std::cout << "Enter input text file name (e.g. input.txt): ";
    if (!(std::cin >> in_filename)) {
        std::cout << "Invalid input file name." << std::endl;
        delete[] m;
        delete[] x;
        delete[] result;
        return 1;
    }

    int read_status = read_real_array_from_file(in_filename, x, n);
    if (read_status == 0) {
        std::cout << "Error: input file does not exist or cannot be opened." << std::endl;
        delete[] m;
        delete[] x;
        delete[] result;
        return 1;
    }
    if (read_status == -1) {
        std::cout << "Error: input file is corrupted or has fewer than " << n << " valid real numbers." << std::endl;
        delete[] m;
        delete[] x;
        delete[] result;
        return 1;
    }

    if (!compute_powers(x, m, result, n)) {
        std::cout << "Error: undefined value encountered when computing x_i^m_i." << std::endl;
        delete[] m;
        delete[] x;
        delete[] result;
        return 1;
    }

    char out_filename[256];
    std::cout << "Enter output text file name (e.g. output.txt): ";
    if (!(std::cin >> out_filename)) {
        std::cout << "Invalid output file name." << std::endl;
        delete[] m;
        delete[] x;
        delete[] result;
        return 1;
    }

    if (!write_real_array_to_file(out_filename, result, n)) {
        std::cout << "Error: could not write results to output file." << std::endl;
        delete[] m;
        delete[] x;
        delete[] result;
        return 1;
    }

    std::cout << "Results successfully written to " << out_filename << std::endl;

    delete[] m;
    delete[] x;
    delete[] result;
    return 0;
}
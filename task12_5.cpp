#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

int read_numbers_from_file(const char *filename, unsigned long long *&numbers, int &count) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        return 0;
    }

    int capacity = 64;
    count = 0;
    numbers = new unsigned long long[capacity];

    unsigned long long value = 0;
    while (fin >> value) {
        if (value > 1000000000000000000ULL) {
            delete[] numbers;
            numbers = nullptr;
            count = 0;
            return -1;
        }
        if (count == capacity) {
            int new_capacity = capacity * 2;
            unsigned long long *temp = new unsigned long long[new_capacity];
            for (int i = 0; i < count; i++) {
                temp[i] = numbers[i];
            }
            delete[] numbers;
            numbers = temp;
            capacity = new_capacity;
        }
        numbers[count] = value;
        count++;
    }

    if (!fin.eof()) {
        delete[] numbers;
        numbers = nullptr;
        count = 0;
        return -1;
    }

    return 1;
}

void compute_reverse_roots(const unsigned long long *numbers, long double *roots, int count) {
    for (int i = 0; i < count; i++) {
        roots[i] = std::sqrt(static_cast<long double>(numbers[count - 1 - i]));
    }
}

void print_roots(const long double *roots, int count) {
    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < count; i++) {
        std::cout << roots[i] << std::endl;
    }
}

int main() {
    char filename[256];
    std::cout << "Enter input text file name (e.g. input.txt): ";
    if (!(std::cin >> filename)) {
        std::cout << "Invalid file name." << std::endl;
        return 1;
    }

    unsigned long long *numbers = nullptr;
    int count = 0;

    int status = read_numbers_from_file(filename, numbers, count);
    if (status == 0) {
        std::cout << "Error: input file does not exist or cannot be opened." << std::endl;
        return 1;
    }
    if (status == -1) {
        std::cout << "Error: input file contains invalid data." << std::endl;
        return 1;
    }

    if (count > 0) {
        long double *roots = new long double[count];
        compute_reverse_roots(numbers, roots, count);
        print_roots(roots, count);
        delete[] roots;
    }

    delete[] numbers;
    return 0;
}
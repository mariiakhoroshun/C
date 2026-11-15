#include <iostream>

bool read_ten_digit_number(unsigned long long &number) {
    unsigned long long value = 0;
    for (int i = 0; i < 10; i++) {
        char ch;
        if (!(std::cin >> ch) || ch < '0' || ch > '9') {
            return false;
        }
        value = value * 10 + static_cast<unsigned long long>(ch - '0');
    }
    number = value;
    return true;
}

bool input_numbers(unsigned long long *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (!read_ten_digit_number(arr[i])) {
            return false;
        }
    }
    return true;
}

unsigned long long calculate_sum(const unsigned long long *arr, int n) {
    unsigned long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

void print_numbers(const unsigned long long *arr, int n) {
    std::cout << "Parsed numbers: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i < n - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

int main() {
    int n = 0;
    std::cout << "Enter n (number of 10-digit natural numbers, e.g. 2): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid value for n." << std::endl;
        return 1;
    }

    unsigned long long *numbers = new unsigned long long[n];

    std::cout << "Enter " << 10 * n << " digits (e.g. 00000000150000000025): ";
    if (!input_numbers(numbers, n)) {
        std::cout << "Invalid input: expected " << 10 * n << " decimal digits." << std::endl;
        delete[] numbers;
        return 1;
    }

    print_numbers(numbers, n);

    unsigned long long total_sum = calculate_sum(numbers, n);
    std::cout << "Sum: " << total_sum << std::endl;

    delete[] numbers;
    return 0;
}
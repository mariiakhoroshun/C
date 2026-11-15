#include <iostream>
#include <iomanip>
#include <cmath>

bool is_perfect_square(int number) {
    if (number < 0) {
        return false;
    }
    int root = static_cast<int>(std::round(std::sqrt(static_cast<double>(number))));
    return root * root == number;
}

double compute_root(int number) {
    return std::sqrt(static_cast<double>(number));
}

void print_border(int length) {
    for (int i = 0; i < length; i++) {
        std::cout << '+';
    }
    std::cout << std::endl;
}

void print_roots_table(int n) {
    const int col_width = 8;
    const int border_length = n * col_width + 3;

    print_border(border_length);

    for (int i = 1; i <= n; i++) {
        std::cout << std::setw(col_width) << i;
    }
    std::cout << std::endl;

    print_border(border_length);

    std::cout << std::fixed;
    for (int i = 1; i <= n; i++) {
        double root = compute_root(i);
        if (is_perfect_square(i)) {
            std::cout << std::setw(col_width) << std::setprecision(0) << root;
        } else {
            std::cout << std::setw(col_width) << std::setprecision(2) << root;
        }
    }
    std::cout << std::endl;

    print_border(border_length);
}

int main() {
    int n = 0;

    std::cout << "Enter a natural number n (e.g. 5): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input: n must be a natural number." << std::endl;
        return 1;
    }

    print_roots_table(n);

    return 0;
}
#include <iostream>
#include <iomanip>
#include <cmath>

bool is_valid_input(long double x, int k) {
    if (x < -10000.0L || x > 10000.0L) {
        return false;
    }
    if (k <= -10 || k >= 10) {
        return false;
    }
    return true;
}

long double compute_power(long double x, int k) {
    if (x == 0.0L && k > 0) {
        return 0.0L;
    }
    long double result = std::pow(x, static_cast<long double>(k));
    if (result == 0.0L) {
        result = 0.0L;
    }
    return result;
}

bool is_finite_result(long double value) {
    return std::isfinite(value);
}

void print_formatted_power(long double value) {
    std::cout << "Result: "
              << std::fixed
              << std::setprecision(4)
              << std::setw(25)
              << std::setfill('0')
              << std::internal
              << value
              << std::endl;
}

int main() {
    long double x = 0.0L;
    int k = 0;

    std::cout << "Enter a real number x in [-10000, 10000] (e.g. -12.5): ";
    if (!(std::cin >> x)) {
        std::cout << "Invalid input for x." << std::endl;
        return 1;
    }

    std::cout << "Enter an integer exponent k with |k| < 10 (e.g. 3): ";
    if (!(std::cin >> k)) {
        std::cout << "Invalid input for k." << std::endl;
        return 1;
    }

    if (!is_valid_input(x, k)) {
        std::cout << "Error: x must be in [-10000, 10000] and |k| must be less than 10." << std::endl;
        return 1;
    }

    long double result = compute_power(x, k);
    if (!is_finite_result(result)) {
        std::cout << "Error: result is undefined (division by zero)." << std::endl;
        return 1;
    }

    print_formatted_power(result);

    return 0;
}
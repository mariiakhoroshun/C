#include <iostream>
#include <iomanip>
#include <cmath>

double calculate_power(double x, double y) {
    return std::pow(x, y);
}

bool is_valid_number(double value) {
    return std::isfinite(value);
}

int main() {
    double x = 0.0;
    double y = 0.0;

    std::cout << "Enter real number x (e.g. 2.5): ";
    if (!(std::cin >> x)) {
        std::cout << "Invalid input for x." << std::endl;
        return 1;
    }

    while (std::cin.get() != '\n' && std::cin.good()) {
    }

    std::cout << "Enter real number y on the next line (e.g. 3.0): ";
    if (!(std::cin >> y)) {
        std::cout << "Invalid input for y." << std::endl;
        return 1;
    }

    double result = calculate_power(x, y);

    if (!is_valid_number(result)) {
        std::cout << "Result is undefined or infinite." << std::endl;
        return 1;
    }

    std::cout << "Decimal representation: " << std::fixed << std::setprecision(6) << result << std::endl;
    std::cout << "Scientific representation: " << std::scientific << std::setprecision(6) << result << std::endl;

    return 0;
}
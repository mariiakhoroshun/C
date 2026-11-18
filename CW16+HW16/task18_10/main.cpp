#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "Function.h"

double custom_quadratic(double x) {
    return x * x + 2.0 * x - 3.0;
}

void test_function() {
    task10::Function<double> f_pow = task10::Function<double>::create_power(2.0, 0.0, 3.0);
    bool t1 = (std::fabs(f_pow.left_rectangles(6) - 6.875) < 1e-9 &&
               std::fabs(f_pow.right_rectangles(6) - 11.375) < 1e-9 &&
               std::fabs(f_pow.midpoint_rectangles(6) - 8.9375) < 1e-9 &&
               std::fabs(f_pow.trapezoidal(6) - 9.125) < 1e-9 &&
               std::fabs(f_pow.simpson(6) - 9.0) < 1e-9);

    const double pi = std::acos(-1.0);
    task10::Function<double> f_cos = task10::Function<double>::create_cos(0.0, pi / 2.0);
    bool t2 = (std::fabs(f_cos.simpson(100) - 1.0) < 1e-9);

    task10::Function<double> f_sqrt = task10::Function<double>::create_sqrt(0.0, 4.0);
    bool t3 = (std::fabs(f_sqrt.simpson(1000) - (16.0 / 3.0)) < 1e-5);

    const double e = std::exp(1.0);
    task10::Function<double> f_log = task10::Function<double>::create_log(1.0, e);
    bool t4 = (std::fabs(f_log.simpson(100) - 1.0) < 1e-7);

    task10::Function<double> f_custom(custom_quadratic, 0.0, 2.0);
    bool t5 = (std::fabs(f_custom.simpson(4) - (2.0 / 3.0)) < 1e-9);

    std::ostringstream oss;
    f_pow.sample(0.0, 2.0, 3, oss);
    std::string table_out = oss.str();
    bool t6 = (table_out.find("0.000000") != std::string::npos &&
               table_out.find("1.000000") != std::string::npos &&
               table_out.find("2.000000") != std::string::npos &&
               table_out.find("4.000000") != std::string::npos);

    bool t7 = false;
    try {
        task10::Function<double> bad_log = task10::Function<double>::create_log(-1.0, 2.0);
        bad_log.evaluate(-1.0);
    } catch (const std::domain_error&) {
        t7 = true;
    }

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (Power x^2 all 5 integration rules): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (Cosine integral on [0, pi/2]): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (Sqrt integral on [0, 4]): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (Log integral on [1, e]): " << (t4 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 5 (Custom function pointer): " << (t5 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 6 (Sampling table generation): " << (t6 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 7 (Domain error handling): " << (t7 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_function();

    int choice = 0;
    std::cout << "Select function type:" << std::endl;
    std::cout << "1 - Power function (coeff * x^p)" << std::endl;
    std::cout << "2 - Cosine (cos(x))" << std::endl;
    std::cout << "3 - Square root (sqrt(x))" << std::endl;
    std::cout << "4 - Natural logarithm (ln(x))" << std::endl;
    std::cout << "Enter choice (1-4): ";
    if (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cout << "Invalid function choice." << std::endl;
        return 1;
    }

    double a = 0.0;
    double b = 0.0;
    std::cout << "Enter interval bounds [a, b] (e.g. 1 4): ";
    if (!(std::cin >> a >> b)) {
        std::cout << "Invalid interval input." << std::endl;
        return 1;
    }

    try {
        task10::Function<double> func;
        if (choice == 1) {
            double coeff = 1.0;
            double exponent = 1.0;
            std::cout << "Enter coefficient and exponent (e.g. 1 2 for x^2): ";
            if (!(std::cin >> coeff >> exponent)) {
                std::cout << "Invalid parameters." << std::endl;
                return 1;
            }
            func = task10::Function<double>::create_power(exponent, a, b, coeff);
        } else if (choice == 2) {
            func = task10::Function<double>::create_cos(a, b);
        } else if (choice == 3) {
            func = task10::Function<double>::create_sqrt(a, b);
        } else {
            func = task10::Function<double>::create_log(a, b);
        }

        int n = 0;
        std::cout << "Enter even number of subintervals for integration (e.g. 100): ";
        if (!(std::cin >> n)) {
            std::cout << "Invalid number of subintervals." << std::endl;
            return 1;
        }

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "\n--- Numerical Integration Results ---" << std::endl;
        std::cout << "Left rectangles:     " << func.left_rectangles(n) << std::endl;
        std::cout << "Right rectangles:    " << func.right_rectangles(n) << std::endl;
        std::cout << "Midpoint rectangles: " << func.midpoint_rectangles(n) << std::endl;
        std::cout << "Trapezoidal rule:    " << func.trapezoidal(n) << std::endl;
        std::cout << "Simpson rule:        " << func.simpson(n) << std::endl;

        double sample_a = 0.0;
        double sample_b = 0.0;
        int samples_count = 0;
        std::cout << "\nEnter sampling interval [a, b] and number of samples (e.g. 1 4 7): ";
        if (!(std::cin >> sample_a >> sample_b >> samples_count)) {
            std::cout << "Invalid sampling parameters." << std::endl;
            return 1;
        }

        std::cout << "\nSample Table:" << std::endl;
        func.sample(sample_a, sample_b, samples_count);
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
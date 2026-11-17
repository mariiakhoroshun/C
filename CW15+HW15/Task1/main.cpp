#include <iostream>
#include <cmath>
#include "Rational.h"

Rational find_min_rational(const Rational* arr, int size) {
    Rational min_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

Rational compute_series_sum(double eps, int& terms_count) {
    Rational sum(0, 1);
    terms_count = 0;
    int k = 1;
    while (true) {
        int sign = (k % 2 == 1) ? 1 : -1;
        Rational term(sign, k * k);
        if (std::fabs(term.to_double()) < eps) {
            break;
        }
        sum += term;
        terms_count++;
        k++;
    }
    return sum;
}

void test_rational() {
    Rational def_r;
    Rational a(2, 4);
    Rational b(-3, 6);

    bool ok = true;
    if (def_r.get_nominator() != 1 || def_r.get_denominator() != 1) ok = false;
    if (a != Rational(1, 2) || b != Rational(-1, 2)) ok = false;
    if (a.set_denominator(0)) ok = false;
    if (a.get_denominator() == 0) ok = false;
    if (a.add(Rational(1, 3)) != Rational(5, 6)) ok = false;
    if (a.multiply(Rational(2, 3)) != Rational(1, 3)) ok = false;
    if ((a - Rational(1, 3)) != Rational(1, 6)) ok = false;
    if ((a / Rational(1, 4)) != Rational(2, 1)) ok = false;
    if (!(b < a)) ok = false;

    Rational sample[3] = { Rational(3, 4), Rational(-2, 5), Rational(1, 2) };
    if (find_min_rational(sample, 3) != Rational(-2, 5)) ok = false;

    int count = 0;
    Rational s = compute_series_sum(0.01, count);
    const double pi_sq_12 = std::acos(-1.0) * std::acos(-1.0) / 12.0;
    if (std::fabs(s.to_double() - pi_sq_12) >= 0.01) ok = false;

    std::cout << (ok ? "[TESTS PASSED]\n\n" : "[TESTS FAILED]\n\n");
}

int main() {
    test_rational();

    Rational r1;
    std::cout << "Default constructor value: ";
    r1.print();
    std::cout << "\n";

    int nom = 0;
    int denom = 0;
    std::cout << "Enter integer nominator for r1: ";
    if (!(std::cin >> nom)) {
        std::cout << "Invalid input.\n";
        return 1;
    }
    r1.set_nominator(nom);

    std::cout << "Enter natural denominator for r1 (positive integer, 0 is forbidden): ";
    if (!(std::cin >> denom) || !r1.set_denominator(denom)) {
        std::cout << "Invalid denominator (must be a positive integer).\n";
        return 1;
    }
    std::cout << "Reduced r1 = " << r1 << "\n";

    Rational r2;
    std::cout << "Enter rational number r2 (format: nominator denominator, e.g. 3 4 or 3/4): ";
    if (!r2.input()) {
        std::cout << "Invalid rational number.\n";
        return 1;
    }

    std::cout << "r1 + r2 (method add) = " << r1.add(r2) << "\n";
    std::cout << "r1 * r2 (method multiply) = " << r1.multiply(r2) << "\n";
    std::cout << "r1 - r2 = " << (r1 - r2) << "\n";
    std::cout << "r1 / r2 = " << (r1 / r2) << "\n";
    std::cout << "Comparison: r1 " << (r1 < r2 ? "<" : (r1 > r2 ? ">" : "==")) << " r2\n\n";

    int n = 0;
    std::cout << "Enter number of elements in rational array (positive integer): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid array size.\n";
        return 1;
    }

    Rational* arr = new Rational[n];
    for (int i = 0; i < n; i++) {
        std::cout << "Enter element #" << (i + 1) << " (e.g. -2 5 or -2/5): ";
        if (!(std::cin >> arr[i])) {
            std::cout << "Invalid rational number.\n";
            delete[] arr;
            return 1;
        }
    }

    Rational min_elem = find_min_rational(arr, n);
    std::cout << "Smallest rational number in array: " << min_elem << "\n\n";
    delete[] arr;

    double eps = 0.01;
    int terms = 0;
    Rational series_sum = compute_series_sum(eps, terms);
    const double pi = std::acos(-1.0);
    const double target = (pi * pi) / 12.0;
    double diff = std::fabs(series_sum.to_double() - target);

    std::cout << "Series sum with precision " << eps << " (" << terms << " terms): "
              << series_sum << " (~" << series_sum.to_double() << ")\n";
    std::cout << "Exact value pi^2 / 12 = " << target << "\n";
    std::cout << "Absolute difference = " << diff << "\n";
    if (diff < eps) {
        std::cout << "Verified: the series converges to pi^2 / 12 within precision " << eps << ".\n";
    } else {
        std::cout << "Not within precision " << eps << ".\n";
    }

    return 0;
}
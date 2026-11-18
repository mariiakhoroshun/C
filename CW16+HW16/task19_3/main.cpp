#include <iostream>
#include <sstream>
#include <list>
#include <cmath>
#include "Polynom.h"
#include "Rational.h"

void test_polynom() {
    std::list<int> li1 = {1, -3, 2};
    std::list<int> li2 = {4, 1};
    task19_3::Polynom<int> pi1(li1);
    task19_3::Polynom<int> pi2(li2);

    std::list<int> expected_int_sum = {5, -2, 2};
    std::list<int> expected_int_prod = {4, -11, 5, 2};
    bool t1 = ((pi1 + pi2) == task19_3::Polynom<int>(expected_int_sum) &&
               (pi1 * pi2) == task19_3::Polynom<int>(expected_int_prod) &&
               pi1.evaluate(3) == 10);

    std::list<double> ld1 = {1.5, 2.0};
    std::list<double> ld2 = {-0.5, 4.0};
    task19_3::Polynom<double> pd1(ld1);
    task19_3::Polynom<double> pd2(ld2);
    task19_3::Polynom<double> pd_sum = pd1 + pd2;
    task19_3::Polynom<double> pd_prod = pd1 * pd2;
    bool t2 = (std::fabs(pd_sum.evaluate(2.0) - 13.0) < 1e-9 &&
               std::fabs(pd_prod.evaluate(2.0) - 41.25) < 1e-9);

    std::list<task19_3::Rational> lr1 = {task19_3::Rational(1, 2), task19_3::Rational(1, 3)};
    std::list<task19_3::Rational> lr2 = {task19_3::Rational(1, 4), task19_3::Rational(-1, 3)};
    task19_3::Polynom<task19_3::Rational> pr1(lr1);
    task19_3::Polynom<task19_3::Rational> pr2(lr2);

    task19_3::Polynom<task19_3::Rational> pr_sum = pr1 + pr2;
    task19_3::Polynom<task19_3::Rational> pr_prod = pr1 * pr2;
    task19_3::Rational x_val(3, 2);
    bool t3 = (pr_sum.degree() == 0 &&
               pr_sum.evaluate(x_val) == task19_3::Rational(3, 4) &&
               pr1.evaluate(x_val) == task19_3::Rational(1, 1) &&
               pr_prod.evaluate(x_val) == task19_3::Rational(-1, 4));

    std::istringstream iss("2  1 2  0 1  -1 4");
    task19_3::Polynom<task19_3::Rational> pr_stream;
    bool stream_ok = (iss >> pr_stream) && (pr_stream.degree() == 2) &&
                     (pr_stream(task19_3::Rational(2, 1)) == task19_3::Rational(-1, 2));

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (Polynom<int> add, multiply, evaluate): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (Polynom<double> add, multiply, evaluate): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (Polynom<Rational> add, multiply, evaluate): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (Stream input and evaluation): " << (stream_ok ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_polynom();

    task19_3::Polynom<task19_3::Rational> p1;
    task19_3::Polynom<task19_3::Rational> p2;

    std::cout << "Enter degree and coefficients (nom denom or nom/denom) for first Rational polynomial" << std::endl;
    std::cout << "(e.g. '1  1 2  1 3' or '1  1/2  1/3' means 1/2 + 1/3*x^1): ";
    if (!p1.input()) {
        std::cout << "Invalid polynomial input." << std::endl;
        return 1;
    }

    std::cout << "Enter degree and coefficients for second Rational polynomial (e.g. '1  1/4  -1/3'): ";
    if (!p2.input()) {
        std::cout << "Invalid polynomial input." << std::endl;
        return 1;
    }

    task19_3::Rational x;
    std::cout << "Enter Rational point x (e.g. '3 2' or '3/2'): ";
    if (!(std::cin >> x)) {
        std::cout << "Invalid Rational input." << std::endl;
        return 1;
    }

    task19_3::Polynom<task19_3::Rational> sum = p1 + p2;
    task19_3::Polynom<task19_3::Rational> prod = p1 * p2;

    std::cout << "\nP1(x) = " << p1 << std::endl;
    std::cout << "P2(x) = " << p2 << std::endl;
    std::cout << "P1(x) + P2(x) = " << sum << std::endl;
    std::cout << "P1(x) * P2(x) = " << prod << std::endl;
    std::cout << "P1(" << x << ") = " << p1.evaluate(x) << std::endl;
    std::cout << "P2(" << x << ") = " << p2.evaluate(x) << std::endl;

    return 0;
}
#include <iostream>
#include <string>
#include <cstring>
#include "Rational.h"

void test_get_max() {
    bool t1 = (task1::get_max(10, -25) == 10);
    bool t2 = (task1::get_max(3.14, 2.71) == 3.14);
    bool t3 = (task1::get_max(5, 7.5) == 7.5);
    bool t4 = (task1::get_max(std::string("apple"), std::string("banana")) == "banana");

    const char* cstr1 = "zebra";
    const char* cstr2 = "antelope";
    bool t5 = (std::strcmp(task1::get_max(cstr1, cstr2), "zebra") == 0);

    task1::Rational r1(1, 3);
    task1::Rational r2(2, 5);
    task1::Rational r3(-1, 4);
    task1::Rational r4(-2, 3);
    bool t6 = (task1::get_max(r1, r2) == r2);
    bool t7 = (task1::get_max(r3, r4) == r3);

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (int): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (double): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (mixed int and double): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (std::string): " << (t4 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 5 (const char*): " << (t5 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 6 (positive Rational): " << (t6 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 7 (negative Rational): " << (t7 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_get_max();

    int int_a = 0;
    double double_b = 0.0;
    std::cout << "Enter an integer and a real number (e.g. 4 6.25): ";
    if (!(std::cin >> int_a >> double_b)) {
        std::cout << "Invalid numeric input." << std::endl;
        return 1;
    }
    std::cout << "Max number: " << task1::get_max(int_a, double_b) << std::endl;

    std::string str1;
    std::string str2;
    std::cout << "Enter two words separated by space (e.g. cat dog): ";
    if (!(std::cin >> str1 >> str2)) {
        std::cout << "Invalid string input." << std::endl;
        return 1;
    }
    std::cout << "Max string: " << task1::get_max(str1, str2) << std::endl;

    task1::Rational frac1;
    task1::Rational frac2;
    std::cout << "Enter first fraction (nominator denominator, e.g. 3 4): ";
    if (!(std::cin >> frac1)) {
        std::cout << "Invalid first fraction." << std::endl;
        return 1;
    }
    std::cout << "Enter second fraction (nominator denominator, e.g. 5 6): ";
    if (!(std::cin >> frac2)) {
        std::cout << "Invalid second fraction." << std::endl;
        return 1;
    }
    std::cout << "Max fraction: " << task1::get_max(frac1, frac2) << std::endl;

    return 0;
}
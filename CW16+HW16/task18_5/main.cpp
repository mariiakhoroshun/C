#include <iostream>
#include <string>
#include <cmath>
#include "Array.h"

void test_shell_sort() {
    int raw_init[6] = {23, -4, 15, 0, 8, -11};
    int expected_int[6] = {-11, -4, 0, 8, 15, 23};
    task5::Array<int> arr_int(6, raw_init);
    task5::Array<int> expected_arr_int(6, expected_int);
    arr_int.shell_sort();
    bool t1 = (arr_int == expected_arr_int);

    int static_raw[6] = {9, 1, 7, 3, 5, 2};
    task5::Array<int>::shell_sort(static_raw, 6);
    bool t2 = (static_raw[0] == 1 && static_raw[1] == 2 && static_raw[2] == 3 &&
               static_raw[3] == 5 && static_raw[4] == 7 && static_raw[5] == 9);

    double raw_double[4] = {3.5, -1.25, 0.0, 2.75};
    task5::Array<double> arr_double(4, raw_double);
    task5::Array<double>::shell_sort(arr_double);
    bool t3 = (std::fabs(arr_double[0] + 1.25) < 1e-9 &&
               std::fabs(arr_double[1] - 0.0) < 1e-9 &&
               std::fabs(arr_double[2] - 2.75) < 1e-9 &&
               std::fabs(arr_double[3] - 3.5) < 1e-9);

    std::string raw_str[4] = {"pear", "apple", "orange", "banana"};
    task5::Array<std::string> arr_str(4, raw_str);
    arr_str.shell_sort();
    bool t4 = (arr_str[0] == "apple" && arr_str[1] == "banana" &&
               arr_str[2] == "orange" && arr_str[3] == "pear");

    task5::Array<int> empty_arr;
    empty_arr.shell_sort();
    int single_val[1] = {42};
    task5::Array<int> single_arr(1, single_val);
    single_arr.shell_sort();
    bool t5 = (empty_arr.size() == 0 && single_arr.size() == 1 && single_arr[0] == 42);

    int copy_src[3] = {30, 10, 20};
    task5::Array<int> a1(3, copy_src);
    task5::Array<int> a2 = a1;
    a1.shell_sort();
    bool t6 = (a1[0] == 10 && a2[0] == 30);

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (Array<int> member shell_sort): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (Static raw array shell_sort): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (Array<double> static shell_sort): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (Array<std::string> shell_sort): " << (t4 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 5 (Empty and single-element arrays): " << (t5 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 6 (Deep copy independence): " << (t6 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_shell_sort();

    int n = 0;
    std::cout << "Enter integer array size: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid array size." << std::endl;
        return 1;
    }

    task5::Array<int> user_arr(n);
    std::cout << "Enter " << n << " integers: ";
    if (!(std::cin >> user_arr)) {
        std::cout << "Invalid integer input." << std::endl;
        return 1;
    }

    std::cout << "Original Array<int>: " << user_arr << std::endl;
    user_arr.shell_sort();
    std::cout << "Sorted Array<int> (member shell_sort): " << user_arr << std::endl;

    int m = 0;
    std::cout << "\nEnter real array size for static sort: ";
    if (!(std::cin >> m) || m <= 0) {
        std::cout << "Invalid array size." << std::endl;
        return 1;
    }

    double* raw_arr = new double[m];
    std::cout << "Enter " << m << " real numbers: ";
    for (int i = 0; i < m; ++i) {
        if (!(std::cin >> raw_arr[i])) {
            std::cout << "Invalid real number input." << std::endl;
            delete[] raw_arr;
            return 1;
        }
    }

    task5::Array<double>::shell_sort(raw_arr, m);
    std::cout << "Sorted raw double array (static shell_sort): [";
    for (int i = 0; i < m; ++i) {
        std::cout << raw_arr[i];
        if (i + 1 < m) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;

    delete[] raw_arr;
    return 0;
}
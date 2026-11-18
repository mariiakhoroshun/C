#include <iostream>
#include <sstream>
#include <stack>
#include <cmath>
#include "Stack.h"

template <typename T>
bool verify_with_stl_stack(const T* arr, int n) {
    task2::Stack<T> custom_stack;
    std::stack<T> stl_stack;

    for (int i = 0; i < n; ++i) {
        custom_stack.push(arr[i]);
        stl_stack.push(arr[i]);
    }

    if (custom_stack.size() != static_cast<int>(stl_stack.size())) {
        return false;
    }

    while (!custom_stack.empty() && !stl_stack.empty()) {
        if (custom_stack.top() != stl_stack.top()) {
            return false;
        }
        custom_stack.pop();
        stl_stack.pop();
    }

    return custom_stack.empty() && stl_stack.empty();
}

template <typename T>
void print_array(const T* arr, int n) {
    std::cout << "[";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i];
        if (i + 1 < n) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void test_stack_and_input() {
    std::istringstream int_stream("10 -5 42 7 0 99");
    int* int_arr = nullptr;
    int int_count = task2::input_array(int_arr, int_stream);
    bool t1 = (int_count == 4 && int_arr != nullptr &&
               int_arr[0] == 10 && int_arr[1] == -5 &&
               int_arr[2] == 42 && int_arr[3] == 7);
    bool t2 = verify_with_stl_stack(int_arr, int_count);
    delete[] int_arr;

    std::istringstream double_stream("1.5 -2.25 3.75 0");
    double* double_arr = nullptr;
    int double_count = task2::input_array(double_arr, double_stream);
    bool t3 = (double_count == 3 && double_arr != nullptr &&
               std::fabs(double_arr[0] - 1.5) < 1e-9 &&
               std::fabs(double_arr[1] + 2.25) < 1e-9 &&
               std::fabs(double_arr[2] - 3.75) < 1e-9);
    bool t4 = verify_with_stl_stack(double_arr, double_count);
    delete[] double_arr;

    std::istringstream empty_stream("0");
    int* empty_arr = nullptr;
    int empty_count = task2::input_array(empty_arr, empty_stream);
    bool t5 = (empty_count == 0 && empty_arr == nullptr);

    task2::Stack<int> s1;
    s1.push(100);
    s1.push(200);
    task2::Stack<int> s2 = s1;
    s1.pop();
    bool t6 = (s1.top() == 100 && s2.top() == 200 && s2.size() == 2);

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (int input until 0): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (int Stack vs std::stack): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (double input until 0): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (double Stack vs std::stack): " << (t4 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 5 (empty input starting with 0): " << (t5 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 6 (Stack deep copy): " << (t6 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_stack_and_input();

    int* int_arr = nullptr;
    std::cout << "Enter integers (0 to stop): ";
    int int_count = task2::input_array(int_arr);
    std::cout << "Count: " << int_count << std::endl;
    std::cout << "Resulting int array: ";
    print_array(int_arr, int_count);
    std::cout << "Verified with std::stack<int>: "
              << (verify_with_stl_stack(int_arr, int_count) ? "OK" : "MISMATCH") << std::endl;
    delete[] int_arr;

    std::cin.clear();
    std::cin.ignore(10000, '\n');

    double* double_arr = nullptr;
    std::cout << "\nEnter real numbers (0 to stop): ";
    int double_count = task2::input_array(double_arr);
    std::cout << "Count: " << double_count << std::endl;
    std::cout << "Resulting double array: ";
    print_array(double_arr, double_count);
    std::cout << "Verified with std::stack<double>: "
              << (verify_with_stl_stack(double_arr, double_count) ? "OK" : "MISMATCH") << std::endl;
    delete[] double_arr;

    return 0;
}
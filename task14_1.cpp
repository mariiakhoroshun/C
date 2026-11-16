#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>

bool evaluate_expression_stream(std::istream& in, double& result) {
    double current = 0.0;
    if (!(in >> current)) {
        return false;
    }

    double sum = current;
    int count = 1;
    char op = '\0';

    while (in >> op) {
        if (op == '=') {
            if (count <= 1) {
                return false;
            }
            result = sum;
            return true;
        }

        if (op != '+' && op != '-') {
            return false;
        }

        if (!(in >> current)) {
            return false;
        }

        if (op == '+') {
            sum += current;
        } else {
            sum -= current;
        }
        count++;
    }

    return false;
}

bool evaluate_expression_file(const std::string& filename, double& result) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        return false;
    }
    return evaluate_expression_stream(fin, result);
}

bool write_expression_file(const std::string& filename, const std::string& expression) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }
    fout << expression << '\n';
    return fout.good();
}

void task1_test() {
    std::string valid_tests[] = {
        "10+25-5+3=",
        "-12.5 + 4.25 - 1.75 + 10 =",
        "10 + -3 - -2 =",
        "0.5 - 1.25 + 3.75 ="
    };
    double expected[] = {33.0, 0.0, 9.0, 3.0};

    bool ok = true;
    for (int i = 0; i < 4; i++) {
        std::istringstream iss(valid_tests[i]);
        double res = 0.0;
        if (!evaluate_expression_stream(iss, res) || std::fabs(res - expected[i]) > 1e-9) {
            std::cout << "Failed valid test " << i << ": " << valid_tests[i] << "\n";
            ok = false;
        }
    }

    std::string invalid_tests[] = {
        "42=",
        "10 + 20",
        "10 + =",
        "10 * 5 ="
    };

    for (int i = 0; i < 4; i++) {
        std::istringstream iss(invalid_tests[i]);
        double res = 0.0;
        if (evaluate_expression_stream(iss, res)) {
            std::cout << "Failed invalid test " << i << ": " << invalid_tests[i] << "\n";
            ok = false;
        }
    }

    const std::string temp_file = "temp_test_14_1.txt";
    double file_res = 0.0;
    if (!write_expression_file(temp_file, "15.5 - 2.5 + 7 =") ||
        !evaluate_expression_file(temp_file, file_res) ||
        std::fabs(file_res - 20.0) > 1e-9) {
        std::cout << "Failed file I/O test.\n";
        ok = false;
    }
    std::remove(temp_file.c_str());

    if (ok) {
        std::cout << "Task 1 tests passed.\n";
    }
}

int main() {
    task1_test();

    int mode = 0;
    std::cout << "Select mode (1 - create new file, 2 - read existing file): ";
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cout << "Invalid mode.\n";
        return 1;
    }
    std::cin.ignore();

    std::string filename;
    std::cout << "Enter file name (e.g. expr.txt): ";
    std::getline(std::cin, filename);
    if (filename.empty()) {
        std::cout << "Invalid file name.\n";
        return 1;
    }

    if (mode == 1) {
        std::string expression;
        std::cout << "Enter expression ending with '=' (e.g. 12.5 - 3 + 4.5 =): ";
        std::getline(std::cin, expression);
        if (!write_expression_file(filename, expression)) {
            std::cout << "Error writing to file.\n";
            return 1;
        }
    }

    double result = 0.0;
    if (!evaluate_expression_file(filename, result)) {
        std::cout << "Error: cannot open file or invalid expression format.\n";
        return 1;
    }

    std::cout << "Result: " << result << "\n";
    return 0;
}
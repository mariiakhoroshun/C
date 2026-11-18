#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <cstdio>
#include <cmath>

namespace task19_19 {

template <typename D>
std::deque<D> read_deque_from_file(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    std::deque<D> dq;
    D value = D();
    while (fin >> value) {
        dq.push_back(value);
    }
    return dq;
}

template <typename D>
void remove_middle_elements(std::deque<D>& dq) {
    std::size_t n = dq.size();
    if (n == 0) {
        return;
    }
    if (n % 2 == 1) {
        typename std::deque<D>::iterator mid = dq.begin() + static_cast<std::ptrdiff_t>(n / 2);
        dq.erase(mid);
    } else {
        typename std::deque<D>::iterator mid_left = dq.begin() + static_cast<std::ptrdiff_t>(n / 2 - 1);
        dq.erase(mid_left, mid_left + 2);
    }
}

template <typename D>
void print_deque(const std::deque<D>& dq, std::ostream& out = std::cout) {
    out << "[";
    for (std::size_t i = 0; i < dq.size(); ++i) {
        out << dq[i];
        if (i + 1 < dq.size()) {
            out << ", ";
        }
    }
    out << "]" << std::endl;
}

template <typename D>
void process_file_for_type(const std::string& filename) {
    std::deque<D> dq = read_deque_from_file<D>(filename);
    std::cout << "Original deque (" << dq.size() << " elements): ";
    print_deque(dq);

    remove_middle_elements(dq);
    std::cout << "Deque after removing middle element(s) (" << dq.size() << " elements): ";
    print_deque(dq);
}

}

void test_deque_middle() {
    const std::string temp_odd = "temp_test_odd.txt";
    {
        std::ofstream fout(temp_odd);
        fout << "10 20 30 40 50";
    }
    std::deque<int> dq_odd = task19_19::read_deque_from_file<int>(temp_odd);
    task19_19::remove_middle_elements(dq_odd);
    std::remove(temp_odd.c_str());
    bool t1 = (dq_odd.size() == 4 &&
               dq_odd[0] == 10 && dq_odd[1] == 20 &&
               dq_odd[2] == 40 && dq_odd[3] == 50);

    const std::string temp_even = "temp_test_even.txt";
    {
        std::ofstream fout(temp_even);
        fout << "alpha beta gamma delta";
    }
    std::deque<std::string> dq_even = task19_19::read_deque_from_file<std::string>(temp_even);
    task19_19::remove_middle_elements(dq_even);
    std::remove(temp_even.c_str());
    bool t2 = (dq_even.size() == 2 &&
               dq_even[0] == "alpha" && dq_even[1] == "delta");

    const std::string temp_double = "temp_test_double.txt";
    {
        std::ofstream fout(temp_double);
        fout << "1.5 2.5 3.5";
    }
    std::deque<double> dq_double = task19_19::read_deque_from_file<double>(temp_double);
    task19_19::remove_middle_elements(dq_double);
    std::remove(temp_double.c_str());
    bool t3 = (dq_double.size() == 2 &&
               std::fabs(dq_double[0] - 1.5) < 1e-9 &&
               std::fabs(dq_double[1] - 3.5) < 1e-9);

    std::deque<int> dq_one = {42};
    task19_19::remove_middle_elements(dq_one);
    std::deque<int> dq_two = {1, 2};
    task19_19::remove_middle_elements(dq_two);
    std::deque<int> dq_empty;
    task19_19::remove_middle_elements(dq_empty);
    bool t4 = (dq_one.empty() && dq_two.empty() && dq_empty.empty());

    std::cout << "--- Automated Tests ---" << std::endl;
    std::cout << "Test 1 (odd count int deque from file): " << (t1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 2 (even count string deque from file): " << (t2 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 3 (odd count double deque from file): " << (t3 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Test 4 (1-element, 2-element, and empty deques): " << (t4 ? "PASSED" : "FAILED") << std::endl;
    std::cout << "-----------------------" << std::endl << std::endl;
}

int main() {
    test_deque_middle();

    int mode = 0;
    std::cout << "Choose input mode:" << std::endl;
    std::cout << "1 - Create a new text file from console and process it" << std::endl;
    std::cout << "2 - Read an existing text file" << std::endl;
    std::cout << "Enter mode (1 or 2): ";
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cout << "Invalid mode." << std::endl;
        return 1;
    }

    std::string filename;
    std::cout << "Enter text file name (e.g. data.txt): ";
    if (!(std::cin >> filename)) {
        std::cout << "Invalid file name." << std::endl;
        return 1;
    }

    if (mode == 1) {
        int count = 0;
        std::cout << "Enter number of elements to write to file (e.g. 5): ";
        if (!(std::cin >> count) || count <= 0) {
            std::cout << "Invalid count." << std::endl;
            return 1;
        }
        std::ofstream fout(filename);
        if (!fout.is_open()) {
            std::cout << "Cannot create file." << std::endl;
            return 1;
        }
        std::cout << "Enter " << count << " elements separated by spaces (e.g. 10 20 30 40 50): ";
        for (int i = 0; i < count; ++i) {
            std::string token;
            if (!(std::cin >> token)) {
                std::cout << "Invalid element input." << std::endl;
                return 1;
            }
            if (i > 0) {
                fout << " ";
            }
            fout << token;
        }
        fout.close();
    }

    int type_choice = 0;
    std::cout << "Select element type D (1 - int, 2 - double, 3 - string): ";
    if (!(std::cin >> type_choice) || type_choice < 1 || type_choice > 3) {
        std::cout << "Invalid type choice." << std::endl;
        return 1;
    }

    try {
        if (type_choice == 1) {
            task19_19::process_file_for_type<int>(filename);
        } else if (type_choice == 2) {
            task19_19::process_file_for_type<double>(filename);
        } else {
            task19_19::process_file_for_type<std::string>(filename);
        }
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
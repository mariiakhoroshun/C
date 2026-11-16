#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdio>

std::string trim_spaces(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}

bool parse_int_strict(const std::string& s, int& value) {
    std::string trimmed = trim_spaces(s);
    if (trimmed.empty()) {
        return false;
    }
    std::istringstream iss(trimmed);
    int val = 0;
    char extra = '\0';
    if (!(iss >> val) || (iss >> extra)) {
        return false;
    }
    value = val;
    return true;
}

bool parse_student_line(const std::string& line, std::string& surname, double& average) {
    std::string trimmed = trim_spaces(line);
    if (trimmed.empty()) {
        return false;
    }

    size_t comma_count = 0;
    for (size_t i = 0; i < trimmed.size(); i++) {
        if (trimmed[i] == ',') {
            comma_count++;
        }
    }

    std::string grades_part;

    if (comma_count >= 3) {
        size_t c1 = trimmed.find(',');
        size_t c2 = trimmed.find(',', c1 + 1);
        size_t c3 = trimmed.find(',', c2 + 1);

        surname = trim_spaces(trimmed.substr(0, c1));
        int course = 0;
        if (surname.empty() || !parse_int_strict(trimmed.substr(c1 + 1, c2 - c1 - 1), course) || course <= 0) {
            return false;
        }
        std::string group = trim_spaces(trimmed.substr(c2 + 1, c3 - c2 - 1));
        if (group.empty()) {
            return false;
        }
        grades_part = trimmed.substr(c3 + 1);
    } else {
        std::istringstream iss(trimmed);
        int course = 0;
        std::string group;
        if (!(iss >> surname >> course >> group) || course <= 0 || group.empty()) {
            return false;
        }
        std::getline(iss, grades_part);
    }

    grades_part = trim_spaces(grades_part);
    if (grades_part.empty()) {
        return false;
    }

    long long sum = 0;
    int count = 0;
    size_t pos = 0;

    while (pos <= grades_part.size()) {
        size_t next = grades_part.find(',', pos);
        std::string token = (next == std::string::npos)
            ? grades_part.substr(pos)
            : grades_part.substr(pos, next - pos);

        int grade = 0;
        if (!parse_int_strict(token, grade)) {
            return false;
        }

        sum += grade;
        count++;

        if (next == std::string::npos) {
            break;
        }
        pos = next + 1;
    }

    if (count == 0) {
        return false;
    }

    average = static_cast<double>(sum) / count;
    return true;
}

bool write_lines_to_file(const std::string& filename, const std::string* lines, int n) {
    if (n <= 0) {
        return false;
    }
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        fout << lines[i] << '\n';
    }
    return fout.good();
}

bool create_students_file(const std::string& filename, int n) {
    if (n <= 0) {
        return false;
    }
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        std::string surname;
        std::cout << "Student #" << i + 1 << " surname: ";
        std::getline(std::cin, surname);

        int course = 0;
        std::cout << "Student #" << i + 1 << " course: ";
        if (!(std::cin >> course) || course <= 0) {
            return false;
        }
        std::cin.ignore(10000, '\n');

        std::string group;
        std::cout << "Student #" << i + 1 << " group: ";
        std::getline(std::cin, group);

        std::string grades;
        std::cout << "Student #" << i + 1 << " exam grades (comma-separated, e.g. 85, 90, 78): ";
        std::getline(std::cin, grades);

        std::string record = surname + ", " + std::to_string(course) + ", " + group + ", " + grades;
        std::string check_surname;
        double check_avg = 0.0;
        if (!parse_student_line(record, check_surname, check_avg)) {
            return false;
        }

        fout << record << '\n';
    }

    return fout.good();
}

bool find_worst_student(const std::string& filename, std::string& worst_surname, double& worst_avg) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        return false;
    }

    bool found = false;
    std::string line;

    while (std::getline(fin, line)) {
        if (trim_spaces(line).empty()) {
            continue;
        }
        std::string surname;
        double avg = 0.0;
        if (!parse_student_line(line, surname, avg)) {
            return false;
        }
        if (!found || avg < worst_avg) {
            worst_avg = avg;
            worst_surname = surname;
            found = true;
        }
    }

    return found;
}

void task5_test() {
    std::string lines[] = {
        "Ivanov, 2, K-21, 90, 85, 95",
        "Petrenko, 1, M-12, 60, 65, 70, 65",
        "Kovalenko 3 CS-31 75, 80, 70",
        "Shevchenko, 2, K-22, 88, 92"
    };

    const std::string temp_file = "temp_test_14_5.txt";
    bool ok = true;

    if (!write_lines_to_file(temp_file, lines, 4)) {
        std::cout << "Task 5 failed to create test file.\n";
        ok = false;
    }

    std::string worst_surname;
    double worst_avg = 0.0;
    if (!find_worst_student(temp_file, worst_surname, worst_avg) ||
        worst_surname != "Petrenko" ||
        std::fabs(worst_avg - 65.0) > 1e-9) {
        std::cout << "Task 5 failed: got \"" << worst_surname << "\" (" << worst_avg
                  << "), expected \"Petrenko\" (65.0).\n";
        ok = false;
    }

    std::remove(temp_file.c_str());

    if (ok) {
        std::cout << "Task 5 tests passed.\n";
    }
}

int main() {
    task5_test();

    int mode = 0;
    std::cout << "Select mode (1 - create new file with N lines, 2 - read existing file): ";
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cout << "Invalid mode.\n";
        return 1;
    }
    std::cin.ignore(10000, '\n');

    std::string filename;
    std::cout << "Enter file name (e.g. students.txt): ";
    std::getline(std::cin, filename);
    if (filename.empty()) {
        std::cout << "Invalid file name.\n";
        return 1;
    }

    if (mode == 1) {
        int n = 0;
        std::cout << "Enter number of lines N: ";
        if (!(std::cin >> n) || n <= 0) {
            std::cout << "Invalid N.\n";
            return 1;
        }
        std::cin.ignore(10000, '\n');

        if (!create_students_file(filename, n)) {
            std::cout << "Error creating file or invalid student record format.\n";
            return 1;
        }
    }

    std::string worst_surname;
    double worst_avg = 0.0;
    if (!find_worst_student(filename, worst_surname, worst_avg)) {
        std::cout << "Error reading file or invalid student records.\n";
        return 1;
    }

    std::cout << "Student with the worst average grade: " << worst_surname
              << " (average: " << worst_avg << ")\n";

    return 0;
}
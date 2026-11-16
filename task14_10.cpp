#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

bool read_text_file(const std::string& filename, std::string& content) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        return false;
    }
    std::ostringstream ss;
    ss << fin.rdbuf();
    content = ss.str();
    return !fin.bad();
}

bool write_text_file(const std::string& filename, const std::string& content) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }
    fout << content;
    return fout.good();
}

std::string remove_nth_nonempty_lines_str(const std::string& content, int n, int& removed_count) {
    removed_count = 0;
    std::istringstream iss(content);
    std::ostringstream out;
    std::string line;
    int nonempty_index = 0;

    while (std::getline(iss, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            out << '\n';
            continue;
        }

        nonempty_index++;
        if (nonempty_index % n == 0) {
            removed_count++;
        } else {
            out << line << '\n';
        }
    }

    return out.str();
}

int remove_nth_lines_from_file(const std::string& filename, int n, int& removed_count) {
    removed_count = 0;
    if (n <= 0) {
        return -1;
    }

    std::string content;
    if (!read_text_file(filename, content)) {
        return -1;
    }

    std::string updated = remove_nth_nonempty_lines_str(content, n, removed_count);
    if (removed_count == 0) {
        return 0;
    }

    if (!write_text_file(filename, updated)) {
        return -1;
    }

    return 1;
}

bool create_file_from_input(const std::string& filename, int total_lines) {
    if (total_lines <= 0) {
        return false;
    }
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }
    for (int i = 0; i < total_lines; i++) {
        std::string line;
        std::cout << "Line " << i + 1 << " (press Enter for empty line): ";
        std::getline(std::cin, line);
        fout << line << '\n';
    }
    return fout.good();
}

void print_file_lines(const std::string& content) {
    if (content.empty()) {
        std::cout << "  (empty file)\n";
        return;
    }
    std::istringstream iss(content);
    std::string line;
    int raw_num = 1;
    int nonempty_num = 0;
    while (std::getline(iss, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            std::cout << "  [raw " << raw_num << ", empty]      \"\"\n";
        } else {
            nonempty_num++;
            std::cout << "  [raw " << raw_num << ", non-empty #" << nonempty_num << "] \"" << line << "\"\n";
        }
        raw_num++;
    }
}

void task10_test() {
    std::string sample =
        "First line\n"
        "\n"
        "Second line\n"
        "Third line\n"
        "\n"
        "Fourth line\n";

    int removed = 0;
    std::string res_n2 = remove_nth_nonempty_lines_str(sample, 2, removed);
    std::string expected_n2 =
        "First line\n"
        "\n"
        "Third line\n"
        "\n";

    bool ok = true;
    if (removed != 2 || res_n2 != expected_n2) {
        std::cout << "Task 10 test (N=2) failed.\n";
        ok = false;
    }

    int removed_none = 0;
    std::string res_n5 = remove_nth_nonempty_lines_str(sample, 5, removed_none);
    if (removed_none != 0 || res_n5 != sample) {
        std::cout << "Task 10 test (N=5, no lines removed) failed.\n";
        ok = false;
    }

    int removed_all = 0;
    std::string res_n1 = remove_nth_nonempty_lines_str(sample, 1, removed_all);
    if (removed_all != 4 || res_n1 != "\n\n") {
        std::cout << "Task 10 test (N=1, only empty lines remain) failed.\n";
        ok = false;
    }

    const std::string temp_file = "temp_test_14_10.txt";
    std::string file_after;
    int file_removed = 0;

    if (!write_text_file(temp_file, sample) ||
        remove_nth_lines_from_file(temp_file, 2, file_removed) != 1 ||
        file_removed != 2 ||
        !read_text_file(temp_file, file_after) ||
        file_after != expected_n2) {
        std::cout << "Task 10 file update test failed.\n";
        ok = false;
    }

    int unchanged_removed = 0;
    if (remove_nth_lines_from_file(temp_file, 10, unchanged_removed) != 0 ||
        unchanged_removed != 0) {
        std::cout << "Task 10 unchanged file test failed.\n";
        ok = false;
    }

    std::remove(temp_file.c_str());

    if (ok) {
        std::cout << "Task 10 tests passed.\n";
    }
}

int main() {
    task10_test();

    int mode = 0;
    std::cout << "Select mode (1 - create new file, 2 - modify existing file): ";
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cout << "Invalid mode.\n";
        return 1;
    }
    std::cin.ignore(10000, '\n');

    std::string filename;
    std::cout << "Enter file name (e.g. lines.txt): ";
    std::getline(std::cin, filename);
    if (filename.empty()) {
        std::cout << "Invalid file name.\n";
        return 1;
    }

    if (mode == 1) {
        int total_lines = 0;
        std::cout << "Enter total number of lines to write (e.g. 5): ";
        if (!(std::cin >> total_lines) || total_lines <= 0) {
            std::cout << "Invalid number of lines.\n";
            return 1;
        }
        std::cin.ignore(10000, '\n');

        if (!create_file_from_input(filename, total_lines)) {
            std::cout << "Error creating file.\n";
            return 1;
        }
    }

    std::string before;
    if (!read_text_file(filename, before)) {
        std::cout << "Error: cannot open file.\n";
        return 1;
    }

    std::cout << "\nInitial file contents:\n";
    print_file_lines(before);

    int n = 0;
    std::cout << "\nEnter positive integer N (delete non-empty lines with numbers divisible by N, e.g. 2): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid N. Expected N >= 1.\n";
        return 1;
    }

    int removed_count = 0;
    int status = remove_nth_lines_from_file(filename, n, removed_count);
    if (status < 0) {
        std::cout << "Error processing file.\n";
        return 1;
    }

    if (status == 0) {
        std::cout << "\nNo lines with numbers divisible by " << n << " found. File left unchanged.\n";
    } else {
        std::cout << "\nRemoved " << removed_count << " line(s). Updated file contents:\n";
        std::string after;
        if (!read_text_file(filename, after)) {
            std::cout << "Error reading updated file.\n";
            return 1;
        }
        print_file_lines(after);
    }

    return 0;
}
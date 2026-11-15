#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

bool check_td_tags(const std::string& text) {
    const std::string open_tag = "<td>";
    const std::string close_tag = "</td>";
    int balance = 0;
    size_t pos = 0;

    while (pos < text.size()) {
        size_t next_open = text.find(open_tag, pos);
        size_t next_close = text.find(close_tag, pos);

        if (next_open == std::string::npos && next_close == std::string::npos) {
            break;
        }

        if (next_open != std::string::npos &&
            (next_close == std::string::npos || next_open < next_close)) {
            balance++;
            pos = next_open + open_tag.size();
        } else {
            balance--;
            if (balance < 0) {
                return false;
            }
            pos = next_close + close_tag.size();
        }
    }

    return balance == 0;
}

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

bool check_td_tags_file(const std::string& filename, bool& is_valid) {
    std::string content;
    if (!read_text_file(filename, content)) {
        return false;
    }
    is_valid = check_td_tags(content);
    return true;
}

void task4_test() {
    std::string valid_tests[] = {
        "<table><tr><td>Cell 1</td><td>Cell 2</td></tr></table>",
        "word<td>attached</td>text<td>another</td>end",
        "Plain text without any tags",
        "Line 1 <td>\nLine 2 text\n</td> Line 3"
    };

    std::string invalid_tests[] = {
        "<td>Only opening tag",
        "Only closing tag</td>",
        "</td><td>",
        "<td>First</td><td>Second",
        "<td>First</td></td>"
    };

    bool ok = true;
    for (int i = 0; i < 4; i++) {
        if (!check_td_tags(valid_tests[i])) {
            std::cout << "Task 4 failed valid test " << i << "\n";
            ok = false;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (check_td_tags(invalid_tests[i])) {
            std::cout << "Task 4 failed invalid test " << i << "\n";
            ok = false;
        }
    }

    const std::string temp_file = "temp_test_14_4.txt";
    bool file_valid = false;
    if (!write_text_file(temp_file, "<tr><td>Data</td></tr>\n") ||
        !check_td_tags_file(temp_file, file_valid) ||
        !file_valid) {
        std::cout << "Task 4 file I/O test failed.\n";
        ok = false;
    }
    std::remove(temp_file.c_str());

    if (ok) {
        std::cout << "Task 4 tests passed.\n";
    }
}

int main() {
    task4_test();

    int mode = 0;
    std::cout << "Select mode (1 - create new file, 2 - check existing file): ";
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cout << "Invalid mode.\n";
        return 1;
    }
    std::cin.ignore();

    std::string filename;
    std::cout << "Enter file name (e.g. table.txt): ";
    std::getline(std::cin, filename);
    if (filename.empty()) {
        std::cout << "Invalid file name.\n";
        return 1;
    }

    if (mode == 1) {
        std::string line;
        std::cout << "Enter text with <td> and </td> tags: ";
        std::getline(std::cin, line);
        if (!write_text_file(filename, line + "\n")) {
            std::cout << "Error writing to file.\n";
            return 1;
        }
    }

    bool is_valid = false;
    if (!check_td_tags_file(filename, is_valid)) {
        std::cout << "Error: cannot open file.\n";
        return 1;
    }

    if (is_valid) {
        std::cout << "Tags <td> and </td> are placed correctly.\n";
    } else {
        std::cout << "Error: incorrect placement of <td> and </td> tags.\n";
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdio>

bool is_target_article(const std::string& word) {
    return word == "die" || word == "der" || word == "das";
}

std::string capitalize_after_articles(const std::string& text) {
    std::string result = text;
    bool capitalize_next = false;
    size_t i = 0;

    while (i < result.size()) {
        if (result[i] == ' ' || result[i] == '\n' || result[i] == '\r' || result[i] == '\t') {
            i++;
            continue;
        }

        size_t start = i;
        while (i < result.size() && result[i] != ' ' && result[i] != '\n' && result[i] != '\r' && result[i] != '\t') {
            i++;
        }

        std::string word = result.substr(start, i - start);
        bool next_flag = is_target_article(word);

        if (capitalize_next) {
            result[start] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[start])));
        }

        capitalize_next = next_flag;
    }

    return result;
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

bool process_text_file(const std::string& filename) {
    std::string content;
    if (!read_text_file(filename, content)) {
        return false;
    }
    std::string updated = capitalize_after_articles(content);
    return write_text_file(filename, updated);
}

void task2_test() {
    std::string tests[] = {
        "der baum und die blume und das haus",
        "die sonne scheint auf das meer",
        "diesel order dastehen",
        "der Baum und die",
        "der die das kind"
    };

    std::string expected[] = {
        "der Baum und die Blume und das Haus",
        "die Sonne scheint auf das Meer",
        "diesel order dastehen",
        "der Baum und die",
        "der Die Das Kind"
    };

    bool ok = true;
    for (int i = 0; i < 5; i++) {
        std::string got = capitalize_after_articles(tests[i]);
        if (got != expected[i]) {
            std::cout << "Task 2 failed on test " << i << ": got \"" << got
                      << "\", expected \"" << expected[i] << "\"\n";
            ok = false;
        }
    }

    const std::string temp_file = "temp_test_14_2.txt";
    std::string file_content;
    if (!write_text_file(temp_file, "der hund und die katze\n") ||
        !process_text_file(temp_file) ||
        !read_text_file(temp_file, file_content) ||
        file_content != "der Hund und die Katze\n") {
        std::cout << "Task 2 file I/O test failed.\n";
        ok = false;
    }
    std::remove(temp_file.c_str());

    if (ok) {
        std::cout << "Task 2 tests passed.\n";
    }
}

int main() {
    task2_test();

    int mode = 0;
    std::cout << "Select mode (1 - create new file, 2 - process existing file): ";
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cout << "Invalid mode.\n";
        return 1;
    }
    std::cin.ignore();

    std::string filename;
    std::cout << "Enter file name (e.g. text.txt): ";
    std::getline(std::cin, filename);
    if (filename.empty()) {
        std::cout << "Invalid file name.\n";
        return 1;
    }

    if (mode == 1) {
        std::string line;
        std::cout << "Enter words separated by a single space (e.g. der baum und die blume): ";
        std::getline(std::cin, line);
        if (!write_text_file(filename, line + "\n")) {
            std::cout << "Error writing to file.\n";
            return 1;
        }
    }

    std::string before;
    if (!read_text_file(filename, before)) {
        std::cout << "Error: cannot open file.\n";
        return 1;
    }

    if (!process_text_file(filename)) {
        std::cout << "Error updating file.\n";
        return 1;
    }

    std::string after;
    if (!read_text_file(filename, after)) {
        std::cout << "Error reading updated file.\n";
        return 1;
    }

    std::cout << "Before: " << before;
    if (before.empty() || before.back() != '\n') {
        std::cout << "\n";
    }
    std::cout << "After:  " << after;
    if (after.empty() || after.back() != '\n') {
        std::cout << "\n";
    }

    return 0;
}
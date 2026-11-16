#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

bool is_separator(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' ||
           ch == ',' || ch == '.' || ch == '!' || ch == '?';
}

void reverse_range(std::string& s, size_t left, size_t right) {
    while (left < right) {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        left++;
        right--;
    }
}

std::string decrypt_text(const std::string& text) {
    std::string result = text;
    size_t i = 0;

    while (i < result.size()) {
        if (is_separator(result[i])) {
            i++;
            continue;
        }

        size_t start = i;
        while (i < result.size() && !is_separator(result[i])) {
            i++;
        }

        if (i > start) {
            reverse_range(result, start, i - 1);
        }
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

bool decrypt_file(const std::string& src_filename, const std::string& dst_filename) {
    std::string encrypted;
    if (!read_text_file(src_filename, encrypted)) {
        return false;
    }
    std::string decrypted = decrypt_text(encrypted);
    return write_text_file(dst_filename, decrypted);
}

void task3_test() {
    std::string tests[] = {
        "olleH,   dlrow! woH   era uoy?",
        "gnimmargorp",
        "   , . ! ? ",
        "a, b! c?",
        "tsriF enil.\ndnoceS   enil!"
    };

    std::string expected[] = {
        "Hello,   world! How   are you?",
        "programming",
        "   , . ! ? ",
        "a, b! c?",
        "First line.\nSecond   line!"
    };

    bool ok = true;
    for (int i = 0; i < 5; i++) {
        std::string got = decrypt_text(tests[i]);
        if (got != expected[i]) {
            std::cout << "Task 3 failed on test " << i << ": got \"" << got
                      << "\", expected \"" << expected[i] << "\"\n";
            ok = false;
        }
    }

    const std::string src_temp = "temp_enc_14_3.txt";
    const std::string dst_temp = "temp_dec_14_3.txt";
    std::string file_out;

    if (!write_text_file(src_temp, "terceS   egassem,   degnahcnu!\n") ||
        !decrypt_file(src_temp, dst_temp) ||
        !read_text_file(dst_temp, file_out) ||
        file_out != "Secret   message,   unchanged!\n") {
        std::cout << "Task 3 file I/O test failed.\n";
        ok = false;
    }

    std::remove(src_temp.c_str());
    std::remove(dst_temp.c_str());

    if (ok) {
        std::cout << "Task 3 tests passed.\n";
    }
}

int main() {
    task3_test();

    int mode = 0;
    std::cout << "Select mode (1 - create encrypted file and decrypt, 2 - decrypt existing file): ";
    if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
        std::cout << "Invalid mode.\n";
        return 1;
    }
    std::cin.ignore();

    std::string src_filename;
    std::cout << "Enter source (encrypted) file name (e.g. encrypted.txt): ";
    std::getline(std::cin, src_filename);

    std::string dst_filename;
    std::cout << "Enter destination (decrypted) file name (e.g. decrypted.txt): ";
    std::getline(std::cin, dst_filename);

    if (src_filename.empty() || dst_filename.empty() || src_filename == dst_filename) {
        std::cout << "Invalid file names (must be non-empty and different).\n";
        return 1;
    }

    if (mode == 1) {
        std::string line;
        std::cout << "Enter encrypted text (e.g. olleH,   dlrow! woH era uoy?): ";
        std::getline(std::cin, line);
        if (!write_text_file(src_filename, line + "\n")) {
            std::cout << "Error writing source file.\n";
            return 1;
        }
    }

    std::string encrypted_content;
    if (!read_text_file(src_filename, encrypted_content)) {
        std::cout << "Error: cannot open source file.\n";
        return 1;
    }

    if (!decrypt_file(src_filename, dst_filename)) {
        std::cout << "Error writing destination file.\n";
        return 1;
    }

    std::string decrypted_content;
    if (!read_text_file(dst_filename, decrypted_content)) {
        std::cout << "Error reading destination file.\n";
        return 1;
    }

    std::cout << "Encrypted: " << encrypted_content;
    if (encrypted_content.empty() || encrypted_content.back() != '\n') {
        std::cout << "\n";
    }
    std::cout << "Decrypted: " << decrypted_content;
    if (decrypted_content.empty() || decrypted_content.back() != '\n') {
        std::cout << "\n";
    }

    return 0;
}
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

std::string task1(const std::string& s) {
    size_t first_colon = s.find(':');
    if (first_colon == std::string::npos) {
        return s;
    }

    size_t comma_after = s.find(',', first_colon + 1);
    if (comma_after == std::string::npos) {
        return s.substr(first_colon + 1);
    }

    return s.substr(first_colon + 1, comma_after - first_colon - 1);
}

void task1_inplace(std::string& s) {
    size_t first_colon = s.find(':');
    if (first_colon == std::string::npos) {
        return;
    }

    size_t comma_after = s.find(',', first_colon + 1);
    if (comma_after == std::string::npos) {
        s.erase(0, first_colon + 1);
        return;
    }

    s = s.substr(first_colon + 1, comma_after - first_colon - 1);
}

void task1_test() {
    std::string tests[] = {
        "aaa:fgdsfgdsf,fsdf",
        "fdgsdfgsfdg",
        ":dgfsadg,ds",
        "dsfasd,gdsfg,f:dfasdf,sdgfasd",
        "dsf,dsfsdf,",
        "dsfsdf:dsg:fsdfsdaf",
        "df:::,,,fds",
        "abc:"
    };

    std::string expected[] = {
        "fgdsfgdsf",
        "fdgsdfgsfdg",
        "dgfsadg",
        "dfasdf",
        "dsf,dsfsdf,",
        "dsg:fsdfsdaf",
        "::",
        ""
    };

    int num_tests = 8;
    bool ok = true;
    for (int i = 0; i < num_tests; i++) {
        std::string res_new = task1(tests[i]);
        if (res_new != expected[i]) {
            std::cout << "Task 1 (new) failed on test " << i << ": got \"" << res_new
                      << "\", expected \"" << expected[i] << "\"\n";
            ok = false;
        }
        std::string res_inp = tests[i];
        task1_inplace(res_inp);
        if (res_inp != expected[i]) {
            std::cout << "Task 1 (inplace) failed on test " << i << ": got \"" << res_inp
                      << "\", expected \"" << expected[i] << "\"\n";
            ok = false;
        }
    }
    if (ok) {
        std::cout << "Task 1 tests passed.\n";
    }
}

void task1_run() {
    std::string s;
    std::cout << "Enter string: ";
    std::getline(std::cin, s);

    std::cout << "New string result: " << task1(s) << "\n";
    task1_inplace(s);
    std::cout << "In-place result:   " << s << "\n";
}

void task2_inplace(std::string& s) {
    size_t first_dot = s.find('.');
    if (first_dot == std::string::npos) {
        size_t nonspace = s.find_first_not_of(' ');
        if (nonspace == std::string::npos) {
            s.clear();
        } else {
            s.erase(0, nonspace);
        }
        return;
    }

    size_t last_dot = s.rfind('.');
    if (last_dot == first_dot) {
        s.erase(0, first_dot + 1);
        return;
    }

    s.erase(first_dot, last_dot - first_dot + 1);
}

std::string task2(const std::string& s) {
    std::string result = s;
    task2_inplace(result);
    return result;
}

void task2_test() {
    std::string tests[] = {
        "aaa.fgdsfgdsf.fsdf",
        "fdgsdfgsfdg",
        ".dgfsadg.ds",
        "dsfasd.gdsfg.f.dfasdf.sdgfasd",
        "dsf.dsfsdf.",
        "  dsfsdf.dsg:fsdfsdaf",
        "  dffds",
        "   "
    };

    std::string expected[] = {
        "aaafsdf",
        "fdgsdfgsfdg",
        "ds",
        "dsfasdsdgfasd",
        "dsf",
        "dsg:fsdfsdaf",
        "dffds",
        ""
    };

    int num_tests = 8;
    bool ok = true;
    for (int i = 0; i < num_tests; i++) {
        std::string res_new = task2(tests[i]);
        if (res_new != expected[i]) {
            std::cout << "Task 2 (new) failed on test " << i << ": got \"" << res_new
                      << "\", expected \"" << expected[i] << "\"\n";
            ok = false;
        }
        std::string res_inp = tests[i];
        task2_inplace(res_inp);
        if (res_inp != expected[i]) {
            std::cout << "Task 2 (inplace) failed on test " << i << ": got \"" << res_inp
                      << "\", expected \"" << expected[i] << "\"\n";
            ok = false;
        }
    }
    if (ok) {
        std::cout << "Task 2 tests passed.\n";
    }
}

void task2_run() {
    std::string s;
    std::cout << "Enter string: ";
    std::getline(std::cin, s);

    std::cout << "New string result: " << task2(s) << "\n";
    task2_inplace(s);
    std::cout << "In-place result:   " << s << "\n";
}

std::string task3(const std::string& s) {
    std::string result;
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char cur = static_cast<unsigned char>(s[i]);
        if (std::isalpha(cur)) {
            if (i + 1 == s.size() || std::isspace(static_cast<unsigned char>(s[i + 1]))) {
                continue;
            }
        }
        result.push_back(s[i]);
    }
    return result;
}

void task3_inplace(std::string& s) {
    size_t i = 0;
    while (i < s.size()) {
        unsigned char cur = static_cast<unsigned char>(s[i]);
        if (std::isalpha(cur) &&
            (i + 1 == s.size() || std::isspace(static_cast<unsigned char>(s[i + 1])))) {
            s.erase(i, 1);
        } else {
            i++;
        }
    }
}

void task3_test() {
    std::string tests[] = {
        "aaa  fgdsfgdsf fsdf",
        "fdgsdfgsfdg",
        " dgfsadg ds",
        "dsfasd gdsfg f dfasdf  sdgfasd",
        "dsf dsfsdf ",
        "  dsfsdf dsg fsdfsdaf",
        "  dffds"
    };

    std::string expected[] = {
        "aa  fgdsfgds fsd",
        "fdgsdfgsfd",
        " dgfsad d",
        "dsfas gdsf  dfasd  sdgfas",
        "ds dsfsd ",
        "  dsfsd ds fsdfsda",
        "  dffd"
    };

    int num_tests = 7;
    bool ok = true;
    for (int i = 0; i < num_tests; i++) {
        std::string res_new = task3(tests[i]);
        if (res_new != expected[i]) {
            std::cout << "Task 3 (new) failed on test " << i << ": got \"" << res_new
                      << "\", expected \"" << expected[i] << "\"\n";
            ok = false;
        }
        std::string res_inp = tests[i];
        task3_inplace(res_inp);
        if (res_inp != expected[i]) {
            std::cout << "Task 3 (inplace) failed on test " << i << ": got \"" << res_inp
                      << "\", expected \"" << expected[i] << "\"\n";
            ok = false;
        }
    }
    if (ok) {
        std::cout << "Task 3 tests passed.\n";
    }
}

void task3_run() {
    std::string s;
    std::cout << "Enter Latin words separated by spaces: ";
    std::getline(std::cin, s);

    std::cout << "New string result: " << task3(s) << "\n";
    task3_inplace(s);
    std::cout << "In-place result:   " << s << "\n";
}

size_t partial_split_floats(const std::string& s, double* arr, size_t& n, char delim = ' ') {
    size_t max_n = n;
    size_t count = 0;
    size_t pos = 0;

    while (count < max_n && pos <= s.size()) {
        size_t next = s.find(delim, pos);
        std::string token = (next == std::string::npos) ? s.substr(pos) : s.substr(pos, next - pos);

        size_t first = token.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            size_t last = token.find_last_not_of(" \t\r\n");
            token = token.substr(first, last - first + 1);
            std::stringstream ss(token);
            double val = 0.0;
            char extra = '\0';
            if ((ss >> val) && !(ss >> extra)) {
                arr[count++] = val;
            }
        }

        if (next == std::string::npos) {
            break;
        }
        pos = next + 1;
    }

    n = count;
    return count;
}

void task4_test() {
    std::string tests[] = {
        "0.43223  0.34234  23.545",
        "-432.4, 45.435634",
        "1.5; -2.25; 3.75; 4.5"
    };
    char delims[] = {' ', ',', ';'};
    size_t expected_counts[] = {3, 2, 3};
    double expected[][3] = {
        {0.43223, 0.34234, 23.545},
        {-432.4, 45.435634, 0.0},
        {1.5, -2.25, 3.75}
    };

    bool ok = true;
    for (int i = 0; i < 3; i++) {
        double ar[3] = {0.0, 0.0, 0.0};
        size_t n = 3;
        partial_split_floats(tests[i], ar, n, delims[i]);
        if (n != expected_counts[i]) {
            std::cout << "Task 4 count failed on test " << i << "\n";
            ok = false;
        }
        for (size_t j = 0; j < n; j++) {
            if (std::fabs(ar[j] - expected[i][j]) > 0.0001) {
                std::cout << "Task 4 value failed on test " << i << ": got " << ar[j]
                          << ", expected " << expected[i][j] << "\n";
                ok = false;
            }
        }
    }
    if (ok) {
        std::cout << "Task 4 tests passed.\n";
    }
}

void task4_run() {
    std::string s;
    std::cout << "Enter string with floating-point numbers: ";
    std::getline(std::cin, s);

    std::string delim_line;
    std::cout << "Enter delimiter character (press Enter for space): ";
    std::getline(std::cin, delim_line);
    char delim = delim_line.empty() ? ' ' : delim_line[0];

    size_t n = 0;
    std::cout << "Enter max count n (1..100): ";
    if (!(std::cin >> n) || n == 0 || n > 100) {
        std::cout << "Invalid n.\n";
        return;
    }

    double arr[100];
    partial_split_floats(s, arr, n, delim);

    std::cout << "Parsed " << n << " numbers: ";
    for (size_t i = 0; i < n; i++) {
        std::cout << arr[i] << (i + 1 < n ? ", " : "");
    }
    std::cout << "\n";
}

size_t partial_split_words(const std::string& s, std::string* words, size_t& n, char delim = ' ') {
    size_t max_n = n;
    size_t count = 0;
    size_t pos = 0;

    while (count < max_n && pos <= s.size()) {
        size_t next = s.find(delim, pos);
        std::string word = (next == std::string::npos) ? s.substr(pos) : s.substr(pos, next - pos);

        if (!word.empty()) {
            words[count++] = word;
        }

        if (next == std::string::npos) {
            break;
        }
        pos = next + 1;
    }

    n = count;
    return count;
}

void task5_test() {
    std::string s1 = "  one   two three four  ";
    std::string w1[3];
    size_t n1 = 3;
    partial_split_words(s1, w1, n1, ' ');

    std::string s2 = "alpha,beta,gamma";
    std::string w2[5];
    size_t n2 = 5;
    partial_split_words(s2, w2, n2, ',');

    bool ok = (n1 == 3 && w1[0] == "one" && w1[1] == "two" && w1[2] == "three") &&
              (n2 == 3 && w2[0] == "alpha" && w2[1] == "beta" && w2[2] == "gamma");

    if (ok) {
        std::cout << "Task 5 tests passed.\n";
    } else {
        std::cout << "Task 5 tests failed.\n";
    }
}

void task5_run() {
    std::string s;
    std::cout << "Enter string: ";
    std::getline(std::cin, s);

    std::string delim_line;
    std::cout << "Enter delimiter character (press Enter for space): ";
    std::getline(std::cin, delim_line);
    char delim = delim_line.empty() ? ' ' : delim_line[0];

    size_t n = 0;
    std::cout << "Enter max words count n (1..100): ";
    if (!(std::cin >> n) || n == 0 || n > 100) {
        std::cout << "Invalid n.\n";
        return;
    }

    std::string words[100];
    partial_split_words(s, words, n, delim);

    std::cout << "First " << n << " words:\n";
    for (size_t i = 0; i < n; i++) {
        std::cout << i + 1 << ") \"" << words[i] << "\"\n";
    }
}

std::string shortest_word_first(const std::string& s) {
    std::string best;
    size_t min_len = std::string::npos;
    size_t i = 0;

    while (i < s.size()) {
        if (std::isalpha(static_cast<unsigned char>(s[i]))) {
            size_t start = i;
            while (i < s.size() && std::isalpha(static_cast<unsigned char>(s[i]))) {
                i++;
            }
            std::string word = s.substr(start, i - start);
            if (word.size() < min_len) {
                min_len = word.size();
                best = word;
            }
        } else {
            i++;
        }
    }
    return best;
}

std::string shortest_word_last(const std::string& s) {
    std::string best;
    size_t min_len = std::string::npos;
    size_t i = 0;

    while (i < s.size()) {
        if (std::isalpha(static_cast<unsigned char>(s[i]))) {
            size_t start = i;
            while (i < s.size() && std::isalpha(static_cast<unsigned char>(s[i]))) {
                i++;
            }
            std::string word = s.substr(start, i - start);
            if (word.size() <= min_len) {
                min_len = word.size();
                best = word;
            }
        } else {
            i++;
        }
    }
    return best;
}

std::string shortest_words_all(const std::string& s) {
    std::string result;
    size_t min_len = std::string::npos;
    size_t i = 0;

    while (i < s.size()) {
        if (std::isalpha(static_cast<unsigned char>(s[i]))) {
            size_t start = i;
            while (i < s.size() && std::isalpha(static_cast<unsigned char>(s[i]))) {
                i++;
            }
            std::string word = s.substr(start, i - start);
            if (word.size() < min_len) {
                min_len = word.size();
                result = word;
            } else if (word.size() == min_len) {
                result += " " + word;
            }
        } else {
            i++;
        }
    }
    return result;
}

void task6_test() {
    std::string sentence = "This is an old oak tree in my yard!";
    bool ok = (shortest_word_first(sentence) == "is") &&
              (shortest_word_last(sentence) == "my") &&
              (shortest_words_all(sentence) == "is an in my");

    if (ok) {
        std::cout << "Task 6 tests passed.\n";
    } else {
        std::cout << "Task 6 tests failed.\n";
    }
}

void task6_run() {
    std::string s;
    std::cout << "Enter a Latin sentence: ";
    std::getline(std::cin, s);

    std::string first_w = shortest_word_first(s);
    if (first_w.empty()) {
        std::cout << "No words found.\n";
        return;
    }

    std::cout << "a) First shortest word: " << first_w << "\n";
    std::cout << "b) Last shortest word:  " << shortest_word_last(s) << "\n";
    std::cout << "c) All shortest words:  " << shortest_words_all(s) << "\n";
}

int main() {
    int num_task = 0;
    std::cout << "Select task number (1-6): ";
    if (!(std::cin >> num_task)) {
        std::cout << "Invalid input.\n";
        return 1;
    }
    std::cin.ignore();

    switch (num_task) {
        case 1:
            task1_test();
            task1_run();
            break;
        case 2:
            task2_test();
            task2_run();
            break;
        case 3:
            task3_test();
            task3_run();
            break;
        case 4:
            task4_test();
            task4_run();
            break;
        case 5:
            task5_test();
            task5_run();
            break;
        case 6:
            task6_test();
            task6_run();
            break;
        default:
            std::cout << "No such task.\n";
    }

    return 0;
}
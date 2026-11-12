#include <stdio.h>
#include <stdbool.h>
#include "Date.h"

void test_date(void) {
    Date d1 = {12, 11, 2026};
    Date t1 = get_tomorrow(d1);
    bool test1 = (t1.day == 13 && t1.month == 11 && t1.year == 2026 && get_day_of_week(d1) == 4);

    Date d2 = {28, 2, 2024};
    Date t2 = get_tomorrow(d2);
    bool test2 = (t2.day == 29 && t2.month == 2 && t2.year == 2024);

    Date d3 = {28, 2, 2026};
    Date t3 = get_tomorrow(d3);
    bool test3 = (t3.day == 1 && t3.month == 3 && t3.year == 2026);

    Date d4 = {31, 12, 2026};
    Date t4 = get_tomorrow(d4);
    bool test4 = (t4.day == 1 && t4.month == 1 && t4.year == 2027);

    Date d5 = {31, 4, 2026};
    bool test5 = (is_valid_date(&d5) == false);

    printf("--- Automated Tests (Date) ---\n");
    printf("Test 1 (regular day & weekday 12.11.2026): %s\n", test1 ? "PASSED" : "FAILED");
    printf("Test 2 (leap year 28.02.2024 -> 29.02.2024): %s\n", test2 ? "PASSED" : "FAILED");
    printf("Test 3 (non-leap year 28.02.2026 -> 01.03.2026): %s\n", test3 ? "PASSED" : "FAILED");
    printf("Test 4 (year rollover 31.12.2026 -> 01.01.2027): %s\n", test4 ? "PASSED" : "FAILED");
    printf("Test 5 (invalid date 31.04.2026): %s\n", test5 ? "PASSED" : "FAILED");
    printf("--------------------------------\n\n");
}

int main(void) {
    test_date();

    Date current;
    if (!input_date(&current)) {
        printf("Invalid date.\n");
        return 1;
    }

    Date tomorrow = get_tomorrow(current);
    int weekday = get_day_of_week(current);

    printf("Entered date: ");
    print_date(&current);

    printf("Tomorrow's date: ");
    print_date(&tomorrow);

    printf("Day of the week: ");
    print_day_of_week(weekday);

    return 0;
}
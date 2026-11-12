#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Mount.h"

void test_mount(void) {
    Mount sample[3] = {
        {"Hoverla", 2061.0},
        {"Mount Everest", 8848.86},
        {"K2", 8611.0}
    };

    const char *highest = find_highest_peak(sample, 3);
    bool t1 = (highest != NULL && strcmp(highest, "Mount Everest") == 0);
    bool t2 = (find_highest_peak(NULL, 3) == NULL && find_highest_peak(sample, 0) == NULL);

    printf("--- Automated Tests (Mount) ---\n");
    printf("Test 1 (highest peak -> Mount Everest): %s\n", t1 ? "PASSED" : "FAILED");
    printf("Test 2 (NULL and empty array safety): %s\n", t2 ? "PASSED" : "FAILED");
    printf("Test 3 (search existing K2): ");
    print_peak_height(sample, 3, "K2");
    printf("Test 4 (search missing Elbrus): ");
    print_peak_height(sample, 3, "Elbrus");
    printf("-------------------------------\n\n");
}

int main(void) {
    test_mount();

    int n;
    printf("Enter number of mountains N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    Mount *mountains = (Mount *)malloc((size_t)n * sizeof(Mount));
    if (mountains == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (!input_mounts(mountains, n)) {
        printf("Invalid mountain input.\n");
        free(mountains);
        return 1;
    }

    print_mounts(mountains, n);

    const char *highest_name = find_highest_peak(mountains, n);
    if (highest_name != NULL) {
        printf("\nHighest peak: %s\n", highest_name);
    }

    char search_name[MAX_NAME_LEN];
    printf("\nEnter mountain name to search: ");
    if (scanf(" %255[^\n]", search_name) != 1) {
        printf("Invalid input.\n");
        free(mountains);
        return 1;
    }

    print_peak_height(mountains, n, search_name);

    free(mountains);
    return 0;
}
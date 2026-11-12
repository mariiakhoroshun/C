#include "Mount.h"
#include <stdio.h>
#include <string.h>

bool input_mount(Mount *m) {
    if (m == NULL) {
        return false;
    }
    printf("  Name: ");
    if (scanf(" %255[^\n]", m->name) != 1) {
        return false;
    }
    printf("  Height (m): ");
    if (scanf("%lf", &m->height) != 1 || m->height <= 0.0) {
        return false;
    }
    return true;
}

bool input_mounts(Mount *arr, int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        printf("Mountain #%d:\n", i + 1);
        if (!input_mount(&arr[i])) {
            return false;
        }
    }
    return true;
}

void print_mount(const Mount *m) {
    if (m == NULL) {
        return;
    }
    printf("%-25s | %.2f m\n", m->name, m->height);
}

void print_mounts(const Mount *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }
    printf("\nList of mountains:\n");
    for (int i = 0; i < n; i++) {
        print_mount(&arr[i]);
    }
}

const char *find_highest_peak(const Mount *arr, int n) {
    if (arr == NULL || n <= 0) {
        return NULL;
    }
    int max_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].height > arr[max_idx].height) {
            max_idx = i;
        }
    }
    return arr[max_idx].name;
}

void print_peak_height(const Mount *arr, int n, const char *target_name) {
    if (arr == NULL || n <= 0 || target_name == NULL) {
        return;
    }
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, target_name) == 0) {
            printf("Height of %s: %.2f m\n", arr[i].name, arr[i].height);
            found = true;
        }
    }
    if (!found) {
        printf("Mountain \"%s\" not found in the array.\n", target_name);
    }
}
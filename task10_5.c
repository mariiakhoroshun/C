#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

typedef struct {
    char name[MAX_NAME_LEN];
    double height;
} Mountain;

int input_mountain(Mountain *m) {
    printf("  Name: ");
    if (scanf(" %99[^\n]", m->name) != 1) {
        return 0;
    }
    printf("  Height (m): ");
    if (scanf("%lf", &m->height) != 1) {
        return 0;
    }
    return 1;
}

int input_mountains(Mountain *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("Mountain #%d:\n", i + 1);
        if (!input_mountain(&arr[i])) {
            return 0;
        }
    }
    return 1;
}

void output_mountain(Mountain m) {
    printf("%-25s | %.2f m\n", m.name, m.height);
}

void output_mountains(const Mountain *arr, int n) {
    printf("\nList of mountains:\n");
    for (int i = 0; i < n; i++) {
        output_mountain(arr[i]);
    }
}

const char *find_highest_peak(const Mountain *arr, int n) {
    int max_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].height > arr[max_idx].height) {
            max_idx = i;
        }
    }
    return arr[max_idx].name;
}

void print_peak_height(const Mountain *arr, int n, const char *target_name) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, target_name) == 0) {
            printf("Height of %s: %.2f m\n", arr[i].name, arr[i].height);
            found = 1;
        }
    }
    if (!found) {
        printf("Mountain \"%s\" not found in the array.\n", target_name);
    }
}

int main(void) {
    int n;

    printf("Enter number of mountains N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    Mountain *mountains = (Mountain *)malloc((size_t)n * sizeof(Mountain));
    if (mountains == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (!input_mountains(mountains, n)) {
        printf("Invalid input.\n");
        free(mountains);
        return 1;
    }

    output_mountains(mountains, n);

    const char *highest_name = find_highest_peak(mountains, n);
    printf("\nHighest peak: %s\n", highest_name);

    char search_name[MAX_NAME_LEN];
    printf("\nEnter mountain name to search: ");
    if (scanf(" %99[^\n]", search_name) != 1) {
        printf("Invalid input.\n");
        free(mountains);
        return 1;
    }

    print_peak_height(mountains, n, search_name);

    free(mountains);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    char name[64];
    double price;
    int min_age;
    int max_age;
} Toy;

int is_constructor_name(const char *name) {
    const char *target = "constructor";
    size_t i = 0;
    while (name[i] != '\0' && target[i] != '\0') {
        if (tolower((unsigned char)name[i]) != target[i]) {
            return 0;
        }
        i++;
    }
    return name[i] == '\0' && target[i] == '\0';
}

int create_toys_file(const char *filename, int count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        Toy t;
        memset(&t, 0, sizeof(Toy));
        printf("Toy %d (format: name price min_age max_age, e.g. constructor 500 6 12): ", i + 1);
        if (scanf("%63s %lf %d %d", t.name, &t.price, &t.min_age, &t.max_age) != 4 ||
            t.price < 0.0 || t.min_age < 0 || t.max_age < t.min_age) {
            fclose(file);
            return 0;
        }
        if (fwrite(&t, sizeof(Toy), 1, file) != 1) {
            fclose(file);
            return 0;
        }
    }
    return fclose(file) == 0;
}

int print_toys_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    Toy t;
    int idx = 1;
    while (fread(&t, sizeof(Toy), 1, file) == 1) {
        printf("  #%d: %s | Price: %g UAH | Age: %d-%d\n",
               idx, t.name, t.price, t.min_age, t.max_age);
        idx++;
    }
    if (idx == 1) {
        printf("  (empty)\n");
    }
    int has_error = ferror(file);
    fclose(file);
    return !has_error;
}

int save_constructor_search_to_file(const char *src_filename, const char *dst_filename,
                                    double target_price, int min_age_x, int *found_count) {
    if (found_count == NULL) {
        return 0;
    }
    *found_count = 0;

    FILE *src = fopen(src_filename, "rb");
    if (src == NULL) {
        return 0;
    }
    FILE *dst = fopen(dst_filename, "wb");
    if (dst == NULL) {
        fclose(src);
        return 0;
    }

    Toy t;
    int ok = 1;
    while (fread(&t, sizeof(Toy), 1, src) == 1) {
        if (is_constructor_name(t.name) &&
            fabs(t.price - target_price) < 1e-6 &&
            t.min_age == min_age_x &&
            t.max_age == 12) {
            if (fwrite(&t, sizeof(Toy), 1, dst) != 1) {
                ok = 0;
                break;
            }
            (*found_count)++;
        }
    }

    if (ferror(src)) {
        ok = 0;
    }

    if (ok && *found_count == 0) {
        Toy absence;
        memset(&absence, 0, sizeof(Toy));
        strcpy(absence.name, "Constructor not found");
        absence.price = -1.0;
        absence.min_age = -1;
        absence.max_age = -1;
        if (fwrite(&absence, sizeof(Toy), 1, dst) != 1) {
            ok = 0;
        }
    }

    if (fclose(dst) != 0) {
        ok = 0;
    }
    fclose(src);
    return ok;
}

int print_search_result_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    Toy t;
    int idx = 1;
    while (fread(&t, sizeof(Toy), 1, file) == 1) {
        if (t.price < 0.0) {
            printf("  Result: %s\n", t.name);
        } else {
            printf("  #%d: %s | Price: %g UAH | Age: %d-%d\n",
                   idx, t.name, t.price, t.min_age, t.max_age);
        }
        idx++;
    }
    int has_error = ferror(file);
    fclose(file);
    return !has_error;
}

int main(void) {
    int mode;
    char toys_file[256];
    char result_file[256];
    double target_price;
    int min_age_x;

    printf("Select input mode (1 - create new toys file, 2 - use existing toys file): ");
    if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
        printf("Invalid mode.\n");
        return 1;
    }

    printf("Enter toys binary file name (single word, e.g. toys.bin): ");
    if (scanf("%255s", toys_file) != 1) {
        printf("Invalid file name.\n");
        return 1;
    }

    if (mode == 1) {
        int count;
        printf("Enter number of toys (integer >= 1, e.g. 3): ");
        if (scanf("%d", &count) != 1 || count <= 0) {
            printf("Invalid count.\n");
            return 1;
        }
        if (!create_toys_file(toys_file, count)) {
            printf("Error creating toys file.\n");
            return 1;
        }
    }

    printf("\nToys in file '%s':\n", toys_file);
    if (!print_toys_file(toys_file)) {
        printf("Error reading toys file.\n");
        return 1;
    }

    printf("\nEnter output result binary file name (single word, e.g. res.bin): ");
    if (scanf("%255s", result_file) != 1) {
        printf("Invalid output file name.\n");
        return 1;
    }

    printf("Enter constructor price Y and lower age x (format: Y x, e.g. 500 6): ");
    if (scanf("%lf %d", &target_price, &min_age_x) != 2 || target_price < 0.0 || min_age_x < 0) {
        printf("Invalid search parameters.\n");
        return 1;
    }

    int found_count = 0;
    if (!save_constructor_search_to_file(toys_file, result_file, target_price, min_age_x, &found_count)) {
        printf("Error processing search.\n");
        return 1;
    }

    printf("\nSearch result (written to '%s' and printed to console):\n", result_file);
    if (!print_search_result_file(result_file)) {
        printf("Error reading result file.\n");
        return 1;
    }

    return 0;
}
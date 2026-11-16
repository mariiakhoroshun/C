#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int print_file_contents(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    double value;
    int first = 1;
    while (fread(&value, sizeof(double), 1, file) == 1) {
        if (!first) {
            printf(", ");
        }
        printf("%g", value);
        first = 0;
    }
    if (first) {
        printf("(empty)");
    }
    printf("\n");
    int has_error = ferror(file);
    fclose(file);
    return !has_error;
}

int build_filtered_file(const char *src_filename, const char *dst_filename, double a) {
    FILE *src = fopen(src_filename, "rb");
    if (src == NULL) {
        return 0;
    }
    FILE *dst = fopen(dst_filename, "wb");
    if (dst == NULL) {
        fclose(src);
        return 0;
    }
    double value;
    int ok = 1;
    while (fread(&value, sizeof(double), 1, src) == 1) {
        if (fabs(value) < a) {
            if (fwrite(&value, sizeof(double), 1, dst) != 1) {
                ok = 0;
                break;
            }
        }
    }
    if (ferror(src)) {
        ok = 0;
    }
    if (fclose(dst) != 0) {
        ok = 0;
    }
    fclose(src);
    return ok;
}

int remove_less_than_abs_from_file(const char *filename, double a) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    double value;
    size_t keep_count = 0;
    while (fread(&value, sizeof(double), 1, file) == 1) {
        if (fabs(value) >= a) {
            keep_count++;
        }
    }
    if (ferror(file)) {
        fclose(file);
        return 0;
    }

    double *kept = NULL;
    if (keep_count > 0) {
        kept = (double *)malloc(keep_count * sizeof(double));
        if (kept == NULL) {
            fclose(file);
            return 0;
        }
        rewind(file);
        size_t index = 0;
        while (fread(&value, sizeof(double), 1, file) == 1) {
            if (fabs(value) >= a) {
                kept[index++] = value;
            }
        }
        if (ferror(file)) {
            free(kept);
            fclose(file);
            return 0;
        }
    }
    fclose(file);

    file = fopen(filename, "wb");
    if (file == NULL) {
        free(kept);
        return 0;
    }
    int ok = 1;
    if (keep_count > 0) {
        if (fwrite(kept, sizeof(double), keep_count, file) != keep_count) {
            ok = 0;
        }
    }
    if (fclose(file) != 0) {
        ok = 0;
    }
    free(kept);
    return ok;
}

int main(void) {
    char f_name[256];
    char g_name[256];
    double a;

    printf("Enter existing binary file F name (single word, no spaces, e.g. hi): ");
    if (scanf("%255s", f_name) != 1) {
        printf("Invalid file F name.\n");
        return 1;
    }

    printf("Enter new output binary file G name (single word, e.g. out.bin): ");
    if (scanf("%255s", g_name) != 1) {
        printf("Invalid file G name.\n");
        return 1;
    }

    printf("Enter positive threshold a > 0 (use dot for decimals, e.g. 4.5): ");
    if (scanf("%lf", &a) != 1 || a <= 0.0) {
        printf("Invalid value for a. Expected a > 0.\n");
        return 1;
    }

    printf("Initial file F contents: ");
    if (!print_file_contents(f_name)) {
        printf("Error: file '%s' not found or cannot be read. Create it first using Task 1.\n", f_name);
        return 1;
    }

    if (!build_filtered_file(f_name, g_name, a)) {
        printf("Error building file G.\n");
        return 1;
    }

    if (!remove_less_than_abs_from_file(f_name, a)) {
        printf("Error updating file F.\n");
        return 1;
    }

    printf("File G contents (|x| < %g): ", a);
    if (!print_file_contents(g_name)) {
        printf("Error reading file G.\n");
        return 1;
    }

    printf("Updated file F contents (|x| >= %g): ", a);
    if (!print_file_contents(f_name)) {
        printf("Error reading file F.\n");
        return 1;
    }

    return 0;
}
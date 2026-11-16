#include <stdio.h>
#include <stdlib.h>

int create_int_file(const char *filename, int count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        int value;
        if (scanf("%d", &value) != 1) {
            fclose(file);
            return 0;
        }
        if (fwrite(&value, sizeof(int), 1, file) != 1) {
            fclose(file);
            return 0;
        }
    }
    return fclose(file) == 0;
}

int print_int_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    int value;
    int first = 1;
    while (fread(&value, sizeof(int), 1, file) == 1) {
        if (!first) {
            printf(", ");
        }
        printf("%d", value);
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

int find_max_in_block(const int *block, size_t count) {
    int max_val = block[0];
    for (size_t i = 1; i < count; i++) {
        if (block[i] > max_val) {
            max_val = block[i];
        }
    }
    return max_val;
}

int build_block_max_file(const char *src_filename, const char *dst_filename, int n, size_t *total_elements) {
    if (n <= 0 || total_elements == NULL) {
        return 0;
    }
    *total_elements = 0;

    FILE *src = fopen(src_filename, "rb");
    if (src == NULL) {
        return 0;
    }
    FILE *dst = fopen(dst_filename, "wb");
    if (dst == NULL) {
        fclose(src);
        return 0;
    }

    int *buffer = (int *)malloc((size_t)n * sizeof(int));
    if (buffer == NULL) {
        fclose(dst);
        fclose(src);
        return 0;
    }

    int ok = 1;
    size_t read_count;
    while ((read_count = fread(buffer, sizeof(int), (size_t)n, src)) > 0) {
        int block_max = find_max_in_block(buffer, read_count);
        if (fwrite(&block_max, sizeof(int), 1, dst) != 1) {
            ok = 0;
            break;
        }
        *total_elements += read_count;
    }

    if (ferror(src)) {
        ok = 0;
    }

    free(buffer);
    if (fclose(dst) != 0) {
        ok = 0;
    }
    fclose(src);
    return ok;
}

int main(void) {
    int mode;
    char f_name[256];
    char g_name[256];
    int n;

    printf("Select input mode (1 - create new file F now, 2 - use existing file F): ");
    if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
        printf("Invalid mode.\n");
        return 1;
    }

    printf("Enter binary file F name (single word, e.g. f.bin): ");
    if (scanf("%255s", f_name) != 1) {
        printf("Invalid file F name.\n");
        return 1;
    }

    if (mode == 1) {
        int count;
        printf("Enter number of integers to write to F (integer >= 1, e.g. 7): ");
        if (scanf("%d", &count) != 1 || count <= 0) {
            printf("Invalid count.\n");
            return 1;
        }
        printf("Enter %d integers separated by space or Enter: ", count);
        if (!create_int_file(f_name, count)) {
            printf("Error creating file F.\n");
            return 1;
        }
    }

    printf("Enter output binary file G name (single word, e.g. g.bin): ");
    if (scanf("%255s", g_name) != 1) {
        printf("Invalid file G name.\n");
        return 1;
    }

    printf("Enter group size n (integer >= 1, e.g. 3): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid group size n.\n");
        return 1;
    }

    printf("File F contents: ");
    if (!print_int_file(f_name)) {
        printf("Error reading file F.\n");
        return 1;
    }

    size_t total_elements = 0;
    if (!build_block_max_file(f_name, g_name, n, &total_elements)) {
        printf("Error building file G.\n");
        return 1;
    }

    if (total_elements % (size_t)n == 0) {
        printf("Case 1: total elements (%zu) is divisible by n (%d).\n", total_elements, n);
    } else {
        printf("Case 2: total elements (%zu) is not divisible by n (%d), last group size = %zu.\n",
               total_elements, n, total_elements % (size_t)n);
    }

    printf("File G contents: ");
    if (!print_int_file(g_name)) {
        printf("Error reading file G.\n");
        return 1;
    }

    return 0;
}
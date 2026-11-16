#include <stdio.h>
#include <math.h>

int is_even(int x) {
    return x % 2 == 0;
}

int is_power_of_3(int x) {
    if (x < 1) {
        return 0;
    }
    while (x % 3 == 0) {
        x /= 3;
    }
    return x == 1;
}

int is_perfect_square(int x) {
    if (x < 0) {
        return 0;
    }
    int r = (int)round(sqrt((double)x));
    return (long long)r * r == x;
}

int is_prime(int n) {
    if (n < 2) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }
    for (int d = 3; (long long)d * d <= n; d += 2) {
        if (n % d == 0) {
            return 0;
        }
    }
    return 1;
}

int has_three_divisors(int x) {
    if (x < 4) {
        return 0;
    }
    int r = (int)round(sqrt((double)x));
    if ((long long)r * r != x) {
        return 0;
    }
    return is_prime(r);
}

int is_palindrome(int x) {
    if (x < 0) {
        return 0;
    }
    int original = x;
    long long reversed = 0;
    while (x > 0) {
        reversed = reversed * 10 + (x % 10);
        x /= 10;
    }
    return reversed == original;
}

int is_fibonacci(int x) {
    if (x < 0) {
        return 0;
    }
    if (x == 0 || x == 1) {
        return 1;
    }
    long long f0 = 0;
    long long f1 = 1;
    while (f1 < x) {
        long long next = f0 + f1;
        f0 = f1;
        f1 = next;
    }
    return f1 == x;
}

int matches_filter(int x, char option) {
    switch (option) {
        case 'a':
            return is_even(x);
        case 'b':
            return is_power_of_3(x);
        case 'c':
            return is_perfect_square(x);
        case 'd':
            return has_three_divisors(x);
        case 'e':
            return is_palindrome(x);
        case 'f':
            return is_fibonacci(x);
        default:
            return 0;
    }
}

int create_int_file(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }
    int value;
    while (1) {
        if (scanf("%d", &value) != 1) {
            fclose(file);
            return 0;
        }
        if (value == 0) {
            break;
        }
        if (fwrite(&value, sizeof(int), 1, file) != 1) {
            fclose(file);
            return 0;
        }
    }
    return fclose(file) == 0;
}

int build_filtered_file(const char *src_filename, const char *dst_filename, char option) {
    FILE *src = fopen(src_filename, "rb");
    if (src == NULL) {
        return 0;
    }
    FILE *dst = fopen(dst_filename, "wb");
    if (dst == NULL) {
        fclose(src);
        return 0;
    }
    int value;
    int ok = 1;
    while (fread(&value, sizeof(int), 1, src) == 1) {
        if (matches_filter(value, option)) {
            if (fwrite(&value, sizeof(int), 1, dst) != 1) {
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

int main(void) {
    char f_name[256];
    char g_name[256];
    char option;

    printf("Enter file F name (single word, e.g. f.bin): ");
    if (scanf("%255s", f_name) != 1) {
        printf("Invalid file name.\n");
        return 1;
    }

    printf("Enter integers separated by space or Enter (0 to stop): ");
    if (!create_int_file(f_name)) {
        printf("Error creating file F.\n");
        return 1;
    }

    printf("Enter file G name (single word, e.g. g.bin): ");
    if (scanf("%255s", g_name) != 1) {
        printf("Invalid file name.\n");
        return 1;
    }

    printf("Enter filter letter (a: even, b: power of 3, c: square, d: 3 divisors, e: palindrome, f: Fibonacci): ");
    if (scanf(" %c", &option) != 1 || option < 'a' || option > 'f') {
        printf("Invalid option.\n");
        return 1;
    }

    if (!build_filtered_file(f_name, g_name, option)) {
        printf("Error building file G.\n");
        return 1;
    }

    printf("File F contents: ");
    if (!print_int_file(f_name)) {
        printf("Error reading file F.\n");
        return 1;
    }

    printf("File G contents: ");
    if (!print_int_file(g_name)) {
        printf("Error reading file G.\n");
        return 1;
    }

    return 0;
}
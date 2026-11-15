#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    double x1;
    double y1;
    double x2;
    double y2;
} Rectangle;

double rectangle_area(Rectangle r) {
    return fabs(r.x2 - r.x1) * fabs(r.y1 - r.y2);
}

int input_rectangle(Rectangle *r) {
    return scanf("%d %lf %lf %lf %lf", &r->id, &r->x1, &r->y1, &r->x2, &r->y2) == 5;
}

int create_rectangles_file(const char *filename, int count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        Rectangle r;
        printf("Rectangle %d (format: id x1 y1 x2 y2, e.g. 101 0.0 5.0 4.0 1.0): ", i + 1);
        if (!input_rectangle(&r)) {
            fclose(file);
            return 0;
        }
        if (fwrite(&r, sizeof(Rectangle), 1, file) != 1) {
            fclose(file);
            return 0;
        }
    }
    return fclose(file) == 0;
}

int print_rectangles_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    Rectangle r;
    int ord = 1;
    while (fread(&r, sizeof(Rectangle), 1, file) == 1) {
        printf("  #%d -> ID: %d, Top-Left: (%g, %g), Bottom-Right: (%g, %g), Area: %g\n",
               ord, r.id, r.x1, r.y1, r.x2, r.y2, rectangle_area(r));
        ord++;
    }
    if (ord == 1) {
        printf("  (empty)\n");
    }
    int has_error = ferror(file);
    fclose(file);
    return !has_error;
}

int find_max_area_rectangle(const char *filename, int *best_id, double *max_area) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    Rectangle r;
    int found = 0;
    while (fread(&r, sizeof(Rectangle), 1, file) == 1) {
        double area = rectangle_area(r);
        if (!found || area > *max_area) {
            *max_area = area;
            *best_id = r.id;
            found = 1;
        }
    }
    int has_error = ferror(file);
    fclose(file);
    return found && !has_error;
}

int delete_rectangle_by_id(const char *filename, int target_id) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;
    }
    Rectangle r;
    size_t keep_count = 0;
    int removed = 0;
    while (fread(&r, sizeof(Rectangle), 1, file) == 1) {
        if (r.id == target_id) {
            removed = 1;
        } else {
            keep_count++;
        }
    }
    if (ferror(file)) {
        fclose(file);
        return -1;
    }
    if (!removed) {
        fclose(file);
        return 0;
    }

    Rectangle *kept = NULL;
    if (keep_count > 0) {
        kept = (Rectangle *)malloc(keep_count * sizeof(Rectangle));
        if (kept == NULL) {
            fclose(file);
            return -1;
        }
        rewind(file);
        size_t idx = 0;
        while (fread(&r, sizeof(Rectangle), 1, file) == 1) {
            if (r.id != target_id) {
                kept[idx++] = r;
            }
        }
        if (ferror(file)) {
            free(kept);
            fclose(file);
            return -1;
        }
    }
    fclose(file);

    file = fopen(filename, "wb");
    if (file == NULL) {
        free(kept);
        return -1;
    }
    int ok = 1;
    if (keep_count > 0) {
        if (fwrite(kept, sizeof(Rectangle), keep_count, file) != keep_count) {
            ok = 0;
        }
    }
    if (fclose(file) != 0) {
        ok = 0;
    }
    free(kept);
    return ok ? 1 : -1;
}

int replace_rectangle_by_ordinal(const char *filename, int ordinal_pos, Rectangle new_rect) {
    if (ordinal_pos < 1) {
        return 0;
    }
    FILE *file = fopen(filename, "r+b");
    if (file == NULL) {
        return -1;
    }
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return -1;
    }
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return -1;
    }
    long total_records = file_size / (long)sizeof(Rectangle);
    if (ordinal_pos > total_records) {
        fclose(file);
        return 0;
    }
    long offset = (long)(ordinal_pos - 1) * (long)sizeof(Rectangle);
    if (fseek(file, offset, SEEK_SET) != 0) {
        fclose(file);
        return -1;
    }
    int ok = fwrite(&new_rect, sizeof(Rectangle), 1, file) == 1;
    if (fclose(file) != 0) {
        ok = 0;
    }
    return ok ? 1 : -1;
}

int main(void) {
    char filename[256];
    int n;

    printf("Enter binary file name (single word, e.g. rects.bin): ");
    if (scanf("%255s", filename) != 1) {
        printf("Invalid file name.\n");
        return 1;
    }

    printf("Enter number of rectangles (positive integer, e.g. 3): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid count.\n");
        return 1;
    }

    if (!create_rectangles_file(filename, n)) {
        printf("Error creating file.\n");
        return 1;
    }

    printf("\nInitial file contents:\n");
    if (!print_rectangles_file(filename)) {
        printf("Error reading file.\n");
        return 1;
    }

    int best_id;
    double max_area;
    if (find_max_area_rectangle(filename, &best_id, &max_area)) {
        printf("\nRectangle with largest area: ID = %d, Area = %g\n", best_id, max_area);
    } else {
        printf("\nCould not determine largest area.\n");
    }

    int del_id;
    printf("\nEnter rectangle ID to delete (integer, e.g. 101): ");
    if (scanf("%d", &del_id) != 1) {
        printf("Invalid ID input.\n");
        return 1;
    }

    int del_status = delete_rectangle_by_id(filename, del_id);
    if (del_status == 1) {
        printf("File contents after deletion:\n");
        print_rectangles_file(filename);
    } else if (del_status == 0) {
        printf("Rectangle with ID %d not found.\n", del_id);
    } else {
        printf("File error during deletion.\n");
        return 1;
    }

    int ord_pos;
    Rectangle new_rect;
    printf("\nEnter 1-based ordinal position in file to replace (integer >= 1, e.g. 1): ");
    if (scanf("%d", &ord_pos) != 1) {
        printf("Invalid ordinal position.\n");
        return 1;
    }

    printf("Enter replacement rectangle (format: id x1 y1 x2 y2, e.g. 202 1.0 6.0 5.0 2.0): ");
    if (!input_rectangle(&new_rect)) {
        printf("Invalid rectangle input.\n");
        return 1;
    }

    int rep_status = replace_rectangle_by_ordinal(filename, ord_pos, new_rect);
    if (rep_status == 1) {
        printf("File contents after replacement:\n");
        print_rectangles_file(filename);
    } else if (rep_status == 0) {
        printf("Ordinal position %d is out of range.\n", ord_pos);
    } else {
        printf("File error during replacement.\n");
        return 1;
    }

    return 0;
}
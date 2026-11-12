#ifndef MOUNT_H
#define MOUNT_H

#include <stdbool.h>

#define MAX_NAME_LEN 256

typedef struct {
    char name[MAX_NAME_LEN];
    double height;
} Mount;

bool input_mount(Mount *m);
bool input_mounts(Mount *arr, int n);
void print_mount(const Mount *m);
void print_mounts(const Mount *arr, int n);
const char *find_highest_peak(const Mount *arr, int n);
void print_peak_height(const Mount *arr, int n, const char *target_name);

#endif
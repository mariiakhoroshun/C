#include <stdio.h>
#include <math.h>


double calc_arithmetic_mean(double sum, int count) {
    return sum / count;
}

double calc_geometric_mean(double product, int count) {
    if (product > 0) {
        return pow(product, 1.0 / count);
    } else if (product < 0 && count % 2 != 0) {
        return -pow(-product, 1.0 / count);
    } else {
        return NAN; 
    }
}

int main() {
    double num;
    double sum = 0.0;
    double product = 1.0;
    int count = 0;

    while (1) {
        printf("a[%d]= ", count);
        scanf("%lf", &num);
        if (num == 0.0) {
            break; 
        }
        sum += num;
        product *= num;
        count++;
    }

    if (count > 0) {
        double a_mean = calc_arithmetic_mean(sum, count);
        double g_mean = calc_geometric_mean(product, count);
        printf("\nSum of entered numbers: %lf\n", sum);
        printf("Arithmetic mean: %lf\n", a_mean);
        if (isnan(g_mean)) {
            printf("Geometric mean: does not exist (product is negative and count is even).\n");
        } else {
            printf("Geometric mean: %lf\n", g_mean);
        }
    } else {
        printf("\nYou entered 0 immediately. No data to calculate.\n");
    }
    return 0;
}
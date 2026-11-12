#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char col;
    int row;
} ChessSquare;

typedef struct {
    double x;
    double y;
} Vertex;

typedef struct {
    Vertex v1;
    Vertex v2;
} Rectangle;

typedef struct {
    int degree;
    double *coeffs;
} Polynomial;

int input_date(Date *d) {
    printf("Enter date (day month year): ");
    if (scanf("%d %d %d", &d->day, &d->month, &d->year) != 3) {
        return 0;
    }
    if (d->year < 1 || d->month < 1 || d->month > 12 || d->day < 1) {
        return 0;
    }
    int max_days = 31;
    if (d->month == 4 || d->month == 6 || d->month == 9 || d->month == 11) {
        max_days = 30;
    } else if (d->month == 2) {
        int is_leap = (d->year % 4 == 0 && d->year % 100 != 0) || (d->year % 400 == 0);
        max_days = is_leap ? 29 : 28;
    }
    if (d->day > max_days) {
        return 0;
    }
    return 1;
}

void output_date(Date d) {
    printf("Date: %02d.%02d.%04d\n", d.day, d.month, d.year);
}

int input_chess_square(ChessSquare *sq) {
    printf("Enter chess square (e.g. a5): ");
    if (scanf(" %c%d", &sq->col, &sq->row) != 2) {
        return 0;
    }
    if (sq->col >= 'A' && sq->col <= 'H') {
        sq->col = sq->col - 'A' + 'a';
    }
    if (sq->col < 'a' || sq->col > 'h' || sq->row < 1 || sq->row > 8) {
        return 0;
    }
    return 1;
}

void output_chess_square(ChessSquare sq) {
    printf("Chess square: %c%d\n", sq.col, sq.row);
}

int input_vertex(Vertex *v) {
    if (scanf("%lf %lf", &v->x, &v->y) != 2) {
        return 0;
    }
    return 1;
}

void output_vertex(Vertex v) {
    printf("(%.2f, %.2f)", v.x, v.y);
}

int input_rectangle(Rectangle *rect) {
    printf("Enter first vertex (x1 y1): ");
    if (!input_vertex(&rect->v1)) {
        return 0;
    }
    printf("Enter second vertex (x2 y2): ");
    if (!input_vertex(&rect->v2)) {
        return 0;
    }
    return 1;
}

void output_rectangle(Rectangle rect) {
    printf("Rectangle vertices: ");
    output_vertex(rect.v1);
    printf(" and ");
    output_vertex(rect.v2);
    printf("\n");
}

int input_polynomial(Polynomial *p) {
    p->coeffs = NULL;
    printf("Enter polynomial degree (n >= 0): ");
    if (scanf("%d", &p->degree) != 1 || p->degree < 0) {
        return 0;
    }
    p->coeffs = (double *)malloc((p->degree + 1) * sizeof(double));
    if (p->coeffs == NULL) {
        return 0;
    }
    printf("Enter %d coefficients (from a_0 to a_%d):\n", p->degree + 1, p->degree);
    for (int i = 0; i <= p->degree; i++) {
        printf("a_%d = ", i);
        if (scanf("%lf", &p->coeffs[i]) != 1) {
            free(p->coeffs);
            p->coeffs = NULL;
            return 0;
        }
    }
    return 1;
}

void output_polynomial(Polynomial p) {
    printf("Polynomial of degree %d: P(x) = ", p.degree);
    for (int i = 0; i <= p.degree; i++) {
        if (i == 0) {
            printf("%.2f", p.coeffs[i]);
        } else if (p.coeffs[i] >= 0) {
            printf(" + %.2f*x^%d", p.coeffs[i], i);
        } else {
            printf(" - %.2f*x^%d", -p.coeffs[i], i);
        }
    }
    printf("\n");
}

void free_polynomial(Polynomial *p) {
    free(p->coeffs);
    p->coeffs = NULL;
    p->degree = 0;
}

int main(void) {
    Date d;
    printf("--- Task 1a: Date ---\n");
    if (!input_date(&d)) {
        printf("Invalid date.\n");
        return 1;
    }
    output_date(d);

    ChessSquare sq;
    printf("\n--- Task 1b: Chess Square ---\n");
    if (!input_chess_square(&sq)) {
        printf("Invalid chess square.\n");
        return 1;
    }
    output_chess_square(sq);

    Rectangle rect;
    printf("\n--- Task 1c: Rectangle ---\n");
    if (!input_rectangle(&rect)) {
        printf("Invalid rectangle coordinates.\n");
        return 1;
    }
    output_rectangle(rect);

    Polynomial poly;
    printf("\n--- Task 1d: Polynomial ---\n");
    if (!input_polynomial(&poly)) {
        printf("Invalid polynomial input.\n");
        return 1;
    }
    output_polynomial(poly);
    free_polynomial(&poly);

    return 0;
}
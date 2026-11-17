#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include "Point.h"

std::string to_lower_str(const std::string& s) {
    std::string res = s;
    for (std::size_t i = 0; i < res.size(); i++) {
        res[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(res[i])));
    }
    return res;
}

void add_vertex(Point**& vertices, int& size, int& capacity, double x, double y) {
    if (size == capacity) {
        int new_capacity = (capacity == 0) ? 4 : capacity * 2;
        Point** new_vertices = new Point*[new_capacity];
        for (int i = 0; i < size; i++) {
            new_vertices[i] = vertices[i];
        }
        delete[] vertices;
        vertices = new_vertices;
        capacity = new_capacity;
    }
    vertices[size] = new Point(x, y);
    size++;
}

double compute_polygon_perimeter(Point* const* vertices, int size) {
    if (size < 2) {
        return 0.0;
    }
    if (size == 2) {
        return vertices[0]->distance_to(*vertices[1]);
    }
    double perimeter = 0.0;
    for (int i = 0; i < size; i++) {
        int next_idx = (i + 1) % size;
        perimeter += vertices[i]->distance_to(*vertices[next_idx]);
    }
    return perimeter;
}

void clear_polygon(Point**& vertices, int& size, int& capacity) {
    for (int i = 0; i < size; i++) {
        delete vertices[i];
    }
    delete[] vertices;
    vertices = nullptr;
    size = 0;
    capacity = 0;
}

void test_point() {
    bool ok = (Point::counter() == 0);
    {
        Point p1;
        if (Point::counter() != 1) ok = false;

        Point p2(3.0, 4.0);
        if (Point::counter() != 2) ok = false;

        Point p3 = p2;
        if (Point::counter() != 3) ok = false;

        if (std::fabs(p1.distance_to(p2) - 5.0) >= 1e-9) ok = false;

        Point** poly = nullptr;
        int sz = 0;
        int cap = 0;
        add_vertex(poly, sz, cap, 0.0, 0.0);
        add_vertex(poly, sz, cap, 3.0, 0.0);
        add_vertex(poly, sz, cap, 3.0, 4.0);
        if (Point::counter() != 6) ok = false;
        if (std::fabs(compute_polygon_perimeter(poly, sz) - 12.0) >= 1e-9) ok = false;
        clear_polygon(poly, sz, cap);
        if (Point::counter() != 3) ok = false;
    }
    if (Point::counter() != 0) ok = false;
    std::cout << (ok ? "[TESTS PASSED]\n\n" : "[TESTS FAILED]\n\n");
}

int main() {
    test_point();

    Point** vertices = nullptr;
    int size = 0;
    int capacity = 0;

    while (true) {
        std::string answer;
        std::cout << "Enter vertex? (yes/no): ";
        if (!(std::cin >> answer)) {
            std::cout << "Input terminated.\n";
            break;
        }
        std::string low = to_lower_str(answer);
        if (low == "no" || low == "n") {
            break;
        }
        if (low != "yes" && low != "y") {
            std::cout << "Please answer 'yes' or 'no'.\n";
            continue;
        }

        double x = 0.0;
        double y = 0.0;
        std::cout << "Enter vertex coordinates (x y, e.g. 0 0 or 2.5 -1.5): ";
        if (!(std::cin >> x >> y)) {
            std::cout << "Invalid coordinates.\n";
            clear_polygon(vertices, size, capacity);
            return 1;
        }
        add_vertex(vertices, size, capacity, x, y);
    }

    int vertex_count = Point::counter();
    double perimeter = compute_polygon_perimeter(vertices, size);

    std::cout << "\nNumber of vertices in polygon: " << vertex_count << "\n";
    if (vertex_count < 3) {
        std::cout << "Note: fewer than 3 vertices do not form a closed polygon.\n";
    }
    std::cout << "Polygon perimeter: " << perimeter << "\n";

    clear_polygon(vertices, size, capacity);
    return 0;
}
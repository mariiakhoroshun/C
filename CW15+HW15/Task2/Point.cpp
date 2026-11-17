#include "Point.h"
#include <cmath>

int Point::count = 0;

Point::Point() : x(0.0), y(0.0) {
    count++;
}

Point::Point(double x_val, double y_val) : x(x_val), y(y_val) {
    count++;
}

Point::Point(const Point& other) : x(other.x), y(other.y) {
    count++;
}

Point::~Point() {
    count--;
}

double Point::get_x() const {
    return x;
}

double Point::get_y() const {
    return y;
}

void Point::set_x(double x_val) {
    x = x_val;
}

void Point::set_y(double y_val) {
    y = y_val;
}

int Point::counter() {
    return count;
}

double Point::distance_to(const Point& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Point::input() {
    double x_val = 0.0;
    double y_val = 0.0;
    if (!(std::cin >> x_val >> y_val)) {
        return false;
    }
    x = x_val;
    y = y_val;
    return true;
}

void Point::print() const {
    std::cout << "(" << x << ", " << y << ")";
}

bool Point::operator==(const Point& other) const {
    return std::fabs(x - other.x) < 1e-9 && std::fabs(y - other.y) < 1e-9;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Point& p) {
    if (!p.input()) {
        in.setstate(std::ios::failbit);
    }
    return in;
}
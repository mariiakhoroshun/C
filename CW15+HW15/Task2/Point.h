#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
private:
    double x;
    double y;
    static int count;

public:
    Point();
    Point(double x_val, double y_val);
    Point(const Point& other);
    ~Point();

    double get_x() const;
    double get_y() const;
    void set_x(double x_val);
    void set_y(double y_val);

    static int counter();

    double distance_to(const Point& other) const;

    bool input();
    void print() const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Point& p);
    friend std::istream& operator>>(std::istream& in, Point& p);
};

#endif
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Number {
public:
    virtual double magnitude() const = 0;
    virtual ~Number(){};
};

class Complex : public Number {
private:
    double real;
    double imaginary;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imaginary(i) {}
    double magnitude() const override {
        return std::hypot(real, imaginary);
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    bool operator==(const Complex& other) const {
        const double eps = 1e-9;
        return std::fabs(real - other.real) <= eps &&
               std::fabs(imaginary - other.imaginary) <= eps;
    }

    friend std::ostream& operator<<(std::ostream& out, const Complex& c) {
        out << c.real << (c.imaginary >= 0 ? " + " : " - ")
            << std::fabs(c.imaginary) << "i";
        return out;
    }
};

int main() {
    std::vector<std::unique_ptr<Number>> nums;
    double r, im;

    while (nums.size() < 50 && (std::cin >> r >> im)) {
        nums.push_back(std::make_unique<Complex>(r, im));
    }

    if (nums.empty()) {
        return 0;
    }

    double max_mag = nums[0]->magnitude();
    for (size_t i = 1; i < nums.size(); ++i) {
        double m = nums[i]->magnitude();
        if (m > max_mag) {
            max_mag = m;
        }
    }

    std::cout << "Max magnitude: " << max_mag << '\n';

    const auto& first = static_cast<const Complex&>(*nums[0]);
    if (nums.size() == 1) {
        std::cout << "Sum: " << first << '\n';
    } else {
        const auto& second = static_cast<const Complex&>(*nums[1]);
        std::cout << "Sum: " << (first + second) << '\n';
    }

    return 0;
}
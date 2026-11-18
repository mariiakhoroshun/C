#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace task10 {

template <typename T = double>
class Function {
public:
    enum Kind {
        POWER,
        COSINE,
        SQRT,
        LOGARITHM,
        CUSTOM
    };

private:
    Kind kind;
    T coeff;
    T power;
    T left_bound;
    T right_bound;
    T (*custom_func)(T);

    void validate_interval(T a, T b) const {
        if (a > b) {
            throw std::invalid_argument("Left bound cannot be greater than right bound");
        }
    }

public:
    Function()
        : kind(POWER), coeff(1), power(1), left_bound(0), right_bound(1), custom_func(nullptr) {}

    Function(Kind func_kind, T a, T b, T exponent = 1, T multiplier = 1)
        : kind(func_kind), coeff(multiplier), power(exponent),
          left_bound(a), right_bound(b), custom_func(nullptr) {
        validate_interval(a, b);
    }

    Function(T (*func_ptr)(T), T a, T b)
        : kind(CUSTOM), coeff(1), power(1),
          left_bound(a), right_bound(b), custom_func(func_ptr) {
        if (func_ptr == nullptr) {
            throw std::invalid_argument("Function pointer cannot be null");
        }
        validate_interval(a, b);
    }

    static Function<T> create_power(T exponent, T a = 0, T b = 1, T multiplier = 1) {
        return Function<T>(POWER, a, b, exponent, multiplier);
    }

    static Function<T> create_cos(T a = 0, T b = 1) {
        return Function<T>(COSINE, a, b);
    }

    static Function<T> create_sqrt(T a = 0, T b = 1) {
        return Function<T>(SQRT, a, b);
    }

    static Function<T> create_log(T a = 1, T b = 2) {
        return Function<T>(LOGARITHM, a, b);
    }

    void set_interval(T a, T b) {
        validate_interval(a, b);
        left_bound = a;
        right_bound = b;
    }

    T get_left() const {
        return left_bound;
    }

    T get_right() const {
        return right_bound;
    }

    T evaluate(T x) const {
        switch (kind) {
            case POWER:
                if (x == static_cast<T>(0) && power < static_cast<T>(0)) {
                    throw std::domain_error("Division by zero for negative power");
                }
                if (x < static_cast<T>(0) && std::floor(power) != power) {
                    throw std::domain_error("Fractional power is undefined for negative numbers");
                }
                return coeff * static_cast<T>(std::pow(x, power));
            case COSINE:
                return static_cast<T>(std::cos(x));
            case SQRT:
                if (x < static_cast<T>(0)) {
                    throw std::domain_error("Square root is undefined for negative numbers");
                }
                return static_cast<T>(std::sqrt(x));
            case LOGARITHM:
                if (x <= static_cast<T>(0)) {
                    throw std::domain_error("Logarithm is undefined for non-positive numbers");
                }
                return static_cast<T>(std::log(x));
            case CUSTOM:
                if (custom_func == nullptr) {
                    throw std::runtime_error("Custom function is not set");
                }
                return custom_func(x);
        }
        return static_cast<T>(0);
    }

    T operator()(T x) const {
        return evaluate(x);
    }

    T left_rectangles(int n) const {
        if (n <= 0) {
            throw std::invalid_argument("Number of subintervals must be positive");
        }
        if (left_bound == right_bound) {
            return static_cast<T>(0);
        }
        T h = (right_bound - left_bound) / static_cast<T>(n);
        T sum = static_cast<T>(0);
        for (int i = 0; i < n; ++i) {
            T x = left_bound + static_cast<T>(i) * h;
            sum += evaluate(x);
        }
        return sum * h;
    }

    T right_rectangles(int n) const {
        if (n <= 0) {
            throw std::invalid_argument("Number of subintervals must be positive");
        }
        if (left_bound == right_bound) {
            return static_cast<T>(0);
        }
        T h = (right_bound - left_bound) / static_cast<T>(n);
        T sum = static_cast<T>(0);
        for (int i = 1; i <= n; ++i) {
            T x = left_bound + static_cast<T>(i) * h;
            sum += evaluate(x);
        }
        return sum * h;
    }

    T midpoint_rectangles(int n) const {
        if (n <= 0) {
            throw std::invalid_argument("Number of subintervals must be positive");
        }
        if (left_bound == right_bound) {
            return static_cast<T>(0);
        }
        T h = (right_bound - left_bound) / static_cast<T>(n);
        T sum = static_cast<T>(0);
        for (int i = 0; i < n; ++i) {
            T x = left_bound + (static_cast<T>(i) + static_cast<T>(0.5)) * h;
            sum += evaluate(x);
        }
        return sum * h;
    }

    T trapezoidal(int n) const {
        if (n <= 0) {
            throw std::invalid_argument("Number of subintervals must be positive");
        }
        if (left_bound == right_bound) {
            return static_cast<T>(0);
        }
        T h = (right_bound - left_bound) / static_cast<T>(n);
        T sum = (evaluate(left_bound) + evaluate(right_bound)) / static_cast<T>(2);
        for (int i = 1; i < n; ++i) {
            T x = left_bound + static_cast<T>(i) * h;
            sum += evaluate(x);
        }
        return sum * h;
    }

    T simpson(int n) const {
        if (n < 2 || n % 2 != 0) {
            throw std::invalid_argument("Number of subintervals for Simpson rule must be even and >= 2");
        }
        if (left_bound == right_bound) {
            return static_cast<T>(0);
        }
        T h = (right_bound - left_bound) / static_cast<T>(n);
        T sum = evaluate(left_bound) + evaluate(right_bound);
        for (int i = 1; i < n; ++i) {
            T x = left_bound + static_cast<T>(i) * h;
            if (i % 2 == 1) {
                sum += static_cast<T>(4) * evaluate(x);
            } else {
                sum += static_cast<T>(2) * evaluate(x);
            }
        }
        return sum * (h / static_cast<T>(3));
    }

    void sample(T start, T end, int samples_count, std::ostream& out = std::cout) const {
        validate_interval(start, end);
        if (samples_count <= 0) {
            throw std::invalid_argument("Number of samples must be positive");
        }

        std::pair<T, T>* pairs = new std::pair<T, T>[samples_count];
        try {
            if (samples_count == 1) {
                pairs[0] = std::make_pair(start, evaluate(start));
            } else {
                T step = (end - start) / static_cast<T>(samples_count - 1);
                for (int i = 0; i < samples_count; ++i) {
                    T x = (i == samples_count - 1) ? end : (start + static_cast<T>(i) * step);
                    pairs[i] = std::make_pair(x, evaluate(x));
                }
            }

            out << std::fixed << std::setprecision(6);
            out << "+------------------+------------------+" << std::endl;
            out << "|        x         |       f(x)       |" << std::endl;
            out << "+------------------+------------------+" << std::endl;
            for (int i = 0; i < samples_count; ++i) {
                out << "| " << std::setw(16) << pairs[i].first
                    << " | " << std::setw(16) << pairs[i].second << " |" << std::endl;
            }
            out << "+------------------+------------------+" << std::endl;
        } catch (...) {
            delete[] pairs;
            throw;
        }

        delete[] pairs;
    }

    void sample(int samples_count, std::ostream& out = std::cout) const {
        sample(left_bound, right_bound, samples_count, out);
    }
};

}

#endif
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>

namespace task5 {

template <typename T>
class Array {
private:
    int n;
    T* data;

    void copy_from(const Array& other) {
        if (other.n <= 0 || other.data == nullptr) {
            n = 0;
            data = nullptr;
            return;
        }
        n = other.n;
        data = new T[n];
        for (int i = 0; i < n; ++i) {
            data[i] = other.data[i];
        }
    }

public:
    Array() : n(0), data(nullptr) {}

    explicit Array(int count) : n(0), data(nullptr) {
        if (count < 0) {
            throw std::invalid_argument("Array size cannot be negative");
        }
        if (count > 0) {
            n = count;
            data = new T[n]();
        }
    }

    Array(int count, const T* values) : n(0), data(nullptr) {
        if (count < 0) {
            throw std::invalid_argument("Array size cannot be negative");
        }
        if (count > 0 && values == nullptr) {
            throw std::invalid_argument("Source array pointer is null");
        }
        if (count > 0) {
            n = count;
            data = new T[n];
            for (int i = 0; i < n; ++i) {
                data[i] = values[i];
            }
        }
    }

    Array(const Array& other) : n(0), data(nullptr) {
        copy_from(other);
    }

    ~Array() {
        delete[] data;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            data = nullptr;
            n = 0;
            copy_from(other);
        }
        return *this;
    }

    int size() const {
        return n;
    }

    T& operator[](int index) {
        if (index < 0 || index >= n) {
            throw std::out_of_range("Array index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= n) {
            throw std::out_of_range("Array index out of range");
        }
        return data[index];
    }

    bool operator==(const Array& other) const {
        if (n != other.n) {
            return false;
        }
        for (int i = 0; i < n; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Array& other) const {
        return !(*this == other);
    }

    static void shell_sort(T* arr, int count) {
        if (arr == nullptr || count <= 1) {
            return;
        }
        for (int gap = count / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < count; ++i) {
                T temp = arr[i];
                int j = i;
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    }

    static void shell_sort(Array<T>& arr) {
        arr.shell_sort();
    }

    void shell_sort() {
        shell_sort(data, n);
    }

    friend std::ostream& operator<<(std::ostream& out, const Array<T>& arr) {
        out << "[";
        for (int i = 0; i < arr.n; ++i) {
            out << arr.data[i];
            if (i + 1 < arr.n) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Array<T>& arr) {
        for (int i = 0; i < arr.n; ++i) {
            if (!(in >> arr.data[i])) {
                return in;
            }
        }
        return in;
    }
};

}

#endif
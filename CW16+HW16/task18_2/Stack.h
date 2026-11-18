#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

namespace task2 {

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value, Node* next_node) : data(value), next(next_node) {}
    };

    Node* head;
    int count;

    void copy_from(const Stack& other) {
        if (other.head == nullptr) {
            head = nullptr;
            count = 0;
            return;
        }
        head = new Node(other.head->data, nullptr);
        Node* current_this = head;
        Node* current_other = other.head->next;
        while (current_other != nullptr) {
            current_this->next = new Node(current_other->data, nullptr);
            current_this = current_this->next;
            current_other = current_other->next;
        }
        count = other.count;
    }

public:
    Stack() : head(nullptr), count(0) {}

    Stack(const Stack& other) : head(nullptr), count(0) {
        copy_from(other);
    }

    ~Stack() {
        clear();
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    void push(const T& value) {
        head = new Node(value, head);
        ++count;
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        --count;
    }

    T& top() {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return head->data;
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return head->data;
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }
};

template <typename T>
int input_array(T*& arr, std::istream& in = std::cin) {
    Stack<T> st;
    T value = T();
    while (in >> value) {
        if (value == static_cast<T>(0)) {
            break;
        }
        st.push(value);
    }

    int n = st.size();
    if (n == 0) {
        arr = nullptr;
        return 0;
    }

    arr = new T[n];
    for (int i = n - 1; i >= 0; --i) {
        arr[i] = st.top();
        st.pop();
    }
    return n;
}

}

#endif
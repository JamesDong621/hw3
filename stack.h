#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : public std::vector<T>
{

public:
    Stack() = default; // Use the default constructor

    // Use the default destructor
    ~Stack() = default;

    // Check if the stack is empty
    bool empty() const {
        return std::vector<T>::empty();
    }

    // Get the size of the stack
    size_t size() const {
        return std::vector<T>::size();
    }

    // Push an item onto the stack
    void push(const T& item) {
        std::vector<T>::push_back(item);
    }

    // Pop an item off the stack
    void pop() {
        if (this->empty()) {
            throw std::underflow_error("stack is empty.");
        }
        std::vector<T>::pop_back();
    }

    // Get the item at the top of the stack
    const T& top() const {
        if (this->empty()) {
            throw std::underflow_error("stack is empty.");
        }
        return std::vector<T>::back();
    }
};


#endif
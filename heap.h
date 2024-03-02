#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T>>
class Heap {
public:
    Heap(int m = 2, PComparator c = PComparator()) : m_(m), comp(c) {}

    ~Heap() {}

    void push(const T& item) {
        data.push_back(item); // Add item to the end
        heapifyUp(data.size() - 1); // Restore heap property
    }

    T const & top() const {
        if (empty()) {
            throw std::underflow_error("Heap is empty");
        }
        return data.front(); // The top element is always at the front
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Heap is empty");
        }
        std::swap(data.front(), data.back()); // Move the last element to the top
        data.pop_back(); // Remove the last element
        if (!empty()) {
            heapifyDown(0); // Restore heap property
        }
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

private:
    std::vector<T> data; // Underlying container
    int m_; // ary-ness of the heap
    PComparator comp; 

    void heapifyUp(size_t idx) {
        while (idx > 0) {
            size_t parentIdx = (idx - 1) / m_;
            if (comp(data[idx], data[parentIdx])) { // Compare using the comparator
                std::swap(data[idx], data[parentIdx]);
                idx = parentIdx;
            } else {
                break;
            }
        }
    }

    void heapifyDown(size_t idx) {
        size_t childIdx = m_ * idx + 1; // First child index
        while (childIdx < data.size()) {
            // Find the smallest/largest among the node and all the node's children
            size_t minMaxIdx = idx;
            for (int i = 0; i < m_ && i + childIdx < data.size(); i++) {
                if (comp(data[childIdx + i], data[minMaxIdx])) {
                    minMaxIdx = childIdx + i;
                }
            }

            if (minMaxIdx != idx) {
                std::swap(data[idx], data[minMaxIdx]);
                idx = minMaxIdx;
                childIdx = m_ * idx + 1;
            } else {
                break;
            }
        }
    }
};

#endif

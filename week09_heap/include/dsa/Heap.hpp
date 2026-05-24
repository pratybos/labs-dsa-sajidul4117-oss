// Max-Heap (priority queue) backed by our own DynamicArray.
// Index relationships for a node at index i:
//   parent      = (i - 1) / 2
//   left  child = 2*i + 1
//   right child = 2*i + 2
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range
#include "DynamicArray.hpp"                   // reuse Week 01 DynamicArray for storage

namespace dsa {

    template <class T>
    class Heap {
    public:
        Heap() {}                             // DynamicArray default-constructs itself

        bool empty() const { return data_.size() == 0; }  // empty if no elements
        std::size_t size() const { return data_.size(); } // current element count

        // Return the maximum element. Throws if the heap is empty.
        const T& top() const {
            if (data_.size() == 0) throw std::out_of_range("top on empty heap"); // protect against empty
            return data_[0];                  // max element sits at index 0
        }

        // Insert a value. O(log n) via sift-up.
        void push(const T& value) {
            data_.push_back(value);           // append at end (last leaf)
            sift_up(data_.size() - 1);        // restore heap order upwards
        }

        // Remove the maximum element. Throws if empty. O(log n) via sift-down.
        void pop() {
            if (data_.size() == 0) throw std::out_of_range("pop on empty heap"); // protect against empty
            std::size_t last = data_.size() - 1; // index of the last element
            data_[0] = data_[last];           // move last element to the root
            data_.pop_back();                 // shrink storage by one
            if (data_.size() > 0) sift_down(0, data_.size()); // restore heap order downwards
        }

    private:
        DynamicArray<T> data_;                // heap stored as an array

        // Move the value at index i upward until the heap property holds.
        void sift_up(std::size_t i) {
            while (i > 0) {                   // root has no parent
                std::size_t parent = (i - 1) / 2; // parent index
                if (data_[parent] < data_[i]) {   // child is larger: swap with parent
                    T tmp = data_[parent];
                    data_[parent] = data_[i];
                    data_[i] = tmp;
                    i = parent;               // continue upward
                } else {
                    break;                    // heap property satisfied
                }
            }
        }

        // Move the value at index i downward inside the range [0, n) until heap property holds.
        void sift_down(std::size_t i, std::size_t n) {
            for (;;) {                        // loop until we settle
                std::size_t left  = 2 * i + 1;    // left child index
                std::size_t right = 2 * i + 2;    // right child index
                std::size_t largest = i;          // assume current is largest
                if (left  < n && data_[largest] < data_[left])  largest = left;  // left child bigger?
                if (right < n && data_[largest] < data_[right]) largest = right; // right child bigger?
                if (largest == i) break;          // heap property holds: done
                T tmp = data_[i];                 // swap with the larger child
                data_[i] = data_[largest];
                data_[largest] = tmp;
                i = largest;                      // continue downward
            }
        }
    };

} // namespace dsa

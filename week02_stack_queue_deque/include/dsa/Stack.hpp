// Stack<T> built on top of our DynamicArray. LIFO order.
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range
#include "DynamicArray.hpp"                   // we reuse DynamicArray as the storage

namespace dsa {

    template <class T>
    class Stack {
    public:
        Stack() {}                            // nothing to initialize, DynamicArray default-constructs itself

        void push(const T& value) {           // put a new value on top of the stack
            data_.push_back(value);           // append to the array (back == top)
        }

        void pop() {                          // remove top value
            if (data_.size() == 0) throw std::out_of_range("pop on empty stack"); // can't pop empty
            data_.pop_back();                 // remove last array element
        }

        T& top() {                            // access the top value
            if (data_.size() == 0) throw std::out_of_range("top on empty stack"); // no top if empty
            return data_[data_.size() - 1];   // last element is the top
        }
        const T& top() const {                // const version of top()
            if (data_.size() == 0) throw std::out_of_range("top on empty stack");
            return data_[data_.size() - 1];
        }

        bool empty() const { return data_.size() == 0; } // empty if no elements
        std::size_t size() const { return data_.size(); } // forward to array size

    private:
        DynamicArray<T> data_;                // store elements inside our own dynamic array
    };

} // namespace dsa

// Stack<T>
// --------
// My own LIFO (Last-In-First-Out) stack for the DSA course.
// It is built ON TOP of my own DynamicArray (from week01).
// "On top of" means: I do not store the data myself, I let DynamicArray
// keep the memory and I just call its push_back / pop_back.
//
// Why use DynamicArray here?
//   - push to the END of a dynamic array is O(1) amortized
//   - pop from the END is O(1)
//   - so all stack operations stay O(1) like the lab requires.

#pragma once
#include <cstddef>     // std::size_t
#include <stdexcept>   // std::out_of_range, std::logic_error
#include "DynamicArray.hpp"

namespace dsa {

    template <class T>
    class Stack {
    public:
        // I do not need a special constructor or destructor:
        // DynamicArray handles its own memory.

        // push() puts a value on TOP of the stack.
        // Top = the last element of the underlying array.
        // Complexity: O(1) amortized (DynamicArray grows by doubling).
        void push(const T& value) {
            data_.push_back(value);
        }

        // pop() removes the top value.
        // I throw if the stack is empty so the user notices the mistake.
        // Complexity: O(1).
        void pop() {
            if (data_.size() == 0) {
                throw std::out_of_range("Stack::pop - stack is empty");
            }
            data_.pop_back();
        }

        // top() returns a reference to the value that is on top.
        // I do NOT remove it — that is what pop() is for.
        // Complexity: O(1).
        T& top() {
            if (data_.size() == 0) {
                throw std::out_of_range("Stack::top - stack is empty");
            }
            return data_[data_.size() - 1];
        }

        const T& top() const {
            if (data_.size() == 0) {
                throw std::out_of_range("Stack::top - stack is empty");
            }
            return data_[data_.size() - 1];
        }

        // empty() — true when there is nothing on the stack.
        bool empty() const {
            return data_.size() == 0;
        }

        // size() — how many items are on the stack right now.
        std::size_t size() const {
            return data_.size();
        }

    private:
        // The actual storage. I delegate all the hard work to DynamicArray.
        DynamicArray<T> data_;
    };

} // namespace dsa

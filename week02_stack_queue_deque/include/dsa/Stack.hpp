<<<<<<< HEAD
// Stack<T> built on top of our DynamicArray. LIFO order.
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range
#include "DynamicArray.hpp"                   // we reuse DynamicArray as the storage
=======
//
// Created by marius on 1/26/26.
//

#pragma once
#include <cstddef>
>>>>>>> 1a8add819ac79b3efba7aa41f9c3cf5b73f204e7

namespace dsa {

    template <class T>
    class Stack {
    public:
<<<<<<< HEAD
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
=======
        Stack();

        void push(const T& value);
        void pop();
        T& top();
        const T& top() const;

        bool empty() const;
        std::size_t size() const;

    private:
        // student decides representation
    };

}
>>>>>>> 1a8add819ac79b3efba7aa41f9c3cf5b73f204e7

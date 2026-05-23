// Same DynamicArray copied from Week 01 so Stack can use it.
#pragma once                                  // include guard
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range

namespace dsa {

    template <class T>
    class DynamicArray {
    public:
        DynamicArray() : data_(nullptr), size_(0), capacity_(0) {} // start empty
        ~DynamicArray() { delete[] data_; }   // free buffer when destroyed

        std::size_t size() const { return size_; }     // number of elements
        std::size_t capacity() const { return capacity_; } // buffer size

        T& operator[](std::size_t i) { return data_[i]; }              // unchecked access
        const T& operator[](std::size_t i) const { return data_[i]; }  // const version

        T& at(std::size_t i) {                // checked access
            if (i >= size_) throw std::out_of_range("at"); // bounds check
            return data_[i];
        }
        const T& at(std::size_t i) const {
            if (i >= size_) throw std::out_of_range("at"); // bounds check
            return data_[i];
        }

        void reserve(std::size_t newCap) {    // grow capacity only
            if (newCap <= capacity_) return;  // nothing to do if already big enough
            T* nd = new T[newCap];            // allocate new buffer
            for (std::size_t i = 0; i < size_; ++i) nd[i] = data_[i]; // copy elements
            delete[] data_;                   // free old buffer
            data_ = nd;                       // switch pointer
            capacity_ = newCap;               // update capacity
        }

        void push_back(const T& v) {          // add to the end
            if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2); // grow if full
            data_[size_++] = v;               // place value then bump size
        }

        void pop_back() {                     // remove from the end
            if (size_ > 0) --size_;           // just lower the logical size
        }

        void insert(std::size_t index, const T& v) { // insert at index
            if (index > size_) throw std::out_of_range("insert"); // 0..size allowed
            if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2); // grow if full
            for (std::size_t i = size_; i > index; --i) data_[i] = data_[i - 1]; // shift right
            data_[index] = v;                 // put value
            ++size_;                          // one more element
        }

        void erase(std::size_t index) {       // remove at index
            if (index >= size_) throw std::out_of_range("erase"); // 0..size-1
            for (std::size_t i = index; i + 1 < size_; ++i) data_[i] = data_[i + 1]; // shift left
            --size_;                          // one fewer element
        }

    private:
        T* data_;                             // pointer to allocated buffer
        std::size_t size_;                    // current number of elements
        std::size_t capacity_;                // allocated buffer size
    };

} // namespace dsa

<<<<<<< HEAD
// DynamicArray<T>
// A simple resizable array (like a small std::vector) built from raw memory.
// Educational implementation for Lab 1.

#pragma once                                  // include this header only once per translation unit
#include <cstddef>                            // for std::size_t type
#include <stdexcept>                          // for std::out_of_range exception

namespace dsa {                               // put all course data structures inside the dsa namespace

    template <class T>                        // template so DynamicArray can store any type T
    class DynamicArray {
    public:
        // Default constructor: create an empty array with no allocated memory
        DynamicArray()
            : data_(nullptr),                 // no buffer yet
              size_(0),                       // no elements stored
              capacity_(0) {}                 // capacity is zero

        // Destructor: free the raw memory we allocated
        ~DynamicArray() {
            delete[] data_;                   // delete[] because we allocated with new[]
        }

        // Return how many elements are currently stored
        std::size_t size() const { return size_; }

        // Return how many elements can be stored before a resize is needed
        std::size_t capacity() const { return capacity_; }

        // Unchecked element access (like std::vector::operator[])
        T& operator[](std::size_t index) { return data_[index]; }
        const T& operator[](std::size_t index) const { return data_[index]; }

        // Safe element access: throws std::out_of_range if index is invalid
        T& at(std::size_t index) {
            if (index >= size_) throw std::out_of_range("at(): index out of range"); // check bounds
            return data_[index];              // return reference to element
        }
        const T& at(std::size_t index) const {
            if (index >= size_) throw std::out_of_range("at(): index out of range"); // check bounds
            return data_[index];              // return const reference
        }

        // Grow the buffer to at least newCapacity (never shrink)
        void reserve(std::size_t newCapacity) {
            if (newCapacity <= capacity_) return; // already big enough, do nothing
            T* newData = new T[newCapacity];  // allocate a new bigger buffer
            for (std::size_t i = 0; i < size_; ++i) {
                newData[i] = data_[i];        // copy existing elements into the new buffer
            }
            delete[] data_;                   // free the old buffer
            data_ = newData;                  // point to new buffer
            capacity_ = newCapacity;          // remember the new capacity
        }

        // Add an element to the back; resize when full (capacity x 2 strategy)
        void push_back(const T& value) {
            if (size_ == capacity_) {         // buffer is full, need more space
                std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2; // double, or start at 1
                reserve(newCap);              // grow the buffer
            }
            data_[size_] = value;             // place the new value at the end
            ++size_;                          // increment count
        }

        // Remove the last element (does not shrink capacity)
        void pop_back() {
            if (size_ == 0) return;           // nothing to remove if empty
            --size_;                          // simply lower the logical size
        }

        // Insert a value at position index, shifting later elements right
        void insert(std::size_t index, const T& value) {
            if (index > size_) throw std::out_of_range("insert(): index out of range"); // index may equal size
            if (size_ == capacity_) {         // need more capacity before insert
                std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2; // grow strategy
                reserve(newCap);
            }
            for (std::size_t i = size_; i > index; --i) {
                data_[i] = data_[i - 1];      // shift element one position to the right
            }
            data_[index] = value;             // put the new value into the freed slot
            ++size_;                          // one more element
        }

        // Remove the element at position index, shifting later elements left
        void erase(std::size_t index) {
            if (index >= size_) throw std::out_of_range("erase(): index out of range"); // must be a valid element
            for (std::size_t i = index; i + 1 < size_; ++i) {
                data_[i] = data_[i + 1];      // shift element one position to the left
            }
            --size_;                          // one fewer element
        }

    private:
        T* data_;                             // pointer to raw buffer
        std::size_t size_;                    // number of elements stored
        std::size_t capacity_;                // size of the allocated buffer
=======
//
// Created by marius on 1/26/26.
//

// Supported by GCC, Clang, MSVC

// DynamicArray<T>
// ----------------
// A simple resizable array implementation.
// Implemented as a template so it can store elements of any type T.
// Used to demonstrate memory allocation, resizing, and basic container design.
// This is an educational implementation (not a replacement for std::vector).

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class DynamicArray {
    public:
        DynamicArray();
        ~DynamicArray();

        std::size_t size() const;
        std::size_t capacity() const;

        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;

        // Safe access
        T& at(std::size_t index);
        const T& at(std::size_t index) const;

        void push_back(const T& value);
        void pop_back();

        // Part B (lab / homework)
        void insert(std::size_t index, const T& value);
        void erase(std::size_t index);

        void reserve(std::size_t newCapacity);

    private:
        T* data_;
        std::size_t size_;
        std::size_t capacity_;
>>>>>>> 1a8add819ac79b3efba7aa41f9c3cf5b73f204e7
    };

} // namespace dsa

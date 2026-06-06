// DynamicArray<T>
// ----------------
// My own simple version of std::vector for the DSA course.
// It is a template so it can hold any type T (int, double, string, ...).
// I use raw memory (new[] / delete[]) like the lab requires.
//
// Idea in one sentence:
//   I keep a pointer to a block of memory (data_),
//   I remember how many items I actually have (size_),
//   and I remember how big the block is (capacity_).
//   When the block gets full, I make a bigger block and copy everything over.

#pragma once
#include <cstddef>     // for std::size_t
#include <stdexcept>   // for std::out_of_range

namespace dsa {

    template <class T>
    class DynamicArray {
    public:
        // ---- Big three: constructor, destructor ----
        DynamicArray();
        ~DynamicArray();

        // ---- Info about the array ----
        std::size_t size() const;       // how many items I currently store
        std::size_t capacity() const;   // how many items fit before I must grow

        // ---- Fast access (no checking, like std::vector::operator[]) ----
        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;

        // ---- Safe access (throws if index is bad) ----
        T& at(std::size_t index);
        const T& at(std::size_t index) const;

        // ---- Adding / removing at the end ----
        void push_back(const T& value);
        void pop_back();

        // ---- Part B: insert / erase anywhere ----
        void insert(std::size_t index, const T& value);
        void erase(std::size_t index);

        // ---- Manually grow the storage (does not shrink) ----
        void reserve(std::size_t newCapacity);

    private:
        T* data_;                 // pointer to the raw memory block
        std::size_t size_;        // number of real items in the array
        std::size_t capacity_;    // total slots available in data_
    };


    // =====================================================================
    // Implementation below.
    // Templates must have their code visible to the compiler when used,
    // so I put the definitions in this header file (not in a .cpp file).
    // =====================================================================


    // Constructor: build an empty array.
    // No memory is allocated yet — I only ask for memory when I really need it.
    template <class T>
    DynamicArray<T>::DynamicArray()
        : data_(nullptr), size_(0), capacity_(0) {
    }


    // Destructor: free the memory I allocated with new[].
    // delete[] is safe even when data_ is nullptr.
    template <class T>
    DynamicArray<T>::~DynamicArray() {
        delete[] data_;
    }


    // Return how many real elements are stored.
    template <class T>
    std::size_t DynamicArray<T>::size() const {
        return size_;
    }


    // Return how many elements fit inside the current memory block.
    template <class T>
    std::size_t DynamicArray<T>::capacity() const {
        return capacity_;
    }


    // operator[] — fast access, no bounds checking (just like std::vector).
    // The user is responsible for passing a valid index here.
    template <class T>
    T& DynamicArray<T>::operator[](std::size_t index) {
        return data_[index];
    }

    template <class T>
    const T& DynamicArray<T>::operator[](std::size_t index) const {
        return data_[index];
    }


    // at() — safe access. If the index is wrong I throw std::out_of_range.
    // I check index >= size_ (NOT capacity_) because empty slots are not real items.
    template <class T>
    T& DynamicArray<T>::at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("DynamicArray::at - index is out of range");
        }
        return data_[index];
    }

    template <class T>
    const T& DynamicArray<T>::at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("DynamicArray::at - index is out of range");
        }
        return data_[index];
    }


    // reserve() — make sure capacity is at least newCapacity.
    // Rule from the lab: this function only GROWS the capacity, it never shrinks.
    template <class T>
    void DynamicArray<T>::reserve(std::size_t newCapacity) {
        // If the new size is not bigger, I do nothing.
        if (newCapacity <= capacity_) {
            return;
        }

        // Step 1: allocate a fresh block of raw memory of the new size.
        T* newData = new T[newCapacity];

        // Step 2: copy every existing item into the new block.
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }

        // Step 3: free the old block so I don't leak memory.
        delete[] data_;

        // Step 4: now my "official" memory is the new block.
        data_ = newData;
        capacity_ = newCapacity;
    }


    // push_back() — add one element to the END of the array.
    // If there is no free slot, I grow the capacity first.
    // Growth strategy: double the capacity (or start with 1 if it was 0).
    // Doubling makes push_back run in amortized O(1) time.
    template <class T>
    void DynamicArray<T>::push_back(const T& value) {
        // If I am full, ask reserve() to grow my memory.
        if (size_ == capacity_) {
            std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(newCap);
        }

        // Put the new value at the first free slot, then increase size.
        data_[size_] = value;
        size_ = size_ + 1;
    }


    // pop_back() — remove the last element.
    // I just decrease size_. I do NOT shrink capacity (the lab says so).
    // If the array is empty, I do nothing (this is a safe choice for beginners).
    template <class T>
    void DynamicArray<T>::pop_back() {
        if (size_ == 0) {
            return;
        }
        size_ = size_ - 1;
    }


    // insert(index, value) — put value at position index, shift the rest right.
    // Allowed indices: 0 <= index <= size_  (size_ means "insert at the end").
    template <class T>
    void DynamicArray<T>::insert(std::size_t index, const T& value) {
        // Check the index is in the allowed range.
        if (index > size_) {
            throw std::out_of_range("DynamicArray::insert - index is out of range");
        }

        // Grow if I don't have a free slot to shift into.
        if (size_ == capacity_) {
            std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reserve(newCap);
        }

        // Shift every item from the back toward the position `index`.
        // I have to go from right to left, otherwise I would overwrite values.
        // Example: [10, 20, 30] insert(1, 99) -> shift 30 then 20 -> [10, _, 20, 30]
        for (std::size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }

        // Now the slot at `index` is free — put the new value there.
        data_[index] = value;
        size_ = size_ + 1;
    }


    // erase(index) — remove the element at position index, shift the rest left.
    // Allowed indices: 0 <= index < size_.
    template <class T>
    void DynamicArray<T>::erase(std::size_t index) {
        // Check the index. Note: index == size_ is NOT allowed for erase.
        if (index >= size_) {
            throw std::out_of_range("DynamicArray::erase - index is out of range");
        }

        // Shift every item after `index` one step to the left.
        // Example: [10, 20, 30, 40] erase(1) -> [10, 30, 40, 40] then size shrinks.
        for (std::size_t i = index; i + 1 < size_; ++i) {
            data_[i] = data_[i + 1];
        }

        // Drop the size by 1. Capacity stays the same.
        size_ = size_ - 1;
    }

} // namespace dsa

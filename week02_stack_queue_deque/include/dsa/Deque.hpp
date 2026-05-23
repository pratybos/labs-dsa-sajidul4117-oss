// Deque<T> using a circular buffer with push/pop on both ends.
#pragma once                                  // include guard
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range

namespace dsa {

    template <class T>
    class Deque {
    public:
        Deque()
            : data_(nullptr),                 // buffer not yet allocated
              capacity_(0),                   // buffer size
              head_(0),                       // index of front element
              size_(0) {}                     // count of stored elements

        ~Deque() { delete[] data_; }          // free buffer on destruction

        Deque(const Deque&) = delete;         // forbid copy (raw pointer inside)
        Deque& operator=(const Deque&) = delete;

        void push_back(const T& v) {          // add at the back
            if (size_ == capacity_) grow();   // make room if needed
            std::size_t tail = (head_ + size_) % capacity_; // back index by modulo
            data_[tail] = v;                  // store value at back
            ++size_;                          // size grows by one
        }

        void push_front(const T& v) {         // add at the front
            if (size_ == capacity_) grow();   // make room if needed
            head_ = (head_ + capacity_ - 1) % capacity_; // move head back by 1 (with wrap)
            data_[head_] = v;                 // store new front
            ++size_;                          // size grows by one
        }

        void pop_back() {                     // remove the back element
            if (size_ == 0) throw std::out_of_range("pop_back empty"); // cannot pop from empty
            --size_;                          // logical size shrinks; back is no longer valid
        }

        void pop_front() {                    // remove the front element
            if (size_ == 0) throw std::out_of_range("pop_front empty"); // cannot pop from empty
            head_ = (head_ + 1) % capacity_;  // move head forward (with wrap)
            --size_;                          // size shrinks
        }

        T& front() {                          // get front element
            if (size_ == 0) throw std::out_of_range("front empty"); // empty deque -> throw
            return data_[head_];              // head_ is the front index
        }

        T& back() {                           // get back element
            if (size_ == 0) throw std::out_of_range("back empty"); // empty deque -> throw
            std::size_t idx = (head_ + size_ - 1) % capacity_; // last logical index
            return data_[idx];                // return reference
        }

        bool empty() const { return size_ == 0; } // true when no elements
        std::size_t size() const { return size_; } // number of stored elements

    private:
        T* data_;                             // pointer to circular buffer
        std::size_t capacity_;                // physical buffer size
        std::size_t head_;                    // index of the front element
        std::size_t size_;                    // count of elements stored

        void grow() {                         // grow the buffer keeping logical order
            std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2; // doubling strategy
            T* nd = new T[newCap];            // allocate new larger buffer
            for (std::size_t i = 0; i < size_; ++i) {
                nd[i] = data_[(head_ + i) % capacity_]; // copy logically ordered
            }
            delete[] data_;                   // delete old buffer
            data_ = nd;                       // switch to new buffer
            capacity_ = newCap;               // update capacity
            head_ = 0;                        // elements now start at index 0
        }
    };

} // namespace dsa

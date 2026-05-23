// Queue<T> implemented using a circular buffer (FIFO).
// head_ = index of front element; size_ = number of elements stored.
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range

namespace dsa {

    template <class T>
    class Queue {
    public:
        Queue()
            : data_(nullptr),                 // buffer not allocated yet
              capacity_(0),                   // buffer size is zero
              head_(0),                       // front index
              size_(0) {}                     // no elements stored

        ~Queue() {                            // destructor frees the buffer
            delete[] data_;                   // release allocated memory
        }

        // Disallow copying (we use raw pointer; rule of 3) — keeps things simple.
        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;

        void enqueue(const T& value) {        // add a value to the back
            if (size_ == capacity_) grow();   // grow when full
            std::size_t tail = (head_ + size_) % capacity_; // compute back index using modulo
            data_[tail] = value;              // store value at back
            ++size_;                          // one more element
        }

        void dequeue() {                      // remove the front value
            if (size_ == 0) throw std::out_of_range("dequeue empty"); // cannot remove from empty queue
            head_ = (head_ + 1) % capacity_;  // move head forward (with wrap)
            --size_;                          // one fewer element
        }

        T& front() {                          // access front value
            if (size_ == 0) throw std::out_of_range("front empty"); // cannot read empty queue
            return data_[head_];              // head_ is the front index
        }
        const T& front() const {              // const version of front
            if (size_ == 0) throw std::out_of_range("front empty");
            return data_[head_];
        }

        bool empty() const { return size_ == 0; }      // empty when size is zero
        std::size_t size() const { return size_; }     // current number of elements

    private:
        T* data_;                             // pointer to circular buffer
        std::size_t capacity_;                // total slots in buffer
        std::size_t head_;                    // index of the front element
        std::size_t size_;                    // number of elements stored

        void grow() {                         // double the buffer keeping order intact
            std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2; // new capacity
            T* nd = new T[newCap];            // allocate the new buffer
            for (std::size_t i = 0; i < size_; ++i) {
                nd[i] = data_[(head_ + i) % capacity_]; // copy in logical order starting at head
            }
            delete[] data_;                   // free old buffer
            data_ = nd;                       // switch to new buffer
            capacity_ = newCap;               // remember new capacity
            head_ = 0;                        // elements now start at index 0
        }
    };

} // namespace dsa

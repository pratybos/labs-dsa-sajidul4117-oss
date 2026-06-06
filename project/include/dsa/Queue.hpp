// Queue<T>
// --------
// My own FIFO (First-In-First-Out) queue.
// The lab says I MUST use a "circular buffer" — no shifting allowed.
//
// What is a circular buffer?
//   I have a fixed block of memory (size capacity_).
//   I keep two indices: front_ (where the next item leaves) and
//   back_ (where the next item will be written).
//   When an index reaches the end of the block, it WRAPS AROUND to 0.
//   That is why I use modulo (%) when I move the indices.
//
// Picture (capacity 5):
//   [_ , _ , A , B , C]    front_=2, back_=0, size_=3
//   dequeue -> A leaves -> front_=3
//   enqueue D, E -> wraps: back goes 0,1 -> [D , E , _ , B , C]

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class Queue {
    public:
        // Build an empty queue.
        // I start with no memory; I will allocate the first time I push.
        Queue()
            : data_(nullptr), capacity_(0), size_(0), front_(0), back_(0) {
        }

        // Free the memory block.
        ~Queue() {
            delete[] data_;
        }

        // enqueue() — push to the BACK of the queue.
        // If full, I grow the buffer first.
        // Complexity: O(1) amortized.
        void enqueue(const T& value) {
            if (size_ == capacity_) {
                grow();
            }
            // Write at back_, then move back_ forward by 1, wrapping around.
            data_[back_] = value;
            back_ = (back_ + 1) % capacity_;
            size_ = size_ + 1;
        }

        // dequeue() — remove the front element.
        // Throw if the queue is empty.
        // Complexity: O(1).
        void dequeue() {
            if (size_ == 0) {
                throw std::out_of_range("Queue::dequeue - queue is empty");
            }
            // Move front_ forward by 1, wrapping around.
            // I do NOT shift any other element. That is the whole point.
            front_ = (front_ + 1) % capacity_;
            size_ = size_ - 1;
        }

        // front() — look at (but do not remove) the front element.
        T& front() {
            if (size_ == 0) {
                throw std::out_of_range("Queue::front - queue is empty");
            }
            return data_[front_];
        }

        const T& front() const {
            if (size_ == 0) {
                throw std::out_of_range("Queue::front - queue is empty");
            }
            return data_[front_];
        }

        bool empty() const { return size_ == 0; }
        std::size_t size() const { return size_; }

    private:
        T* data_;                 // raw memory block
        std::size_t capacity_;    // size of the block
        std::size_t size_;        // how many real items inside
        std::size_t front_;       // index where the next dequeue will happen
        std::size_t back_;        // index where the next enqueue will write

        // grow() — make the buffer bigger when it is full.
        // Important: when I copy the old items to the new block,
        // I copy them in LOGICAL order starting from front_.
        // After copy, the new front is 0 and new back is size_.
        void grow() {
            std::size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* newData = new T[newCap];

            // Copy items one by one from front_, walking around the ring.
            for (std::size_t i = 0; i < size_; ++i) {
                newData[i] = data_[(front_ + i) % capacity_];
            }

            delete[] data_;
            data_ = newData;
            capacity_ = newCap;
            front_ = 0;
            back_ = size_;
        }
    };

} // namespace dsa

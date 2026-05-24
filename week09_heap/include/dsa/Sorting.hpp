// Heapsort utilities for Lab 9.
// heapify_down + build_heap let us turn a raw array into a max-heap in O(n).
// heapsort then repeatedly extracts the max into the back of the array.
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t (ints are used for indices)

namespace dsa {

    // Sift the element at index i downward inside the range [0, n).
    // Treats the array as a binary heap with the index relationships:
    //   left = 2*i + 1, right = 2*i + 2.
    template <class T>
    void heapify_down(T* arr, int n, int i) {
        for (;;) {                            // loop until heap property holds at i
            int left    = 2 * i + 1;          // left child index
            int right   = 2 * i + 2;          // right child index
            int largest = i;                  // start by assuming i is the largest
            if (left  < n && arr[largest] < arr[left])  largest = left;  // is left larger?
            if (right < n && arr[largest] < arr[right]) largest = right; // is right larger?
            if (largest == i) return;         // already a heap at this node
            T tmp = arr[i];                   // swap arr[i] with the larger child
            arr[i] = arr[largest];
            arr[largest] = tmp;
            i = largest;                      // continue down from the swapped position
        }
    }

    // Build a max-heap from an unordered array, bottom-up. Runs in O(n).
    template <class T>
    void build_heap(T* arr, int n) {
        for (int i = n / 2 - 1; i >= 0; --i) { // last non-leaf node down to root
            heapify_down(arr, n, i);          // sift each one into place
        }
    }

    // Heapsort. Builds a max-heap then repeatedly moves the max to the back.
    // Complexity: O(n log n) in the worst case.
    template <class T>
    void heapsort(T* arr, int n) {
        if (n < 2) return;                    // already sorted (0 or 1 element)
        build_heap(arr, n);                   // first, build the max-heap
        for (int end = n - 1; end > 0; --end) { // extract max repeatedly
            T tmp = arr[0];                   // swap current max (root) with last
            arr[0]   = arr[end];
            arr[end] = tmp;
            heapify_down(arr, end, 0);        // restore heap property over [0..end)
        }
    }

} // namespace dsa

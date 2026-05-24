// Quicksort for Lab 8. In-place, recursive, using the Lomuto partition scheme.
// Pivot strategy: last element (Lomuto). Average O(n log n), worst O(n^2).
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t (not strictly needed; ints used as indices)

namespace dsa {

    // Lomuto partition.
    // Picks arr[high] as the pivot and arranges:
    //   arr[low..i]   <= pivot
    //   arr[i+1..high-1] > pivot
    //   arr[high] (pivot) is moved to its final index, which is returned.
    template <class T>
    int partition(T* arr, int low, int high) {
        T pivot = arr[high];                  // pivot value is the last element
        int i = low - 1;                      // index of the last element <= pivot
        for (int j = low; j < high; ++j) {    // scan low..high-1
            if (arr[j] <= pivot) {            // element belongs to the left side
                ++i;                          // grow the "<= pivot" region
                T tmp = arr[i];               // swap arr[i] and arr[j]
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        T tmp = arr[i + 1];                   // place pivot just after the "<= pivot" region
        arr[i + 1] = arr[high];
        arr[high]  = tmp;
        return i + 1;                         // final index of the pivot
    }

    // Recursive quicksort over arr[low..high] (inclusive on both ends).
    // Base cases: empty range (low > high) or single element (low == high).
    template <class T>
    void quicksort(T* arr, int low, int high) {
        if (low >= high) return;              // 0 or 1 element: already sorted
        int p = partition(arr, low, high);    // split around the pivot
        quicksort(arr, low, p - 1);           // sort the left side
        quicksort(arr, p + 1, high);          // sort the right side
    }

    // Convenience overload that sorts a whole array of size n.
    template <class T>
    void quicksort(T* arr, std::size_t n) {
        if (n < 2) return;                    // 0 or 1 element: already sorted
        quicksort(arr, 0, static_cast<int>(n) - 1);
    }

} // namespace dsa

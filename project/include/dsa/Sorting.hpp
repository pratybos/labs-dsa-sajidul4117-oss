// Sorting.hpp — Week 08
// ---------------------
// Quicksort using LOMUTO partition.
// Idea (divide and conquer):
//   1. Pick a pivot (I use the LAST element: arr[high]).
//   2. partition() puts every element <= pivot to the LEFT of the pivot
//      and every element > pivot to the RIGHT of it.
//      It returns the final index of the pivot.
//   3. Recursively sort the two halves around the pivot.
//
// Complexity:
//   - Average: O(n log n) — splits the array roughly in half.
//   - Worst:   O(n^2)     — if the pivot is always the smallest/largest
//                           (e.g. already sorted with last-element pivot).
// In-place: yes. Not stable.

#pragma once
#include <cstddef>

namespace dsa {

    // Lomuto partition. Returns the final index of the pivot.
    template <class T>
    int partition(T* arr, int low, int high) {
        T pivot = arr[high];
        int i = low - 1; // i = "last index where arr[i] <= pivot"
        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                // swap arr[i] and arr[j]
                T tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        // Put pivot in its correct place.
        T tmp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = tmp;
        return i + 1;
    }

    // Recursive quicksort over arr[low..high] (inclusive).
    // Base condition: if low >= high, the range has 0 or 1 elements,
    // so nothing to sort. This is what stops the recursion.
    template <class T>
    void quicksort(T* arr, int low, int high) {
        if (low >= high) return;
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }

    // Convenience overload: sort arr[0..n-1].
    template <class T>
    void quicksort(T* arr, std::size_t n) {
        if (n < 2) return;
        quicksort(arr, 0, static_cast<int>(n) - 1);
    }

} // namespace dsa

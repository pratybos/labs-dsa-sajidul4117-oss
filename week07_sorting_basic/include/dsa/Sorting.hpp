// Sorting algorithms for Lab 7: Bubble Sort and Shell Sort.
// Both work in-place on raw arrays and (optionally) report counts via out-params.
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t

namespace dsa {

    // Bubble Sort: repeatedly compare adjacent pairs and swap if out of order.
    // - Sorts in non-decreasing order.
    // - Uses an "early exit" flag so a sorted array runs in O(n).
    // Optional out-parameters report comparison and swap counts (pass nullptr to skip).
    template <class T>
    void bubble_sort(T* a, std::size_t n,
                     std::size_t* comparisons = nullptr,
                     std::size_t* swaps = nullptr) {
        std::size_t cmps = 0;                 // local counters (cheaper than dereferencing every iteration)
        std::size_t swps = 0;
        if (n < 2) {                          // nothing to sort
            if (comparisons) *comparisons = cmps;
            if (swaps)       *swaps = swps;
            return;
        }
        for (std::size_t i = 0; i + 1 < n; ++i) { // n-1 passes maximum
            bool swapped = false;             // track whether this pass made any swap
            for (std::size_t j = 0; j + 1 < n - i; ++j) { // last i elements are already in place
                ++cmps;                       // counting each comparison
                if (a[j + 1] < a[j]) {        // out of order: swap
                    T tmp = a[j];             // classic 3-step swap
                    a[j]  = a[j + 1];
                    a[j + 1] = tmp;
                    ++swps;                   // count the swap
                    swapped = true;           // mark that progress was made
                }
            }
            if (!swapped) break;              // array already sorted: exit early
        }
        if (comparisons) *comparisons = cmps; // write back counts if requested
        if (swaps)       *swaps = swps;
    }

    // Shell Sort: gapped insertion sort. Uses the simple gap sequence n/2, n/4, ..., 1.
    // - "Comparisons" count the inner-loop key comparisons inside each gapped insertion.
    // - "Moves/swaps" count the element shifts plus the final placement (1 per inserted element).
    template <class T>
    void shell_sort(T* a, std::size_t n,
                    std::size_t* comparisons = nullptr,
                    std::size_t* moves = nullptr) {
        std::size_t cmps = 0;                 // local counters
        std::size_t mvs  = 0;
        if (n < 2) {                          // nothing to sort
            if (comparisons) *comparisons = cmps;
            if (moves)       *moves = mvs;
            return;
        }
        for (std::size_t gap = n / 2; gap > 0; gap /= 2) { // shrinking gap
            for (std::size_t i = gap; i < n; ++i) {        // gapped insertion sort
                T temp = a[i];                // value to be placed
                std::size_t j = i;            // current candidate slot
                while (j >= gap) {            // walk backwards in steps of `gap`
                    ++cmps;                   // count the comparison
                    if (a[j - gap] > temp) {  // shift larger element right by `gap`
                        a[j] = a[j - gap];
                        ++mvs;                // count the shift
                        j -= gap;             // continue looking further left
                    } else {
                        break;                // correct position found; stop
                    }
                }
                a[j] = temp;                  // place the held value
                ++mvs;                        // count the final placement
            }
        }
        if (comparisons) *comparisons = cmps; // write back counts if requested
        if (moves)       *moves = mvs;
    }

} // namespace dsa

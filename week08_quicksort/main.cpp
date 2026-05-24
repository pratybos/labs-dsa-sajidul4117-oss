// Demo for Lab 8: quicksort on three classic cases (random / sorted / reverse).
//
// Pivot strategy: Lomuto partition with the last element as the pivot.
// Complexity (high level):
//   - Average:    O(n log n)
//   - Worst case: O(n^2)  (e.g. already-sorted input with last-element pivot)
//   - Space:      O(log n) average recursion depth.
#include <iostream>                           // for printing
#include "dsa/Sorting.hpp"                    // our sorting algorithms

// Helper: print an array on one labelled line.
static void print(const int* a, std::size_t n, const char* label) {
    std::cout << label;
    for (std::size_t i = 0; i < n; ++i) std::cout << a[i] << " ";
    std::cout << "\n";
}

int main() {
    // Case 1: random values.
    int rnd[] = {5, 2, 9, 1, 7, 3, 8, 4, 6};
    print(rnd, 9, "random before:  ");
    dsa::quicksort(rnd, 9);
    print(rnd, 9, "random after:   ");

    // Case 2: already sorted (Lomuto worst-case behaviour).
    int srt[] = {1, 2, 3, 4, 5, 6, 7, 8};
    print(srt, 8, "sorted before:  ");
    dsa::quicksort(srt, 8);
    print(srt, 8, "sorted after:   ");

    // Case 3: reverse sorted.
    int rev[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    print(rev, 9, "reverse before: ");
    dsa::quicksort(rev, 9);
    print(rev, 9, "reverse after:  ");
    return 0;
}

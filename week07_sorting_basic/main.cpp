// Demo for Lab 7: run Bubble Sort and Shell Sort on the same input and
// compare operation counts.
#include <iostream>                           // for printing
#include "dsa/Sorting.hpp"                    // our sorting algorithms

// Print an array to stdout in one line.
static void print(const int* a, std::size_t n, const char* label) {
    std::cout << label;
    for (std::size_t i = 0; i < n; ++i) std::cout << a[i] << " ";
    std::cout << "\n";
}

int main() {
    int input[] = {5, 2, 9, 1, 7, 3, 8, 4, 6}; // shared input
    constexpr std::size_t N = sizeof(input) / sizeof(input[0]);

    int a[N];                                 // working copy fo bubble sort
    for (std::size_t i = 0; i < N; ++i) a[i] = input[i];
    std::size_t bc = 0, bs = 0;               // counters for bubble sort
    dsa::bubble_sort(a, N, &bc, &bs);
    print(a, N, "bubble sorted:  ");
    std::cout << "  comparisons=" << bc << " swaps=" << bs << "\n";

    int b[N];                                 // working copy for shell. sort
    for (std::size_t i = 0; i < N; ++i) b[i] = input[i];
    std::size_t sc = 0, sm = 0;               // counters for shell sort
    dsa::shell_sort(b, N, &sc, &sm);
    print(b, N, "shell  sorted:  ");
    std::cout << "  comparisons=" << sc << " moves=" << sm << "\n";
    return 0;
}

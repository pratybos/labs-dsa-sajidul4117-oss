// Demo for Lab 9: priority queue (max-heap) and heapsort.
// Heapsort guarantees O(n log n) in the worst case because:
//  - build_heap is O(n)
//  - each of the n-1 extract-max operations is O(log n)
#include <iostream>                           // for printing
#include "dsa/Heap.hpp"                       // our max-heap
#include "dsa/Sorting.hpp"                    // our heapsort

static void print(const int* a, int n, const char* label) {
    std::cout << label;
    for (int i = 0; i < n; ++i) std::cout << a[i] << " ";
    std::cout << "\n";
}

int main() {
    // Priority queue demo: push values, peek and pop them in descending order.
    dsa::Heap<int> pq;
    int values[] = {3, 1, 7, 5, 9, 2, 6};
    for (int v : values) pq.push(v);
    std::cout << "top = " << pq.top() << "\n"; // 9
    std::cout << "popping in order: ";
    while (!pq.empty()) {
        std::cout << pq.top() << " ";          // print current max
        pq.pop();                              // remove it
    }
    std::cout << "\n";

    // Heapsort demo on a sample array.
    int a[] = {3, 1, 7, 5, 9, 2, 6};
    print(a, 7, "before heapsort: ");
    dsa::heapsort(a, 7);
    print(a, 7, "after  heapsort: ");
    return 0;
}

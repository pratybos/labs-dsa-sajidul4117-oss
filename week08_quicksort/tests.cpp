#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/Sorting.hpp"
#include <cstddef>

// Helper: check the array is non-decreasing.
template <class T>
static bool is_sorted(const T* a, std::size_t n) {
    for (std::size_t i = 1; i < n; ++i) if (a[i] < a[i - 1]) return false;
    return true;
}

TEST_CASE("partition places pivot correctly and splits the array") {
    int a[] = {3, 8, 2, 5, 1, 4, 7, 6};       // pivot will be the last (6)
    int n = 8;
    int p = dsa::partition(a, 0, n - 1);
    CHECK(a[p] == 6);                         // pivot landed at returned index
    for (int i = 0; i < p; ++i)   CHECK(a[i] <= 6); // left side <= pivot
    for (int i = p + 1; i < n; ++i) CHECK(a[i] > 6);  // right side > pivot
}

TEST_CASE("quicksort: empty and single element") {
    int empty[1];                             // never read; just need a pointer
    dsa::quicksort<int>(empty, 0);            // must not crash
    int one[] = {42};
    dsa::quicksort(one, 1);
    CHECK(one[0] == 42);
}

TEST_CASE("quicksort: random array") {
    int a[] = {5, 2, 9, 1, 7, 3, 8, 4, 6};
    dsa::quicksort(a, 9);
    CHECK(is_sorted(a, 9));
}

TEST_CASE("quicksort: already sorted array (Lomuto worst case)") {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    dsa::quicksort(a, 8);
    CHECK(is_sorted(a, 8));
}

TEST_CASE("quicksort: reverse sorted array") {
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    dsa::quicksort(a, 9);
    CHECK(is_sorted(a, 9));
}

TEST_CASE("quicksort: array with duplicates") {
    int a[] = {3, 1, 3, 2, 1, 2, 3, 1};
    dsa::quicksort(a, 8);
    CHECK(is_sorted(a, 8));
}

TEST_CASE("quicksort: negative numbers") {
    int a[] = {3, -1, 4, -5, 0, -2, 9};
    dsa::quicksort(a, 7);
    CHECK(is_sorted(a, 7));
    CHECK(a[0] == -5);
    CHECK(a[6] == 9);
}

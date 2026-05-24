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

TEST_CASE("bubble_sort handles empty and single-element arrays") {
    int empty[1];                             // not used; just to have a pointer
    dsa::bubble_sort<int>(empty, 0);          // must not crash.
    int one[] = {42};
    dsa::bubble_sort(one, 1);
    CHECK(one[0] == 42);
}

TEST_CASE("bubble_sort sorts random, sorted, and reverse arrays") {
    int random[]  = {5, 2, 9, 1, 7, 3, 8, 4, 6};
    int sorted[]  = {1, 2, 3, 4, 5};
    int reverse[] = {9, 7, 5, 3, 1};

    dsa::bubble_sort(random,  9);
    dsa::bubble_sort(sorted,  5);
    dsa::bubble_sort(reverse, 5);

    CHECK(is_sorted(random,  9));
    CHECK(is_sorted(sorted,  5));
    CHECK(is_sorted(reverse, 5));
}

TEST_CASE("bubble_sort early-exits on an already-sorted array") {
    int a[] = {1, 2, 3, 4, 5};
    std::size_t cmps = 0, swps = 0;
    dsa::bubble_sort(a, 5, &cmps, &swps);
    CHECK(is_sorted(a, 5));
    CHECK(swps == 0);                         // no swaps needed
    CHECK(cmps == 4);                         // one full pass of n-1 comparisons, then exit
}

TEST_CASE("shell_sort handles empty and single-element arrays") {
    int empty[1];
    dsa::shell_sort<int>(empty, 0);
    int one[] = {42};
    dsa::shell_sort(one, 1);
    CHECK(one[0] == 42);
}

TEST_CASE("shell_sort sorts random, sorted, reverse, and duplicates") {
    int random[]     = {5, 2, 9, 1, 7, 3, 8, 4, 6};
    int sorted[]     = {1, 2, 3, 4, 5};
    int reverse[]    = {9, 7, 5, 3, 1};
    int duplicates[] = {3, 1, 3, 2, 1, 2, 3};

    dsa::shell_sort(random,     9);
    dsa::shell_sort(sorted,     5);
    dsa::shell_sort(reverse,    5);
    dsa::shell_sort(duplicates, 7);

    CHECK(is_sorted(random,     9));
    CHECK(is_sorted(sorted,     5));
    CHECK(is_sorted(reverse,    5));
    CHECK(is_sorted(duplicates, 7));
}

TEST_CASE("shell_sort counts comparisons and moves") {
    int a[] = {5, 2, 9, 1, 7};
    std::size_t cmps = 0, mvs = 0;
    dsa::shell_sort(a, 5, &cmps, &mvs);
    CHECK(is_sorted(a, 5));
    CHECK(cmps > 0);                          // some comparisons were made
    CHECK(mvs  > 0);                          // some placements/shifts happened
}

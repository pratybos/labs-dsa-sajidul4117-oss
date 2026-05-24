#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/Heap.hpp"
#include "dsa/Sorting.hpp"
#include <stdexcept>

template <class T>
static bool is_sorted(const T* a, int n) {
    for (int i = 1; i < n; ++i) if (a[i] < a[i - 1]) return false;
    return true;
}

TEST_CASE("empty heap: top/pop throw, size 0") {
    dsa::Heap<int> h;
    CHECK(h.empty());
    CHECK(h.size() == 0);
    CHECK_THROWS_AS(h.top(), std::out_of_range);
    CHECK_THROWS_AS(h.pop(), std::out_of_range);
}

TEST_CASE("heap push/top/pop produce descending order") {
    dsa::Heap<int> h;
    int vs[] = {3, 1, 7, 5, 9, 2, 6};
    for (int v : vs) h.push(v);
    CHECK(h.size() == 7);
    CHECK(h.top() == 9);
    int prev = 1000000;
    while (!h.empty()) {
        int cur = h.top();
        h.pop();
        CHECK(cur <= prev);                   // monotonically non-increasing
        prev = cur;
    }
}

TEST_CASE("heap handles duplicates") {
    dsa::Heap<int> h;
    int vs[] = {5, 1, 5, 1, 5};
    for (int v : vs) h.push(v);
    CHECK(h.top() == 5);
    h.pop(); CHECK(h.top() == 5);
    h.pop(); CHECK(h.top() == 5);
    h.pop(); CHECK(h.top() == 1);
    h.pop(); CHECK(h.top() == 1);
    h.pop(); CHECK(h.empty());
}

TEST_CASE("heapify_down restores heap property at a single node") {
    int a[] = {1, 9, 7, 5, 4, 6, 3};          // root 1 violates max-heap property
    dsa::heapify_down(a, 7, 0);               // sift down from root
    CHECK(a[0] == 9);                         // largest of root + children now at root
}

TEST_CASE("build_heap builds a valid max-heap (parent >= children)") {
    int a[] = {3, 1, 7, 5, 9, 2, 6};
    dsa::build_heap(a, 7);
    for (int i = 0; i < 7; ++i) {
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < 7) CHECK(a[i] >= a[l]);
        if (r < 7) CHECK(a[i] >= a[r]);
    }
}

TEST_CASE("heapsort: empty and single element") {
    int empty[1];
    dsa::heapsort<int>(empty, 0);             // must not crash
    int one[] = {42};
    dsa::heapsort(one, 1);
    CHECK(one[0] == 42);
}

TEST_CASE("heapsort: random, sorted, reverse, duplicates") {
    int random[]     = {3, 1, 7, 5, 9, 2, 6};
    int sorted[]     = {1, 2, 3, 4, 5};
    int reverse[]    = {9, 7, 5, 3, 1};
    int duplicates[] = {3, 1, 3, 2, 1, 2, 3};

    dsa::heapsort(random,     7);
    dsa::heapsort(sorted,     5);
    dsa::heapsort(reverse,    5);
    dsa::heapsort(duplicates, 7);

    CHECK(is_sorted(random,     7));
    CHECK(is_sorted(sorted,     5));
    CHECK(is_sorted(reverse,    5));
    CHECK(is_sorted(duplicates, 7));
}

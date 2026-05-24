#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/BST.hpp"
#include <stdexcept>

// Helper: build the sample tree used in many tests.
//          50
//         /  \
//       30    70
//      / \    / \
//    20  40 60  80
static void build_sample(dsa::BST<int>& t) {
    int ks[] = {50, 30, 70, 20, 40, 60, 80};
    for (int k : ks) t.insert(k);
}

TEST_CASE("empty tree") {
    dsa::BST<int> t;
    CHECK(t.empty());
    CHECK(t.size() == 0);
    CHECK(t.height() == 0);
    CHECK_FALSE(t.contains(42));
    CHECK_THROWS_AS(t.min(), std::out_of_range);
    CHECK_THROWS_AS(t.max(), std::out_of_range);
}

TEST_CASE("insert and contains; duplicates ignored") {
    dsa::BST<int> t;
    build_sample(t);
    CHECK(t.size() == 7);
    t.insert(40);                             // duplicate
    CHECK(t.size() == 7);                     // size unchanged
    CHECK(t.contains(20));
    CHECK(t.contains(80));
    CHECK_FALSE(t.contains(99));
}

TEST_CASE("min, max, height") {
    dsa::BST<int> t;
    build_sample(t);
    CHECK(t.min() == 20);
    CHECK(t.max() == 80);
    CHECK(t.height() == 3);                   // balanced: 3 levels
}

TEST_CASE("inorder produces sorted order") {
    dsa::BST<int> t;
    build_sample(t);
    int out[16];
    t.inorder(out);
    int expected[] = {20, 30, 40, 50, 60, 70, 80};
    for (int i = 0; i < 7; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("remove leaf (case 1)") {
    dsa::BST<int> t;
    build_sample(t);
    CHECK(t.remove(20));                      // 20 is a leaf
    CHECK(t.size() == 6);
    CHECK_FALSE(t.contains(20));
    int out[16];
    t.inorder(out);
    int expected[] = {30, 40, 50, 60, 70, 80};
    for (int i = 0; i < 6; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("remove node with one child (case 2)") {
    dsa::BST<int> t;
    // Build: 10 -> right 20 -> right 30 (each node has only a right child)
    t.insert(10); t.insert(20); t.insert(30);
    CHECK(t.remove(20));                      // 20 has only one child (30)
    CHECK(t.size() == 2);
    CHECK(t.contains(10));
    CHECK(t.contains(30));
    CHECK_FALSE(t.contains(20));
}

TEST_CASE("remove node with two children (case 3)") {
    dsa::BST<int> t;
    build_sample(t);
    CHECK(t.remove(50));                      // root with two children
    CHECK(t.size() == 6);
    CHECK_FALSE(t.contains(50));
    int out[16];
    t.inorder(out);                           // still sorted, just without 50
    int expected[] = {20, 30, 40, 60, 70, 80};
    for (int i = 0; i < 6; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("remove returns false for missing key") {
    dsa::BST<int> t;
    build_sample(t);
    CHECK_FALSE(t.remove(999));
    CHECK(t.size() == 7);                     // unchanged
}

TEST_CASE("remove all keys empties the tree") {
    dsa::BST<int> t;
    build_sample(t);
    int ks[] = {20, 40, 60, 80, 30, 70, 50};
    for (int k : ks) CHECK(t.remove(k));
    CHECK(t.empty());
    CHECK(t.size() == 0);
}

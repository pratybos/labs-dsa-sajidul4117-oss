#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/BinaryTree.hpp"
#include <stdexcept>

// Helper: build the tree used in most tests
//      1
//     / \
//    2   3
//   / \
//  4   5
static void build_sample(dsa::BinaryTree<int>& t) {
    t.set_root(1);
    t.add_left(1, 2);
    t.add_right(1, 3);
    t.add_left(2, 4);
    t.add_right(2, 5);
}

TEST_CASE("tree starts empty") {
    dsa::BinaryTree<int> t;
    CHECK(t.empty());
    CHECK(t.size() == 0);
    CHECK(t.height() == 0);
    CHECK_FALSE(t.contains(1));
}

TEST_CASE("set_root creates the root") {
    dsa::BinaryTree<int> t;
    t.set_root(10);
    CHECK(t.size() == 1);
    CHECK(t.height() == 1);
    CHECK(t.contains(10));
    CHECK_THROWS_AS(t.set_root(20), std::logic_error); // root already exists
}

TEST_CASE("add_left/add_right work and throw correctly") {
    dsa::BinaryTree<int> t;
    t.set_root(1);
    t.add_left(1, 2);
    t.add_right(1, 3);

    CHECK(t.size() == 3);
    CHECK_THROWS_AS(t.add_left(1, 99), std::logic_error);     // slot taken
    CHECK_THROWS_AS(t.add_right(1, 99), std::logic_error);    // slot taken
    CHECK_THROWS_AS(t.add_left(42, 5), std::out_of_range);    // parent not found
    CHECK_THROWS_AS(t.add_right(42, 5), std::out_of_range);   // parent not found
}

TEST_CASE("preorder traversal") {
    dsa::BinaryTree<int> t;
    build_sample(t);
    int out[8];
    t.preorder(out);
    int expected[] = {1, 2, 4, 5, 3};
    for (int i = 0; i < 5; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("inorder traversal") {
    dsa::BinaryTree<int> t;
    build_sample(t);
    int out[8];
    t.inorder(out);
    int expected[] = {4, 2, 5, 1, 3};
    for (int i = 0; i < 5; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("postorder traversal") {
    dsa::BinaryTree<int> t;
    build_sample(t);
    int out[8];
    t.postorder(out);
    int expected[] = {4, 5, 2, 3, 1};
    for (int i = 0; i < 5; ++i) CHECK(out[i] == expected[i]);
}

TEST_CASE("height and contains") {
    dsa::BinaryTree<int> t;
    build_sample(t);
    CHECK(t.height() == 3);
    CHECK(t.contains(1));
    CHECK(t.contains(5));
    CHECK_FALSE(t.contains(99));
}

TEST_CASE("clear empties the tree") {
    dsa::BinaryTree<int> t;
    build_sample(t);
    t.clear();
    CHECK(t.size() == 0);
    CHECK(t.empty());
    CHECK(t.height() == 0);
    CHECK_FALSE(t.contains(1));
}

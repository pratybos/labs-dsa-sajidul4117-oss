#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/DynamicArray.hpp"
#include <cstddef>
#include <stdexcept>

TEST_CASE("starts empty") {
    dsa::DynamicArray<int> a;
    CHECK(a.size() == 0);
    CHECK(a.capacity() == 0);
}

TEST_CASE("push_back stores values") {
    dsa::DynamicArray<int> a;
    a.push_back(5);
    a.push_back(8);
    a.push_back(2);

    CHECK(a.size() == 3);
    CHECK(a[0] == 5);
    CHECK(a[1] == 8);
    CHECK(a[2] == 2);
}

TEST_CASE("capacity grows but never less than size") {
    dsa::DynamicArray<int> a;

    std::size_t lastCap = a.capacity();
    for (int i = 0; i < 30; ++i) {
        a.push_back(i);
        CHECK(a.size() == static_cast<std::size_t>(i + 1));
        CHECK(a.capacity() >= a.size());
        CHECK(a.capacity() >= lastCap); // non-decreasing
        lastCap = a.capacity();
    }
}

TEST_CASE("pop_back decreases size (does not require shrinking capacity)") {
    dsa::DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    const std::size_t capBefore = a.capacity();

    a.pop_back();
    CHECK(a.size() == 2);
    CHECK(a[0] == 1);
    CHECK(a[1] == 2);

    // capacity may stay the same
    CHECK(a.capacity() == capBefore);
}

TEST_CASE("at() bounds checking") {
    dsa::DynamicArray<int> a;
    a.push_back(10);

    CHECK(a.at(0) == 10);
    CHECK_THROWS_AS(a.at(1), std::out_of_range);
    CHECK_THROWS_AS(a.at(999), std::out_of_range);
}

TEST_CASE("insert shifts elements to the right") {
    dsa::DynamicArray<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30); // [10,20,30]

    a.insert(1, 99); // [10,99,20,30]
    CHECK(a.size() == 4);
    CHECK(a[0] == 10);
    CHECK(a[1] == 99);
    CHECK(a[2] == 20);
    CHECK(a[3] == 30);
}

TEST_CASE("insert at end behaves like push_back") {
    dsa::DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);

    a.insert(2, 3); // index == size
    CHECK(a.size() == 3);
    CHECK(a[0] == 1);
    CHECK(a[1] == 2);
    CHECK(a[2] == 3);
}

TEST_CASE("erase shifts elements to the left") {
    dsa::DynamicArray<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    a.push_back(40); // [10,20,30,40]

    a.erase(1); // remove 20 -> [10,30,40]
    CHECK(a.size() == 3);
    CHECK(a[0] == 10);
    CHECK(a[1] == 30);
    CHECK(a[2] == 40);
}

TEST_CASE("erase last element is like pop_back") {
    dsa::DynamicArray<int> a;
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);

    a.erase(2); // remove last
    CHECK(a.size() == 2);
    CHECK(a[0] == 7);
    CHECK(a[1] == 8);
}

TEST_CASE("insert/erase invalid index throws") {
    dsa::DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);

    CHECK_THROWS_AS(a.insert(99, 5), std::out_of_range);
    CHECK_THROWS_AS(a.erase(99), std::out_of_range);

    // erase at index==size is invalid
    CHECK_THROWS_AS(a.erase(a.size()), std::out_of_range);
}

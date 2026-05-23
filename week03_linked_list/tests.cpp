#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/SinglyLinkedList.hpp"
#include <stdexcept>

TEST_CASE("List starts empty") {
    dsa::SinglyLinkedList<int> list;
    CHECK(list.empty());
    CHECK(list.size() == 0);
}

TEST_CASE("push_front builds correct order") {
    dsa::SinglyLinkedList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1); // 1 -> 2 -> 3

    CHECK_FALSE(list.empty());
    CHECK(list.size() == 3);
    CHECK(list.front() == 1);
    CHECK(list.back() == 3);
}

TEST_CASE("push_back builds correct order") {
    dsa::SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3); // 1 -> 2 -> 3

    CHECK(list.size() == 3);
    CHECK(list.front() == 1);
    CHECK(list.back() == 3);
}

TEST_CASE("pop_front removes from front") {
    dsa::SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front(); // removes 1
    CHECK(list.size() == 2);
    CHECK(list.front() == 2);
    CHECK(list.back() == 3);

    list.pop_front(); // removes 2
    CHECK(list.size() == 1);
    CHECK(list.front() == 3);
    CHECK(list.back() == 3);
}

TEST_CASE("pop_back removes from back") {
    dsa::SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back(); // removes 3
    CHECK(list.size() == 2);
    CHECK(list.front() == 1);
    CHECK(list.back() == 2);

    list.pop_back(); // removes 2
    CHECK(list.size() == 1);
    CHECK(list.front() == 1);
    CHECK(list.back() == 1);
}

TEST_CASE("pop on empty throws") {
    dsa::SinglyLinkedList<int> list;
    CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
    CHECK_THROWS_AS(list.pop_back(), std::out_of_range);
    CHECK_THROWS_AS(list.front(), std::out_of_range);
    CHECK_THROWS_AS(list.back(), std::out_of_range);
}

TEST_CASE("clear removes everything") {
    dsa::SinglyLinkedList<int> list;
    for (int i = 0; i < 10; ++i) list.push_back(i);

    CHECK(list.size() == 10);
    list.clear();
    CHECK(list.size() == 0);
    CHECK(list.empty());
    CHECK_THROWS_AS(list.front(), std::out_of_range);
}

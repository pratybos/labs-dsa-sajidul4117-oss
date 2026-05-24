#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/HashTable.hpp"
#include <stdexcept>

TEST_CASE("constructor rejects non-positive capacity") {
    CHECK_THROWS_AS(dsa::HashTable(0),  std::invalid_argument);
    CHECK_THROWS_AS(dsa::HashTable(-1), std::invalid_argument);
}

TEST_CASE("basic put/get/contains/size") {
    dsa::HashTable t(10);
    CHECK(t.size() == 0);
    CHECK_FALSE(t.contains(42));
    CHECK(t.get(42) == nullptr);

    CHECK(t.put(1, 100));                     // new key
    CHECK(t.put(2, 200));
    CHECK(t.size() == 2);
    CHECK(t.contains(1));
    CHECK(*t.get(1) == 100);
    CHECK(*t.get(2) == 200);
}

TEST_CASE("put on an existing key updates value and returns false") {
    dsa::HashTable t(10);
    t.put(5, 50);
    CHECK_FALSE(t.put(5, 555));               // existing key -> update
    CHECK(t.size() == 1);                     // no new entry
    CHECK(*t.get(5) == 555);                  // value updated
}

TEST_CASE("collisions resolved by separate chaining") {
    // Capacity 10 makes 1, 11, 21 all hash to bucket 1.
    dsa::HashTable t(10);
    t.put(1, 100);
    t.put(11, 110);
    t.put(21, 121);
    CHECK(t.size() == 3);
    CHECK(*t.get(1)  == 100);
    CHECK(*t.get(11) == 110);
    CHECK(*t.get(21) == 121);
}

TEST_CASE("negative keys hash to a valid bucket") {
    dsa::HashTable t(10);
    CHECK(t.put(-7, -70));
    CHECK(t.contains(-7));
    CHECK(*t.get(-7) == -70);
}

TEST_CASE("remove handles head, middle, and tail of a chain") {
    // Insert 1, 11, 21 all into the same bucket.
    // Chain order (head-insert) is: 21 -> 11 -> 1.
    dsa::HashTable t(10);
    t.put(1, 100);
    t.put(11, 110);
    t.put(21, 121);

    CHECK(t.remove(11));                      // middle of the chain
    CHECK_FALSE(t.contains(11));
    CHECK(t.contains(1));
    CHECK(t.contains(21));
    CHECK(t.size() == 2);

    CHECK(t.remove(21));                      // head of the chain
    CHECK_FALSE(t.contains(21));
    CHECK(t.contains(1));
    CHECK(t.size() == 1);

    CHECK(t.remove(1));                       // tail (and only) node
    CHECK(t.size() == 0);

    CHECK_FALSE(t.remove(1));                 // already gone
}

TEST_CASE("bucket_count is the capacity passed in") {
    dsa::HashTable t(7);
    CHECK(t.bucket_count() == 7);
}

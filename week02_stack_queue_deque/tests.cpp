#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/Stack.hpp"
#include "dsa/Queue.hpp"
#include "dsa/Deque.hpp"

#include <stdexcept>

TEST_CASE("Stack: push/top/pop basic") {
    dsa::Stack<int> s;
    CHECK(s.empty());
    CHECK(s.size() == 0);

    s.push(10);
    s.push(20);
    s.push(30);

    CHECK_FALSE(s.empty());
    CHECK(s.size() == 3);
    CHECK(s.top() == 30);

    s.pop();
    CHECK(s.size() == 2);
    CHECK(s.top() == 20);

    s.pop();
    s.pop();
    CHECK(s.empty());
    CHECK(s.size() == 0);
}

TEST_CASE("Stack: top/pop throw on empty") {
    dsa::Stack<int> s;
    CHECK_THROWS_AS(s.top(), std::out_of_range);
    CHECK_THROWS_AS(s.pop(), std::out_of_range);
}

TEST_CASE("Queue: enqueue/front/dequeue basic") {
    dsa::Queue<int> q;
    CHECK(q.empty());
    CHECK(q.size() == 0);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    CHECK_FALSE(q.empty());
    CHECK(q.size() == 3);
    CHECK(q.front() == 1);

    q.dequeue();
    CHECK(q.size() == 2);
    CHECK(q.front() == 2);

    q.dequeue();
    CHECK(q.size() == 1);
    CHECK(q.front() == 3);

    q.dequeue();
    CHECK(q.empty());
    CHECK(q.size() == 0);
}

TEST_CASE("Queue: front/dequeue throw on empty") {
    dsa::Queue<int> q;
    CHECK_THROWS_AS(q.front(), std::out_of_range);
    CHECK_THROWS_AS(q.dequeue(), std::out_of_range);
}

TEST_CASE("Queue: circular buffer wrap-around works") {
    // This test forces head/tail to wrap by doing many enqueue/dequeue operations.
    dsa::Queue<int> q;

    for (int i = 0; i < 100; ++i) {
        q.enqueue(i);
        CHECK(q.front() == i);
        q.dequeue();
        CHECK(q.empty());
    }

    // Now fill and partially drain repeatedly
    for (int round = 0; round < 5; ++round) {
        for (int i = 0; i < 20; ++i) q.enqueue(round * 100 + i);
        CHECK(q.size() == 20);
        for (int i = 0; i < 10; ++i) q.dequeue();
        CHECK(q.size() == 10);
        for (int i = 0; i < 10; ++i) q.enqueue(round * 1000 + i);
        CHECK(q.size() == 20);

        // ensure ordering remains FIFO
        int first = q.front();
        (void)first; // just to show we can read it without throwing
        while (!q.empty()) q.dequeue();
        CHECK(q.empty());
    }
}

TEST_CASE("Deque: push/pop basic from both ends") {
    dsa::Deque<int> d;
    CHECK(d.empty());
    CHECK(d.size() == 0);

    d.push_back(2);   // [2]
    d.push_front(1);  // [1,2]
    d.push_back(3);   // [1,2,3]

    CHECK_FALSE(d.empty());
    CHECK(d.size() == 3);
    CHECK(d.front() == 1);
    CHECK(d.back() == 3);

    d.pop_front();    // [2,3]
    CHECK(d.size() == 2);
    CHECK(d.front() == 2);
    CHECK(d.back() == 3);

    d.pop_back();     // [2]
    CHECK(d.size() == 1);
    CHECK(d.front() == 2);
    CHECK(d.back() == 2);

    d.pop_back();     // []
    CHECK(d.empty());
    CHECK(d.size() == 0);
}

TEST_CASE("Deque: operations throw on empty") {
    dsa::Deque<int> d;
    CHECK_THROWS_AS(d.front(), std::out_of_range);
    CHECK_THROWS_AS(d.back(), std::out_of_range);
    CHECK_THROWS_AS(d.pop_front(), std::out_of_range);
    CHECK_THROWS_AS(d.pop_back(), std::out_of_range);
}

TEST_CASE("Deque: circular wrap-around works (stress)") {
    dsa::Deque<int> d;

    // push/pop many times to force wrap
    for (int i = 0; i < 50; ++i) {
        d.push_back(i);
    }
    CHECK(d.front() == 0);
    CHECK(d.back() == 49);

    for (int i = 0; i < 25; ++i) {
        d.pop_front();
    }
    CHECK(d.front() == 25);

    for (int i = 50; i < 80; ++i) {
        d.push_back(i);
    }
    CHECK(d.back() == 79);

    // Now mix front pushes too
    for (int i = 100; i < 110; ++i) {
        d.push_front(i);
    }
    CHECK(d.front() == 109);

    // Basic integrity: size is consistent and we can pop everything
    std::size_t n = d.size();
    for (std::size_t i = 0; i < n; ++i) {
        d.pop_front();
    }
    CHECK(d.empty());
    CHECK(d.size() == 0);
}

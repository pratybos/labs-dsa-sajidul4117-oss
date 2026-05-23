<<<<<<< HEAD
// Simple demo program for Lab 2: shows Stack, Queue, and Deque.
#include <iostream>                           // for printing
#include "dsa/Stack.hpp"                      // our Stack
#include "dsa/Queue.hpp"                      // our Queue
#include "dsa/Deque.hpp"                      // our Deque

int main() {
    dsa::Stack<int> s;                        // create an empty stack
    s.push(1); s.push(2); s.push(3);          // push 3 values
    std::cout << "stack top = " << s.top() << "\n"; // expect 3

    dsa::Queue<int> q;                        // create an empty queue
    q.enqueue(1); q.enqueue(2); q.enqueue(3); // add 3 values
    std::cout << "queue front = " << q.front() << "\n"; // expect 1

    dsa::Deque<int> d;                        // create an empty deque
    d.push_back(2); d.push_front(1); d.push_back(3); // [1,2,3]
    std::cout << "deque front = " << d.front() << ", back = " << d.back() << "\n"; // 1 .. 3

    return 0;                                 // success
=======
//
// Created by marius on 1/26/26.
//
int main(int argc, char *argv[]) {

    return 0;
>>>>>>> 1a8add819ac79b3efba7aa41f9c3cf5b73f204e7
}

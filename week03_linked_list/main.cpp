// Simple demo program for Lab 3: shows SinglyLinkedList.
#include <iostream>                           // for printing
#include "dsa/SinglyLinkedList.hpp"           // our linked list

int main() {
    dsa::SinglyLinkedList<int> list;          // empty list
    list.push_back(1);                        // list: 1
    list.push_back(2);                        // list: 1 -> 2
    list.push_back(3);                        // list: 1 -> 2 -> 3
    list.push_front(0);                       // list: 0 -> 1 -> 2 -> 3

    std::cout << "size = " << list.size() << "\n"; // 4
    std::cout << "front = " << list.front() << ", back = " << list.back() << "\n"; // 0, 3

    list.reverse();                           // list: 3 -> 2 -> 1 -> 0
    std::cout << "after reverse front = " << list.front() << "\n"; // 3

    list.remove_first(2);                     // remove value 2
    std::cout << "contains 2? " << list.find(2) << "\n"; // 0 (false)
    return 0;                                 // done
}

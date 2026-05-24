// Demo for Lab 5: insert keys into a BST, show traversal, min/max, remove.
#include <iostream>                           // for printing
#include "dsa/BST.hpp"                        // our BST

int main() {
    dsa::BST<int> t;                          // empty BST
    int keys[] = {50, 30, 70, 20, 40, 60, 80, 30}; // last 30 is a duplicate
    for (int k : keys) t.insert(k);           // insert all keys

    std::cout << "size = " << t.size() << "\n";  // duplicate ignored -> 7
    std::cout << "height = " << t.height() << "\n";
    std::cout << "min = " << t.min() << "  max = " << t.max() << "\n";

    int buf[16];                              // buffer for inorder output
    t.inorder(buf);                           // sorted order
    std::cout << "inorder: ";
    for (std::size_t i = 0; i < t.size(); ++i) std::cout << buf[i] << " ";
    std::cout << "\n";

    std::cout << "contains 40? " << t.contains(40) << "\n"; // 1
    std::cout << "contains 99? " << t.contains(99) << "\n"; // 0

    std::cout << "remove 30 (one child case maybe): " << t.remove(30) << "\n";
    std::cout << "remove 50 (root, two children):  " << t.remove(50) << "\n";
    std::cout << "remove 999 (missing):            " << t.remove(999) << "\n";

    t.inorder(buf);                           // sorted order removals
    std::cout << "inorder after removes: ";
    for (std::size_t i = 0; i < t.size(); ++i) std::cout << buf[i] << " ";
    std::cout << "\n";
    return 0;
}

// Simple demo program for Lab 4: builds a small tree and prints traversals.
//      1
//     / \
//    2   3
//   / \
//  4   5
#include <iostream>                           // for printing
#include "dsa/BinaryTree.hpp"                 // our binary tree

int main() {
    dsa::BinaryTree<int> t;                   // empty binary tree
    t.set_root(1);                            // root = 1
    t.add_left(1, 2);                         // 2 is left child of 1
    t.add_right(1, 3);                        // 3 is right child of 1
    t.add_left(2, 4);                         // 4 is left child of 2
    t.add_right(2, 5);                        // 5 is right child of 2

    int buf[16];                              // buffer for traversal results
    t.preorder(buf);                          // expected: 1 2 4 5 3
    std::cout << "preorder:  ";               // label 1
    for (std::size_t i = 0; i < t.size(); ++i) std::cout << buf[i] << " "; // print each
    std::cout << "\n";

    t.inorder(buf);                           // expected: 4 2 5 1 3
    std::cout << "inorder:   ";
    for (std::size_t i = 0; i < t.size(); ++i) std::cout << buf[i] << " ";
    std::cout << "\n";

    t.postorder(buf);                         // expected: 4 5 2 3 1
    std::cout << "postorder: ";
    for (std::size_t i = 0; i < t.size(); ++i) std::cout << buf[i] << " ";
    std::cout << "\n";

    std::cout << "height = " << t.height() << "\n";       // expected 3
    std::cout << "contains 5? " << t.contains(5) << "\n"; // expected 1
    return 0;
}

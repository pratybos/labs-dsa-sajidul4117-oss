// Simple demo program for Lab 1: shows DynamicArray in action.
#include <iostream>                           // for std::cout to print output
#include "dsa/DynamicArray.hpp"               // our own DynamicArray implementation

int main() {
    dsa::DynamicArray<int> a;                 // create an empty array of ints
    for (int i = 1; i <= 5; ++i) a.push_back(i * 10); // add 10, 20, 30, 40, 50

    a.insert(2, 999);                         // insert 999 at index 2 -> 10 20 999 30 40 50
    a.erase(0);                               // erase first element -> 20 999 30 40 50

    std::cout << "size = " << a.size() << "\n"; // print size
    for (std::size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " ";             // print each element
    }
    std::cout << "\n";                        // newline at the end
    return 0;                                 // exit success
}

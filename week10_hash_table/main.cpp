// Demo for Lab 10: hash table with separate chaining (capacity = 10).
// Keys 1, 11, 21 all hash to bucket 1, so they collide and form a chain.
#include <iostream>                           // for printing
#include "dsa/HashTable.hpp"                  // our hash table

int main() {
    dsa::HashTable t(10);                     // 10 buckets so 1, 11, 21 collide

    // Insert several key/value pairs (including deliberate collisions).
    t.put(1, 100);
    t.put(11, 110);
    t.put(21, 121);
    t.put(2, 200);
    t.put(3, 300);
    t.put(-7, -70);                           // negative key -> bucket 3 (after fix-up)

    std::cout << "size = " << t.size()
              << "  buckets = " << t.bucket_count() << "\n";

    // Search and print a few values.
    int keys_to_check[] = {1, 11, 21, 2, 99, -7};
    for (int k : keys_to_check) {
        int* v = t.get(k);                    // pointer to value, or nullptr if missing
        std::cout << "get(" << k << ") = ";
        if (v) std::cout << *v << "\n";
        else   std::cout << "(missing)\n";
    }

    // Update existing key and re-print.
    bool inserted = t.put(11, 999);
    std::cout << "put(11,999) returned inserted=" << inserted
              << ", value now = " << *t.get(11) << "\n";

    // Remove a colliding key and confirm the chain still works.
    std::cout << "remove(11) = " << t.remove(11) << "\n";
    std::cout << "contains(11) = " << t.contains(11) << "\n";
    std::cout << "contains(21) = " << t.contains(21) << "\n"; // still there
    std::cout << "contains(1)  = " << t.contains(1)  << "\n"; // still there
    return 0;
}

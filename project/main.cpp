// Algorithm Playground (DSA Integrator)
// ======================================
// This is the final course project. It is ONE console program that ties
// together the data structures and algorithms I built during the labs.
//
// Everything here uses MY OWN implementations from the weekly labs
// (copied into include/dsa/). I do NOT use any STL container
// (no std::vector, std::stack, std::queue, std::map, ...).
// The only standard headers I use are <iostream> (printing/reading) and
// <stdexcept> (catching the errors my structures throw).
//
// The program is menu-driven: it shows a list of options, the user types a
// number, and the matching demo runs. After each demo it returns to the menu.
//
// Data structures used (all my own):
//   1. DynamicArray  (week01)  - resizable array, also used to read numbers
//   2. Stack         (week02)  - LIFO, used to reverse text
//   3. Queue         (week02)  - FIFO, used to simulate a waiting line
//   4. SinglyLinkedList (week03)- node list, used as a simple "name list"
//   5. BST           (week05)  - sorted set, insert/search/in-order
//   6. Graph         (week06)  - adjacency list, used by BFS and DFS
//
// Algorithms used (all my own):
//   - Quicksort (week08)       - sorting numbers
//   - BFS and DFS  (week06)    - graph traversal

#include <iostream>
#include <stdexcept>

#include "dsa/DynamicArray.hpp"
#include "dsa/Stack.hpp"
#include "dsa/Queue.hpp"
#include "dsa/SinglyLinkedList.hpp"
#include "dsa/BST.hpp"
#include "dsa/Graph.hpp"
#include "dsa/Sorting.hpp"

// -----------------------------------------------------------------------------
// Small helper: read one whole integer from the user.
// If the user types something that is not a number, std::cin goes into a
// "fail" state. I clear it and ask again so the program never gets stuck.
// -----------------------------------------------------------------------------
static int read_int(const char* prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;            // got a valid number -> done
        }
        // Bad input: clear the error flag and throw away the rest of the line.
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "  (please type a whole number)\n";
    }
}

// =============================================================================
// Option 1 - DynamicArray demo
// I push a few numbers, show size/capacity (to prove it grows by doubling),
// then read them back with at() which is the bounds-checked accessor.
// =============================================================================
static void demo_dynamic_array() {
    std::cout << "\n--- DynamicArray demo ---\n";
    dsa::DynamicArray<int> arr;

    std::cout << "Pushing 10, 20, 30, 40, 50...\n";
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.push_back(40);
    arr.push_back(50);

    std::cout << "size = " << arr.size()
              << ", capacity = " << arr.capacity() << "\n";

    std::cout << "Elements: ";
    for (std::size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr.at(i) << " ";   // at() throws if i is out of range
    }
    std::cout << "\n";

    std::cout << "insert(2, 99) -> put 99 at index 2 and shift right:\n";
    arr.insert(2, 99);
    std::cout << "Elements: ";
    for (std::size_t i = 0; i < arr.size(); ++i) std::cout << arr.at(i) << " ";
    std::cout << "\n";

    std::cout << "erase(0) -> remove the first element:\n";
    arr.erase(0);
    std::cout << "Elements: ";
    for (std::size_t i = 0; i < arr.size(); ++i) std::cout << arr.at(i) << " ";
    std::cout << "\n";
}

// =============================================================================
// Option 2 - Stack demo (LIFO)
// Real use: reverse a short text. I push every character, then pop them.
// Because a stack is Last-In-First-Out, popping gives the reverse order.
// =============================================================================
static void demo_stack() {
    std::cout << "\n--- Stack demo (reverse a word) ---\n";
    std::cout << "Type a word (no spaces): ";

    char buffer[128];
    std::cin >> buffer;               // read a single word into the buffer

    dsa::Stack<char> s;
    // Push every character onto the stack.
    for (int i = 0; buffer[i] != '\0'; ++i) {
        s.push(buffer[i]);
    }

    // Pop them back: top() reads the last pushed char, pop() removes it.
    std::cout << "Reversed: ";
    while (!s.empty()) {
        std::cout << s.top();
        s.pop();
    }
    std::cout << "\n";
}

// =============================================================================
// Option 3 - Queue demo (FIFO)
// Real use: a ticket / waiting line. People join the back, are served from
// the front. First-In-First-Out, exactly the order they arrived.
// =============================================================================
static void demo_queue() {
    std::cout << "\n--- Queue demo (waiting line) ---\n";
    dsa::Queue<int> q;

    std::cout << "Customers 1..5 join the line (enqueue)...\n";
    for (int id = 1; id <= 5; ++id) {
        q.enqueue(id);
    }

    std::cout << "Serving them in arrival order (dequeue): ";
    while (!q.empty()) {
        std::cout << "#" << q.front() << " ";   // who is first
        q.dequeue();                              // serve and remove
    }
    std::cout << "\n";
}

// =============================================================================
// Option 4 - Singly Linked List demo
// I build a small list of numbers, search for a value, reverse the list,
// and remove an element. This shows node-based storage with my own pointers.
// =============================================================================
static void demo_linked_list() {
    std::cout << "\n--- Singly Linked List demo ---\n";
    dsa::SinglyLinkedList<int> list;

    std::cout << "push_back 1, 2, 3, 4 ...\n";
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    std::cout << "size = " << list.size() << "\n";

    int target = read_int("Search for which value? ");
    std::cout << (list.find(target) ? "Found it!\n" : "Not in the list.\n");

    std::cout << "reverse() the list, then print from the front by popping:\n";
    list.reverse();
    while (!list.empty()) {
        std::cout << list.front() << " ";
        list.pop_front();
    }
    std::cout << "\n";
}

// =============================================================================
// Option 5 - Binary Search Tree demo
// Insert keys, then in-order traversal prints them SORTED (that is the magic
// of a BST). Also show contains() and min()/max().
// =============================================================================
static void demo_bst() {
    std::cout << "\n--- Binary Search Tree demo ---\n";
    dsa::BST<int> tree;

    // Insert in a scrambled order on purpose, to prove sorting comes from the tree.
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = 7;
    std::cout << "Inserting: ";
    for (int i = 0; i < n; ++i) {
        std::cout << values[i] << " ";
        tree.insert(values[i]);
    }
    std::cout << "\n";

    // in-order writes the keys in sorted order into an array I provide.
    int out[7];
    tree.inorder(out);
    std::cout << "In-order (sorted) output: ";
    for (std::size_t i = 0; i < tree.size(); ++i) std::cout << out[i] << " ";
    std::cout << "\n";

    std::cout << "min = " << tree.min() << ", max = " << tree.max()
              << ", height = " << tree.height() << "\n";

    int target = read_int("contains() which value? ");
    std::cout << (tree.contains(target) ? "Yes, it is in the tree.\n"
                                        : "No, not found.\n");
}

// =============================================================================
// Option 6 - Sort numbers (Quicksort)
// The user types how many numbers and the numbers themselves. I store them in
// a raw array, run my quicksort, and print before/after.
// I read into my own DynamicArray first so I never use std::vector.
// =============================================================================
static void demo_sort() {
    std::cout << "\n--- Quicksort demo ---\n";
    int count = read_int("How many numbers? ");
    if (count <= 0) {
        std::cout << "Nothing to sort.\n";
        return;
    }

    // Read the numbers into a raw array (quicksort works on raw arrays).
    int* a = new int[count];
    for (int i = 0; i < count; ++i) {
        a[i] = read_int("  number: ");
    }

    std::cout << "Before: ";
    for (int i = 0; i < count; ++i) std::cout << a[i] << " ";
    std::cout << "\n";

    // quicksort(arr, n) is the convenience overload from week08.
    dsa::quicksort(a, static_cast<std::size_t>(count));

    std::cout << "After:  ";
    for (int i = 0; i < count; ++i) std::cout << a[i] << " ";
    std::cout << "\n";

    delete[] a;   // every new[] needs a delete[]
}

// =============================================================================
// Helper for the graph demos: a plain function the Graph calls on each visited
// vertex. The Graph API takes a function pointer "void (*visit)(int)".
// =============================================================================
static void print_vertex(int v) {
    std::cout << v << " ";
}

// =============================================================================
// Option 7 - Traverse a graph (BFS and DFS)
// I build a small fixed graph, then run BFS and DFS from vertex 0.
// BFS uses my Queue; DFS uses recursion. Both use a visited[] array.
//
// Graph picture (undirected):
//      0 --- 1
//      |     |
//      2 --- 3 --- 4
// =============================================================================
static void demo_graph() {
    std::cout << "\n--- Graph traversal demo (BFS & DFS) ---\n";
    dsa::Graph g(5, false);   // 5 vertices, undirected
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    std::cout << "Graph edges: 0-1, 0-2, 1-3, 2-3, 3-4\n";

    std::cout << "BFS from 0 (breadth-first, uses my Queue): ";
    g.bfs(0, print_vertex);
    std::cout << "\n";

    std::cout << "DFS from 0 (depth-first, recursive):       ";
    g.dfs(0, print_vertex);
    std::cout << "\n";
}

// =============================================================================
// The menu loop. Show options, read a choice, run the demo, repeat until exit.
// =============================================================================
static void print_menu() {
    std::cout << "\n========= Algorithm Playground =========\n";
    std::cout << " 1. DynamicArray  (push/insert/erase)\n";
    std::cout << " 2. Stack         (reverse a word)\n";
    std::cout << " 3. Queue         (waiting line)\n";
    std::cout << " 4. Linked List   (find/reverse)\n";
    std::cout << " 5. BST           (sorted insert/search)\n";
    std::cout << " 6. Sort numbers  (Quicksort)\n";
    std::cout << " 7. Traverse graph(BFS & DFS)\n";
    std::cout << " 0. Exit\n";
    std::cout << "========================================\n";
}

int main() {
    std::cout << "Welcome to my Algorithm Playground!\n";
    std::cout << "Every option below uses MY OWN data structures (no STL).\n";

    bool running = true;
    while (running) {
        print_menu();
        int choice = read_int("Choose an option: ");

        // I wrap each demo in try/catch because my structures throw
        // std::out_of_range on bad use. Catching it keeps the program alive.
        try {
            switch (choice) {
                case 1: demo_dynamic_array(); break;
                case 2: demo_stack();         break;
                case 3: demo_queue();         break;
                case 4: demo_linked_list();   break;
                case 5: demo_bst();           break;
                case 6: demo_sort();          break;
                case 7: demo_graph();         break;
                case 0:
                    running = false;
                    std::cout << "Goodbye!\n";
                    break;
                default:
                    std::cout << "Unknown option, try again.\n";
                    break;
            }
        } catch (const std::exception& e) {
            // Print the error message but do not crash.
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}

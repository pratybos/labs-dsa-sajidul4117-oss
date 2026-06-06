# Algorithm Playground (DSA Integrator)

A single menu-driven C++ console application that ties together the data
structures and algorithms I implemented during the labs (weeks 01–10).
Everything uses **my own implementations** — no STL containers
(`std::vector`, `std::stack`, `std::queue`, `std::map`, …) are used anywhere.
The only standard headers used are `<iostream>` and `<stdexcept>`.

## Project description

The program shows a menu, the user types a number, and the matching demo runs.
Each option demonstrates one of my own data structures or algorithms working on
real input, then returns to the menu. Option `0` exits.

```
========= Algorithm Playground =========
 1. DynamicArray  (push/insert/erase)
 2. Stack         (reverse a word)
 3. Queue         (waiting line)
 4. Linked List   (find/reverse)
 5. BST           (sorted insert/search)
 6. Sort numbers  (Quicksort)
 7. Traverse graph(BFS & DFS)
 0. Exit
========================================
```

## Implemented data structures (5 used, all my own)

| Structure          | Source lab | Where it is used in the program |
|--------------------|-----------|----------------------------------|
| `DynamicArray<T>`  | week01    | Option 1 demo; also the storage **inside** `Stack` and `Graph` adjacency lists |
| `Stack<T>`         | week02    | Option 2 — reverse a word (LIFO) |
| `Queue<T>`         | week02    | Option 3 — waiting line (FIFO); also used **inside** BFS |
| `SinglyLinkedList<T>` | week03 | Option 4 — find / reverse a node list |
| `BST<T>`           | week05    | Option 5 — sorted insert, search, in-order, min/max/height |
| `Graph`            | week06    | Option 7 — adjacency-list graph traversed by BFS and DFS |

> This is 6 of the 5 required structures. `DynamicArray` and `Queue` are not
> just declared — they are the internal storage of `Stack`, `Graph`, and `BFS`,
> so they are actively used even beyond their own menu options.

## Implemented algorithms (2+ used, all my own)

| Algorithm   | Source lab | Where it is used |
|-------------|-----------|------------------|
| **Quicksort** (Lomuto partition) | week08 | Option 6 — sorts user-entered numbers in place |
| **BFS** (breadth-first search)   | week06 | Option 7 — graph traversal using my own `Queue` |
| **DFS** (depth-first search)     | week06 | Option 7 — graph traversal using recursion |

## Time complexity (high level)

| Operation | Complexity | Note |
|-----------|-----------|------|
| `DynamicArray::push_back` | O(1) amortized | doubles capacity when full |
| `DynamicArray::insert/erase` | O(n) | must shift elements |
| `Stack::push/pop/top` | O(1) amortized | end of a DynamicArray |
| `Queue::enqueue/dequeue/front` | O(1) amortized | circular buffer, no shifting |
| `SinglyLinkedList::push_front/back` | O(1) | tail pointer kept |
| `SinglyLinkedList::find/remove_first/reverse` | O(n) | must walk nodes |
| `BST::insert/contains/remove` | O(h) | h = height; O(log n) balanced, O(n) worst (sorted input) |
| `BST::inorder` | O(n) | visits every node once |
| **Quicksort** | O(n log n) average, **O(n²) worst** | Lomuto pivot = last element; worst case on already-sorted input |
| **BFS / DFS** | O(V + E) | each vertex and edge visited once; `visited[]` prevents cycles |

## Project structure

```
project/
  CMakeLists.txt
  main.cpp
  README.md
  include/
    dsa/
      DynamicArray.hpp      (week01)
      Stack.hpp             (week02)
      Queue.hpp             (week02)
      SinglyLinkedList.hpp  (week03)
      BST.hpp               (week05)
      Graph.hpp             (week06)
      Sorting.hpp           (week08, quicksort)
```

## Build and run

From inside the `project/` folder:

```bash
cmake -S . -B build
cmake --build build
```

Run the program:

```bash
./build/playground          # Linux / macOS
build\playground.exe        # Windows
```

Then type a menu number and follow the prompts. Choose `0` to exit.

## Notes for the defense

- **No STL containers** anywhere — every container is one of my lab headers.
- Each menu demo is wrapped in `try/catch`, because my structures throw
  `std::out_of_range` on misuse (e.g. popping an empty stack). The program
  prints the error and stays alive instead of crashing.
- Input reading uses a small `read_int` helper that rejects non-numbers so the
  menu never gets stuck on bad input.

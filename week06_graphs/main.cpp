// Demo for Lab 6: build a small undirected graph and run BFS + DFS
#include <iostream>                           // for printing
#include "dsa/Graph.hpp"                      // our Graph

// Free function used as a visitor callback (matches `void (*)(int)` signature).
static void print_int(int x) {
    std::cout << x << " ";
}

int main() {
    //   0 - 1 - 2
    //   |       |
    //   3       4       (vertex 5 is isolated to show disconnected traversal)
    dsa::Graph g(6, /*directed=*/false);      // 6 vertices, undirected
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 3);
    g.add_edge(2, 4);

    std::cout << "BFS from 0: ";
    g.bfs(0, print_int);                      // expect: 0 1 3 2 4
    std::cout << "\n";

    std::cout << "DFS from 0 (recursive): ";
    g.dfs(0, print_int);                      // expect: 0 1 2 4 3
    std::cout << "\n";

    std::cout << "DFS from 0 (iterative, own Stack): ";
    g.dfs_iter(0, print_int);                 // same vertices reachable from 0
    std::cout << "\n";

    std::cout << "BFS over all components: ";
    g.bfs_all(print_int);                     // includes isolated vertex 5
    std::cout << "\n";

    std::cout << "components = " << g.connected_components() << "\n"; // 2
    std::cout << "has_path(0,4) = " << g.has_path(0, 4) << "\n"; // 1
    std::cout << "has_path(0,5) = " << g.has_path(0, 5) << "\n"; // 0
    return 0;
}

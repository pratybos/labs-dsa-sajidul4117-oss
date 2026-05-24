#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dsa/Graph.hpp"
#include <stdexcept>

// Globals used to record the order .
// Free functions are required because Graph stores a `void(*)(int)` callback.
static int g_visited[64];
static int g_visited_count = 0;
static void reset_visited() { g_visited_count = 0; }
static void record(int x) { g_visited[g_visited_count++] = x; }

TEST_CASE("vertex_count and bounds checking") {
    dsa::Graph g(4);
    CHECK(g.vertex_count() == 4);
    CHECK_THROWS_AS(g.add_edge(-1, 0), std::out_of_range);
    CHECK_THROWS_AS(g.add_edge(0, 4),  std::out_of_range);
    CHECK_THROWS_AS(g.bfs(7, record),  std::out_of_range);
    CHECK_THROWS_AS(g.dfs(7, record),  std::out_of_range);
}

TEST_CASE("BFS visits every reachable vertex once in level order") {
    //   0 - 1 - 2
    //   |       |
    //   3       4
    dsa::Graph g(5, false);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 3);
    g.add_edge(2, 4);

    reset_visited();
    g.bfs(0, record);
    CHECK(g_visited_count == 5);              // all reachable
    // BFS order with these adjacency lists is deterministic:
    int expected[] = {0, 1, 3, 2, 4};
    for (int i = 0; i < 5; ++i) CHECK(g_visited[i] == expected[i]);
}

TEST_CASE("DFS (recursive) visits every reachable vertex once") {
    dsa::Graph g(5, false);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 3);
    g.add_edge(2, 4);

    reset_visited();
    g.dfs(0, record);
    CHECK(g_visited_count == 5);
    // Expected DFS order: 0 -> 1 -> 2 -> 4 -> 3
    int expected[] = {0, 1, 2, 4, 3};
    for (int i = 0; i < 5; ++i) CHECK(g_visited[i] == expected[i]);
}

TEST_CASE("DFS iterative (own Stack) reaches the same vertices") {
    dsa::Graph g(5, false);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 3);
    g.add_edge(2, 4);

    reset_visited();
    g.dfs_iter(0, record);
    CHECK(g_visited_count == 5);              // visits each once
}

TEST_CASE("graphs with cycles do not loop forever") {
    //   0 - 1
    //   |   |
    //   3 - 2     (cycle 0-1-2-3-0)
    dsa::Graph g(4, false);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 0);

    reset_visited();
    g.bfs(0, record);
    CHECK(g_visited_count == 4);

    reset_visited();
    g.dfs(0, record);
    CHECK(g_visited_count == 4);
}

TEST_CASE("bfs_all and dfs_all visit disconnected components") {
    dsa::Graph g(6, false);
    g.add_edge(0, 1);
    g.add_edge(2, 3);
    // vertices 4 and 5 are isolated

    reset_visited();
    g.bfs_all(record);
    CHECK(g_visited_count == 6);              // all six vertices visited

    reset_visited();
    g.dfs_all(record);
    CHECK(g_visited_count == 6);
}

TEST_CASE("directed graph respects edge direction") {
    dsa::Graph g(3, true);                    // directed
    g.add_edge(0, 1);                         // only 0 -> 1
    g.add_edge(1, 2);                         // only 1 -> 2

    reset_visited();
    g.bfs(0, record);
    CHECK(g_visited_count == 3);              // 0,1,2 reachable from 0

    reset_visited();
    g.bfs(2, record);
    CHECK(g_visited_count == 1);              // nothing reachable from 2 except itself
    CHECK(g_visited[0] == 2);
}

TEST_CASE("connected_components and has_path") {
    dsa::Graph g(6, false);
    g.add_edge(0, 1);
    g.add_edge(2, 3);
    // isolated: 4, 5
    CHECK(g.connected_components() == 4);     // {0,1},{2,3},{4},{5}
    CHECK(g.has_path(0, 1));
    CHECK_FALSE(g.has_path(0, 3));
    CHECK(g.has_path(4, 4));                  // trivial self-path
}

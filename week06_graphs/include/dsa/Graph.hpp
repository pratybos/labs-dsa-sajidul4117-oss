// Graph
// Unweighted graph using adjacency lists built on our own DynamicArray.
// Supports both directed and undirected modes.
// BFS uses our Queue. DFS is recursive (with an iterative variant available below).
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range
#include "DynamicArray.hpp"                   // our own DynamicArray (reused from Week 01)
#include "Queue.hpp"                          // our own Queue (reused from Week 02)
#include "Stack.hpp"                          // our own Stack (used for optional iterative DFS)

namespace dsa {

    class Graph {
    public:
        // Create a graph with `vertices` vertices indexed 0..vertices-1.
        Graph(int vertices, bool directed = false)
            : v_(vertices),                   // remember vertex count
              directed_(directed),            // remember direction mode
              adj_(new DynamicArray<int>[vertices]) {} // one adjacency list per vertex

        ~Graph() {                            // destructor frees the adjacency-list array
            delete[] adj_;                    // each DynamicArray destroys its own buffer
        }

        Graph(const Graph&) = delete;         // disallow copying (raw owning pointer)
        Graph& operator=(const Graph&) = delete;

        int vertex_count() const { return v_; }   // number of vertices

        // Add an edge u-v (or u->v in directed mode).
        void add_edge(int u, int v) {
            check_vertex(u);                  // bounds-check both endpoints
            check_vertex(v);
            adj_[u].push_back(v);             // record neighbour v in u's list
            if (!directed_) adj_[v].push_back(u); // mirror edge if undirected
        }

        // BFS starting at `start`. Calls visit(vertex) for each vertex in BFS order.
        // Uses our own Queue. Time complexity O(V + E).
        void bfs(int start, void (*visit)(int)) const {
            check_vertex(start);              // bounds-check the start vertex
            bool* seen = new bool[v_]();      // visited flags, zero-initialised
            Queue<int> q;                     // BFS frontier queue (our own Queue)
            seen[start] = true;               // mark start visited before enqueuing
            q.enqueue(start);                 // begin from start
            while (!q.empty()) {              // standard BFS loop
                int u = q.front();            // peek next vertex
                q.dequeue();                  // remove it from the queue
                visit(u);                     // run the visitor callback
                const DynamicArray<int>& nbrs = adj_[u]; // alias for clarity
                for (std::size_t i = 0; i < nbrs.size(); ++i) {
                    int w = nbrs[i];          // neighbour
                    if (!seen[w]) {           // only enqueue unseen neighbours
                        seen[w] = true;       // mark before enqueue to avoid duplicates
                        q.enqueue(w);
                    }
                }
            }
            delete[] seen;                    // free the visited array
        }

        // DFS starting at `start`. Recursive variant. O(V + E).
        void dfs(int start, void (*visit)(int)) const {
            check_vertex(start);              // bounds-check
            bool* seen = new bool[v_]();      // visited flags
            dfs_rec(start, seen, visit);      // start recursion
            delete[] seen;                    // free flags
        }

        // BFS that visits every component (handles disconnected graphs).
        void bfs_all(void (*visit)(int)) const {
            bool* seen = new bool[v_]();      // shared visited array across components
            for (int s = 0; s < v_; ++s) {    // try every vertex as a possible start
                if (seen[s]) continue;        // already discovered in an earlier BFS
                Queue<int> q;                 // fresh queue for this component
                seen[s] = true;
                q.enqueue(s);
                while (!q.empty()) {
                    int u = q.front(); q.dequeue();
                    visit(u);
                    const DynamicArray<int>& nbrs = adj_[u];
                    for (std::size_t i = 0; i < nbrs.size(); ++i) {
                        int w = nbrs[i];
                        if (!seen[w]) { seen[w] = true; q.enqueue(w); }
                    }
                }
            }
            delete[] seen;                    // free flags
        }

        // DFS that visits every component (handles disconnected graphs).
        void dfs_all(void (*visit)(int)) const {
            bool* seen = new bool[v_]();      // shared visited array
            for (int s = 0; s < v_; ++s) {    // try every vertex as a possible start
                if (!seen[s]) dfs_rec(s, seen, visit); // start a new DFS at unseen vertex
            }
            delete[] seen;                    // free flags
        }

        // Optional bonus: iterative DFS using our own Stack.
        void dfs_iter(int start, void (*visit)(int)) const {
            check_vertex(start);              // bounds-check
            bool* seen = new bool[v_]();      // visited flags
            Stack<int> st;                    // our own Stack (LIFO)
            st.push(start);                   // start
            while (!st.empty()) {
                int u = st.top(); st.pop();   // pop next vertex
                if (seen[u]) continue;        // skip if already processed
                seen[u] = true;               // mark visited
                visit(u);                     // run visitor
                const DynamicArray<int>& nbrs = adj_[u];
                // push neighbours in reverse so smaller-index neighbours come out first
                for (std::size_t i = nbrs.size(); i-- > 0; ) {
                    if (!seen[nbrs[i]]) st.push(nbrs[i]);
                }
            }
            delete[] seen;                    // free flags
        }

        // Optional bonus: number of connected components (treat undirected).
        int connected_components() const {
            bool* seen = new bool[v_]();      // visited flags
            int count = 0;                    // component counter
            for (int s = 0; s < v_; ++s) {    // try every vertex as a possible start
                if (seen[s]) continue;        // skip if already discovered
                ++count;                      // new component
                Queue<int> q;                 // BFS to mark this component
                seen[s] = true;
                q.enqueue(s);
                while (!q.empty()) {
                    int u = q.front(); q.dequeue();
                    const DynamicArray<int>& nbrs = adj_[u];
                    for (std::size_t i = 0; i < nbrs.size(); ++i) {
                        int w = nbrs[i];
                        if (!seen[w]) { seen[w] = true; q.enqueue(w); }
                    }
                }
            }
            delete[] seen;                    // free flags
            return count;                     // total components
        }

        // Optional bonus: BFS-based reachability check.
        bool has_path(int u, int v) const {
            check_vertex(u);                  // bounds-check both endpoints
            check_vertex(v);
            if (u == v) return true;          // trivial case
            bool* seen = new bool[v_]();      // visited flags
            Queue<int> q;                     // standard BFS
            seen[u] = true; q.enqueue(u);
            bool found = false;               // result flag
            while (!q.empty() && !found) {
                int x = q.front(); q.dequeue();
                const DynamicArray<int>& nbrs = adj_[x];
                for (std::size_t i = 0; i < nbrs.size(); ++i) {
                    int w = nbrs[i];
                    if (w == v) { found = true; break; }  // target reached
                    if (!seen[w]) { seen[w] = true; q.enqueue(w); }
                }
            }
            delete[] seen;                    // free flags
            return found;                     // true if v reachable from u
        }

    private:
        int v_;                               // number of vertices
        bool directed_;                       // true if directed
        DynamicArray<int>* adj_;              // array of adjacency lists (length v_)

        void check_vertex(int x) const {      // bounds-check a vertex index
            if (x < 0 || x >= v_) throw std::out_of_range("vertex out of range");
        }

        // Recursive DFS helper.
        void dfs_rec(int u, bool* seen, void (*visit)(int)) const {
            seen[u] = true;                   // mark visited before recursing
            visit(u);                         // pre-order visit
            const DynamicArray<int>& nbrs = adj_[u];
            for (std::size_t i = 0; i < nbrs.size(); ++i) {
                int w = nbrs[i];              // neighbour
                if (!seen[w]) dfs_rec(w, seen, visit); // descend into unseen neighbour
            }
        }
    };

} // namespace dsa

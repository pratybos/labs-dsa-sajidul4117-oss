// Graph
// -----
// Adjacency-list graph for vertices 0..V-1, unweighted.
// I store one DynamicArray<int> per vertex — the neighbors of that vertex.
// "adj_" is itself a DynamicArray of DynamicArray<int>.
//
// Directed mode (passed at construction):
//   - directed=true   -> add_edge(u,v) adds only u -> v
//   - directed=false  -> add_edge(u,v) adds both u -> v and v -> u
//
// BFS uses MY Queue. DFS uses recursion (simpler to defend).
// bfs_all/dfs_all restart from every unvisited vertex so disconnected
// graphs are fully covered.

#pragma once
#include <cstddef>
#include <stdexcept>
#include "DynamicArray.hpp"
#include "Queue.hpp"

namespace dsa {

    class Graph {
    public:
        Graph(int vertices, bool directed = false)
            : V_(vertices), directed_(directed), adj_(nullptr) {
            if (vertices < 0) {
                throw std::out_of_range("Graph: negative vertex count");
            }
            // I allocate one DynamicArray per vertex.
            // I use "new[]" which calls default constructors -> empty arrays.
            adj_ = new DynamicArray<int>[V_];
        }

        ~Graph() {
            delete[] adj_;
        }

        int vertex_count() const { return V_; }

        // add_edge(u, v) — both endpoints must be valid.
        void add_edge(int u, int v) {
            check(u); check(v);
            adj_[u].push_back(v);
            if (!directed_) {
                adj_[v].push_back(u);
            }
        }

        // BFS from start, calling visit(vertex) for each visited vertex in order.
        void bfs(int start, void (*visit)(int)) const {
            check(start);
            bool* visited = new bool[V_];
            for (int i = 0; i < V_; ++i) visited[i] = false;

            Queue<int> q;
            visited[start] = true;
            q.enqueue(start);
            while (!q.empty()) {
                int u = q.front();
                q.dequeue();
                visit(u);
                // Walk u's neighbors and enqueue the unvisited ones.
                for (std::size_t i = 0; i < adj_[u].size(); ++i) {
                    int w = adj_[u][i];
                    if (!visited[w]) {
                        visited[w] = true;
                        q.enqueue(w);
                    }
                }
            }
            delete[] visited;
        }

        // DFS from start (recursive).
        void dfs(int start, void (*visit)(int)) const {
            check(start);
            bool* visited = new bool[V_];
            for (int i = 0; i < V_; ++i) visited[i] = false;
            dfs_rec(start, visited, visit);
            delete[] visited;
        }

        // Visits every vertex (even in disconnected graphs) using BFS.
        void bfs_all(void (*visit)(int)) const {
            bool* visited = new bool[V_];
            for (int i = 0; i < V_; ++i) visited[i] = false;

            for (int s = 0; s < V_; ++s) {
                if (visited[s]) continue;
                Queue<int> q;
                visited[s] = true;
                q.enqueue(s);
                while (!q.empty()) {
                    int u = q.front();
                    q.dequeue();
                    visit(u);
                    for (std::size_t i = 0; i < adj_[u].size(); ++i) {
                        int w = adj_[u][i];
                        if (!visited[w]) {
                            visited[w] = true;
                            q.enqueue(w);
                        }
                    }
                }
            }
            delete[] visited;
        }

        void dfs_all(void (*visit)(int)) const {
            bool* visited = new bool[V_];
            for (int i = 0; i < V_; ++i) visited[i] = false;
            for (int s = 0; s < V_; ++s) {
                if (!visited[s]) {
                    dfs_rec(s, visited, visit);
                }
            }
            delete[] visited;
        }

    private:
        int V_;
        bool directed_;
        DynamicArray<int>* adj_;   // array of size V_

        void check(int v) const {
            if (v < 0 || v >= V_) {
                throw std::out_of_range("Graph: vertex out of range");
            }
        }

        void dfs_rec(int u, bool* visited, void (*visit)(int)) const {
            visited[u] = true;
            visit(u);
            for (std::size_t i = 0; i < adj_[u].size(); ++i) {
                int w = adj_[u][i];
                if (!visited[w]) {
                    dfs_rec(w, visited, visit);
                }
            }
        }
    };

} // namespace dsa

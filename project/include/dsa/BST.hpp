// BST<T>  — Binary Search Tree
// ----------------------------
// Rules (these are the WHOLE point of a BST):
//   For every node with key K:
//     - all keys in the LEFT  subtree are <  K
//     - all keys in the RIGHT subtree are >  K
//   Duplicates: I IGNORE them (do not insert).
//
// I use recursion for insert, contains, traversal, and remove —
// recursion fits trees naturally because a subtree is also a tree.

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class BST {
    private:
        struct Node {
            T key;
            Node* left;
            Node* right;
            Node(const T& k) : key(k), left(nullptr), right(nullptr) {}
        };

        Node* root_;
        std::size_t size_;

        // ---------- recursive helpers ----------

        void clear_rec(Node* n) {
            if (n == nullptr) return;
            clear_rec(n->left);
            clear_rec(n->right);
            delete n;
        }

        // Insert key into the subtree, return the (possibly new) root of subtree.
        // If the key already exists, I just return n (ignore the duplicate).
        Node* insert_rec(Node* n, const T& key) {
            if (n == nullptr) {
                size_ = size_ + 1;
                return new Node(key);
            }
            if (key < n->key) {
                n->left = insert_rec(n->left, key);
            } else if (n->key < key) {
                n->right = insert_rec(n->right, key);
            }
            // else: equal -> ignore
            return n;
        }

        bool contains_rec(Node* n, const T& key) const {
            if (n == nullptr) return false;
            if (key < n->key) return contains_rec(n->left, key);
            if (n->key < key) return contains_rec(n->right, key);
            return true; // equal
        }

        // Smallest key in the subtree = leftmost node.
        Node* min_node(Node* n) const {
            while (n->left != nullptr) n = n->left;
            return n;
        }

        Node* max_node(Node* n) const {
            while (n->right != nullptr) n = n->right;
            return n;
        }

        std::size_t height_rec(Node* n) const {
            if (n == nullptr) return 0;
            std::size_t hL = height_rec(n->left);
            std::size_t hR = height_rec(n->right);
            return 1 + (hL > hR ? hL : hR);
        }

        void inorder_rec(Node* n, T* out, std::size_t& idx) const {
            if (n == nullptr) return;
            inorder_rec(n->left, out, idx);
            out[idx++] = n->key;
            inorder_rec(n->right, out, idx);
        }

        // Remove key from subtree rooted at n.
        // Returns the new root of that subtree. Sets `removed` to true if found.
        // The 3 cases:
        //   - no children -> just delete and return nullptr
        //   - one child   -> replace n with that child
        //   - two children -> find inorder successor (min of right subtree),
        //                     copy its key here, then remove that successor
        Node* remove_rec(Node* n, const T& key, bool& removed) {
            if (n == nullptr) return nullptr;
            if (key < n->key) {
                n->left = remove_rec(n->left, key, removed);
                return n;
            }
            if (n->key < key) {
                n->right = remove_rec(n->right, key, removed);
                return n;
            }
            // Found the node to remove.
            removed = true;
            if (n->left == nullptr && n->right == nullptr) {
                delete n;
                return nullptr;
            }
            if (n->left == nullptr) {
                Node* r = n->right;
                delete n;
                return r;
            }
            if (n->right == nullptr) {
                Node* l = n->left;
                delete n;
                return l;
            }
            // Two children: replace with inorder successor.
            Node* succ = min_node(n->right);
            n->key = succ->key;
            bool dummy = false;
            n->right = remove_rec(n->right, succ->key, dummy);
            return n;
        }

    public:
        BST() : root_(nullptr), size_(0) {}
        ~BST() { clear_rec(root_); }

        std::size_t size() const { return size_; }
        bool empty() const { return root_ == nullptr; }

        void insert(const T& key) {
            root_ = insert_rec(root_, key);
        }

        bool contains(const T& key) const {
            return contains_rec(root_, key);
        }

        const T& min() const {
            if (root_ == nullptr) {
                throw std::out_of_range("BST::min - empty");
            }
            return min_node(root_)->key;
        }

        const T& max() const {
            if (root_ == nullptr) {
                throw std::out_of_range("BST::max - empty");
            }
            return max_node(root_)->key;
        }

        std::size_t height() const {
            return height_rec(root_);
        }

        // Writes keys in sorted order into out (caller provides size>=size()).
        void inorder(T* out) const {
            std::size_t idx = 0;
            inorder_rec(root_, out, idx);
        }

        // Returns true if the key was found and removed.
        bool remove(const T& key) {
            bool removed = false;
            root_ = remove_rec(root_, key, removed);
            if (removed) size_ = size_ - 1;
            return removed;
        }
    };

} // namespace dsa

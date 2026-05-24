// BST<T>
// Binary Search Tree implemented with raw pointers and recursion.
// Duplicates are ignored. Memory is managed manually with new/delete.
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range
#include <utility>                            // for std::move (not strictly needed but allowed)

namespace dsa {

    template <class T>
    class BST {
    private:
        struct Node {                         // a BST node
            T key;                            // the stored key
            Node* left;                       // left subtree (keys < key)
            Node* right;                      // right subtree (keys > key)
            Node(const T& k) : key(k), left(nullptr), right(nullptr) {} // create a leaf
        };

    public:
        BST() : root_(nullptr), size_(0) {}   // empty tree

        ~BST() { clear_rec(root_); }          // free all nodes

        BST(const BST&) = delete;             // disallow copy (raw pointers)
        BST& operator=(const BST&) = delete;  // disallow assignment

        std::size_t size() const { return size_; }       // number of nodes
        bool empty() const { return root_ == nullptr; }  // true if no root

        // Insert a key; duplicates are ignored.
        void insert(const T& key) {
            root_ = insert_rec(root_, key);   // recursive insert returns subtree root
        }

        // Return true if the key exists in the tree.
        bool contains(const T& key) const {
            return contains_rec(root_, key);  // recursive search
        }

        // Return the minimum key. Throws if the tree is empty.
        T min() const {
            if (!root_) throw std::out_of_range("min on empty BST"); // protect against empty tree
            return min_node(root_)->key;      // leftmost node's key
        }

        // Return the maximum key. Throws if the tree is empty.
        T max() const {
            if (!root_) throw std::out_of_range("max on empty BST"); // protect against empty tree
            return max_node(root_)->key;      // rightmost node's key
        }

        // Height: empty = 0, leaf = 1, otherwise 1 + max(left,right).
        std::size_t height() const {
            return height_rec(root_);         // recursive helper
        }

        // Inorder traversal: writes keys in sorted order into out[0..size()).
        void inorder(T* out) const {
            std::size_t idx = 0;              // write index
            inorder_rec(root_, out, idx);     // recursive helper
        }

        // Remove a key; returns true if removed, false if not found.
        bool remove(const T& key) {
            bool removed = false;             // flag set inside the recursive helper
            root_ = remove_rec(root_, key, removed); // rebuild subtree without the key
            return removed;                   // tell caller whether anything was deleted
        }

    private:
        Node* root_;                          // pointer to root node
        std::size_t size_;                    // number of nodes stored

        // Recursive insert: returns the (possibly new) subtree root.
        Node* insert_rec(Node* n, const T& key) {
            if (!n) {                         // empty slot: create the new node here
                ++size_;                      // one more node
                return new Node(key);         // allocate and return
            }
            if (key < n->key) {               // smaller key goes left
                n->left = insert_rec(n->left, key);
            } else if (n->key < key) {        // larger key goes right (avoid '>' so only '<' is required on T)
                n->right = insert_rec(n->right, key);
            }
            // equal: ignore duplicate (per spec)
            return n;                         // return unchanged subtree root
        }

        // Recursive search.
        static bool contains_rec(Node* n, const T& key) {
            if (!n) return false;             // base: not found
            if (key < n->key) return contains_rec(n->left, key);  // search left subtree
            if (n->key < key) return contains_rec(n->right, key); // search right subtree
            return true;                      // equal: found
        }

        // Leftmost node of a non-null subtree.
        static Node* min_node(Node* n) {
            while (n->left) n = n->left;      // walk left until no more
            return n;                         // leftmost
        }

        // Rightmost node of a non-null subtree.
        static Node* max_node(Node* n) {
            while (n->right) n = n->right;    // walk right until no more
            return n;                         // rightmost
        }

        // Recursive height.
        static std::size_t height_rec(Node* n) {
            if (!n) return 0;                 // empty tree height is 0
            std::size_t lh = height_rec(n->left);  // left subtree height
            std::size_t rh = height_rec(n->right); // right subtree height
            return 1 + (lh > rh ? lh : rh);   // 1 + max child height
        }

        // Inorder traversal helper (left, root, right).
        static void inorder_rec(Node* n, T* out, std::size_t& idx) {
            if (!n) return;                   // base: empty
            inorder_rec(n->left, out, idx);   // left subtree first
            out[idx++] = n->key;              // then this node
            inorder_rec(n->right, out, idx);  // then right subtree
        }

        // Recursive remove. Handles all 3 cases (leaf / one child / two children).
        Node* remove_rec(Node* n, const T& key, bool& removed) {
            if (!n) return nullptr;           // base: key not present
            if (key < n->key) {               // descend left
                n->left = remove_rec(n->left, key, removed);
            } else if (n->key < key) {        // descend right
                n->right = remove_rec(n->right, key, removed);
            } else {
                // found the node to delete
                removed = true;               // tell caller a node was removed
                if (!n->left && !n->right) {  // case 1: leaf
                    delete n;                 // free this node
                    --size_;                  // one fewer node
                    return nullptr;           // parent's pointer becomes null
                }
                if (!n->left) {               // case 2a: only right child
                    Node* r = n->right;       // save right subtree
                    delete n;                 // free this node
                    --size_;                  // one fewer node
                    return r;                 // parent now points to right child
                }
                if (!n->right) {              // case 2b: only left child
                    Node* l = n->left;        // save left subtree
                    delete n;                 // free this node
                    --size_;                  // one fewer node
                    return l;                 // parent now points to left child
                }
                // case 3: two children. Replace key with inorder successor (min of right subtree).
                Node* succ = min_node(n->right); // smallest key in right subtree
                n->key = succ->key;           // copy successor key up to this node
                n->right = remove_rec(n->right, succ->key, removed); // remove successor from right subtree
                // 'removed' was already true; the recursive call will set it true again. Fine.
            }
            return n;                         // return current (possibly unchanged) subtree root
        }

        // Recursive postorder deletion of every node.
        static void clear_rec(Node* n) {
            if (!n) return;                   // base: nothing to delete
            clear_rec(n->left);               // delete left subtree first
            clear_rec(n->right);              // then right subtree
            delete n;                         // finally this node
        }
    };

} // namespace dsa

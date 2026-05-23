// BinaryTree<T>
// A plain (non-BST) binary tree built manually using set_root / add_left / add_right.
// Recursive traversals: preorder, inorder, postorder.
// Memory is managed manually with new/delete.
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range, std::logic_error

namespace dsa {

    template <class T>
    class BinaryTree {
    private:
        struct Node {                         // a binary-tree node
            T value;                          // the stored value
            Node* left;                       // pointer to left child (nullptr if none)
            Node* right;                      // pointer to right child (nullptr if none)
            Node(const T& v) : value(v), left(nullptr), right(nullptr) {} // create a leaf node
        };

    public:
        BinaryTree() : root_(nullptr), size_(0) {} // empty tree

        ~BinaryTree() {                       // destructor cleans memory
            clear();                          // delete all nodes
        }

        BinaryTree(const BinaryTree&) = delete;            // disallow copying (raw pointers)
        BinaryTree& operator=(const BinaryTree&) = delete; // disallow assignment

        std::size_t size() const { return size_; }         // total number of nodes
        bool empty() const { return root_ == nullptr; }    // true if no root

        // Create the root. Throws if a root already exists.
        void set_root(const T& value) {
            if (root_) throw std::logic_error("root already exists"); // already created
            root_ = new Node(value);          // allocate root node
            ++size_;                          // one node now
        }

        // Add a left child to the node whose value == parentValue.
        void add_left(const T& parentValue, const T& childValue) {
            Node* p = find_node(root_, parentValue); // search for the parent
            if (!p) throw std::out_of_range("parent not found"); // no such parent
            if (p->left) throw std::logic_error("left child already exists"); // slot taken
            p->left = new Node(childValue);   // create the left child
            ++size_;                          // bump node count
        }

        // Add a right child to the node whose value == parentValue.
        void add_right(const T& parentValue, const T& childValue) {
            Node* p = find_node(root_, parentValue); // search for the parent
            if (!p) throw std::out_of_range("parent not found"); // no such parent
            if (p->right) throw std::logic_error("right child already exists"); // slot taken
            p->right = new Node(childValue);  // create the right child
            ++size_;                          // bump node count
        }

        // Preorder traversal: root, left, right. Writes values into out[0..size()).
        void preorder(T* out) const {
            std::size_t idx = 0;              // write index passed by reference
            preorder_rec(root_, out, idx);    // recursive helper
        }

        // Inorder traversal: left, root, right.
        void inorder(T* out) const {
            std::size_t idx = 0;              // write index
            inorder_rec(root_, out, idx);     // recursive helper
        }

        // Postorder traversal: left, right, root.
        void postorder(T* out) const {
            std::size_t idx = 0;              // write index
            postorder_rec(root_, out, idx);   // recursive helper
        }

        // Height: empty tree = 0, leaf = 1, otherwise 1 + max(left,right).
        std::size_t height() const {
            return height_rec(root_);         // recursive helper
        }

        // Returns true if the value exists anywhere in the tree.
        bool contains(const T& value) const {
            return find_node(root_, value) != nullptr; // reuse find_node
        }

        // Delete every node and reset state.
        void clear() {
            clear_rec(root_);                 // recursively delete all nodes
            root_ = nullptr;                  // no root anymore
            size_ = 0;                        // no nodes left
        }

    private:
        Node* root_;                          // pointer to root node
        std::size_t size_;                    // total nodes count

        // Search a subtree for a node with the given value.
        static Node* find_node(Node* n, const T& value) {
            if (!n) return nullptr;           // base: nothing here
            if (n->value == value) return n;  // found at this node
            Node* l = find_node(n->left, value);  // search left subtree
            if (l) return l;                  // return early if found
            return find_node(n->right, value); // otherwise search right subtree
        }

        // Recursive helpers for traversals: each writes value then recurses.
        static void preorder_rec(Node* n, T* out, std::size_t& idx) {
            if (!n) return;                   // base: empty
            out[idx++] = n->value;            // root first
            preorder_rec(n->left, out, idx);  // then left
            preorder_rec(n->right, out, idx); // then right
        }
        static void inorder_rec(Node* n, T* out, std::size_t& idx) {
            if (!n) return;                   // base: empty
            inorder_rec(n->left, out, idx);   // left first
            out[idx++] = n->value;            // then root
            inorder_rec(n->right, out, idx);  // then right
        }
        static void postorder_rec(Node* n, T* out, std::size_t& idx) {
            if (!n) return;                   // base: empty
            postorder_rec(n->left, out, idx); // left first
            postorder_rec(n->right, out, idx);// then right
            out[idx++] = n->value;            // root last
        }

        // Recursive height calculation.
        static std::size_t height_rec(Node* n) {
            if (!n) return 0;                 // empty tree height is 0
            std::size_t lh = height_rec(n->left);  // height of left subtree
            std::size_t rh = height_rec(n->right); // height of right subtree
            return 1 + (lh > rh ? lh : rh);   // 1 (this node) + max child height
        }

        // Recursive deletion (post-order delete).
        static void clear_rec(Node* n) {
            if (!n) return;                   // base: nothing to delete
            clear_rec(n->left);               // delete left subtree first
            clear_rec(n->right);              // delete right subtree
            delete n;                         // then delete this node
        }
    };

} // namespace dsa

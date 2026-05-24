// HashTable: int->int hash table using separate chaining.
// Each bucket holds a small singly-linked list of (key,value) pairs.
// This lab focuses on hashing + collisions, so resizing is not implemented.
#pragma once                                  // include only once
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::invalid_argument

namespace dsa {

    class HashTable {
    private:
        struct Node {                         // bucket chain node
            int key;                          // stored key
            int value;                        // stored value
            Node* next;                       // pointer to next node in this bucket's chain
            Node(int k, int v) : key(k), value(v), next(nullptr) {} // create a new node
        };

    public:
        // Build a hash table with the given fixed bucket capacity.
        explicit HashTable(int capacity)
            : capacity_(capacity),            // remember bucket count
              size_(0),                       // no entries yet
              buckets_(nullptr) {
            if (capacity <= 0) throw std::invalid_argument("capacity must be positive"); // protect against bad input
            buckets_ = new Node*[capacity];   // allocate the array of bucket-head pointers
            for (int i = 0; i < capacity; ++i) buckets_[i] = nullptr; // start each bucket empty
        }

        ~HashTable() {                        // destructor frees every chain node and the bucket array
            for (int i = 0; i < capacity_; ++i) {
                Node* n = buckets_[i];        // walk this bucket's chain
                while (n) {                   // delete each node
                    Node* nx = n->next;       // remember next before delete
                    delete n;                 // free the node
                    n = nx;                   // move on
                }
            }
            delete[] buckets_;                // free the bucket pointer array
        }

        HashTable(const HashTable&) = delete; // disallow copying (raw owning pointers)
        HashTable& operator=(const HashTable&) = delete;

        int size() const { return size_; }                 // number of stored key/value pairs
        int bucket_count() const { return capacity_; }     // number of buckets

        // Insert a new key, or update the value if the key already exists.
        // Returns true if a new key was inserted, false if an existing key was updated.
        bool put(int key, int value) {
            int idx = bucket_index(key);      // figure out which bucket
            Node* n = buckets_[idx];          // walk the chain looking for the key
            while (n) {
                if (n->key == key) {          // key already present: update the value
                    n->value = value;         // overwrite
                    return false;             // not a new insertion
                }
                n = n->next;                  // continue along the chain
            }
            Node* fresh = new Node(key, value); // not found: create a new chain node
            fresh->next = buckets_[idx];        // push it at the chain head (O(1))
            buckets_[idx] = fresh;              // new head
            ++size_;                            // bump entry count
            return true;                        // new key inserted
        }

        // True if the key exists in the table.
        bool contains(int key) const {
            return find(key) != nullptr;      // reuse find()
        }

        // Return a pointer to the value associated with `key`, or nullptr if not found.
        // Returning a pointer lets callers both read and write the stored value.
        int* get(int key) {
            Node* n = find(key);              // look up the chain node
            return n ? &n->value : nullptr;   // pointer to stored value, or nullptr
        }

        // Remove the key. Returns true if removed, false if the key was not found.
        bool remove(int key) {
            int idx = bucket_index(key);      // bucket where the chain lives
            Node* prev = nullptr;             // trailing pointer used to relink the chain
            Node* cur  = buckets_[idx];       // current node being examined
            while (cur) {
                if (cur->key == key) {        // found the node to remove
                    if (prev) prev->next = cur->next; // unlink from middle/tail
                    else      buckets_[idx] = cur->next; // unlink head: bucket points to next
                    delete cur;               // free node memory
                    --size_;                  // one fewer entry
                    return true;              // success
                }
                prev = cur;                   // remember previous
                cur  = cur->next;             // move on
            }
            return false;                     // not found
        }

    private:
        int capacity_;                        // number of buckets (fixed)
        int size_;                            // number of stored entries
        Node** buckets_;                      // array of chain heads (length capacity_)

        // Map a (possibly negative) key into [0, capacity_).
        // The two-step modulo handles negative keys correctly.
        int bucket_index(int key) const {
            int idx = key % capacity_;        // may be negative if key is negative
            if (idx < 0) idx += capacity_;    // shift into the non-negative range
            return idx;                       // valid bucket index
        }

        // Find a chain node by key (helper for get/contains).
        Node* find(int key) const {
            int idx = bucket_index(key);      // bucket where the chain lives
            Node* n = buckets_[idx];          // walk the chain
            while (n) {
                if (n->key == key) return n;  // hit
                n = n->next;                  // miss: keep looking
            }
            return nullptr;                   // not present
        }
    };

} // namespace dsa

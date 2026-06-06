// SinglyLinkedList<T>
// -------------------
// A linked list built from Nodes.
// Each Node has a value and a pointer to the NEXT node.
// I keep both head_ (first node) and tail_ (last node) so push_back is O(1).
//
// Memory rule (very important): every "new" I do, I must "delete" later.
// The destructor walks the list and deletes every node.

#pragma once
#include <cstddef>
#include <stdexcept>

namespace dsa {

    template <class T>
    class SinglyLinkedList {
    private:
        // The Node struct lives INSIDE the list class because nobody else
        // needs to know about it. It is a private detail.
        struct Node {
            T value;
            Node* next;
            Node(const T& v) : value(v), next(nullptr) {}
        };

        Node* head_;
        Node* tail_;
        std::size_t size_;

    public:
        // Empty list — no nodes yet.
        SinglyLinkedList()
            : head_(nullptr), tail_(nullptr), size_(0) {
        }

        // Destructor: free every node so I don't leak memory.
        ~SinglyLinkedList() {
            // Walk from head and delete every node one by one.
            Node* cur = head_;
            while (cur != nullptr) {
                Node* nextNode = cur->next;
                delete cur;
                cur = nextNode;
            }
        }

        // push_front — put a new node at the BEGINNING. O(1).
        void push_front(const T& value) {
            Node* n = new Node(value);
            n->next = head_;
            head_ = n;
            if (tail_ == nullptr) {
                // list was empty -> the new node is also the tail
                tail_ = n;
            }
            size_ = size_ + 1;
        }

        // push_back — put a new node at the END. O(1) thanks to tail_.
        void push_back(const T& value) {
            Node* n = new Node(value);
            if (tail_ == nullptr) {
                // empty list
                head_ = n;
                tail_ = n;
            } else {
                tail_->next = n;
                tail_ = n;
            }
            size_ = size_ + 1;
        }

        // pop_front — remove the first node. O(1). Throws if empty.
        void pop_front() {
            if (head_ == nullptr) {
                throw std::out_of_range("SinglyLinkedList::pop_front - empty");
            }
            Node* old = head_;
            head_ = head_->next;
            if (head_ == nullptr) {
                // The list became empty -> tail must also be reset.
                tail_ = nullptr;
            }
            delete old;
            size_ = size_ - 1;
        }

        // front — read the first value. Throws if empty.
        T& front() {
            if (head_ == nullptr) {
                throw std::out_of_range("SinglyLinkedList::front - empty");
            }
            return head_->value;
        }
        const T& front() const {
            if (head_ == nullptr) {
                throw std::out_of_range("SinglyLinkedList::front - empty");
            }
            return head_->value;
        }

        bool empty() const { return head_ == nullptr; }
        std::size_t size() const { return size_; }

        // find(v) — return true if v appears anywhere. O(n).
        bool find(const T& value) const {
            Node* cur = head_;
            while (cur != nullptr) {
                if (cur->value == value) return true;
                cur = cur->next;
            }
            return false;
        }

        // remove_first(v) — remove the FIRST node whose value == v.
        // Returns true if something was removed.
        // I have to keep a "prev" pointer so I can re-link prev->next.
        bool remove_first(const T& value) {
            Node* prev = nullptr;
            Node* cur = head_;
            while (cur != nullptr) {
                if (cur->value == value) {
                    if (prev == nullptr) {
                        // Removing head
                        head_ = cur->next;
                    } else {
                        prev->next = cur->next;
                    }
                    // If we removed the tail, update tail_
                    if (cur == tail_) {
                        tail_ = prev;
                    }
                    delete cur;
                    size_ = size_ - 1;
                    return true;
                }
                prev = cur;
                cur = cur->next;
            }
            return false;
        }

        // reverse — flip the list in place. Iterative version.
        // Classic 3-pointer trick: prev, cur, next.
        void reverse() {
            Node* prev = nullptr;
            Node* cur = head_;
            tail_ = head_; // the old head will become the new tail
            while (cur != nullptr) {
                Node* nxt = cur->next;  // remember the rest
                cur->next = prev;       // flip the arrow
                prev = cur;             // move prev forward
                cur = nxt;              // move cur forward
            }
            head_ = prev;
        }
    };

} // namespace dsa

<<<<<<< HEAD
// SinglyLinkedList<T>
// Node-based linked list using raw pointers and manual memory management.
// We keep a head_ pointer (and size_) so most operations are easy.
#pragma once                                  // include only once per translation unit
#include <cstddef>                            // for std::size_t
#include <stdexcept>                          // for std::out_of_range
=======
//
// Created by marius on 1/27/26.
//

#pragma once
#include <cstddef>
#include <stdexcept>
>>>>>>> 1a8add819ac79b3efba7aa41f9c3cf5b73f204e7

namespace dsa {

    template <class T>
    class SinglyLinkedList {
    private:
<<<<<<< HEAD
        struct Node {                         // single list node
            T value;                          // value stored in the node
            Node* next;                       // pointer to the next node (nullptr if last)
            Node(const T& v, Node* n = nullptr) : value(v), next(n) {} // small constructor
        };

    public:
        SinglyLinkedList() : head_(nullptr), size_(0) {} // start with empty list

        ~SinglyLinkedList() {                 // destructor must free every node
            clear();                          // reuse clear() to delete everything
        }

        SinglyLinkedList(const SinglyLinkedList&) = delete;            // copying disabled (raw pointer)
        SinglyLinkedList& operator=(const SinglyLinkedList&) = delete; // assignment disabled

        bool empty() const { return size_ == 0; }      // empty when no nodes
        std::size_t size() const { return size_; }     // current number of nodes

        T& front() {                          // reference to first element
            if (!head_) throw std::out_of_range("front empty"); // throw on empty list
            return head_->value;              // value of head node
        }
        const T& front() const {              // const version
            if (!head_) throw std::out_of_range("front empty");
            return head_->value;
        }

        T& back() {                           // reference to last element
            if (!head_) throw std::out_of_range("back empty"); // empty list -> throw
            Node* cur = head_;                // walk from head
            while (cur->next) cur = cur->next; // stop at the last node
            return cur->value;                // return its value
        }
        const T& back() const {               // const version
            if (!head_) throw std::out_of_range("back empty");
            Node* cur = head_;
            while (cur->next) cur = cur->next;
            return cur->value;
        }

        void push_front(const T& v) {         // insert at the front - O(1)
            head_ = new Node(v, head_);       // new node points to current head, becomes new head
            ++size_;                          // size grows by one
        }

        void push_back(const T& v) {          // insert at the end
            Node* node = new Node(v, nullptr); // create the new tail node
            if (!head_) {                     // empty list?
                head_ = node;                 // new node is also the head
            } else {                          // otherwise walk to current tail
                Node* cur = head_;            // start from head
                while (cur->next) cur = cur->next; // stop at last node
                cur->next = node;             // link new node after current tail
            }
            ++size_;                          // size grows
        }

        void pop_front() {                    // remove first node
            if (!head_) throw std::out_of_range("pop_front empty"); // cannot pop empty
            Node* old = head_;                // remember current head
            head_ = head_->next;              // move head to next node
            delete old;                       // free old head node
            --size_;                          // size shrinks by one
        }

        void pop_back() {                     // remove last node
            if (!head_) throw std::out_of_range("pop_back empty"); // cannot pop empty
            if (!head_->next) {               // only one node?
                delete head_;                 // free it
                head_ = nullptr;              // list is now empty
            } else {
                Node* cur = head_;            // walk to second-to-last node
                while (cur->next->next) cur = cur->next; // stop one before last
                delete cur->next;             // free last node
                cur->next = nullptr;          // new last node points to null
            }
            --size_;                          // size shrinks
        }

        bool find(const T& v) const {         // search the list for value v
            Node* cur = head_;                // start at head
            while (cur) {                     // walk all nodes
                if (cur->value == v) return true; // found
                cur = cur->next;              // go next
            }
            return false;                     // not found
        }

        bool remove_first(const T& v) {       // remove first node whose value == v
            Node* cur = head_;                // current node
            Node* prev = nullptr;             // previous node
            while (cur) {                     // scan list
                if (cur->value == v) {        // match found
                    if (prev) prev->next = cur->next; // unlink from middle/end
                    else head_ = cur->next;   // unlink from head
                    delete cur;               // free the node
                    --size_;                  // size shrinks
                    return true;              // removed
                }
                prev = cur;                   // advance prev
                cur = cur->next;              // advance cur
            }
            return false;                     // value was not in the list
        }

        void reverse() {                      // reverse the list in-place (iterative)
            Node* prev = nullptr;             // becomes new next pointer
            Node* cur = head_;                // walker pointer
            while (cur) {                     // walk every node
                Node* nxt = cur->next;        // save next first
                cur->next = prev;             // flip the link
                prev = cur;                   // move prev forward
                cur = nxt;                    // move cur forward
            }
            head_ = prev;                     // prev is the new head
        }

        void clear() {                        // delete every node
            while (head_) {                   // while there is something to delete
                Node* next = head_->next;     // remember next node
                delete head_;                 // free current head
                head_ = next;                 // move head to next
            }
            size_ = 0;                        // list is now empty
        }

    private:
        Node* head_;                          // pointer to first node (nullptr if empty)
        std::size_t size_;                    // number of nodes in the list
=======
        struct Node {
            T value;
            Node* next;
            Node(const T& v, Node* n = nullptr) : value(v), next(n) {}
        };

    public:
        SinglyLinkedList();
        ~SinglyLinkedList();

        // Rule of 3/5: LATER (not implementing just copying now)
        SinglyLinkedList(const SinglyLinkedList&) = delete;
        SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

        bool empty() const;
        std::size_t size() const;

        T& front();
        const T& front() const;

        T& back();               // O(n) for singly list (unless you store tail)
        const T& back() const;

        void push_front(const T& value);
        void push_back(const T& value);

        void pop_front();        // throws if empty
        void pop_back();         // throws if empty

        void clear();

    private:
        Node* head_;
        std::size_t size_;
>>>>>>> 1a8add819ac79b3efba7aa41f9c3cf5b73f204e7
    };

} // namespace dsa

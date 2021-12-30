#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>

#include <initializer_list>

template<typename T>
class LinkedList {

    private:
        Node<T> * head;
        Node<T> * tail;
        int numOfElements;

    public:

        /*
            Creates an empty LinkedList
        */
        LinkedList()
            : head(nullptr), tail(nullptr), numOfElements(0) {}

        /*
            Creates a new LinkedList using an initialiser_list
        */
        LinkedList(const std::initializer_list<T> & listIn) 
            : head(nullptr), tail(nullptr), numOfElements(0) {
                for (auto & value : listIn) {
                    push_back(value);
                }
                numOfElements = listIn.size();
            }

        /*
            Inserts a new element at the front of the list
        */
        void push_front(const T & dataToFront) {
            Node<T> * newNode = new Node<T>(dataToFront);
            if (head == nullptr) { // list is empty
                head = newNode;
                tail = newNode;
            } else {
                newNode->next = head;
                head = newNode;
                newNode->next->previous = newNode;
            }
            numOfElements++;
        }

        /*
            Returns a reference to the node at the front of the list
        */
        T & front() {
            return head->data;
        }

        /*
            Inserts the new element at the rear of the list
        */
        void push_back(const T & dataToBack) {
            Node<T> * newNode = new Node<T>(dataToBack);
            if (head == nullptr && tail == nullptr) { // list is empty
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                newNode->previous = tail;
                tail = newNode;
            }
            numOfElements++;
        }

        /*
            Returns a reference to the node at the tail
        */
        T & back() {
            return tail->data;
        }

        /*
            Returns the number of elements in the list      
        */
        const int & size() {
            return numOfElements;
        }

        /*
            Returns an iterator pointing to the head
        */
        NodeIterator<T> begin() {
            return NodeIterator<T>(head);
        }

        /*
            Returns an iterator pointing to null
        */
        NodeIterator<T> end() {
            return NodeIterator<T>(nullptr);
        }

        /*
            Returns a read only iterator pointing to the head
        */
        ConstNodeIterator<T> begin() const {
            return ConstNodeIterator<T>(head);
        }

        /*
            Returns a read only interator pointing to null
        */
        ConstNodeIterator<T> end() const {
            return ConstNodeIterator<T>(nullptr);
        }

        /*
            De-constructor
            Deletes all of the nodes in the list
        */
        ~LinkedList() {
            Node<T> * current = head;
            Node<T> * toBeDeleted = nullptr;
            for (int i = 1; i < numOfElements; ++i) {
               toBeDeleted = current;
               current = current->next;
                delete toBeDeleted;
            }
            delete tail;
        }

        /*
            Reverses the list
        */
        void reverse() {
            Node<T> * oldTail = tail;
            Node<T> * currentNode = tail;
            Node<T> * temporaryNode;
            for (int i = 0; i < numOfElements - 1; ++i) {
                temporaryNode = currentNode->previous;
                currentNode->next = temporaryNode;
                currentNode->previous = temporaryNode->next;
                currentNode = currentNode->next;
            }
            currentNode->previous = currentNode->next;
            currentNode->next = nullptr;
            tail = currentNode;
            head = oldTail;
        }

        /*
            Inserts new element into list 
            Returns the iterator pointing to the new node
        */
        NodeIterator<T> insert(NodeIterator<T> itr, const T & element) {
            if (itr.getCurrent() == nullptr) {
                Node<T> * newNode = new Node<T>(element);
                newNode->previous = tail;
                tail->next = newNode;
                tail = newNode;
                numOfElements++;
                return NodeIterator<T>(newNode);
            } else if (itr.getCurrent() == head) {
                Node<T> * newNode = new Node<T>(element);
                newNode->next = head;
                head->previous = newNode;
                head = newNode;
                numOfElements++;
                return NodeIterator<T>(newNode);
            } else {
                Node<T> * newNode = new Node<T>(element);
                Node<T> * currentNode = itr.getCurrent();
                newNode->previous = currentNode->previous;
                currentNode->previous->next = newNode;
                newNode->next = currentNode;
                currentNode->previous = newNode;
                numOfElements++;
                return NodeIterator<T>(newNode);
            }
        }

        /*
            Erases the node at the iterator position provided
            Returns the iterator of the node proceeding the deleted node
        */
        NodeIterator<T> erase(NodeIterator<T> itr) {
            Node<T> * toBeDeleted = itr.getCurrent();
            if (numOfElements == 1) {
                delete toBeDeleted;
                return end();
            }
            else if (head == toBeDeleted) {
                toBeDeleted->next->previous = nullptr;
                head = toBeDeleted->next;
            } else if (tail == toBeDeleted) {
                toBeDeleted->previous->next = nullptr;
                tail = toBeDeleted->previous;
            } else {
                toBeDeleted->previous->next = toBeDeleted->next;
                toBeDeleted->next->previous = toBeDeleted->previous;
            }
            itr.operator++();
            numOfElements--;
            delete toBeDeleted;
            return itr;
        }
};



#endif

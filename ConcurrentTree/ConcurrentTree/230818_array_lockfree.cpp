#include <iostream>
#include "SpinLock.hpp"

template <typename T>
class Node {
public:
    T data;
    atomic<Node<T>*> prev;
    atomic<Node<T>*> next;

    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LockFreeDoublyLinkedList {
private:
    T data;
    Node<T>* head;
    Node<T>* tail;

public:
    LockFreeDoublyLinkedList() {
        head = new Node<T>(T());
        tail = new Node<T>(T());
        head->next.store(tail);
        tail->prev.store(head);
    }

    bool search(T value) {
        Node<T>* current = head->next.load();
        while (current != tail) {
            if (current->data == value) {
                return true;
            }
            current = current->next.load();
        }
        return false;
    }

    void insert(T value) {
        Node<T>* new_node = new Node<T>(value);

        while (true) {
            Node<T>* prev_node = head;
            Node<T>* current_node = head->next.load();

            while (current_node != tail && current_node->data < value) {
                prev_node = current_node;
                current_node = current_node->next.load();
            }

            new_node->prev.store(prev_node);
            new_node->next.store(current_node);

            if (prev_node->next.compare_exchange_weak(current_node, new_node)) {
                current_node->prev.store(new_node);
                return;
            }
        }
    }

    void print() {
        Node<T>* current = head->next.load();
        cout << "List Contents: ";
        while (current != tail) {
            cout << current->data << " ";
            current = current->next.load();
        }
        cout << endl;
    }
};


int main(void) {

    LockFreeDoublyLinkedList<int> list;

    list.insert(3);
    list.insert(1);
    list.insert(5);
    list.insert(2);
    list.insert(4);

    list.print();
  


	return 0;
}
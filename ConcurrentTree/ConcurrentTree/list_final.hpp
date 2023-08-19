#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <algorithm>
#include <condition_variable>
using namespace std;

template <typename T>

class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;
    bool mark;
    mutex mtx; // ���ؽ��� ��带 ��ȣ��.
    Node(T value) : data(value), prev(nullptr), next(nullptr), mark(false) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    mutex listMtx;
    condition_variable cv;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // ��� ���� �Լ�
    void insertNode(T value) {
        Node<T>* newNode = new Node<T>(value);

        unique_lock<mutex> lock(listMtx);
        while (tail && tail->mark) {
            cv.wait(lock, [this]() { return !tail->mark; });
        }

        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        cout << value << " insert" << '\n';
        cv.notify_all();  // Notify other threads waiting on the condition variable
    }




    // ��� ���� �Լ�
    void deleteNode(T value) {
        {
            std::unique_lock<std::mutex> lock(listMtx);
            while (tail && tail->mark) {
                cv.wait(lock, [this]() { return !tail->mark; });
            }
            Node<T>* current = head;
            current->mark = true;
            while (current) {
                if (current->data == value) {
                    if (current == head) {
                        head = head->next;
                        if (head)
                            head->prev = nullptr;
                    }
                    else if (current == tail) {
                        tail = tail->prev;
                        if (tail)
                            tail->next = nullptr;
                    }
                    else {
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                    }
                    cout << value << " delete" << '\n';
                    delete current;
                    break;
                }
                current = current->next;
            }
        }

        cv.notify_all();
    }

    // ã�� �Լ�
    bool search(T value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // ����Ʈ ��� �Լ�
    void displayList() {
        Node<T>* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << endl;
    }



    // �Ҹ���
    ~DoublyLinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

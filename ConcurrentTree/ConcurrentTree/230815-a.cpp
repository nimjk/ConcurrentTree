#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <algorithm>
#include <condition_variable>
using namespace std;

int CAS(int old_val, int new_val, int* address) {
    int value = *address;
    if (value == old_val)
        *address = new_val;
    return value;
};

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    bool mark;
    mutex mtx; // 뮤텍스로 노드를 보호함.
    Node(int value) : data(value), prev(nullptr), next(nullptr), mark(false) {}
};

void setMarkAndProcess(Node* node, int newValue) {
    {
        lock_guard<mutex> lock(node->mtx);  // Lock the node's mutex
        node->mark = true;
    }

    // Simulate some processing
    this_thread::sleep_for(std::chrono::seconds(1));

    {
        lock_guard<mutex> lock(node->mtx);  // Lock the node's mutex
        node->mark = false;
    }
}

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    mutex listMtx;
    condition_variable cv;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // 노드 삽입 함수
    void insertNode(int value) {
        Node* newNode = new Node(value);

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
        cv.notify_all();  // Notify other threads waiting on the condition variable
    }




    // 노드 삭제 함수
    void deleteNode(int value) {
        {
            std::unique_lock<std::mutex> lock(listMtx);
            while (tail && tail->mark) {
                cv.wait(lock, [this]() { return !tail->mark; });
            }
            Node* current = head;
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
                    delete current;
                    break;
                }
                current = current->next;
            }
        }

        cv.notify_all();  // Notify other threads waiting on the condition variable
    }
    // 리스트 출력 함수
    void displayList() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // 소멸자
    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList dll;

    thread thread1([&dll]() {
        for (int i = 0; i < 250;  i++)
            dll.insertNode(i);
        });
    thread thread2([&dll]() {
        for (int i = 250; i < 500; i++)
            dll.insertNode(i);
        });
    thread thread3([&dll]() {
        for (int i = 500; i < 750; i++)
            dll.insertNode(i);
        });
    thread thread4([&dll]() {
        for (int i = 200; i < 450; i++)
            dll.deleteNode(i);
        });

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    dll.displayList();

    return 0;
}
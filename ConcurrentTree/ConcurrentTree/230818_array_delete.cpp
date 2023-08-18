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

/*int CAS(int old_val, int new_val, int* address) {
    int value = *address;
    if (value == old_val)
        *address = new_val;
    return value;
};*/

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    bool mark;
    mutex mtx; // 뮤텍스로 노드를 보호함.
    Node(int value) : data(value), prev(nullptr), next(nullptr), mark(false) {}
};

/*void setMarkAndProcess(Node* node, int newValue) {
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
}*/

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
                    cout << value << " delete" << '\n';
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
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool search(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
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
        for (int i = 4900; i < 5000; i++)
        {
            dll.deleteNode(i);
            cout << "1번 스레드 호출" << '\n';
        }
        });
    thread thread2([&dll]() {
        for (int i = 4800; i < 4900; i++)
        {
            dll.deleteNode(i);
            cout << "2번 스레드 호출" << '\n';
        }
        });
    thread thread3([&dll]() {
        for (int i = 4700; i < 4800; i++)
        {
            dll.deleteNode(i);
            cout << "3번 스레드 호출" << '\n';
        }

        });
    thread thread4([&dll]() {
        for (int i = 4600; i < 4700; i++)
        {
            dll.deleteNode(i);
            cout << "4번 스레드 호출" << '\n';
        }
        });

    

    srand(GetTickCount64());
    int arr[2000];
    int count = 0;
    clock_t start, end;
    double duration;
    start = clock();
    while (count < 2000) {
        int tmp = rand() % 5000 + 1;
        int isSame = 0;
        for (int i = 0; i < count; i++) {
            if (tmp == arr[i]) {
                isSame = 1;
                break;
            }
        }
        if (isSame == 0) {
            arr[count] = tmp;
            dll.insertNode(arr[count]);
            count++;
        }
    }
    end = clock();

    duration = (double)(end - start) / CLOCKS_PER_SEC;
    

  
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    dll.displayList();
    cout << "Time of generation list : " << duration << "초\n";
    
    
    int searchcnt = 0;


    double mintime, maxtime;
    double totaltime = 0;
    double meantime = 0;


    while (searchcnt < 100) {
        int searchidx = rand() % 2000;
        int searchnum = rand() % 5000 + 1;

        start = clock();
        dll.search(searchnum); // 
        end = clock();

        duration = (double)(end - start) / CLOCKS_PER_SEC;

        if (searchcnt == 0) {
            mintime = duration;
            maxtime = duration;
        }

        else {
            if (mintime > duration) {
                mintime = duration;
            }
            else if (maxtime < duration) {
                maxtime = duration;
            }
        }

        totaltime += duration;

        searchcnt++;
    }

    meantime = totaltime / (searchcnt + 1);

    cout << "minimum time of search : "<<fixed << mintime << "초\n";
    cout << "maximum time of search : " << maxtime << "초\n";
    cout << "total time of search : " << totaltime << "초\n";
    cout << "average time of search : " << meantime << "초\n";

    return 0;
}
    
    
    
    
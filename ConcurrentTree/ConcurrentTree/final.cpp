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

int main() {
    DoublyLinkedList<int> dll; // list ����� �̸� ����

    srand(GetTickCount64());  // ������ 2õ���� ���� ����.
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
        if (isSame == 0) {      // �ߺ��� ��� �Ÿ��� insert
            arr[count] = tmp;
            dll.insertNode(arr[count]);
            count++;
        }
    }
    end = clock();
    //���۰� �� �ð��� �̿��� list�� insert �ð� ���
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    //��Ƽ�����带 �̿��� ���� ����
    thread thread1([&dll]() {
        for (int i = 4500; i < 5000; i++)
        {
            dll.deleteNode(i);
            cout << "1�� ������ ȣ��" << '\n';
        }
    });
    thread thread2([&dll]() {
        for (int i = 4000; i < 4500; i++)
        {
            dll.deleteNode(i);
            cout << "2�� ������ ȣ��" << '\n';
        }
        });
    thread thread3([&dll]() {
        for (int i = 3500; i < 4000; i++)
        {
            dll.deleteNode(i);
            cout << "3�� ������ ȣ��" << '\n';
        }

        });
    thread thread4([&dll]() {
        for (int i = 3000; i < 3500; i++)
        {
            dll.deleteNode(i);
            cout << "4�� ������ ȣ��" << '\n';
        }
    });


    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();


  
    dll.displayList();
    cout << "Time of generation list : " << duration << "��\n";


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

    cout << "minimum time of search : " << fixed << mintime << "��\n";
    cout << "maximum time of search : " << maxtime << "��\n";
    cout << "total time of search : " << totaltime << "��\n";
    cout << "average time of search : " << meantime << "��\n";

    return 0;
}




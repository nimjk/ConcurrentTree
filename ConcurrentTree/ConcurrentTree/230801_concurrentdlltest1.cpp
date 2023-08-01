#include <iostream>
#include <list>
#include <mutex>
#include <thread>

std::list<int> linked_list;
std::mutex list_mutex;

void insert_element(int value) {
    std::lock_guard<std::mutex> lock(list_mutex);
    linked_list.push_back(value);
}

void remove_element(int value) {
    std::lock_guard<std::mutex> lock(list_mutex);
    linked_list.remove(value);
}

void print_list() {
    std::lock_guard<std::mutex> lock(list_mutex);
    for (const auto& item : linked_list) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::thread thread1(insert_element, 1);
    std::thread thread2(insert_element, 2);
    std::thread thread3(remove_element, 1);
    std::thread thread4(print_list);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    return 0;
}


// 이 코드에서 결과는 1,2가 나올때가 있고 2만 나올때도 있고 안나올때도 있음
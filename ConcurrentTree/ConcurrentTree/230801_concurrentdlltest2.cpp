#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

std::list<int> linked_list;
std::mutex list_mutex;
std::condition_variable cv_insert, cv_remove;

void insert_element(int value) {
    std::lock_guard<std::mutex> lock(list_mutex);
    linked_list.push_back(value);
    cv_insert.notify_one();
}

void remove_element(int value) {
    std::unique_lock<std::mutex> lock(list_mutex);
    cv_insert.wait(lock, [] { return linked_list.size() > 0; });  //람다 표현식
    linked_list.remove(value);
    cv_remove.notify_one();
}

void print_list() {
    std::unique_lock<std::mutex> lock(list_mutex);
    cv_remove.wait(lock, [] { return linked_list.size() > 0; }); 
    cv_insert.wait(lock, [] { return linked_list.size() > 0; });
    
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
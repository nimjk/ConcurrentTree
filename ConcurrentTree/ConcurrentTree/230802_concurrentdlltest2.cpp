#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

std::list<int> linked_list;
std::mutex list_mutex;
std::condition_variable cv_insert, cv_remove;

void insert_element(int value) {
    std::lock_guard<std::mutex> loc(list_mutex);
    linked_list.push_back(value);
    cv_insert.notify_one();
}

size_t list_size() {
    std::lock_guard<std::mutex> loc(list_mutex);
    return linked_list.size();
}
void remove_element(int value) {
    std::unique_lock<std::mutex> loc1(list_mutex);
    cv_insert.wait(loc1, [] { return linked_list.size() > 0; });  //람다 표현식
    linked_list.remove(value);
    cv_remove.notify_one();
}

void print_list() {
    std::unique_lock<std::mutex> loc2(list_mutex);
    cv_insert.wait(loc2, [] { return linked_list.size() == 3; }); 
    cv_remove.wait(loc2, [] { return linked_list.size() > 0; });
    for (const auto& item : linked_list) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::thread thread1(insert_element, 1);
    std::thread thread2(insert_element, 2);
    std::thread thread3(insert_element, 3);
    std::thread thread4(print_list);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    return 0;
}
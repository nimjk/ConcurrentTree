#include <iostream>
#include <vector>
#include <thread>
#include <mutex>



const int ARRAY_SIZE = 10;
std::vector<int> concurrentArray(ARRAY_SIZE); // concurrentArray는 동시 접근 가능한 배열입니다.
std::mutex arrayMutex; // 배열에 접근하기 위한 mutex

void WriteToConcurrentArray(int index, int value) {
    std::lock_guard<std::mutex> lock(arrayMutex); // 배열에 접근하기 전에 mutex를 락합니다.
    concurrentArray[index] = value;
}

int ReadFromConcurrentArray(int index) {
    // 읽기 작업에는 mutex를 사용하지 않습니다.
    return concurrentArray[index];
}

int main() {
    std::vector<std::thread> threads;

    // 여러 스레드에서 배열에 값을 쓰기(write) 작업을 수행합니다.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        threads.push_back(std::thread(WriteToConcurrentArray, i, i + 1));
    }

    // 스레드가 모두 끝날 때까지 기다립니다.
    for (auto& thread : threads) {
        thread.join();
    }

    threads.clear(); // 이전에 생성된 스레드들을 제거합니다.

    // 여러 스레드에서 배열에서 값을 읽기(read) 작업을 수행합니다.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        threads.push_back(std::thread(ReadFromConcurrentArray, i));
    }

    // 스레드가 모두 끝날 때까지 기다립니다.
    for (auto& thread : threads) {
        thread.join();
    }

    // 배열의 최종 상태를 출력합니다.
    std::cout << "Concurrent Array: ";
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        std::cout << concurrentArray[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
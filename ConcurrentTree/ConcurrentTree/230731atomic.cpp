#include <iostream>
#include <vector>
#include <thread>
#include <mutex>



const int ARRAY_SIZE = 10;
std::vector<int> concurrentArray(ARRAY_SIZE); // concurrentArray�� ���� ���� ������ �迭�Դϴ�.
std::mutex arrayMutex; // �迭�� �����ϱ� ���� mutex

void WriteToConcurrentArray(int index, int value) {
    std::lock_guard<std::mutex> lock(arrayMutex); // �迭�� �����ϱ� ���� mutex�� ���մϴ�.
    concurrentArray[index] = value;
}

int ReadFromConcurrentArray(int index) {
    // �б� �۾����� mutex�� ������� �ʽ��ϴ�.
    return concurrentArray[index];
}

int main() {
    std::vector<std::thread> threads;

    // ���� �����忡�� �迭�� ���� ����(write) �۾��� �����մϴ�.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        threads.push_back(std::thread(WriteToConcurrentArray, i, i + 1));
    }

    // �����尡 ��� ���� ������ ��ٸ��ϴ�.
    for (auto& thread : threads) {
        thread.join();
    }

    threads.clear(); // ������ ������ ��������� �����մϴ�.

    // ���� �����忡�� �迭���� ���� �б�(read) �۾��� �����մϴ�.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        threads.push_back(std::thread(ReadFromConcurrentArray, i));
    }

    // �����尡 ��� ���� ������ ��ٸ��ϴ�.
    for (auto& thread : threads) {
        thread.join();
    }

    // �迭�� ���� ���¸� ����մϴ�.
    std::cout << "Concurrent Array: ";
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        std::cout << concurrentArray[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
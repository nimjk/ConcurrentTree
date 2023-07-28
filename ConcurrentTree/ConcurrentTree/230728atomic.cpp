#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
using namespace std;

// 데이터 레이스를 막기 위해 뮤텍스로 보호한 버전
long long mutexInt = 0;
std::mutex mutex_;

void someFunctionWithMutex() {
    for (long long i = 0; i < 25000000; i++) {
        std::lock_guard<std::mutex> lock(mutex_);
        mutexInt += i;
    }
}

void someFunctionWithMutex2() {
    for (long long i = 25000000; i < 50000000; i++) {
        std::lock_guard<std::mutex> lock(mutex_);
        mutexInt += i;
    }
}


void someFunctionWithMutex3() {
    for (long long i = 50000000; i < 75000000; i++) {
        std::lock_guard<std::mutex> lock(mutex_);
        mutexInt += i;
    }
}


void someFunctionWithMutex4() {
    for (long long i = 75000000; i < 100000000; i++) {
        std::lock_guard<std::mutex> lock(mutex_);
        mutexInt += i;
    }
}


// 원자적 연산으로 계산한 버전
std::atomic<long long> atomicInt = 0;

void someFunctionWithAtomic() {
    for (long long i = 0; i < 25000000; i++) {
        atomicInt.fetch_add(i, std::memory_order_relaxed);
    }
}

void someFunctionWithAtomic2() {
    for (long long i = 25000000; i < 50000000; i++) {
        atomicInt.fetch_add(i, std::memory_order_relaxed);
    }
}
void someFunctionWithAtomic3() {
    for (long long i = 50000000; i < 75000000; i++) {
        atomicInt.fetch_add(i, std::memory_order_relaxed);
    }
}
void someFunctionWithAtomic4() {
    for (long long i = 75000000; i < 100000000; i++) {
        atomicInt.fetch_add(i, std::memory_order_relaxed);
    }
}


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    // 뮤텍스를 사용한 버전
    thread t1(someFunctionWithMutex);
    thread t2(someFunctionWithMutex2);
    thread t3(someFunctionWithMutex3);
    thread t4(someFunctionWithMutex4);
  
    t1.join();
    t2.join();
    t3.join();
    t4.join();
  

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    cout << "Time taken with mutex: " << elapsed.count() << " seconds." << endl;

    // 원자적 연산을 사용한 버전
    start = std::chrono::high_resolution_clock::now();

    thread t9(someFunctionWithAtomic);
    thread t10(someFunctionWithAtomic2);
    thread t11(someFunctionWithAtomic3);
    thread t12(someFunctionWithAtomic4);
  

    t9.join();
    t10.join();
    t11.join();
    t12.join();
    

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    cout << "Time taken with atomic: " << elapsed.count() << " seconds." << endl;


    long long normalint = 0;
    start = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < 100000000; i++)
        normalint += i;

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    cout << "Time taken normal for syntax " << elapsed.count() << " seconds." << endl;

    return 0;
}

/*
Time taken with mutex: 10.4345 seconds.
Time taken with atomic: 1.69765 seconds.
Time taken normal for syntax 0.307333 seconds.
*/
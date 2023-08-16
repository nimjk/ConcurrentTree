#include <iostream>
#include <thread>
#include <vector>

std::atomic_flag spinlock = ATOMIC_FLAG_INIT; // Unifor initialization is not allowed
static const size_t NumberOfThreads{50};
static const size_t LoopsPerThread{100};

void dowork(size_t threadNumber, std::vector<size_t> &data)
{
    for (size_t i = 0; i < LoopsPerThread; i++)
    {
        while (spinlock.test_and_set())
        {
        } // Spins until lock is acquired
        // save to handle shared data
        data.push_back(threadNumber);
        spinlock.clear(); // Release the acquired lock
    }
}

int main()
{
    std::vector<size_t> data;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < NumberOfThreads; ++i)
    {
        threads.push_back(std::thread{dowork, i, std::ref(data)});
    }
    for (auto &t : threads)
    {
        t.join();
    }
    std::cout << "data contains" << data.size()
              << " elemants, expected " << NumberOfThreads * LoopsPerThread << ".\n";
}

#include <iostream>
#include <thread>
#include <random>
#include <atomic>

// 원 내부에 점이 있는지 검사하고 카운트를 증가시키는 함수
void monteCarloPiCalculation(std::atomic<int>& insideCircleCount, int totalPoints) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    int insideCount = 0;
    for (int i = 0; i < totalPoints; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= 1) {
            insideCount++;
        }
    }

    insideCircleCount += insideCount;
}

int main() {
    const int numThreads = 4;
    const int totalPoints = 1000000;  // 시뮬레이션할 전체 점의 수
    std::atomic<int> insideCircleCount(0);

    std::thread threads[numThreads];

    // 각 스레드를 시작
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(monteCarloPiCalculation, std::ref(insideCircleCount), totalPoints / numThreads);
    }

    // 모든 스레드의 완료를 대기
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    // 파이 값 계산
    double pi = static_cast<double>(insideCircleCount) / totalPoints * 4;

    std::cout << "Estimated Pi: " << pi << std::endl;

    return 0;
}

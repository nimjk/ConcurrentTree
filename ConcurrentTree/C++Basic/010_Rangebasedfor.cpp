#include <iostream>
#include <stdio.h>
using namespace std;

int main(int argc, char *arcstring[])
{
    int aList[5] = {10, 20, 30, 40, 50};
    // 전형적인 C스타일 반복문
    for (int i = 0; i < 5; ++i)
        cout << aList[i] << ' ';

    cout << endl;

    // 조건식의 차이
    // 위에서 aList를 읽기만 하고 l-value를 사용하거나 단항 증/감 연산을 수행하지 않음.
    // 범위 기반 C++11 스타일 반복문
    // 각 요소의 값을 n에 복사

    for (auto n : aList)
        cout << n << ' ';
    cout << endl;

    for (auto &n : aList)
        cout << n << ' ';
    cout << endl;

    return 0;
}
#include <stdio.h>
#include <iostream>
// 다중 정의와 모호성
void TestFunc(int a)
{
    std::cout << "TestFunc(int)" << std::endl;
}

void TestFunc(int a, int b = 10)
{
    std::cout << "TestFunc(int, int)" << std::endl;
}

int main(int argc, char *argv[])
{
    TestFunc(5);

    return 0;
}

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <string>

int main(int argc, char *arcv[])
{
    int nAge;
    std::cout << "나이를 입력" << std::endl;
    std::cin >> nAge;

    char Job[32];
    std::cout << "직업을 입력" << std::endl;
    std::cin >> Job;

    std::string strName;
    std::cout << "이름을 입력" << std::endl;
    std::cin >> strName;

    std::cout << "당신의 나이는 " << nAge << "세이며 "
              << "직업은 " << Job << "이고 "
              << "이름은 " << strName << "입니다." << std::endl;

    return 0;
}
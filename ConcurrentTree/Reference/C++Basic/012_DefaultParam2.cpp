#include <iostream>
#include <stdio.h>

int TestFunc(int = 10); // 실인수 생략가능

int TestFunc(int nParam)
{
    return nParam;
}

int main(int argc, char *arcstring[])
{

     // 호출자가 실인수 확정 , 디폴트 값 무시
    std::cout << TestFunc(20) << std::endl;

    return 0;
}
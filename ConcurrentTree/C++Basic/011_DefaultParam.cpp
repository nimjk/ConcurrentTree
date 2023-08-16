#include <iostream>
#include <stdio.h>

// nParam 매개변수의 디폴트 값은 10
int TestFunc(int nParam = 10)
{
    return nParam;
}

int main(int argc, char *arcstring[])
{

    std::cout << TestFunc() << std::endl;
    // 호출자가 실인수 확정 , 디폴트 값 무시
    std::cout << TestFunc(20) << std::endl;

    return 0;
}
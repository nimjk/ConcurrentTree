#include <iostream>
#include <stdio.h>

// 매개변수가 두 개 일 때의 디폴트 값
int TestFunc(int nParam1, int nParam2 = 2)
// 피호출자 함수 매개변수의 디폴트 값은 반드시 오른쪽 매개변수부터 기술
// 호출자 함수가 피호출자 함수 매개변수의 실인수를 기술하면 이는
// 왼쪽부터 짝을 맞추어 적용되며, 짝이 맞지 않는 매개변수는 디폴트 값을 적용
{
    return nParam1 * nParam2;
}

int main(int argc, char *arcstring[])
{

    std::cout << TestFunc(10) << std::endl;

    std::cout << TestFunc(10, 6) << std::endl;

    return 0;
}
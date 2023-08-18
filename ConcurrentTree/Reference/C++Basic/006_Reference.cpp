#include <iostream>
#include <stdio.h>

int main(int argc, char *arcstring[])
{
    int nData = 10;
    // declare reference
    int &ref = nData;

    ref = 20;
    std::cout << nData << std::endl;

    // 참조하는 변수값 변하지 않게 고정
    int nNewData = 10;
    const int &Newref = nNewData;
    ref = 30;

    std::cout << nNewData << std::endl;

    int *pnData = &nData;
    *pnData = 30;
    std::cout << nData << std::endl;
    return 0;
}
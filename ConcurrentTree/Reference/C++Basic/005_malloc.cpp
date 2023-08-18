#include <iostream>
#include <stdio.h>

int main(int argc, char *arcv[])
{
    int *pData = new int;
    int *pNewData = new int(10);

    *pData = 5;

    std::cout << "*pData : " << *pData << std::endl;
    std::cout << "*pNewData : " << *pNewData << std::endl;

    delete pData;
    delete pNewData;

    int *pArr = new int[5];
    for (int i = 0; i < 5; ++i)
        pArr[i] = (i + 1) * 10;

    for (int i = 0; i < 5; ++i)
        std::cout << i << "번째 인덱스" << i << ":" << pArr[i] << std::endl;

    delete[] pArr;

    return 0;
}
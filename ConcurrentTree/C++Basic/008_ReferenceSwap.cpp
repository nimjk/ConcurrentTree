#include <iostream>
#include <stdio.h>
using namespace std;

// 참조 전달이므로 호출자 변수의 값을 변경할 수 있다.
void Swap(int &a, int &b)
{
    int nTmp = a;
    a = b;
    b = nTmp;
}

int main(int argv, char *arcstring[])
{
    int x = 10, y = 20;

    Swap(x, y);

    cout << x << "<-x" << y << "<- y" << endl;
    return 0;
}
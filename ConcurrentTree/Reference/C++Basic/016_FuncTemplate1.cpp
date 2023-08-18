#include <iostream>
#include <stdio.h>
using namespace std;
// typename 은 자료형을 의미 , T는 자료형 , 템플릿은 일종의 틀
// 굳이 형식을 지정하지 않아도 쉽게 코드 확장할 수 있다.
template <typename T>
T TestFunc(T a)
{
    cout << "매개변수 a:" << a << endl;

    return a;
}

int main(int argc, char *arcv[])
{
    cout << "int\t" << TestFunc(3) << endl;
    cout << "double\t" << TestFunc(3.3) << endl;
    cout << "char\t" << TestFunc('A') << endl;
    cout << "char*\t" << TestFunc("TestString") << endl;
    return 0;
}
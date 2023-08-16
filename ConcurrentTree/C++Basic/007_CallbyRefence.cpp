#include <iostream>
#include <stdio.h>
using namespace std;

void TestFunc(int &rParam)
{
    // 피호출자 함수에서 원본 값 변경
    rParam = 100;
}
int main(int argv, char *arcstring[])
{
    int nData = 0;

    // deliver variable using reference
    // 참조에 의한 인수 전달
    TestFunc(nData); // TestFunc(&nData)라고 쓰면 컴파일에러
    // 함수의 매개변수가 참조자인 경우, 호출자 코드만 봐서는 참조 형식이라는 사실을 알 수 없다.

    cout << nData << endl;
    return 0;
}
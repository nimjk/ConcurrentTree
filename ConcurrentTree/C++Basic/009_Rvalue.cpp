#include <iostream>
#include <stdio.h>
using namespace std;

// r-value 참조자 : 임시 결과 , 연산에 활용된 직후 소멸
//  r-value:대입연산에서 두개의 피연산자 중 오른쪽에 위치한 연산자 , 변수와 상수 모두 해당

int TestFunc(int nParam)
{
    int nResult = nParam * 2;
    return nResult;
}

int main(int argc, char *arcstring[])
{
    // 값을 받아서 변수에 넣어줌
    int nInput = 0;
    cout << "Input number: " << endl;
    cin >> nInput;

    // 산술 연산으로 만들어진 임시 객체에 대한 r-value 참조
    //************************
    int &&rdata = nInput + 5;
    cout << rdata << endl;
    // 함수 반환으로 만들어진 임시 객체에 대한 r-value 참조
    //*************************
    int &&result = TestFunc(10);

    result += 10;
    cout << result << endl;
    return 0;
}
#include <iostream>
#include <stdio.h>
using namespace std;

// namespace는 C++가 지원하는 각종 요소들(변수, 함수, 클래스 등)을 한 범주에 묶어주기 위한 문법
//'소속'
// 아래 g_nData 변수와 TestFunc()함수는 모두 TEST라는 네임스페이스에 속한다.
namespace TEST
{
    int g_nData = 100;

    void TestFunc(void)
    {
        cout << "TEST::TestFunc()" << endl;
    }
}

using namespace TEST;

int main(int argc, char *arcv[])
{

    TestFunc();
    cout << TEST::g_nData << endl;

    return 0;
}
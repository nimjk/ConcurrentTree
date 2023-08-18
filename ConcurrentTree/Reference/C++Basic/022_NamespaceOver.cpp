#include <iostream>
#include <stdio.h>
using namespace std;

// 전역(개념상 무소속)
void TestFunc(void) { cout << "::TestFunc()" << endl; }

namespace TEST
{
    // TEST 네임스페이스 소속
    void TestFunc(void) { cout << "TEST::TestFunc()" << endl; }
}

namespace MYDATA
{
    // MYDATA 네임스페이스 소속
    void TestFunc(void) { cout << "MYDATA::TestFunc()" << endl; }
}

int main(int argc, char *argv[])
{
    TestFunc();
    ::TestFunc();
    TEST::TestFunc();
    MYDATA::TestFunc();

    return 0;
}
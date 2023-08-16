#include <iostream>
#include <stdio.h>
using namespace std;

template <typename T>
T Add(T a, T b)
{

    return a + b;
}

int main(int argc, char *arcv[])
{
    cout << Add(3, 4) << endl;
    cout << Add(3.3, 4.4) << endl;
    cout << Add<int>(5, 5) << endl;

    return 0;
}
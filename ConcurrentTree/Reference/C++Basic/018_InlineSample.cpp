#include <iostream>
// #include <stdio.h>
#include <cstdio>

// 함수를 호출하면 스택 메모리 사용이 증가하고 매개변수 때문에 메모리 복사가 일어난다.
// 제어 흐름도 이동해야 한다.
// 함수 호출로 인한 오버헤드를 극복하고자 매크로를 사용한다.
// 매크로는 함수가 아니다. 따라서 논리적 오류를 발생시키기도 한다.
// 이를 보완하기 위해 인라인inline함수가 나왔다. 매개변수에 형식을 지정할 수 있어 매크로를 보완한다.

// 최적화(Optimization)이란, 고급어(하이레벨언어)를 기계어로 번역하는 과정에서 CPU나 메모리 사용의
// 효율을 높이도록 코드를 변경하는 것이다.

#define ADD(a, b) ((a) + (b))

using namespace std;

int Add(int a, int b)
{
    return a + b;
}

inline int AddNew(int a, int b)
{
    return a + b;
}

int main(int argc, char *arcv[])
{
    int a, b;
    scanf("%d%d", &a, &b);

    printf("ADD(): %d\n", ADD(a, b));
    printf("Add(): %d\n", Add(a, b));
    printf("AddNew(): %d\n", AddNew(a, b));

    return 0;
}
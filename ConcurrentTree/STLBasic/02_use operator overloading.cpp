// 2차원 평면상의 한 점을 표현하는 클래스 Point이용해 연산자 오버로딩 설명
// 연산자 오버로딩의 핵심은 클래스 타입(사용자 정의 타입)의 객체에 연산자를 사용하면
// 컴파일러는 정의된 함수를 호출함
#include <iostream>
using namespace std;

class Point
{
    int x;
    int y;

public:
    Point(int _x = 0, int _y = 0)
        : x(_x),
          y(_y) {}

    void Print() const { cout << x << ',' << y << endl; }
    void operator+(Point arg)
    {
        cout << "operator +() 함수호출" << endl;
    }
};

int main()
{
    Point p1(2, 3), p2(5, 5);

    p1 + p2;  // p1.operator+(p2);와 같다
    p1 *p2;   // p1.operator*(p2);
    p1 = p2;  // p1.operator=(p2);
    p1 == p2; // p1.operator==(p2);
    p1 += p2; // p1.operator+=(p2);

    return 0;
}

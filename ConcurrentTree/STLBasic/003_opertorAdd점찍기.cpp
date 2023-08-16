#include <iostream>
using namespace std;

class Point
{
    int x;
    int y;

public:
    Point(int _x = 0, int _y = 0)
        : x(_x), y(_y) {}
    void Print() const { cout << x << ',' << y << endl; }
    const Point operator+(const Point &arg)
        const
    {
        Point pt;
        pt.x = this->x + arg.x;
        pt.y = this->y + arg.y;

        return pt;
    }
    // const 멤버함수는 멤버함수 내에서 멤버 변수를 변경하지 않는다는 것을 보장한다.
    // 따라서 const 객체는 const 멤버 함수만 호출할 수 있다.
    // const 멤버 함수에서 멤버 변수를 변경하면 컴파일러 에러이다.
};

int main()
{
    Point p1(2, 3), p2(5, 5);
    Point p3;

    // 연산자 오버로딩
    p3 = p1 + p2; // 컴파일러가 p1.operator+(p2)로 해석해서 호출
    p3.Print();
    p3 = p1.operator+(p2); // 직접호출
    p3.Print();
    return 0;
}

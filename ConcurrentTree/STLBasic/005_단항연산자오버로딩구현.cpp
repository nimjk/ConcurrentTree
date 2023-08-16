#include <iostream>
using namespace std;

class Point
{
    int x;
    int y;

public:
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    void Print() const { cout << x << ',' << y << endl; }

    const Point &operator++() // 전위 ++
    {
        ++x;
        ++y;
        return *this;
    }

    const Point &operator++(int) // 후위 ++
    {
        Point pt(x, y);
        ++x; // 내부 구현이므로 멤버 변수는 전위 ++연산을 사용해도 무방.
        ++y;
        return pt;
    }
};

int main()
{
    Point p1(2, 3), p2(2, 3);
    Point result;

    result = ++p1; // p1.operator++(); 과 같다.
    p1.Print();
    result.Print();

    result = p2++;  // p2.operator++(int); 과  같다.
    p2.Print();     // 위 구문에서 p2에 후위 ++연산이 되어져 x,y값이 1 증가함.
    result.Print(); // result에는 먼저 p2 본래 값이 들어가고 아직 연산된 값은 들어가지 않음

    Point temp;
    temp = p2++; // temp에 p2값 받아오고 p2에 후위++연산하기)

    return 0;
}
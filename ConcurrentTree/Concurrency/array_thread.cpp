#include <array>
#include <iostream>
#include <thread>

class Stack
{
public:
    int getNum(int idx)
    {
        if (idx < 0)
        {
            throw std::runtime_error("error");
        }
        if (mIdx < idx)
        {
            throw std::runtime_error("error");
        }
        return mNums[idx];
    }

    void push_back(int num)
    {
        if (mIdx == 199)
        {
            throw std::runtime_error("error");
        }
        ++mIdx;
        mNums[mIdx] = num;
    }
} int main()
{
    Stack st;
    st.puch_back(1);
    st.puch_back(3);
    st.puch_back(5);
    st.puch_back(7);
    st.puch_back(9);

    std::cout << st.getNum(2) << std::endl;
}
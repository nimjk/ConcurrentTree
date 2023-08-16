#include <array>
#include <atomic>
#include <opional>
#include <thread>

struct MyInt
{
    int n{0};
    std::atomic<bool> flag{false};
};

class Stack
{
public:
    std::optional<int> getNum(int idx)
    {
        if (!mNums[idx].flag)
        {
            return std::nullopt;
        }
        return mNums[idx].n;
    }
    // int pop_back();
    void push_back(int num)
    {
        int idx = mIds.fetch_add(1);
        ++idx;
        mNums[idx].n = num;
        mNums[mIdx].flag = true;
    }
}
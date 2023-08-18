// https://www.techiedelight.com/ko/find-minimum-maximum-value-array-cpp/

/* for문 활용
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int main()
{
    int arr[] = { 4, 2, 1, 6, -8, 5 };

    int min = INT_MAX, max = INT_MIN;
    for (int i: arr)
    {
        if (i < min) {
            min = i;
        }

        if (i > max) {
            max = i;
        }
    }

    std::cout << "The min element is " << min << endl;
    std::cout << "The max element is " << max << endl;

    return 0;
}
*/

/* 최대 최소를 pair로 반환

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int arr[] = { 4, 2, 1, 6, -8, 5 };

    std::pair<int*, int*> minmax = std::minmax_element(std::begin(arr), std::end(arr));

    std::cout << "The min element is " << *(minmax.first) << std::endl;
    std::cout << "The max element is " << *(minmax.second) << std::endl;

    return 0;
}

*/

/* 최대 최소 개별 반환
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int arr[] = { 4, 2, 1, 6, -8, 5 };

    int *min = std::min_element(std::begin(arr), std::end(arr));
    int *max = std::max_element(std::begin(arr), std::end(arr));

    std::cout << "The min element is " << *min << std::endl;
    std::cout << "The max element is " << *max << std::endl;

    return 0;
}
 */
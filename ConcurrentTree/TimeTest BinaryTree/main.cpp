#include <iostream>
#include "Binary Tree.h"
// #include <stdlib.h>
// #include <time.h>
#include <cstdlib>
#include <ctime>
// #include <afxwin.h>
// #include <unistd.h>
#include <time.h>
// using namespace chrono; // 나노 단위 시간 측정
using namespace std;

int main()
{
    BST obj;
    int option, val;

    // system_clock::time_point start_time = system_clock::now(); // 코드 시작 시간
    int arr[2000];
    // std::uniform_int_distribution<int> dis(0, 500)

    // GetTickCount() for linux
    // int count = 0;

    // unsigned long GetTickCount()
    // {
    //     struct timespec tp;

    //     clock_gettime(CLOCK_MONOTONIC, &tp);
    //     return (unsigned long)(tp.tv_sec * 1000 + tp.tv_nsec / 1000000);
    // }

    srand((unsigned int)time(NULL));
    //  cout << "from clock_gettime" << tp << endl;
    int count = 0;
    clock_t start, end;
    double duration;

    start = clock();
    while (count < 2000)
    {
        int tmp = rand() % 5000 + 1;
        int isSame = 0;

        for (int i = 0; i < 2000; i++)
        {
            if (tmp == arr[i]) // 삽입 값 중복확인
            {
                isSame = 1;
                break;
            }
        }
        if (isSame == 0)
        {
            arr[count] = tmp;
            count++;
        }
    }
    int insertcount = 0; // 어레이 값 트리에 넣어주기
    while (insertcount < 2000)
    {
        TreeNode *new_node = new TreeNode();
        new_node->value = arr[insertcount];
        obj.root = obj.insertRecursive(obj.root, new_node);
        insertcount++;
    }

    cout << "Binary Tree:" << endl;
    obj.print2D(obj.root, 3);
    // system_clock::time_point end_time = system_clock::now(); // 코드 종료시간

    // seconds sec = duration_cast<seconds>(end_time - start_time); // 시간 계산(종료-시작)

    // cout << "걸린 시간 :" << sec.count() << "seconds" << endl;
    // 인서트 된 값 보기
    // cout << "Inserted Value: \n"
    //   << insertcount << ", " << endl;

    // 지정 값 탐색 하기 (1개)
    /*
        // Node n1;
        TreeNode *new_node = new TreeNode();
        new_node = obj.iterativeSearch(val);
        new_node = obj.recursiveSearch(obj.root, val);
        if (new_node != NULL)
        {
            cout << "Value found" << endl;
        }
        else
        {
            cout << "Value NOT found" << endl;
        }

        int *min = std::min_element(std::begin(arr), std::end(arr));
        int *max = std::max_element(std::begin(arr), std::end(arr));

        std::cout << "The min element is " << *min << std::endl;
        std::cout << "The max element is " << *max << std::endl;
    */

    int searchcnt = 0;

    long double mintime, maxtime;
    long double totaltime = 0;
    long double meantime = 0;

    while (searchcnt < 100)
    {
        TreeNode *new_node = new TreeNode();
        int searchidx = rand() % 2000;
        int searchnum = rand() % 5000 + 1;

        start = clock();
        new_node = obj.recursiveSearch(obj.root, arr[searchidx]);
        if (new_node != NULL)
        {
            cout << "Value found" << endl;
        }
        else
        {
            cout << "Value NOT found" << endl;
        }

        end = clock();

        duration = (long double)(end - start) / CLOCKS_PER_SEC;

        if (searchcnt == 0)
        {
            mintime = duration;
            maxtime = duration;
        }

        else
        {
            if (mintime > duration)
            {
                mintime = duration;
            }
            else if (maxtime < duration)
            {
                maxtime = duration;
            }
        }

        totaltime += duration;

        searchcnt++;
    }

    meantime = totaltime / (searchcnt + 1);

    cout << "minimum time of search : " << fixed << mintime << "초\n";
    cout << "maximum time of search : " << maxtime << "초\n";
    cout << "total time of search : " << totaltime << "초\n";
    cout << "average time of search : " << meantime << "초\n";

    return 0;
    // 1개의 값 탐색 시간 확인

    // 1개의 값 탐색 시간 벡터에 넣기

    // 최소 탐색 시간 출력

    // 최대 탐색 시간 출력

    // 평균 탐색 시간 출력

    //--------------------------------------

    // 탐색할 값 50개 임의로 뽑기

    // 지정 값 탐색 하기 (50개) (for 문? iterator?)
    // for (int i = 0; i <= 49; ++i)
    // {
    //}

    // 50개 값 각각의 탐색 시간 확인

    // 50개 값 각각의 탐색 시간 벡터에 넣기

    // 최소 탐색 시간 출력

    // 최대 탐색 시간 출력

    // 평균 탐색 시간 출력

    // 총 탐색 시간 출력
}
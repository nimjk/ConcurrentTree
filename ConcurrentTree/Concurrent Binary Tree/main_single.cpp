#include <iostream>
#include "Binary Tree.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <time.h>
#include <mutex>
#include <vector>
using namespace std;
/*
뮤텍스 추가 생성
*/
mutex mtx;
// arry->vec
// voidInsertValueTest.cpp

// voidserchValuesTest.cpp

//
int main()
{
    BST obj;
    int option, val;
    // arr->vec
    vector<int> arr;
    // int arr[2000];

    srand((unsigned int)time(NULL));
    //  cout << "from clock_gettime" << tp << endl;
    int count = 0;
    clock_t searchstart, searchend;
    double searchduration;

    while (count < 2000)
    {
        int tmp = rand() % 5000 + 1;
        int isSame = 0;

        for (int i = 0; i < arr.size(); i++) // vector 변경지점
        {
            if (tmp == arr[i]) // 삽입 값 중복확인
            {
                isSame = 1;
                break;
            }
        }
        if (isSame == 0)
        {
            arr.push_back(tmp); // vector 변경지점
            count++;
        }
    } // 벡터 어레이 생성
    // 이진트리 만들기
    int insertcount = 0; // 어레이 값 트리에 넣어주기
    while (insertcount < 2000)
    {
        TreeNode *new_node = new TreeNode();
        new_node->value = arr[insertcount]; // 새 노드에 어레이 값 넣기
        // 재귀해서 루트노드 정하기
        obj.root = obj.insertRecursive(obj.root, new_node); //
        insertcount++;
    }

    cout << "Binary Tree:" << endl;
    obj.print2D(obj.root, 3);

    // 탐색
    int searchcnt = 0;

    long double mintime, maxtime;
    long double totaltime = 0;
    long double meantime = 0;

    // 100번 탐색
    while (searchcnt < 100)
    {
        TreeNode *new_node = new TreeNode();
        int singlethreadidx = rand() % 2000;
        int singlethreadnum = rand() % 5000 + 1;

        // 탐색시작
        searchstart = clock();
        new_node = obj.recursiveSingleThread(obj.root, singlethreadnum); // 살짝 이해안됨
        if (new_node != NULL)
        {
            cout << "Value found" << endl;
        }
        else
        {
            cout << "Value NOT found" << endl;
        }
        searchend = clock();
        // 탐색 끝
        searchduration = (long double)(searchend - searchstart) /
                         CLOCKS_PER_SEC; // 걸린 시간

        if (searchcnt == 0)
        {
            mintime = searchduration;
            maxtime = searchduration;
        }

        else
        {
            if (mintime > searchduration)
            {
                mintime = searchduration;
            }
            else if (maxtime < searchduration)
            {
                maxtime = searchduration;
            }
        }

        totaltime += searchduration;

        searchcnt++;
    }
    // 100번 탐색 종료
    meantime = totaltime / (searchcnt + 1);

    cout << "minimum time of SingleThread : " << fixed << mintime << "초\n";
    cout << "maximum time of SingleThread : " << maxtime << "초\n";
    cout << "total time of SingleThread : " << totaltime << "초\n";
    cout << "average time of SingleThread : " << meantime << "초\n";

    // 싱글스레드 실행
    // 삽입 . 삭제 2000번

    int threadcnt = 0;
    long double threadmintime, threadmaxtime;
    long double threadtotaltime = 0;
    long double threadmeantime = 0;

    while (threadcnt < 2000)
    {
        searchStart = clock();

        thread thread1([&obj]() // 숫자 변경
                       {
                    for (int j = 0; j < 2000; j++){
                        int i = rand() % 5000+1; // 숫자 변경
                        TreeNode *new_node = new_node;
                        new_node = obj.iterativeSingleThread(i);
                        if(new_node != NULL){
                            
                        unique_lock<mutex> lock(mtx);
                        obj.deleteNode(obj.root, i);
                        
                        cout << "delete working " << '\n'; // 숫자 변경
                        }
                    } 
                    for (int j = 0; j < 2000; j++)
                       {
                           int i = rand() % 8750 + 5001;
                           TreeNode *new_node1 = new TreeNode();
                           new_node1->value = i;
                           unique_lock<mutex> lock(mtx);
                           obj.insertRecursive(obj.root, new_node1);
                           cout << "insert working " << '\n'; // 숫자 변경
                       } });
        threadcnt++;
    };

    thread1.join();
    searchend = clock();

    searchduration = (long double)(searchend - searchstart) / CLOCKS_PER_SEC; // 싱글스레드 걸린 시간

    if (threadcnt == 0)
    {
        threadmintime = searchduration;
        threadmaxtime = searchduration;
    }

    else
    {
        if (threadmintime > searchduration)
        {
            threadmintime = searchduration;
        }
        else if (threadmaxtime < searchduration)
        {
            threadmaxtime = searchduration;
        }
    }

    totaltime += searchduration;

    threadmeantime = totaltime / (threadcnt + 1);

    cout << "minimum time of SingleThread : " << fixed << threadmintime << "초\n";
    cout << "maximum time of SingleThread : " << threadmaxtime << "초\n";
    cout << "total time of SingleThread : " << threadtotaltime << "초\n";
    cout << "average time of SingleThread : " << threadmeantime << "초\n";
    return 0;
}

/*
thread2.join();
thread3.join();
thread4.join();

thread thread5([&obj]() // 숫자 변경
               {
                       for (int j = 0; j < 2000; j++)
                       {
                           int i = rand() % 1250 + 8751;
                           TreeNode *new_node1 = new TreeNode();
                           new_node1->value = i;
                           unique_lock<mutex> lock(mtx);
                           obj.insertRecursive(obj.root, new_node1);
                           cout << "thread 5 working " << '\n'; // 숫자 변경
                       } });

thread thread6([&obj]() // 숫자 변경
               {
                        for(int j=0;j<500;j++){
                        int i = rand() % 1250 + 6251;
                            TreeNode *new_node2 = new TreeNode();
                            new_node2->value = i;
                            unique_lock<mutex> lock(mtx);
                            obj.insertRecursive(obj.root, new_node2);
                            cout << "thread 6 working " << '\n'; // 숫자 변경

                        } });

thread thread7([&obj]() // 숫자 변경
               {
                        for(int j=0;j<500;j++){
                        int i = rand() % 1250 + 7501;
                            TreeNode *new_node3 = new TreeNode();
                            new_node3->value = i;

                            unique_lock<mutex> lock(mtx);
                            obj.insertRecursive(obj.root, new_node3);
                            cout << "thread 7 working " << '\n'; // 숫자 변경

                        } });

thread thread8([&obj]() // 숫자 변경
               {
                        for(int j=0;j<500;j++){
                        int i = rand() % 5000 + 8751;
                            TreeNode *new_node4 = new TreeNode();
                            new_node4->value = i;

                            unique_lock<mutex> lock(mtx);
                            obj.insertRecursive(obj.root, new_node4);
                            cout << "thread 8 working " << '\n'; // 숫자 변경

                        } });

thread5.join();
thread6.join();
thread7.join();
thread8.join();


*/

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
    clock_t start, end;
    double duration;

    start = clock();
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
        int searchidx = rand() % 2000;
        int searchnum = rand() % 5000 + 1;

        // 탐색시작
        start = clock();
        new_node = obj.recursiveSearch(obj.root, searchnum); // 살짝 이해안됨
        if (new_node != NULL)
        {
            cout << "Value found" << endl;
        }
        else
        {
            cout << "Value NOT found" << endl;
        }
        end = clock();
        // 탐색 끝
        duration = (long double)(end - start) / CLOCKS_PER_SEC; // 걸린 시간

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
    // 100번 탐색 종료
    meantime = totaltime / (searchcnt + 1);

    cout << "minimum time of search : " << fixed << mintime << "초\n";
    cout << "maximum time of search : " << maxtime << "초\n";
    cout << "total time of search : " << totaltime << "초\n";
    cout << "average time of search : " << meantime << "초\n";

    // delete 멀티스레드 실행부분

    clock_t deletestart, deleteend;
    double deleteduration;

    deletestart = clock();
    thread thread1([&obj]() // 숫자 변경
                   {
                    for (int j = 0; j < 500; j++){
                        int i = rand() % 1250 + 1; // 숫자 변경
                        TreeNode *new_node = new_node;
                        new_node = obj.iterativeSearch(i);
                        if(new_node != NULL){
                            
                        unique_lock<mutex> lock(mtx);
                        obj.deleteNode(obj.root, i);
                        
                        cout << "thread 1 working " << '\n'; // 숫자 변경
                        }
                    } });

    thread thread2([&obj]() // 숫자 변경
                   {
                       for (int j = 0; j < 500; j++){
                        int i = rand() % 1250 + 1251; // 숫자 변경
                        TreeNode *new_node = new_node;
                        new_node = obj.iterativeSearch(i);
                        if(new_node != NULL){
                            
                        unique_lock<mutex> lock(mtx);
                        obj.deleteNode(obj.root, i);
                        
                       cout << "thread 2 working " << '\n'; // 숫자 변경
                        }
                    } });

    thread thread3([&obj]() // 숫자 변경
                   {
                       for (int j = 0; j < 500; j++){
                        int i = rand() % 1250 + 2501; // 숫자 변경
                        TreeNode *new_node = new_node;
                        new_node = obj.iterativeSearch(i);
                        if(new_node != NULL){
                            
                        unique_lock<mutex> lock(mtx);
                        obj.deleteNode(obj.root, i);
                        
                       cout << "thread 3 working " << '\n'; // 숫자 변경
                        }
                    } });

    thread thread4([&obj]() // 숫자 변경
                   {
                       for (int j = 0; j < 500; j++){
                        int i = rand() % 1250 + 3751; // 숫자 변경
                        TreeNode *new_node = new_node;
                        new_node = obj.iterativeSearch(i);
                        if(new_node != NULL){
                            
                        unique_lock<mutex> lock(mtx);
                        obj.deleteNode(obj.root, i);
                        
                       cout << "thread 4 working " << '\n'; // 숫자 변경
                        }
                    } });

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    end = clock();
    // delete 시간 계산
    deleteduration = (long double)(deleteend - deletestart) / CLOCKS_PER_SEC; // 걸린 시간

    cout << "delete 진행 완료\n"
         << endl;

    /*
        int threadcnt = 0;
        long double threadmintime, threadmaxtime;
        long double threadtotaltime = 0;
        long double threadmeantime = 0;
        while (threadcnt < 2000)
        {
            start = clock();

            if (threadcnt == 0)
            {
                threadmintime = duration;
                threadmaxtime = duration;
            }

            else
            {
                if (threadmintime > duration)
                {
                    threadmintime = duration;
                }
                else if (threadmaxtime < duration)
                {
                    threadmaxtime = duration;
                }
            }

            totaltime += duration;
        }

        // 100번 탐색 종료
        meantime = totaltime / (searchcnt + 1);

        cout << "minimum time of search : " << fixed << mintime << "초\n";
        cout << "maximum time of search : " << maxtime << "초\n";
        cout << "total time of search : " << totaltime << "초\n";
        cout << "average time of search : " << meantime << "초\n";
        */

    // insert 멀티스레드 실행 부분
    clock_t insertstart, insertend;
    double insertduration;

    insertstart = clock();

    thread thread5([&obj]() // 숫자 변경
                   {
                       for (int j = 0; j < 500; j++)
                       {
                           int i = rand() % 1250 + 5001;
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

    insertend = clock();
    // insert 멀티스레드 시간 계산
    insertduration = (long double)(insertend - insertstart) / CLOCKS_PER_SEC; // 걸린 시간

    return 0;
}
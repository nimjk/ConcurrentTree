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
        new_node = obj.recursiveSearch(obj.root, searchnum);
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

    /* chat GPT 방식
        thread t1(searchValues, ref(obj), ref(arr)); // 스레드 1 - 검색
        thread t2(insertValues, ref(obj), ref(arr)); // 스레드 2 - 삽입
        thread t3(deleteValues, ref(obj), ref(arr)); // 스레드 3 - 삭제

        t1.join();
        t2.join();
        t3.join();

        */

    thread thread1([&obj]() // 숫자 변경
                   {
                       int i = rand() % 1250 + 1; // 숫자 변경
                       TreeNode *new_node = obj.iterativeSearch(i);
                       if (new_node != NULL)
                       {
                           unique_lock<mutex> lock(mtx);
                           obj.deleteNode(obj.root, i);
                       }
                       cout << "thread 1 working " << '\n'; // 숫자 변경
                   });

    thread thread2([&obj]() // 숫자 변경
                   {
                       int i = rand() % 1250 + 1250; // 숫자 변경
                       TreeNode *new_node = obj.iterativeSearch(i);
                       if (new_node != NULL)
                       {
                           unique_lock<mutex> lock(mtx);
                           obj.deleteNode(obj.root, i);
                       }
                       cout << "thread 2 working " << '\n'; // 숫자 변경
                   });

    thread thread3([&obj]() // 숫자 변경
                   {
                       int i = rand() % 1250 + 2500; // 숫자 변경
                       TreeNode *new_node = obj.iterativeSearch(i);
                       if (new_node != NULL)
                       {
                           unique_lock<mutex> lock(mtx);
                           obj.deleteNode(obj.root, i);
                       }
                       cout << "thread 3 working " << '\n'; // 숫자 변경
                   });

    thread thread4([&obj]() // 숫자 변경
                   {
                       int i = rand() % 1250 + 3750; // 숫자 변경
                       TreeNode *new_node = obj.iterativeSearch(i);
                       if (new_node != NULL)
                       {
                           unique_lock<mutex> lock(mtx);
                           obj.deleteNode(obj.root, i);
                       }
                       cout << "thread 4 working " << '\n'; // 숫자 변경
                   });

    int deletethreadcount = 0;
    while (deletethreadcount < 2000)
    {
        thread5.join();
        deletethreadcount++;
        thread6.join();
        deletethreadcount++;
        thread7.join();
        deletethreadcount++;
        thread8.join();
        deletethreadcount++;
    }

    thread thread5([&obj]() // 숫자 변경
                   {
                       int i = rand() % 5000 + 5001;
                       TreeNode *new_node = obj.iterativeSearch(i);
                       if (new_node == NULL)
                       {
                           unique_lock<mutex> lock(mtx);
                           obj.insertRecursive(obj.root, new_node);
                       }
                       cout << "thread 5 working " << '\n'; // 숫자 변경
                   });

    thread thread6([&obj]() // 숫자 변경
                   {
                       int i = rand() % 5000 + 5001;
                       TreeNode *new_node = obj.iterativeSearch(i);
                       if (new_node == NULL)
                       {
                           unique_lock<mutex> lock(mtx);
                           obj.insertRecursive(obj.root, new_node);
                       }
                       cout << "thread 6 working " << '\n'; // 숫자 변경
                   });

    thread thread7([&obj]() // 숫자 변경
                   {
                       int i = rand() % 5000 + 5001;
                       TreeNode *new_node = obj.iterativeSearch(i);
                       if (new_node == NULL)
                       {
                           unique_lock<mutex> lock(mtx);
                           obj.insertRecursive(obj.root, new_node);
                       }
                       cout << "thread 7 working " << '\n'; // 숫자 변경
                   });

    thread thread8([&obj]() // 숫자 변경
                   {
                       int i = rand() % 5000 + 5001;
                       TreeNode *new_node = obj.iterativeSearch(i);
                       if (new_node == NULL)
                       {
                           unique_lock<mutex> lock(mtx);
                           obj.insertRecursive(obj.root, new_node);
                       }
                       cout << "thread 8 working " << '\n'; // 숫자 변경
                   });

    int insertthreadcount = 0;
    while (insertthreadcount < 2000)
    {
        thread5.join();
        insertthreadcount++;
        thread6.join();
        insertthreadcount++;
        thread7.join();
        insertthreadcount++;
        thread8.join();
        insertthreadcount++;
    }
    /*
    thread thread2([&obj]()
                   {
                           for (int i = 1000; i < 1500; i++)
                           {
                               insertValues(obj.root, i);
                               cout << "thread 2: " << '\n';
                           } });

    thread thread2([&obj]()
                   {
                           for (int i = 1500; i < 2000; i++)
                           {
                               deleteValues(obj.root, i);
                               cout << "thread 3: " << '\n';
                           } });
    thread thread2([&obj]()
                   {
                           for (int i = 2000; i < 2500; i++)
                           {
                               deleteValues(obj.root, i);
                               cout << "thread 3: " << '\n';
                           } });

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    cout << "Binary Tree: " << end;
    obj.print2D(obj.root, 3);
*/
    //
    // mutex mtx;
    // thread thread1([&obj]()
    //                {
    //                 for (int i = 0; i < 1000; i++)
    //     {
    //         mtx.lock();
    //         TreeNode *new_node = new TreeNode();
    //          new_node->value = rand()%5000+5001;

    //         obj.root=obj.insertRecursive(obj.root,new_node);
    //         mtx.unlock();
    //         cout << "1번 스레드 호출" << '\n';
    //     } });

    // thread thread2([&obj]()
    //                {
    //                 for (int i = 1000; i<2000; i++)
    //     {

    //         TreeNode *new_node = new TreeNode();
    //         new_node->value = rand()%5000+1;

    //         mtx.lock();
    //         if (new_node != NULL) {
    //             obj.deleteNode(obj.root, new_node);
    //             cout << "Value Deleted" << endl;
    //         }
    //         else {
    //             cout << "Value NOT found" << endl;
    //         }
    //         mtx.unlock();
    //         cout << "2번 스레드 호출" << '\n';
    //     } });

    // thread2.join(); // 스레드 종료 대기

    // // delete new_node; // 메모리 해제
    //  //thread thread2([arr]()
    //                 { dll.insertNode(2); });
    //  //thread thread3([arr]()
    //                 { dll.insertNode(3); });
    //  // thread thread4([arr]()
    //  {
    //      dll.deleteNode(1);

    // thread2.join();
    // thread3.join();
    // thread4.join();

    return 0;
}
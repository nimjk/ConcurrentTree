#include <iostream>
#include "Binary Tree.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <time.h>
#include <mutex>
using namespace std;

// arry->vec
void insertValues(BST &obj, TreeNode *new_node, const vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        TreeNode *new_node = new TreeNode();
        new_node->value = arr[i];
        obj.insertRecursive(obj.root, new_node);
    }
}

void deleteValues(BST &obj, TreeNode *new_node, const vector<int> &arr)
{
    int val;
    for (int i = 0; i < arr.size(); i++)
    {
        TreeNode *new_node = obj.iterativeSearch(val);
        new_node = obj.iterativeSearch(val);
        if (new_node != NULL)
        {
            obj.deleteNode(obj.root, val);
            cout << "Value Deleted" << endl;
        }
        else
        {
            cout << "Value NOT found" << endl;
        }
    }
}
//
int main()
{
    BST obj;
    int option, val;
    // arr->vec
    vector<int> arr;
    // int arr[2000];

    srand((unsigned int)time(NULL));

    int count = 0;
    clock_t start, end;
    double duration;

    start = clock();
    while (count < 2000)
    {
        int tmp = rand() % 5000 + 1;
        int isSame = 0;

        for (int i = 0; i < arr.size(); i++) // 변경
        {
            if (tmp == arr[i]) // 삽입 값 중복확인
            {
                isSame = 1;
                break;
            }
        }
        if (isSame == 0)
        {
            arr.push_back(tmp);       // 변경
            insertValues(&obj, &arr); // 위에 void insertValues 함수 생성
            count++;
        }
    }

    cout << "Binary Tree:" << endl;
    obj.print2D(obj.root, 3);

    deleteValues(obj, arr);
}

/*
 ✘ kyojinku@Jane-MacBook-Pro  ~/Documents/GitHub/ConcurrentTree/ConcurrentTree/Async BinaryTree  ⇅ kyojin ±  cd "/Users/kyojinku/Documents/GitHub/ConcurrentTree/ConcurrentTree/Async BinaryTree/" && g++ voidInsertValuesTest.cpp -o voidInsertValuesTest && "/Users/kyojinku/Documents/GitHub/ConcurrentTre
e/ConcurrentTree/Async BinaryTree/"voidInsertValuesTest
voidInsertValuesTest.cpp:53:13: error: no matching function for call to 'insertValues'
            insertValues(&obj, &arr); // 위에 void insertValues 함수 생성
            ^~~~~~~~~~~~
voidInsertValuesTest.cpp:11:6: note: candidate function not viable: requires 3 arguments, but 2 were provided
void insertValues(BST &obj, TreeNode *new_node, const vector<int> &arr)
     ^
1 error generated.
*/
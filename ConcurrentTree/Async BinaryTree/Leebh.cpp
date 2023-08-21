#pragma once

#define SPACE 10

#include <mutex>

using namespace std;

class TreeNode

{

public:
        int value;
       

    TreeNode *left;

        TreeNode *right;

     

   


    TreeNode()

   
    {

                value = 0;

                left = NULL;

                right = NULL;

           
    }

        TreeNode(int v)

   
    {

                value = v;

                left = NULL;

                right = NULL;

           
    }
};

class BST

{

private:
     

    mutex treeMtx;

public:
        TreeNode *root;

        BST()

   
    {

                root = NULL;

           
    }

        bool isTreeEmpty()

   
    {

                if (root == NULL)

       
        {

                        return true;

                   
        }

                else

                   
        {

                        return false;

                   
        }

           
    }

        void insertNode(TreeNode *new_node)

   
    {

                unique_lock<mutex> treeLock(treeMtx);

           

           

        if (root == NULL) // 루트 노드가 비어있으면 , 루트에 받은 노드의 값을 넣음

       
        {

                        root = new_node;

                        cout << "Value Inserted as root node!" << endl;

                   
        }

                else

                   
        {

                        TreeNode *temp = root;

                        while (temp != NULL)

           
            {

                                if (new_node->value == temp->value)

               
                {

                                        cout << "Value Already exist,"

                         << "Insert another value!" << endl;

                                        return;

                                   
                }

                                else if ((new_node->value < temp->value) && (temp->left == NULL))

               
                {

                                        temp->left = new_node;

                                        cout << "Value Inserted to the left!" << endl;

                                        break;

                                   
                }

                                else if (new_node->value < temp->value)

               
                {

                                        temp = temp->left;

                                   
                }

                                else if ((new_node->value > temp->value) && (temp->right == NULL))

               
                {

                                        temp->right = new_node;

                                        cout << "Value Inserted to the right!" << endl;

                                        break;

                                   
                }

                                else

                                   
                {

                                        temp = temp->right;

                                   
                }

                           
            }

                   
        }

           
    }

        TreeNode *insertRecursive(TreeNode *r, TreeNode *new_node)

   
    {

                if (r == NULL)

       
        {

                        r = new_node;

                        cout << "Insertion successful" << endl;

                        return r;

                   
        }

                if (new_node->value < r->value)

       
        {

                        r->left = insertRecursive(r->left, new_node);

                   
        }

                else if (new_node->value > r->value)

       
        {

                        r->right = insertRecursive(r->right, new_node);

                   
        }

                else

                   
        {

                        cout << "No duplicate values allowed!" << endl;

                        return r;

                   
        }

                return r;

           
    }

        void print2D(TreeNode *r, int space)

   
    {

                if (r == NULL) // Base case  1

            return;

                space += SPACE;
                  // Increase distance between levels   2

        print2D(r->right, space); // Process right child first 3

                cout << endl;

                for (int i = SPACE; i < space; i++) // 5

            cout << " ";
                            // 5.1

        cout << r->value << "\n";
                  // 6

        print2D(r->left, space);
                    // Process left child  7

   
    }

        void printPreorder(TreeNode *r) //(current node, Left, Right)

   
    {

                if (r == NULL)

            return;

                /* first print data of node */

        cout << r->value << " ";

                /* then recur on left sutree */

        printPreorder(r->left);

                /* now recur on right subtree */

        printPreorder(r->right);

           
    }

        void printInorder(TreeNode *r) //  (Left, current node, Right)

   
    {

                if (r == NULL)

            return;

                /* first recur on left child */

        printInorder(r->left);

                /* then print the data of node */

        cout << r->value << " ";

                /* now recur on right child */

        printInorder(r->right);

           
    }

        void printPostorder(TreeNode *r) //(Left, Right, Root)

   
    {

                if (r == NULL)

            return;

                // first recur on left subtree

        printPostorder(r->left);

                // then recur on right subtree

        printPostorder(r->right);

                // now deal with the node

        cout << r->value << " ";

           
    }

        TreeNode *iterativeSearch(int v)

   
    {

                if (root == NULL)

       
        {

                        return root;

                   
        }

                else

                   
        {

                        TreeNode *temp = root;

                        while (temp != NULL)

           
            {

                                if (v == temp->value)

               
                {

                                        return temp;

                                   
                }

                                else if (v < temp->value)

               
                {

                                        temp = temp->left;

                                   
                }

                                else

                                   
                {

                                        temp = temp->right;

                                   
                }

                           
            }

                        return NULL;

                   
        }

           
    }

        TreeNode *recursiveSearch(TreeNode *r, int val)

   
    {

                if (r == NULL || r->value == val)

            return r;

                else if (val < r->value)

            return recursiveSearch(r->left, val);

                else

                        return recursiveSearch(r->right, val);

           
    }

        int height(TreeNode *r)

   
    {

                if (r == NULL)

            return -1;

                else

                   
        {

                        /* compute the height of each subtree */

            int lheight = height(r->left);

                        int rheight = height(r->right);

                        /* use the larger one */

            if (lheight > rheight)

                return (lheight + 1);

                        else

                                return (rheight + 1);

                   
        }

           
    }

        /* Print nodes at a given level */

    void printGivenLevel(TreeNode *r, int level)

   
    {

                if (r == NULL)

            return;

                else if (level == 0)

            cout << r->value << " ";

                else // level > 0

       
        {

                        printGivenLevel(r->left, level - 1);

                        printGivenLevel(r->right, level - 1);

                   
        }

           
    }

        void printLevelOrderBFS(TreeNode *r)

   
    {

                int h = height(r);

                for (int i = 0; i <= h; i++)

            printGivenLevel(r, i);

           
    }

        TreeNode *minValueNode(TreeNode *node)

   
    {

                TreeNode *current = node;

                /* loop down to find the leftmost leaf */

        while (current->left != NULL)

       
        {

                        current = current->left;

                   
        }

                return current;

           
    }

        TreeNode *deleteNode(TreeNode *r, int v)

   
    {

                unique_lock<mutex> treeLock(treeMtx);

                // base case

        if (r == NULL)

       
        {

                        return NULL;

                   
        }

                // If the key to be deleted is smaller than the root's key,

        // then it lies in left subtree

        else if (v < r->value)

       
        {

                        r->left = deleteNode(r->left, v);

                   
        }

                // If the key to be deleted is greater than the root's key,

        // then it lies in right subtree

        else if (v > r->value)

       
        {

                        r->right = deleteNode(r->right, v);

                   
        }

                // if key is same as root's key, then This is the node to be deleted

        else

                   
        {

                        // node with only one child or no child

            if (r->left == NULL)

           
            {

                                TreeNode *temp = r->right;

                                delete r;

                                return temp;

                           
            }

                        else if (r->right == NULL)

           
            {

                                TreeNode *temp = r->left;

                                delete r;

                                return temp;

                           
            }

                        else

                           
            {

                                // node with two children: Get the inorder successor (smallest

                // in the right subtree)

                TreeNode *temp = minValueNode(r->right);

                                // Copy the inorder successor's content to this node

                r->value = temp->value;

                                // Delete the inorder successor

                r->right = deleteNode(r->right, temp->value);

                                // deleteNode(r->right, temp->value);

           
            }

                   
        }

                return r;

           
    }
};

-- -- --

#include <iostream>

#include "Binary Tree.h"

#include <cstdlib>

#include <ctime>

#include <thread>

#include <time.h>

#include <mutex>

#include <vector>

      using namespace std;

int main()

{

        BST obj;

        int option, val;

        vector<int> arr;

        srand((unsigned int)time(NULL));

        int count = 0;

        clock_t start, end;

        double duration;

        start = clock();

        while (count < 2000)

   
    {

                int tmp = rand() % 5000 + 1;

                int isSame = 0;

                for (int i = 0; i < arr.size(); i++)

       
        {

                        if (tmp == arr[i])

           
            {

                                isSame = 1;

                                break;

                           
            }

                   
        }

                if (isSame == 0)

       
        {

                        arr.push_back(tmp);

                        count++;

                   
        }

           
    }

        int insertcount = 0;

        while (insertcount < 2000)

   
    {

                TreeNode *new_node = new TreeNode();

                new_node->value = arr[insertcount];

                obj.root = obj.insertRecursive(obj.root, new_node);

                insertcount++;

           
    }

       


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

        cout << "minimum time of search : " << fixed << mintime << "sec\n";

        cout << "maximum time of search : " << maxtime << "sec\n";

        cout << "total time of search : " << totaltime << "sec\n";

        cout << "average time of search : " << meantime << "sec\n";

        //

   

    thread thread1([&obj]()
                    {

        for (int i = 500; i < 1000; i++)

        {

            obj.deleteNode(obj.root, i);

            cout << "thread 1:" << '\n';

        }

    });

        thread thread2([&obj]()
                       {

        for (int i = 1000; i < 1500; i++)

        {

            obj.deleteNode(obj.root, i);

            cout << "thread 2:" << '\n';

        }

    });

        thread thread3([&obj]()
                       {

        for (int i = 1500; i < 2000; i++)

        {

            obj.deleteNode(obj.root, i);

            cout << "thread 3:" << '\n';

        }

        });

        thread thread4([&obj]()
                       {

        for (int i = 2000; i < 2500; i++)

        {

            obj.deleteNode(obj.root, i);

            cout << "thread 4:" << '\n';

        }

        });

        thread1.join();

        thread2.join();

        thread3.join();

        thread4.join();

        cout << "Binary Tree:" << endl;

        obj.print2D(obj.root, 3);

        // delete new_node;

    //  //thread thread2([arr]()

    //                 { dll.insertNode(2); });

    //  //thread thread3([arr]()

    //                 { dll.insertNode(3); });

    //  // thread thread4([arr]()

    //  {

    //      dll.deleteNode(1);


    // thread2.join();

    // thread3.join();

    // thread4.join();


    return 0;
}

맨위로

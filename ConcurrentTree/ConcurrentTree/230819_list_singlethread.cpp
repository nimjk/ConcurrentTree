#include <iostream>
#include "list_final.hpp"


using namespace std;



int main(void) {
    DoublyLinkedList<int> dll; // list ����� �̸� ����

    clock_t start, end;
    double duration;
    start = clock();


    srand(GetTickCount64());  // ������ 2õ���� ���� ����.
    int arr[2000];
    int count = 0;

    while (count < 2000) {
        int tmp = rand() % 5000 + 1;
        int isSame = 0;
        for (int i = 0; i < count; i++) {
            if (tmp == arr[i]) {
                isSame = 1;
                break;
            }
        }
        if (isSame == 0) {      // �ߺ��� ��� �Ÿ��� insert
            arr[count] = tmp;
            dll.insertNode(arr[count]);
            count++;
        }
    }
    end = clock();
    //���۰� �� �ð��� �̿��� list�� insert �ð� ���
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time of generation list : " << duration << "��\n";





    int searchcnt = 0;

    clock_t start5, end5;
    double duration5;

    double mintime, maxtime;
    double totaltime = 0;
    double meantime = 0;


    while (searchcnt < 100) {
        int searchidx = rand() % 2000;
        int searchnum = rand() % 5000 + 1;

        start5 = clock();
        dll.search(searchnum); // 
        end5 = clock();

        duration5 = (double)(end5 - start5) / CLOCKS_PER_SEC;

        if (searchcnt == 0) {
            mintime = duration5;
            maxtime = duration5;
        }

        else {
            if (mintime > duration5) {
                mintime = duration5;
            }
            else if (maxtime < duration5) {
                maxtime = duration5;
            }
        }

        totaltime += duration5;

        searchcnt++;
    }

    meantime = totaltime / (searchcnt + 1);





    //��Ƽ�����带 �̿��� ���� ����

    clock_t start4, end4;
    double duration4;
    start4 = clock();

    int arr9[2000];
    int count9 = 0;

    while (count9 < 2000) {
        int tmp9 = rand() % 5000 + 1;
        int isSame9 = 0;
        for (int i = 0; i < count9; i++) {
            if (tmp9 == arr[i]) {
                isSame9 = 1;
                break;
            }
        }
        if (isSame9 == 0) {      // �ߺ��� ��� �Ÿ��� insert
            arr9[count9] = tmp9;
            dll.deleteNode(arr9[count9]);
            count9++;
        }
    }



    end4 = clock();
    duration4 = (double)(end4 - start4) / CLOCKS_PER_SEC;

    cout << "�߰� delete ���� �Ϸ�\n";


    dll.displayList();






    cout << "minimum time of search : " << fixed << mintime << "��\n";
    cout << "maximum time of search : " << maxtime << "��\n";
    cout << "total time of search : " << totaltime << "��\n";
    cout << "average time of search : " << meantime << "��\n";


    cout << "Time of single generation list : " << fixed << duration << "��\n";

    cout << "Time of single delete list : " << duration4 << "��\n";
    cout << '\n';

    return 0;
}




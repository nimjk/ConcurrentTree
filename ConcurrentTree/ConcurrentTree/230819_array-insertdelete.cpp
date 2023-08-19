#include <iostream>
#include "final.hpp"


using namespace std;



int main() {
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

    clock_t start2, end2;
    double duration2;
    start2 = clock();
    thread thread1([&dll]() {
        for (int i = 4500; i < 5000; i++)
        {
            dll.deleteNode(i);
            cout << "1�� ������ ȣ��" << '\n';
        }
    });
    thread thread2([&dll]() {
        for (int i = 4000; i < 4500; i++)
        {
            dll.deleteNode(i);
            cout << "2�� ������ ȣ��" << '\n';
        }
        });
    thread thread3([&dll]() {
        for (int i = 3500; i < 4000; i++)
        {
            dll.deleteNode(i);
            cout << "3�� ������ ȣ��" << '\n';
        }

        });
    thread thread4([&dll]() {
        for (int i = 3000; i < 3500; i++)
        {
            dll.deleteNode(i);
            cout << "4�� ������ ȣ��" << '\n';
        }
    });


    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    end2 = clock();
    duration2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

    cout << "delete ���� �Ϸ�\n";
    
    clock_t start3, end3;
    double duration3;
    start3 = clock();


    thread thread5([&dll]() {
        int arr5[500];
        int count5 = 0; 
        
        srand(GetTickCount64());  // ������ 500���� ���� ����.
           
        while (count5 < 500) {
            int tmp5 = rand() % 5000 + 5001;
            int isSame5 = 0;
            for (int i = 0; i < count5; i++) {
                if (tmp5 == arr5[i]) {
                    isSame5 = 1;
                    break;
                }
            }
            if (isSame5 == 0) {      // �ߺ��� ��� �Ÿ��� insert
                arr5[count5] = tmp5;
                dll.insertNode(arr5[count5]);
                count5++;
            }
        }
        
    });

    thread thread6([&dll]() {
        int arr6[500];
        int count6 = 0;

        srand(GetTickCount64());  // ������ 500���� ���� ����.

        while (count6 < 500) {
            int tmp6 = rand() % 5000 + 5001;
            int isSame6 = 0;
            for (int i = 0; i < count6; i++) {
                if (tmp6 == arr6[i]) {
                    isSame6 = 1;
                    break;
                }
            }
            if (isSame6 == 0) {      // �ߺ��� ��� �Ÿ��� insert
                arr6[count6] = tmp6;
                dll.insertNode(arr6[count6]);
                count6++;
            }
        }

    });

    thread thread7([&dll]() {
        int arr7[500];
        int count7 = 0;

        srand(GetTickCount64());  // ������ 500���� ���� ����.
        
        while (count7 < 500) {
            int tmp7 = rand() % 5000 + 5001;
            int isSame7 = 0;
            for (int i = 0; i < count7; i++) {
                if (tmp7 == arr7[i]) {
                    isSame7 = 1;
                    break;
                }
            }
            if (isSame7 == 0) {      // �ߺ��� ��� �Ÿ��� insert
                arr7[count7] = tmp7;
                dll.insertNode(arr7[count7]);
                count7++;
            }
        }
    }); 
    thread thread8([&dll]() {
        int arr8[500];
        int count8 = 0;

        srand(GetTickCount64());  // ������ 500���� ���� ����.

        while (count8 < 500) {
            int tmp8 = rand() % 5000 + 5001;
            int isSame8 = 0;
            for (int i = 0; i < count8; i++) {
                if (tmp8 == arr8[i]) {
                    isSame8 = 1;
                    break;
                }
            }
            if (isSame8 == 0) {      // �ߺ��� ��� �Ÿ��� insert
                arr8[count8] = tmp8;
                dll.insertNode(arr8[count8]);
                count8++;
            }
        }
    });
  
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();

    end3 = clock();
    //���۰� �� �ð��� �̿��� list�� insert �ð� ���
    duration3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
   




    
    cout << "�߰� insert ���� �Ϸ� \n";



    //��Ƽ�����带 �̿��� ���� ����

    clock_t start4, end4;
    double duration4;
    start4 = clock();
    for (int j = 0; j < 4; j++)
    {
        for (int i = 8001; i < 10000; i++)
        {
            dll.deleteNode(i);
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


    cout << "Time of single generation list : " << fixed <<  duration << "��\n";
    cout << "Time of multithread delete list : " << duration2 << "��\n";
    cout << "Time of multithread generation list : " << duration3 << "��\n";
    cout << "Time of single delete list : " << duration4 << "��\n";
    cout << '\n';
   
    return 0;
}




#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>
using namespace std;

struct Item {
	int index;
	int value;

	Item(int idx, int val) : index(idx), value(val) {}
};
list<int> my_list;
mutex my_mutex;

void ThreadFunction(int value)
{
	lock_guard<mutex> lock(my_mutex);

	my_list.push_back(value);
	cout << "value : " << value << " inserted. " << '\n';
}

void ThreadFunctionUnique(int value)
{
	unique_lock<mutex> lock(my_mutex);
	my_list.push_back(value);
	cout << "value : " << value << " inserted. " << '\n';
}


int main(void) {
	
	chrono::system_clock::time_point start = chrono::system_clock::now();
	thread t1(ThreadFunction, 1);
	thread t2(ThreadFunction, 2);
	thread t3(ThreadFunction, 3);
	thread t4(ThreadFunction, 4);	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	
	chrono::duration<double>sec = chrono::system_clock::now() - start;
	
	cout << sec.count() << "\n";



	chrono::system_clock::time_point start2 = chrono::system_clock::now();

	thread t5(ThreadFunctionUnique, 1);
	thread t6(ThreadFunctionUnique, 2);
	thread t7(ThreadFunctionUnique, 3);
	thread t8(ThreadFunctionUnique, 4);
	t5.join();
	t6.join();
	t7.join();
	t8.join();

	chrono::duration<double>sec2 = chrono::system_clock::now() - start2;

	cout << sec2.count() << "\n";



	return 0;
}

// unique_lock 과 lock_guard 사이의 시간은 별 차이가 없음
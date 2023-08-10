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

void ThreadFunction2(int index, int value) { // 자료의 넣는 순서를 명시하면 되지 않을까? 
	unique_lock<mutex> lock(my_mutex);
	my_list.emplace_back(index, value);
	cout << "index : " << index << "and value: " << value << "inserted. " << "\n";
	my_list.sort([](const Item& A, const Item& B) {
		return A.index < A.index;
		});
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



	chrono::system_clock::time_point start3 = chrono::system_clock::now();
	thread t9(ThreadFunction2, 0, 1);
	thread t10(ThreadFunction2, 1, 2);
	thread t11(ThreadFunction2, 2, 3);
	thread t12(ThreadFunction2, 3, 4);
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	for (auto it = my_list.front() ; it != my_list.back(); it++)
	{
		cout << it;
	}
	chrono::duration<double>sec3 = chrono::system_clock::now() - start3;

	cout << sec3.count();

	return 0;
}

// unique_lock 과 lock_guard 사이의 시간은 별 차이가 없음
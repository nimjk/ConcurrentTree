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
list<Item> my_list;
mutex my_mutex;

void ThreadFunction2(int index, int value) { // 자료의 넣는 순서를 명시하면 되지 않을까? 
	unique_lock<mutex> lock(my_mutex);
	my_list.emplace_back(index, value);
	cout << "index : " << index << "and value: " << value << "inserted. " << "\n";
	my_list.sort([](const Item& A, const Item& B) {
		return A.index < B.index;
		});
}
int main(void) {




	chrono::system_clock::time_point start3 = chrono::system_clock::now();
	thread t9(ThreadFunction2, 0, 1);
	thread t10(ThreadFunction2, 1, 2);
	thread t11(ThreadFunction2, 2, 3);
	thread t12(ThreadFunction2, 3, 4);
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	for (auto it = my_list.begin(); it != my_list.end(); it++)
	{
		cout << it->value << '\n';
	}
	chrono::duration<double>sec3 = chrono::system_clock::now() - start3;

	cout << sec3.count() << '\n';


}
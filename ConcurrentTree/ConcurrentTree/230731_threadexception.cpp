#include <iostream>
#include <thread>
using namespace std;

void doSomeWork()
{
	for (int i = 0; i < 5; ++i)
	{
		cout << i << endl;
	}
	cout << "Thread throwing a runtime_error exception..." << endl;
	throw runtime_error("Exception from Thread");
}


void threadFunc(exception_ptr& err)
{
	try {
		doSomeWork();
	}
	catch (...) {
		cout << "Thread caught exception, returning exception..." << endl;
		err = current_exception();
	}
}

void doWorkInThread()
{
	exception_ptr error; // 따로 빼는 이유는 메인 스레드에서 예외처리하기 위함.
	//스레드를 구동함
	thread t{ threadFunc, ref(error) };
	thread t2{ threadFunc, ref(error) };
	//스레드가 종료할떄까지 기다림.
	t.join();
	t2.join();
	//스레드에 익셉션이 발생했는지 검사
	if (error) {
		cout << "Main thread received exception, rethrowing it..." << endl;
		rethrow_exception(error);
	}
	else {
		cout << "Main thread did not receive any exception." << endl;
	}
}

int main()
{
	try {
		doWorkInThread();
	}
	catch (const exception& e) {
		cout << "Main function caught: '" << e.what() << "'" << endl;
	}
} // 전문가를 위한 C++ 23장 1142~1144p 예제
// 예외가 발생할때, 따로 정리해두고 마지막에 
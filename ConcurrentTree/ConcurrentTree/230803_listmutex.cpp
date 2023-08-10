#include <iostream>
#include <mutex>
using namespace std;

template <typename T>
class Node { 
public:
	T data; 
	Node* next; 
	Node* prev;

	template <typename T>
	Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
	//이니셜라이저로 노드 구현.
};


template <typename T>
class dlist { 
private:
	Node<T>* head; 
	Node<T>* tail;
	size_t count; 
public:

	dlist() : head(nullptr), tail(nullptr), count(0) {} 

	dlist(const dlist& other) : head(nullptr), tail(nullptr), count(0)
	{				
		Node<T>* cur = other.head;
		while (cur != nullptr)
		{
			push_back(cur->data); 
			cur = cur->next;
		}
	}



	void push_back(const T& value)
	{
		Node<T>* newNode = new Node<T>(value); 
		if (head == nullptr) 
		{
			head = newNode; 
			tail = newNode;
		}
		else
		{
			tail->next = newNode; 
			newNode->prev = tail;
			tail = newNode;
		}
		count++;
	}


	void push_front(const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		count++;
	}

	void pop_back() {
		if (tail == nullptr) return; 

		if (head == tail) {  
			delete tail;
			head = tail = nullptr;
		}
		else {
			Node<T>* prevNode = tail->prev; 
			prevNode->next = nullptr; 
			delete tail; 
			tail = prevNode; 
		}
		count--;
	}

	void pop_front() {
		if (head == nullptr) return;

		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		else {
			Node<T>* nextNode = head->next;
			nextNode->prev = nullptr;
			delete head;
			head = nextNode;
		}
		count--;
	}




	void print_list() const {

		Node<T>* cur = head;	
		while (cur != nullptr) {	
			cout << cur->data << " "; 
			cur = cur->next; 
		}
		cout << endl;  
	}

	void get_size() const {
		cout << count;
	}

};



int main(void)
{
	dlist <int> lis;
	lis.push_back(2);
	lis.push_back(2);
	lis.push_front(3);
	lis.push_front(4);
	lis.print_list();

	lis.pop_back();
	lis.pop_front();

	lis.print_list();
	lis.get_size();



	return 0;
}
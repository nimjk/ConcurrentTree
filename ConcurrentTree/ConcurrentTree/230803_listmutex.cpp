#include <iostream>
#include <mutex>
using namespace std;

template <typename T>
class Node { // ��� Ŭ���� ����
public:
	T data; // data�� ����
	Node* next; //���� �κ��� ����Ű�� �ּҸ� ��������� ����
	Node* prev; //�� �κ��� ����Ű�� �ּҸ� ��������� ����

	template <typename T>
	Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
	//�̴ϼȶ������� ��� ����.
};


template <typename T>
class list_bh { //����_����Ʈ ����
private:
	Node<T>* head; // ����� �ּҸ� ���� head tail��� ����.
	Node<T>* tail;
	size_t count; // List�� ũ�⸦ ���ϱ� ���� count ����
public:

	list_bh() : head(nullptr), tail(nullptr), count(0) {} //�⺻ ������

	list_bh(const list_bh& other) : head(nullptr), tail(nullptr), count(0)
	{				//���� ������. "���� ����"�� ���� & ���
		Node<T>* cur = other.head;
		while (cur != nullptr)
		{
			push_back(cur->data); // push_back�� ���� ����Լ��� �����Ұ�
			cur = cur->next;
		}
	}



	void push_back(const T& value)
	{
		Node<T>* newNode = new Node<T>(value); // ���ο� ��� ����Ʈ ����
		if (head == nullptr) // ���� �����Ͱ� 0�����
		{
			head = newNode; // ���ο� ������ ����. head�� tail�� �Ѵ� newNode�� ����Ŵ
			tail = newNode;
		}
		else
		{
			tail->next = newNode; // �����Ͱ� �־��ٸ� next�� newNode�� ���� (�� head�� ���ο� ����� point)
			newNode->prev = tail; // �� ����� prev���� tail�� �ּ�(�� ��� point)�� ����Ŵ.
			tail = newNode; // ������ newNode�� ���Ž�Ŵ
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
		if (tail == nullptr) return; // ����Ʈ�� ��������� �ƹ��͵� �������� �ʰ� ��������

		if (head == tail) {    //����Ʈ�� �ϳ��� ��常 �����ϴ� ���.
			delete tail;
			head = tail = nullptr;
		}
		else {
			Node<T>* prevNode = tail->prev; // ����Ʈ�� 2�� �̻��� ��� ����. tail�� ���� prevNode�� ����
			prevNode->next = nullptr; // prevNode�� next�� ����
			delete tail; // ������ ���� ������ ������ ����
			tail = prevNode; //  ���Ӱ� ������ ���� (next�� null tail�� prevNode)�� tail ����
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

		Node<T>* cur = head;	 //��� ����Ʈ �ϳ��� head�� ����
		while (cur != nullptr) {	// ��尡 nullptr�� �ƴϸ�
			cout << cur->data << " "; // ������ data ������ ���
			cur = cur->next;  // ���� ���� �ű�
		}
		cout << endl;   // ���� hpp�� cpp������ �и��� �� std::cout / std::endl�� ���� �˾ƺ���.
	}

	void get_size() const {
		cout << count; // �Լ����� count�Ǵ� ���� ����� 
	}


	Node<T>* begin() { // ����Ʈ�� ù �κ��� �����ͷ� ��ȯ�ϴ� �Լ�. auto iterator�� ��������
		return head;
	}


	Node<T>* end() { //����Ʈ�� ���κ� ��ȯ�Լ�
		return nullptr;
	}


};



int main(void)
{
	list_bh <int> lis;
	lis.push_back(2);
	lis.push_back(2);
	lis.push_front(3);
	lis.push_front(4);
	lis.print_list();

	lis.pop_back();
	lis.pop_front();

	lis.print_list();
	lis.get_size();

	cout << endl;


	auto it = lis.begin();
	for (auto i = it; i != lis.end(); i++)
		i->data += 1;
	lis.print_list();  //����� ������ ���ϴ� ������ �� �𸣰���



	return 0;
}
#include "objects.h"
#include <chrono>
#include <iomanip> 

template<typename T>
class Node
{
public:
	Node<T> *next;
	Node<T> *prev;
	T value; 

	Node() : prev(nullptr), next(nullptr) {};
	Node(T a) : prev(nullptr), next(nullptr), value(a) {};
	~Node()
	{
		//std::cout << "delite Node" <<  std:: endl;
	};

};

template<typename T>
class List
{
private:
	Node<T> *cur;
	Node<T> *head;
	Node<T> *tail;
	unsigned int _size; 
public:
	
	List(): cur(nullptr), head(nullptr), tail(nullptr), _size(0) {};
	~List() 
	{
		//std::cout << "delite list" << std::endl;
		clear();
	};

	void push_back(T a) 
	{
		if (_size == 0) {
			head = new Node<T>(a);
			tail = head;
		}
		else {
			Node<T>* temp = new Node<T>(a);
			tail->next = temp;
			temp->prev = tail;
			tail = tail->next; 
		}
		_size++; 
		return;
	}


	void push_front(T a)
	{
		if (_size == 0) {
			head = new Node<T>(a);
			tail = head;
		}
		else {
			Node<T>* temp = new Node<T>(a);
			head->prev = temp;
			temp->next = head;
			head = tail->prev;
		}
		_size++;
		return;
	}

	void pop_front()
	{
		if (_size == 0) return;
		Node<T>* temp =head;

		if (head == tail) tail = nullptr;
		head = head->next;

		if (temp == cur) cur = nullptr;
		delete temp;
		_size--;
		return;
	}

	void pop_back() 
	{
		if (_size == 0) return;
		Node<T>* temp = tail;

		if (head == tail) head = nullptr;
		tail = tail->prev;

		if (temp == cur) cur = nullptr;
		delete temp;
		_size--;
		return;
	}

	void insert(T value) 
	{
		
		if (size == 0) 
		{
			push_back(value);
			return;
		}
		Node<T>* temp = new Node(value);
		temp->next = cur;
		temp->prev = cur->prev;
		if (cur->prev != nullptr) cur->prev->next = temp;
		cur->prev = temp;
		if (cur == head) head = temp;
		_size++;
	}

	void erase() {
		if (cur == nullptr) return;
		if (cur == head) {
			pop_front();
			return;
		}
		if (cur == tail) {
			pop_back();
			return;
		}
		
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		Node<T>* temp = cur;
		cur = cur->next;
		delete temp;
		_size--;
		
	}


	void clear() 
	{
		while (head != nullptr) {
			pop_back();
		}
	}

	bool endOfList() 
	{
		return cur == nullptr;
	}


	void first() 
	{
		cur = head;
	}

	void last() 
	{
		cur = tail;
	}

	int size()
	{
		return _size;

	}

	void next()
	{
		if (cur != nullptr) cur =cur->next;
		
	}

	void prev()
	{
		if (cur != nullptr) cur = cur->prev;
		
	}
	T get_current() {
		if (endOfList()) return T();
		return cur->value;
	}

};

void createList(int n) {
	List<Point > *a = new  List<Point>();
	for (int i = 0; i < n / 2; i++) a->push_back(Point());
	for (int i = 0; i < n / 2; i++) a->push_back(Circle());
	
	delete a;
}
double setSquareList(int n) {
	List<Circle > a;
	for (int i = 0; i < n; i++) a.push_back(Circle(1,1,i));

	double ans = 0;
	for (a.first(); !a.endOfList(); a.next()) ans += a.get_current().square();
	return ans;
}



int main() {
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);

	for (int i = 10; i <= 1e6; i *= 10) {
		auto start = std::chrono::steady_clock::now();
		createList(i);
		auto finish = std::chrono::steady_clock::now();
		std::chrono::duration<double> delta = finish - start;
		std::cout << "Time to create a sheet for "<< i  <<" elements: " <<std::fixed <<std::setprecision(10)<< delta.count() << std::endl;
	}
	std::cout << std::endl;
	for (int i = 1; i <= 1e6; i *= 10) {
		auto start = std::chrono::steady_clock::now();
		std::cout <<"The area of circles from 0 to " << i-1 << " is equal to" << setSquareList(i) << std::endl;
		auto finish = std::chrono::steady_clock::now();
		std::chrono::duration<double> delta = finish - start;
		std::cout << "Time to create a sheet for " << i << " elements: " << std::fixed << std::setprecision(10) << delta.count() << std::endl;
	}
}

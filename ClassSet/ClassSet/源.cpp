#include<iostream>
using namespace std;

template<class T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node()
	{
		next = NULL;
	}
	Node(T item)
	{
		data = item;
		next = NULL;
	}
};

template<class T>
class Myset
{
public:
	Node<T>* front_node;
	Node<T>* rear_node;
	int count;
	Myset()
	{
		front_node = NULL;
		rear_node = NULL;
		count = 0;
	}
	Myset(Myset<T> set)
	{

		Node<T> temp_pointer = NULL;
		while (set.front_node != NULL)
		{
			front_node = new Node<T>(set.front_node->data);
			front_node = new
				set.front_node = set.front_node->next;
		}
	}
	bool isExist(T item)
	{
		Node<T>* temp_pointer = front_node;
		if (temp_pointer == NULL)
			return false;
		else
		{
			while (temp_pointer->next != NULL)
			{
				if (temp_pointer->data == item)
					return true;
				temp_pointer = temp_pointer->next;
			}
			return false;
		}
	}

	bool addItem(T item)
	{
		if (front_node == NULL)
		{
			front_node = new Node<T>(item);
			rear_node = front_node;
			count++;
			return true;
		}
		else
		{
			if (isExist(item))
				return true;
			else
			{
				rear_node->next = new Node<T>(item);
				rear_node = rear_node->next;
				count++;
			}
			return true;
		}
		return false;
	}

	bool print()
	{
		Node<T>* temp_pointer = front_node;
		if (front_node == NULL)
		{
			cout << "{}" << endl;
			return false;
		}
		else
		{
			temp_pointer = front_node;
			cout << '{';
			while (temp_pointer != NULL)
			{
				cout << temp_pointer->data << ", ";
				temp_pointer = temp_pointer->next;
			}
			cout << '}' << endl;
			return true;
		}
	}

	bool removeItem(T item)
	{
		if (!isExist(item))
			return true;
		else {
			Node<T>* temp_pointer = front_node;
			Node<T>* temp_pointer2 = NULL;
			if (front_node->data == item) {
				front_node = temp_pointer->next;
				delete temp_pointer;
				return true;
			}
			else {
				while (temp_pointer->next != NULL) {
					if (temp_pointer->next->data == item) {
						temp_pointer2 = temp_pointer->next;
						temp_pointer->next = temp_pointer->next->next;
						delete temp_pointer2;
					}
					temp_pointer = temp_pointer->next;
				}
				return true;
			}
			return false;
		}
	}

	Myset<T> operator+(Myset<T> set)
	{
		Myset<T> temp;
		temp.front_node = front_node;
		temp.rear_node = rear_node;
		Node<T>* temp_pointer = set.front_node;
		while (temp_pointer != NULL) {
			temp.addItem(temp_pointer->data);
			temp_pointer = temp_pointer->next;
		}
		return temp;
	}
	Myset<T> operator-(Myset<T> set)
	{

		Myset<T> temp;
		temp.front_node = front_node;
		temp.rear_node = rear_node;
		Node<T>* temp_pointer = set.front_node;
		while (temp_pointer != NULL) {
			temp.removeItem(temp_pointer->data);
			temp_pointer = temp_pointer->next;
		}
		return temp;
	}
};




int main()
{
	cout << "hello world" << endl;
	Myset<int> a, b;
	for (int i = 0; i<10; i++)
	{
		a.addItem(i);
	}
	b.addItem(1);
	b.addItem(10);
	b.addItem(23);
	b.addItem(78);
	a.removeItem(5);
	a.removeItem(13);
	a.print();
	b.print();

	(a + b).print();
	a.print();
	b.print();

	return 0;
}

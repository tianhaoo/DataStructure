#include<iostream>

using namespace std;

class Node
{
public:
	int data;
	int freq;
	Node* pre;
	Node* next;
	Node() {
		data = 0;
		freq = 0;
		next = 0;
		pre = 0;
	}
};

class myLink
{
public:
	Node* pointer;
	Node* current;
	myLink() {
		pointer = NULL;
		current = NULL;
	}
	void add(int a)
	{
		Node* p1 = new Node;
		p1->data = a;
		Node* p2 = pointer;
		if (pointer == NULL)
		{
			pointer = p1;
			return;
		}
		while (p2->next != NULL)
		{
			p2 = p2->next;
		}
		p2->next = p1;
		p1->pre = p2;
		return;
	}
	void print()
	{
		Node* p2 = pointer;
		if (pointer == NULL)
		{
			return;
		}
		while (p2 != NULL)
		{
			cout << p2->data << ' ';
			p2 = p2->next;
		}
		cout << endl;
		return;

	}

	void locate(Node* L, int x);

	void swap(Node* a, Node*b)
	{
		int temp,temp2;
		temp = a->data;
		a->data = b->data;
		b->data = temp;
		temp2 = a->freq;
		a->freq = b->freq;
		b->freq = temp2;
	}
};

void myLink::locate( Node* L,int x)
{
	Node* temp = L;
	if (temp == NULL)
	{
		return;
	}
	while (temp->next != NULL)
	{
		if (temp->data == x)
		{
			temp->freq++;
			current = temp;
		}
		temp = temp->next;
	}
	Node* temp2 = L;

	while (temp2->next != NULL)
	{
		Node* temp3 = temp2->next;
		while (temp3 != NULL)
		{
			if (temp2->freq > temp3->freq)
			{
				swap(temp2, temp3);
			}
			temp3 = temp3->next;
		}
		temp2 = temp2->next;
	}

}
int main()
{
	myLink a;
	for (int i = 78; i < 100; i++)
	{
		a.add(i);
	}
	a.print();

	a.locate(a.pointer, 88);

	a.print();


	system("pause");
	return 0;
}
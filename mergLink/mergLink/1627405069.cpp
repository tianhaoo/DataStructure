#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Node 
{
public:
	int data;
	Node* next;
	Node()
	{
		data = 0;
		next = NULL;
	}
	Node(int a)
	{
		data = a;
		next = NULL;
	}
};

class myLink
{
	int count;
	Node* pointer;

public:
	myLink()
	{
		count = 0;
		pointer = NULL;
	}
	void add(int a)
	{
		Node* p = pointer;
		if (p == NULL)
		{
			pointer = new Node(a);
		}

		else {
			while (p->next != NULL)
				p = p->next;
			p->next = new Node(a);
		}
		return;
	}
	void print()
	{
		Node* p = pointer;
		while (p != NULL)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
	int top()
	{
		Node* temp = pointer;
		if (temp == NULL)
		{
			return -1;
		}
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		return temp->data;
	}
	bool pop()
	{
		Node* temp = pointer;
		if (temp == NULL)
		{
			return false;
		}
		else if (temp->next == NULL)
		{
			pointer = 0;
			return true;
		}
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}
		delete temp->next;
		temp->next = 0;
		return true;
	}


};

int main()
{
	myLink a, b,c;
	vector<int> ve;
	for (int i = 0; i < 20; i++)
	{
		a.add(i);
		b.add(49 - i);
	}
	a.add(1000);
	a.print();
	b.print();
	while (a.top() != -1)
	{
		ve.push_back(a.top());
		a.pop();
	}
	while (b.top() != -1)
	{
		ve.push_back(b.top());
		b.pop();
	}

	sort(ve.begin(), ve.end());
	for (int i = 0; i < ve.size(); i++)
	{
		c.add(ve[i]);
	}
	c.print();
	return 0;
}
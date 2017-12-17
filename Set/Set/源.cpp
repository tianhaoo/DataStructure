#include <iostream>
using namespace std;

#define MaxSize 100

template<class T>
class MySet
{
public:
	T items[MaxSize];
	int count;
	MySet()
	{
		count = 0;
	}
	bool isExist(T item)   //����һ�����飬������ھͷ���true, ����ͷ���false
	{
		for (int i = 0; i<count; i++)
		{
			if (items[i] == item)
				return true;
		}
		return false;
	}
	int size()
	{
		return count;
	}
	bool addItem(T item)  // ���������Ԫ�أ� ����Ѿ����ھͲ�����������true��
	{
		if (this->isExist(item))
			return true;
		else
		{
			items[count] = item;
			count++;
			return false;
		}	
		return false;
	}

	bool removeItem(T item)  // �������Ƴ�Ԫ�أ� ���û�оͷ���false
	{
		T temp[MaxSize];                     // ��һ��temp����
		if (!this->isExist(item))
			return false;
		for (int i = 0; i< count; i++)       //��������д���Ҫ�Ƴ���Ԫ�أ� ��ô�����Ƴ�����
		{
			if (items[i] == item)
			{
				for (int j = i + 1; j<count; j++)   // ��i��¼�´��Ƴ�Ԫ�ص�λ�ã���Ҫ�Ƴ���Ԫ�غ����Ԫ��ȫ�ŵ�temp��������
					temp[j] = items[j];
				count--;
				for (int k = i; k<count; k++)      // ��i��ʼ��temp���������Ԫ�ظ���items�����Ԫ��
					items[k] = temp[k + 1];
				return true;
			}
		}
	}
	MySet<T> operator+ (MySet<T> set)            // ��������
	{
		MySet<T> temp;
		for (int i = 0; i<count; i++)
			temp.items[i] = items[i];
		temp.count += count;
		for (int i = 0; i<set.size(); i++)
		{
			temp.addItem(set.items[i]);
		}

		return temp;
	}
	MySet<T> operator* (MySet<T> set)           // ��������
	{
		MySet<T> temp;
		for (int i = 0; i<count; i++)
		{
			for (int j = 0; j<set.size(); j++)
			{
				if (this->items[i] == set.items[j])
					temp.addItem(items[i]);
			}
		}
		return temp;
	}
	MySet operator- (MySet set)               // �����
	{
		MySet<T> temp;
		for (int i = 0; i<count; i++)
		{
			temp.items[i] = items[i];
		}
		temp.count += count;
		for (int j = 0; j<set.size(); j++)
		{
			temp.removeItem(set.items[j]);
		}

		return temp;
	}
	bool print()                      // ���������
	{
		if (count == 0)
		{
			cout << "{}" << endl;
			return true;
		}
		cout << '{';
		for (int i = 0; i< count; i++)
		{
			cout << items[i];
			if (i != count - 1)
				cout << " ,";
		}
		cout << '}' << endl;
		return true;
	}
};














int main()                          // main�������Լ�����Ĺ���
{
	MySet<int> a, b, c;
	a.addItem(5);
	a.addItem(6);
	b.addItem(5);
	b.addItem(7);
	b.addItem(10);
	c.addItem(10);
	b.removeItem(6);
	cout << "����a:" << a.size();
	a.print();
	cout << "����b:" << b.size();
	b.print();
	cout << "����c:" << c.size();
	c.print();

	cout << "a+b+c" << (a+b).size();
	(a+b+c).print();
	cout << "����a:" << a.size();
	a.print();
	cout << "����b:" << b.size();
	b.print();
	cout << "����c:" << c.size();
	c.print();

	cout << "a*b" << (a*b).size();
	(a*b).print();
	cout << "����a:" << a.size();
	a.print();
	cout << "����b:" << b.size();
	b.print();
	cout << "����c:" << c.size();
	c.print();

	cout << "a-b" << (a-b).size();
	(a - b).print();
	cout << "����a:" << a.size();
	a.print();
	cout << "����b:" << b.size();
	b.print();
	cout << "����c:" << c.size();
	c.print();

	system("pause");
	return 0;
}
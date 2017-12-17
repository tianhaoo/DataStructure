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
	bool isExist(T item)   //遍历一遍数组，如果存在就返回true, 否则就返回false
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
	bool addItem(T item)  // 给集合添加元素， 如果已经存在就不操作并返回true；
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

	bool removeItem(T item)  // 给集合移除元素， 如果没有就返回false
	{
		T temp[MaxSize];                     // 开一个temp数组
		if (!this->isExist(item))
			return false;
		for (int i = 0; i< count; i++)       //如果数组中存在要移除的元素， 那么进行移除操作
		{
			if (items[i] == item)
			{
				for (int j = i + 1; j<count; j++)   // 用i记录下待移除元素的位置，把要移除的元素后面的元素全放到temp数组里面
					temp[j] = items[j];
				count--;
				for (int k = i; k<count; k++)      // 从i开始用temp数组里面的元素覆盖items里面的元素
					items[k] = temp[k + 1];
				return true;
			}
		}
	}
	MySet<T> operator+ (MySet<T> set)            // 并集操作
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
	MySet<T> operator* (MySet<T> set)           // 交集操作
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
	MySet operator- (MySet set)               // 差集操作
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
	bool print()                      // 输出集合类
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














int main()                          // main函数测试集合类的功能
{
	MySet<int> a, b, c;
	a.addItem(5);
	a.addItem(6);
	b.addItem(5);
	b.addItem(7);
	b.addItem(10);
	c.addItem(10);
	b.removeItem(6);
	cout << "集合a:" << a.size();
	a.print();
	cout << "集合b:" << b.size();
	b.print();
	cout << "集合c:" << c.size();
	c.print();

	cout << "a+b+c" << (a+b).size();
	(a+b+c).print();
	cout << "集合a:" << a.size();
	a.print();
	cout << "集合b:" << b.size();
	b.print();
	cout << "集合c:" << c.size();
	c.print();

	cout << "a*b" << (a*b).size();
	(a*b).print();
	cout << "集合a:" << a.size();
	a.print();
	cout << "集合b:" << b.size();
	b.print();
	cout << "集合c:" << c.size();
	c.print();

	cout << "a-b" << (a-b).size();
	(a - b).print();
	cout << "集合a:" << a.size();
	a.print();
	cout << "集合b:" << b.size();
	b.print();
	cout << "集合c:" << c.size();
	c.print();

	system("pause");
	return 0;
}
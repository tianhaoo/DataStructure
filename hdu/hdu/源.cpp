#include<iostream>
#include<vector>
using namespace std;


void search(const int& a, const int& b);

int main()
{
	int a, b;
	while (cin >> a&&cin >> b)
	{
		search(a,b);
	}
	
}
void search(const int& a, const int& b)
{
	int count = 0;
	vector<int> ve1;
	for (int i = a; i <= b; i++)
	{
		int x = i / 100;
		int y = (i - 100 * x) / 10;
		int z = i - 100 * x - 10 * y;
		int m = x*x*x + y*y*y + z*z*z;
		if (m == i)
		{
			ve1.push_back(i);
			count++;
		}
	}
	if (count == 0)
	{
		cout << "no" << endl;
	}
	else
	{
		for (int j = 0; j < ve1.size(); j++)
		{
			cout << ve1[j];
			if (j < ve1.size() - 1)
			{
				cout << ' ';
			}
			else
			{
				cout << endl;
			}
		}		
	}



}
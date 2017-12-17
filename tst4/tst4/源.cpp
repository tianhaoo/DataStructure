#include <iostream>
using namespace std;
int main()
{
	char c;
	cout << "enter a sentence:" << endl;
	while ((c = cin.get()) != EOF)
		cout << c << endl;
	return 0;
}
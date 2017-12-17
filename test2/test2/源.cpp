#include <iostream>
using namespace std;

int main()
{
	int t, res[4];
	cin >> t;
	res[0] = 5;
	res[1] = 1;
	res[2] = 3;
	res[3] = 7;
	for (int i = 0; i < t; i++) {
		int n;
		cin >> n;
		if (n == 0)
			cout << 0 << endl;
		else
			cout << res[n % 4] << endl;
	}


	return 0;
}
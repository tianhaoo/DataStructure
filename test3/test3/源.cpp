#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int n, t;
		vector<int> vt;
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> t;
			vt.push_back(t);
		}
		if (n == 1) {
			if(vt[0] == 15)
				cout << "down" << endl;
			else if(vt[0] == 0)
				cout << "up" << endl;
			else
				cout << -1 << endl;
		}
		else if (n == 30) {
			if (vt[29] < vt[0])
				cout << "up" << endl;
			else
				cout << "down" << endl;
		}
		else {
			if (vt[n - 1] == 0) {
				cout << "up" << endl;
			}
			else if(vt[n-1] == 15){
				cout << "down" << endl;
			}
			else {
				if (vt[n - 2] < vt[n - 1])
					cout << "up" << endl;
				else
					cout << "down" << endl;
			}
		}
			

		vt.clear();
	}
	return 0;
}
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char t;
		string str;
		stack<char> sta, res;
		cin >> str;
		sta.push(str[0]);
		for (int i = 1; i < str.size(); i++){
			t = str[i];
			if (t == sta.top()) {
				sta.pop();
			}
			else {
				sta.push(t);
			}
		}
		while (!sta.empty()) {
			res.push(sta.top());
			sta.pop();
		}
		while (!res.empty()) {
			cout << res.top();
			res.pop();
		}
		cout << endl;


	}
	
	
	return 0;
}
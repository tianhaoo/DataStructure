#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int maxrow = 50;
const int maxcol = 50;

bool user_say_yes()
{
	int c;
	bool initial_response = true;
	do {
		if (initial_response) {
			cout << "(y,n)?" << flush;
		}
		else {
			cout << "Respond with either y or n: " << flush;
		}

		do {
			c = cin.get();
		} while (c == '\n' || c == ' ' || c == '\t');

		initial_response = false;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	return (c == 'y' || c == 'Y');
}

void instructions()
{
	cout << "Game Begin now!" << endl;
	return;
}

class Life {
	int grid[maxrow + 2][maxcol + 2];
	int neighbor_count(int row, int col);
public:
	void initialize();
	void print();
	void update();

};

int Life::neighbor_count(int row, int col)
{
	int count = 0;
	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = col - 1; j <= col + 1; j++) {
			count += grid[i][j];
		}
	}
	count -= grid[row][col];
	return count;
}


void Life::update()
{
	int new_grid[maxrow + 2][maxcol + 2];
	for (int i = 1; i <= maxrow; i++) {
		for (int j = 1; j <= maxcol; j++) {
			switch (neighbor_count(i, j)) {
			case 2:
				new_grid[i][j] = grid[i][j];
				break;
			case 3:
				new_grid[i][j] = 1;
				break;
			default:
				new_grid[i][j] = 0;
			}
		}
	}
	for (int i = 1; i <= maxrow; i++) {
		for (int j = 1; j <= maxcol; j++) {
			grid[i][j] = new_grid[i][j];
		}
	}
}

void Life::initialize()
{
	for (int i = 0; i < maxrow + 2; i++) {
		for (int j = 0; j < maxrow + 2; j++) {
			grid[i][j] = 0;
		}
	}
	int row, col;
	cout << "Type in \"hand\" to list the coordinates for living cells or type in \"filename\" to import from a file" << endl;
	//选择是手动输入坐标还是从文件中读取第一代的坐标信息

	string s;
	cout << "(hand,\"filename\")?" << flush;
	cin >> s;

	if (s == "hand") {
		cout << "Terminate the list with the special pair -1 -1." << endl;
		cin >> row >> col;
		while (row != -1 && row != -1) {
			if (row >= 1 && row <= maxrow) {
				if (col >= 1 && col <= maxcol) {
					grid[row][col] = 1;
				}
				else {
					cout << "column is out of range." << endl;
				}
			}
			else {
				cout << "row is out of range." << endl;
			}
			cin >> row >> col;
		}
		return;
	}
	else {
		ifstream in(s);
		in >> row >> col;
		while (row != -1 && row != -1) {
			if (row >= 1 && row <= maxrow) {
				if (col >= 1 && col <= maxcol) {
					grid[row][col] = 1;
				}
				else {
					cout << "column is out of range." << endl;
				}
			}
			else {
				cout << "row is out of range." << endl;
			}
			in >> row >> col;
		}
		return;
	}
}

void Life::print()
{
	cout << "The current configuration is:" << endl;
	for (int i = 1; i <= maxrow; i++)
	{
		for (int j = 1; j <= maxcol; j++) {
			if (grid[i][j] == 1)
				cout << '*';
			else
				cout << ' ';
		}
		cout << endl;
	}
	cout << endl;
	return;
}


int main()
{
	//生成第一种可能的配置
	ofstream out1("1.txt");
	for (int i = 0; i<20; i++)
	{
		out1 << i + 1 << ' ' << i + 1 << ' ';
	}
	out1 << -1 << ' ' << -1 << ' ';
	out1.close();

	//生成第二种可能的配置
	ofstream out2("Virus.txt");
	for (int i = 1; i <= 50; i++) {
		for (int j = 1; j <= 50; j++) {
			{
				if (i % 3 != 0 && j % 3 != 0) {
					out2 << i << ' ' << j << ' ';
				}
			}
		}
	}
	out2 << 27 << ' ' << 28 << ' ';
	out2 << -1 << ' ' << -1 << ' ';
	out2.close();
	
	//生成第三种可能的配置
	ofstream out3("Barber_Pole.txt");
	out3 << 1 << ' ' << 1 << ' ' << 1 << ' ' << 2 << ' ' << 2 << ' ' << 1 << ' ';
	for (int i = 1; i <= 20; i++) {
		out3 << i << ' ' << i + 1 << ' ';
	}

	Life configuration;
	instructions();
	configuration.initialize();
	configuration.print();
	cout << "Continue viewing new generations?" << endl;
	while (user_say_yes()) {
		configuration.update();
		configuration.print();
		cout << "Continue viewing new generations?" << endl;
	}

	return 0;
}
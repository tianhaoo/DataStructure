#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<string>
using namespace std;

typedef int Vertex;
template <int max_size>
class Digraph {
	int count;
	Vertex visited[max_size];   // �����洢���з��ʹ��Ľڵ�
	list<Vertex> neighbors[max_size];      // һ����max_size������ÿһ����������������������������Vertex
	void traverse(Vertex v, bool visited[], void(*visit)(Vertex&))const;
public:
	Digraph();
	void depth_first(void(*visit)(Vertex&))const;
	void breadth_first(void(*visit)(Vertex&))const;
	void create();
};

template<int max_size>
Digraph<max_size>::Digraph() {
	for (Vertex v = 0; v < max_size; v++)
		visited[v] = false;
}


template <int max_size>
void Digraph<max_size>::depth_first(void(*visit)(Vertex&))const {
	bool visited[max_size];
	for (int v = 0; v < max_size; v++) 
		visited[v] = false;
	for (int v = 0; v < max_size; v++) {
		if (!visited[v])
			traverse(v, visited, visit); 
	}
}

template <int max_size>
void Digraph<max_size>::traverse(Vertex v, bool visited[], void(*visit)(Vertex&))const {
	visited[v] = true;
	(*visit)(v);
	Vertex w;
	list<Vertex>::iterator it;
	for (it = neighbors[v].begin(); it != neighbors[v].end(); it++) {
		w = *it;
		if (!visited[w])
			traverse(w, visited, visit);
	}

}

template<int max_size>
void Digraph<max_size>::breadth_first(void(*visit)(Vertex&))const {
	queue<Vertex> q;
	bool visited[max_size];
	Vertex v, w, x;
	for (v = 0; v < max_size; v++)
		visited[v] = false;
	for (v = 0; v < max_size; v++) {
		if (!visited[v]) {
			q.push(v);
			while (!q.empty()) {
				w = q.front();
				if (!visited[w]) {
					visited[w] = true;
					(*visit)(w);
					for (list<Vertex>::iterator it = neighbors[w].begin(); it != neighbors[w].end(); it++)
						q.push(*it);
				}
				q.pop();
			}
		}
	}
}

template<int max_size>
void Digraph<max_size>::create() {
	cout << "Ĭ�����нڵ㶼�Ǵ�0��"
		 << max_size
		 << "�ı��" 
		 << endl;

	int en;
	cout << "������ߵĸ���" << endl;
	cin >> en;
	cout << "����������ͼ�ıߣ� ��ʽΪ(v1,v2), ע����Ӣ�����źͶ���, v1�Ǳߵ�ʼ�㣬 v2�Ǳߵ��յ㣬v1, v2 ȡֵ�Ǹո��������Щ�ڵ�" << endl;
	char temp[20];
	int v1, v2;
	for (int i = 0; i < en; i++) {
		cin >> temp;
		sscanf_s(temp, "(%d,%d)", &v1, &v2);
		neighbors[v1].push_back(v2);
	}
}
void print(Vertex& x) {
	cout << x << ' ';
}

int main()
{
	Digraph<5> a;
	a.create();

	a.depth_first(print);




	system("pause");
	return 0;
}
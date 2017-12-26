#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<string>
using namespace std;

typedef int Vertex;
template <int max_size>
class Digraph {
	list<Vertex> neighbors[max_size];      // һ����max_size������ÿһ����������������������������Vertex
	void traverse(Vertex v, bool visited[], void(*visit)(Vertex&));
	void traverse(Vertex v, bool visited[]);
public:
	list<Vertex>* fetch_neighbors();
	void depth_first(void(*visit)(Vertex&));
	void breadth_first(void(*visit)(Vertex&));
	void create();
	vector<Digraph<max_size>> connected_subgraph();
};

template<int max_size>
list<Vertex>* Digraph<max_size>::fetch_neighbors() {
	return neighbors;
}

template <int max_size>
void Digraph<max_size>::depth_first(void(*visit)(Vertex&)) {     // ������ȱ�������������
	bool visited[max_size];
	for (int v = 0; v < max_size; v++) 
		visited[v] = false;
	for (int v = 0; v < max_size; v++) {
		if (!visited[v])
			traverse(v, visited, visit); 
	}
}

template <int max_size>
void Digraph<max_size>::traverse(Vertex v, bool visited[], void(*visit)(Vertex&)) {   // ������ȱ����ĵݹ麯��
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
void Digraph<max_size>::breadth_first(void(*visit)(Vertex&)) {               // ������ȱ���
	queue<Vertex> q;
	bool visited[max_size];
	Vertex v, w;
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
					list<Vertex>::iterator it;
					for (it = (neighbors[w]).begin(); it != (neighbors[w]).end(); it++)
						q.push(*it);
				}
				q.pop();
			}
		}
	}
}

template<int max_size>
void Digraph<max_size>::create() {                   // �����û����봴��ͼ
	cout << "Ĭ�����нڵ㶼�Ǵ�0��"
		 << max_size-1
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

template<int max_size>
vector<Digraph<max_size>> Digraph<max_size>::connected_subgraph() {    // ����ͨ��ͼ����������������ͼ����ͨ��ͼ��ɵ�����
	vector<Digraph<max_size>> temp_vec;


	bool visited[max_size], passed[max_size];
	for (int i = 0; i < max_size; i++) {
		visited[i] = false;
		passed[i] = false;
	}
		
	for (int v = 0; v < max_size; v++) {
		Digraph<max_size> temp_digraph;
		if (!visited[v])
			traverse(v, visited);

		for (int i = 0; i < max_size; i++) {
			if (visited[i] && !passed[i]) {
				temp_digraph.fetch_neighbors()[i] = neighbors[i];
				passed[i] = true;
			}		
		}
		temp_vec.push_back(temp_digraph);
	}

	return temp_vec;
}

template<int max_size>
void Digraph<max_size>::traverse(Vertex v, bool visited[]) {      // ����ͨ��ͼ�ĵݹ麯��
	visited[v] = true;
	Vertex w;
	list<Vertex>::iterator it;
	for (it = neighbors[v].begin(); it != neighbors[v].end(); it++) {
		w = *it;
		if (!visited[w])
			traverse(w, visited);
	}
}


void print(Vertex& x) {
	cout << x << ' ';
}


int main()
{
	const int size = 7;
	Digraph<size> a;
	vector<Digraph<size>> vec_subdigraph;

	a.create();

	a.breadth_first(print);
	cout << endl;

	a.breadth_first(print);
	cout << endl;

	vec_subdigraph = a.connected_subgraph();

	for (int i = 0; i < vec_subdigraph.size(); i++) {
		(vec_subdigraph[i]).breadth_first(print);
		cout << endl;
	}

	system("pause");
	return 0;
}
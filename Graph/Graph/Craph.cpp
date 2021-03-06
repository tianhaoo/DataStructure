#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<string>
using namespace std;

typedef int Vertex;
template <int max_size>
class Digraph {
	list<Vertex> neighbors[max_size];      // 一共有max_size个链表每一个链表用来储存与他相连的所有Vertex
	
	void traverse(Vertex v, bool visited[], void(*visit)(Vertex&));
	void traverse(Vertex v, bool visited[]);
public:
	bool disabled[max_size];
	Digraph();
	list<Vertex>* fetch_neighbors();
	void depth_first(void(*visit)(Vertex&), Vertex start=0);
	void breadth_first(void(*visit)(Vertex&), Vertex start=0);
	void create();
	vector<Digraph<max_size>> connected_subgraph();
};

template<int max_size>
Digraph<max_size>::Digraph()
{
	for (int i = 0; i < max_size; i++)
		disabled[i] = false;
}


template<int max_size>
list<Vertex>* Digraph<max_size>::fetch_neighbors() {
	return neighbors;
}

template <int max_size>
void Digraph<max_size>::depth_first(void(*visit)(Vertex&), Vertex start) {     // 深度优先遍历的主调函数
	bool visited[max_size];
	for (int v = 0; v < max_size; v++) 
		visited[v] = false;
	for (int v = start; v < max_size; v++) {
		if (!visited[v])
			traverse(v, visited, visit); 
	}
}

template <int max_size>
void Digraph<max_size>::traverse(Vertex v, bool visited[], void(*visit)(Vertex&)) {   // 深度优先遍历的递归函数
	visited[v] = true;
	if(!disabled[v])
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
void Digraph<max_size>::breadth_first(void(*visit)(Vertex&), Vertex start) {               // 广度优先遍历
	queue<Vertex> q;
	bool visited[max_size];
	Vertex v, w;
	for (v = 0; v < max_size; v++)
		visited[v] = false;
	for (v = start; v < max_size; v++) {
		if (!visited[v]) {
			q.push(v);
			while (!q.empty()) {
				w = q.front();
				if (!visited[w]) {
					visited[w] = true;
					if(!disabled[w])
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
void Digraph<max_size>::create() {                   // 根据用户输入创建图
	cout << "默认所有节点都是从0到"
		 << max_size-1
		 << "的编号" 
		 << endl;

	int en;
	cout << "请输入边的个数" << endl;
	cin >> en;
	cout << "请输入有向图的边， 形式为(v1,v2), 注意是英文括号和逗号, v1是边的始点， v2是边的终点，v1, v2 取值是刚刚输入的那些节点" << endl;
	char temp[20];
	int v1, v2;
	for (int i = 0; i < en; i++) {
		cin >> temp;
		sscanf_s(temp, "(%d,%d)", &v1, &v2);
		neighbors[v1].push_back(v2);
	}
}

template<int max_size>
vector<Digraph<max_size>> Digraph<max_size>::connected_subgraph() {    // 求连通子图的主调函数，返回图的连通子图组成的向量
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
			else {
				temp_digraph.disabled[i] = true;
			}
		}
		temp_vec.push_back(temp_digraph);
	}

	return temp_vec;
}

template<int max_size>
void Digraph<max_size>::traverse(Vertex v, bool visited[]) {      // 求连通子图的递归函数
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
	
	cout << "从默认位置开始的广度优先遍历" << endl;
	a.breadth_first(print); // 不选定起点默认是从零开始遍历
	cout << endl;

	cout << "从3开始的深度优先遍历" << endl;
	a.breadth_first(print, 3); 
	cout << endl;

	cout << "从默认位置开始的深度优先遍历" << endl;
	a.depth_first(print); // 不选定起点默认是从零开始遍历
	cout << endl;

	cout << "从3开始的深度优先遍历" << endl;
	a.depth_first(print, 3); 
	cout << endl;

	vec_subdigraph = a.connected_subgraph();

	cout << "下面输出a的连通子图, 一个图占用一行，有的图没有节点，仅仅输出一个换行" << endl;
	for (int i = 0; i < vec_subdigraph.size(); i++) {
		vec_subdigraph[i].breadth_first(print);
		cout << endl;
	}

	system("pause");
	return 0;
}
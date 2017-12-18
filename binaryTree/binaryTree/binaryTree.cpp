#include <iostream>
#include <queue>
using namespace std;

template<class Entry>
struct Binary_node {
	// data members:
	Entry data;
	Binary_node<Entry> *left;
	Binary_node<Entry> *right;
	// constructors:
	Binary_node();
	Binary_node(const Entry &x);
};

template<class Entry>
Binary_node<Entry>::Binary_node() {
	left = NULL;
	right = NULL;
}

template<class Entry>
Binary_node<Entry>::Binary_node(const Entry &x) {
	data = x;
	left = NULL;
	right = NULL;
}


template <class Entry>
class Binary_tree {
	// 被调用的递归函数
	bool search_and_insert(Binary_node<Entry>* &sub_root, const Entry &new_data); // 注意这里用了指针的引用，如果不加引用的话，操作的只是一个副本
	void recursive_inorder(Binary_node<Entry>* sub_root, void(*visit)(Entry &)); // 第二个参数是一个函数指针
	void recursive_preorder(Binary_node<Entry>* sub_root, void(*visit)(Entry &));
	void recursive_postorder(Binary_node<Entry>* sub_root, void(*visit)(Entry &));
	int recursive_size(Binary_node<Entry>* sub_root)const;
	int recursive_height(Binary_node<Entry>* sub_root)const;
	Binary_node<Entry>* recursive_copy(Binary_node<Entry>* sub_root);
	void recursive_clear(Binary_node<Entry>* &sub_root);
	void recursive_deleteleaf(Binary_node<Entry>* &sub_root);
public:
	Binary_tree();
	bool empty()const;
	// 递归的主调函数
	bool insert(const Entry &new_data);
	void inorder(void(*visit)(Entry &)); 
	void preorder(void(*visit)(Entry &));
	void postorder(void(*visit)(Entry &));
	// 常用的方法
	int size()const;
	int height()const;
	Binary_tree<Entry> copy();
	void clear();
	void deleteleaf();
	// 广度优先遍历又称层次遍历，需要借助队列实现
	void breadthfirst(void(*visit)(Entry &));
protected:
	Binary_node<Entry>* root;
};


template <class Entry>
Binary_tree<Entry>::Binary_tree() {
	root = NULL;
}

template <class Entry>
bool Binary_tree<Entry>::empty()const {
	return root == NULL;
}

template <class Entry>
bool Binary_tree<Entry>::insert(const Entry &new_data) {
	return search_and_insert(root, new_data);
}

template <class Entry>
bool Binary_tree<Entry>::search_and_insert(Binary_node<Entry>* &sub_root, const Entry &new_data) {
	if (sub_root == NULL) {
		sub_root = new Binary_node<Entry>(new_data);
		return true;
	}
	// 我们假定树里面所有的元素都是互不相同的
	else if (new_data < sub_root->data) {
		return search_and_insert(sub_root->left, new_data);
	}
	else if (new_data > sub_root->data) {
		return search_and_insert(sub_root->right, new_data);
	}
	else {
		return false;
	}
}

template<class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &)) {
	recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry>* sub_root, void (*visit)(Entry &)) {
	if (sub_root != NULL) {
		recursive_inorder(sub_root->left, visit);
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->right, visit);
	}
}

template<class Entry>
void Binary_tree<Entry>::preorder(void(*visit)(Entry &)) {
	recursive_preorder(root, visit);
}

template<class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry>* sub_root, void(*visit)(Entry &)) {
	if (sub_root != NULL) {
		(*visit)(sub_root->data);
		recursive_preorder(sub_root->left, visit);
		recursive_preorder(sub_root->right, visit);
	}
}

template <class Entry>
void Binary_tree<Entry>::postorder(void(*visit)(Entry &)) {
	recursive_postorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry>* sub_root, void(*visit)(Entry &)) {
	if (sub_root != NULL) {
		recursive_postorder(sub_root->left, visit);
		recursive_postorder(sub_root->right, visit);
		(*visit)(sub_root->data);
	}
}

template<class Entry>
int Binary_tree<Entry>::size()const {
	return recursive_size(root);
}

template<class Entry>
int Binary_tree<Entry>::recursive_size(Binary_node<Entry>* sub_root)const {
	if (sub_root == NULL)
		return 0;
	return 1 + recursive_size(sub_root->left) + recursive_size(sub_root->right);
}

template<class Entry>
int Binary_tree<Entry>::height()const {
	return recursive_height(root);
}

template<class Entry>
int Binary_tree<Entry>::recursive_height(Binary_node<Entry>* sub_root)const {
	if (sub_root == NULL)
		return 0;
	int left = recursive_height(sub_root->left);
	int right = recursive_height(sub_root->right);
	if (left > right)
		return 1 + left;
	else
		return 1 + right;
}

template<class Entry>
Binary_tree<Entry> Binary_tree<Entry>::copy() {
	Binary_tree<Entry> temp;
	temp.root = recursive_copy(root);
	return temp;
}

template<class Entry>
Binary_node<Entry>* Binary_tree<Entry>::recursive_copy(Binary_node<Entry>* sub_root) {
	if (sub_root == NULL)
		return NULL;
	Binary_node<Entry>* temp = new Binary_node<Entry>(sub_root->data);
	temp->left = recursive_copy(sub_root->left);
	temp->right = recursive_copy(sub_root->right);
	return temp;
}

template<class Entry>
void Binary_tree<Entry>::clear() {
	recursive_clear(root);
}

template<class Entry>
void Binary_tree<Entry>::recursive_clear(Binary_node<Entry>* &sub_root) {
	if (sub_root != NULL) {
		recursive_clear(sub_root->left);
		recursive_clear(sub_root->right);
		delete sub_root;
		sub_root = NULL;
	}
}

template<class Entry>
void Binary_tree<Entry>::deleteleaf() {
	recursive_deleteleaf(root);
}

template<class Entry>
void Binary_tree<Entry>::recursive_deleteleaf(Binary_node<Entry>* &sub_root) {
	if (sub_root == NULL)
		return;
	if (sub_root->left == NULL && sub_root->right == NULL) {
		delete sub_root;
		sub_root = NULL;
		return;
	}
	recursive_deleteleaf(sub_root->left);
	recursive_deleteleaf(sub_root->right);
}

template<class Entry>
void Binary_tree<Entry>::breadthfirst(void(*visit)(Entry &)) {
	queue<Binary_node<Entry>*> temp;
	temp.push(root);
	while (!temp.empty()) {
		Binary_node<Entry>* p = temp.front();
		temp.pop();
		(*visit)(p->data);
		if (p->left != NULL) {
			temp.push(p->left);
		}
		if (p->right != NULL) {
			temp.push(p->right);
		}
	}
}


void print(int &x) {
	cout << x << ' ';
}

int main()
{
	Binary_tree<int> a, b;
	a.insert(1);
	a.insert(6);
	a.insert(3);
	a.insert(5);
	a.insert(7);
	a.insert(9);
	a.insert(4);
	a.insert(8);
	a.insert(2);


	cout << "inorder" << endl;
	a.inorder(print);
	cout << endl;

	cout << "preorder" << endl;
	a.preorder(print);
	cout << endl;

	cout << "postorder" << endl;
	a.postorder(print);
	cout << endl;

	cout << "breadthfirst" << endl;
	a.breadthfirst(print);
	cout << endl;

	cout << "size" << endl;
	cout << a.size() << endl;

	cout << "Is it empty?" << endl;
	if (a.empty())
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	cout << "a.deleteleaf()" << endl;
	a.deleteleaf();

	cout << "inorder" << endl;
	a.inorder(print);
	cout << endl;


	cout << endl;

	b = a.copy();

	cout << "next is b:" << endl;
	b.insert(100);
	b.insert(500);
	b.insert(-1);
	b.insert(0);
	b.insert(-5);

	cout << "inorder" << endl;
	b.inorder(print);
	cout << endl;

	cout << "size" << endl;
	cout << b.size() << endl;

	cout << "b.clear()" << endl;
	b.clear();

	cout << "inorder" << endl;
	b.inorder(print);
	cout << endl;

	cout << "size" << endl;
	cout << b.size() << endl;

	cout << "Is it empty?" << endl;
	if (b.empty())
		cout << "yes" << endl;
	else
		cout << "no" << endl;




	system("pause");
	return 0;
}

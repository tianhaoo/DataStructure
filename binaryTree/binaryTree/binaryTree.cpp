#include <iostream>
#include <queue>
#include <vector>
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
	// �����õĵݹ麯��
	bool search_and_insert(Binary_node<Entry>* &sub_root, const Entry &new_data); // ע����������ָ������ã�����������õĻ���������ֻ��һ������
	void recursive_inorder(Binary_node<Entry>* sub_root, void(*visit)(Entry &)); // �ڶ���������һ������ָ��
	void recursive_preorder(Binary_node<Entry>* sub_root, void(*visit)(Entry &));
	void recursive_postorder(Binary_node<Entry>* sub_root, void(*visit)(Entry &));
	int recursive_size(Binary_node<Entry>* sub_root)const;
	int recursive_height(Binary_node<Entry>* sub_root)const;
	Binary_node<Entry>* recursive_copy(Binary_node<Entry>* sub_root);
	void recursive_clear(Binary_node<Entry>* &sub_root);
	void recursive_deleteleaf(Binary_node<Entry>* &sub_root);
	bool search_and_destroy(Binary_node<Entry>* &sub_root, const Entry& target);
	bool remove_root(Binary_node<Entry>* &sub_root);
	void recursive_create(Binary_node<Entry>* &sub_root, vector<Entry> &preorder, vector<Entry> &inorder);
	int recursive_two_degree_count(Binary_node<Entry>* sub_root);
	int recursive_count_leaf(Binary_node<Entry>* sub_root);
public:
	Binary_tree();
	bool empty()const;
	// �ݹ����������
	bool insert(const Entry &new_data);
	void inorder(void(*visit)(Entry &)); 
	void preorder(void(*visit)(Entry &));
	void postorder(void(*visit)(Entry &));
	// ���õķ���
	void create_by_preorder_and_inorder();
	int size()const;
	int height()const;
	Binary_tree<Entry> copy();
	void clear();
	void deleteleaf();
	bool remove(const Entry& target);
	int two_degree_count();
	int count_leaf();
	// ������ȱ����ֳƲ�α�������Ҫ��������ʵ��
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
	// ���Ǽٶ����������е�Ԫ�ض��ǻ�����ͬ��
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

template<class Entry>
bool Binary_tree<Entry>::remove(const Entry& target) {
	return search_and_destroy(root, target);
}

template<class Entry>
bool Binary_tree<Entry>::search_and_destroy(Binary_node<Entry>* &sub_root, const Entry& target) {
	if (sub_root == NULL || sub_root->data == target)
		return remove_root(sub_root);
	else if (target < sub_root->data)
		return search_and_destroy(sub_root->left, target);
	else
		return search_and_destroy(sub_root->right, target);
}

template<class Entry>
bool Binary_tree<Entry>::remove_root(Binary_node<Entry>* &sub_root) {
	if (sub_root == NULL)
		return false;
	Binary_node<Entry>* to_delete = sub_root;
	// Remember node to delete at end.
	if (sub_root->right == NULL)
		sub_root = sub_root->left;
	else if (sub_root->left == NULL)
		sub_root = sub_root->right;
	else { // Neither subtree is empty.
		to_delete = sub_root->left;
		// Move left to find predecessor��ǰ��).
		Binary_node<Entry>* parent = sub_root; // parent of to_delete.
		while (to_delete->right != NULL) {
			// to_delete is not the predecessor.
			parent = to_delete;
			to_delete = to_delete->right;
		}
		sub_root->data = to_delete->data; // Move from to_delete to root
		if (parent == sub_root)
			sub_root->left = to_delete->left;
		else
			parent->right = to_delete->left;
	}
	delete to_delete; // Remove to_delete from tree.
	return true;
}

template<class Entry>
void Binary_tree<Entry>::create_by_preorder_and_inorder() {
	int n;
	Entry temp;
	vector<Entry> preorder, inorder;                     // store the user input;
	
	cout << "Please enter an integer representing the size of tree:";
	cin >> n;

	cout << "Please enter a series of entries in preorder, separated by spaces:" << endl;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		preorder.push_back(temp);
	}
	cout << "Please enter a series of entries in inorder, separated by spaces:" << endl;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		inorder.push_back(temp);
	}
	recursive_create(root, preorder, inorder);
	return;
}


template<class Entry>
void Binary_tree<Entry>::recursive_create(Binary_node<Entry>* &sub_root, vector<Entry> &preorder, vector<Entry> &inorder) {
	int len_pre = preorder.size(), len_in = inorder.size();
	if (!len_in || !len_pre){
		sub_root = NULL;
		return;
	}

	sub_root = new Binary_node<Entry>(preorder[0]);
	int in = 0;
	while (preorder[0] != inorder[in])
		in++;
	preorder.erase(preorder.begin());

	vector<Entry>::iterator it_in = inorder.begin();
	vector<Entry> inorder_left, inorder_right;
	if (in != 0) {
		inorder_left = vector<Entry>(it_in, it_in + in);
	}
	if (in != len_in - 1) {
		inorder_right = vector<Entry>(it_in + in + 1, inorder.end());
	}
	recursive_create(sub_root->left, preorder, inorder_left);
	recursive_create(sub_root->right, preorder, inorder_right);
	return;

}


template<class Entry>
int Binary_tree<Entry>::two_degree_count() {
	return recursive_two_degree_count(root);
}

template<class Entry>
int Binary_tree<Entry>::recursive_two_degree_count(Binary_node<Entry>* sub_root) {
	if (sub_root == NULL)
		return 0;
	else if (sub_root->left != NULL && sub_root->right != NULL) {
		return 1;
	}
	else {
		return recursive_two_degree_count(sub_root->left) + recursive_two_degree_count(sub_root->right);
	}
}

template<class Entry>
int Binary_tree<Entry>::count_leaf() {
	return recursive_count_leaf(root);
}

template<class Entry>
int Binary_tree<Entry>::recursive_count_leaf(Binary_node<Entry>* sub_root) {
	if (sub_root == NULL)
		return 0;
	if (sub_root->left == NULL && sub_root->right == NULL) {
		return 1;
	}
	return recursive_count_leaf(sub_root->left) + recursive_count_leaf(sub_root->right);
}

void print(int &x) {
	cout << x << ' ';
}

void print(char &x) {
	cout << x << ' ';
}


int main()
{
	Binary_tree<int> a, b;
	a.insert(2);
	a.insert(1);
	a.insert(3);
	//a.insert(6);
	//a.insert(5);
	//a.insert(7);
	//a.insert(9);
	//a.insert(4);
	//a.insert(8);
	cout << "inorder" << endl;
	a.inorder(print);
	cout << endl;

	cout << "count_leaf" << endl;
	cout << a.count_leaf();
	cout << endl;

	cout << "two_degree_count()" << endl;
	cout << a.two_degree_count() << endl;


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

	a.remove(1);
	a.remove(7);
	a.remove(6);

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

	//cout << "next is c" << endl;
	//Binary_tree<char> c;
	//c.create_by_preorder_and_inorder();

	//cout << "inorder" << endl;
	//c.inorder(print);
	//cout << endl;

	//cout << "preorder" << endl;
	//c.preorder(print);
	//cout << endl;

	//cout << "postorder" << endl;
	//c.postorder(print);
	//cout << endl;

	//cout << "breadthfirst" << endl;
	//c.breadthfirst(print);
	//cout << endl;

	//cout << "size" << endl;
	//cout << c.size() << endl;

	//cout << "Is it empty?" << endl;
	//if (c.empty())
	//	cout << "yes" << endl;
	//else
	//	cout << "no" << endl;






	system("pause");
	return 0;
}
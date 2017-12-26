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
	bool search_and_destroy(Binary_node<Entry>* &sub_root, const Entry& target);
	bool remove_root(Binary_node<Entry>* &sub_root);
	void recursive_create(Binary_node<Entry>* &sub_root, vector<Entry> &preorder, vector<Entry> &inorder);
	int recursive_two_degree_count(Binary_node<Entry>* sub_root);
	int recursive_count_leaf(Binary_node<Entry>* sub_root);
	int recursive_find_arrangement(Binary_node<Entry>* sub_root, const Entry& target);
	bool recursive_is_binary_tree(Binary_node<Entry>* sub_root);
	Entry maxValue(Binary_node<Entry>* sub_root);
	Entry minValue(Binary_node<Entry>* sub_root);
public:
	Binary_tree();
	bool empty()const;
	// 递归的主调函数
	bool insert(const Entry &new_data);
	void inorder(void(*visit)(Entry &)); 
	void preorder(void(*visit)(Entry &));
	void postorder(void(*visit)(Entry &));
	// 常用的方法
	void create_by_preorder_and_inorder();
	int size()const;
	int height()const;
	Binary_tree<Entry> copy();
	void clear();
	void deleteleaf();
	bool remove(const Entry& target);
	int two_degree_count();
	int count_leaf();
	int breadth();
	int find_arrangement(const Entry& target);
	// 广度优先遍历又称层次遍历，需要借助队列实现
	void breadthfirst(void(*visit)(Entry &));
	bool is_binary_tree();
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
	// 这里的insert在插入的同时按照大小顺序排列好，小的放在左边， 大的放在右边
	return search_and_insert(root, new_data);
}

template <class Entry>
bool Binary_tree<Entry>::search_and_insert(Binary_node<Entry>* &sub_root, const Entry &new_data) {
	// 递归的边界
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
		// false代表插入不成功
		return false;
	}
}

template<class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &)) {
	recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry>* sub_root, void (*visit)(Entry &)) {
	// 传进来的第二个参数是一个函数指针。名为visit,返回值为void,接受一个Entry类型的参数。这样写好处是保证了高度的OO特性，值得学习。
	//递归边界
	if (sub_root != NULL) {
		// 三种遍历只是下面三条语句的顺序不一样
		recursive_inorder(sub_root->left, visit);
		(*visit)(sub_root->data);       // 此处代表调用传进来的函数。
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
	// 递归的边界
	if (sub_root == NULL)
		return 0;
	// 经典的递归
	return 1 + recursive_size(sub_root->left) + recursive_size(sub_root->right);
}

template<class Entry>
int Binary_tree<Entry>::height()const {
	return recursive_height(root);
}

template<class Entry>
int Binary_tree<Entry>::recursive_height(Binary_node<Entry>* sub_root)const {
	// 递归边界
	if (sub_root == NULL)
		return 0;
	// 递归求最大的子树的高度
	int left = recursive_height(sub_root->left);
	int right = recursive_height(sub_root->right);
	// 只要大的
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

template<class Entry >
Binary_node<Entry>* Binary_tree<Entry>::recursive_copy(Binary_node<Entry>* sub_root) {
	// 递归边界
	if (sub_root == NULL)
		return NULL;
	// 深拷贝
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
		// 递归调用
		recursive_clear(sub_root->left);
		recursive_clear(sub_root->right);
		// 删除
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
	// 递归边界
	if (sub_root == NULL)
		return;
	// 每一次递归要做的事情
	if (sub_root->left == NULL && sub_root->right == NULL) {
		delete sub_root;
		sub_root = NULL;
		return;
	}
	// 递归调用
	recursive_deleteleaf(sub_root->left);
	recursive_deleteleaf(sub_root->right);
}

template<class Entry>
void Binary_tree<Entry>::breadthfirst(void(*visit)(Entry &)) {
	// 用一个队列作为辅助
	// 先把根节点入队
	queue<Binary_node<Entry>*> temp;
	temp.push(root);

	while (!temp.empty()) {
		// 新建一个临时指针指向队首元素，即为即将出队和访问的元素
		Binary_node<Entry>* p = temp.front();
		// 用指针抓住后就可以出队了，当然也可以在循环体末尾进行出队
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
/*
如何删除树的节点？
1. 被删除的节点是叶子节点
直接将其双亲节点的相应指针域置为空
2. 被删除的节点只有一个左子节点或者右子节点
将其双亲节点的相应指针域的值改为被删除节点相应的的左子树或右子树
3. 被删除的节点有两个子节点
以其前驱结点替代之，然后再删除该前驱结点
（意思是先将前驱结点的数据赋值给待删除节点，待删除节点的前驱结点一定是个叶子节点，容易删除。）
*/
template<class Entry>
bool Binary_tree<Entry>::remove_root(Binary_node<Entry>* &sub_root) {
	// 如果是空，返回false代表没找到
	if (sub_root == NULL)
		return false;
	Binary_node<Entry>* to_delete = sub_root;
	// Remember node to delete at end.
	if (sub_root->right == NULL)
		sub_root = sub_root->left;
	else if (sub_root->left == NULL)
		sub_root = sub_root->right;
	else { // Neither subtree is empty.
		// 一个节点的左子节点的最右子节点是这个节点的前驱结点
		to_delete = sub_root->left;
		// Move left to find predecessor（前驱).
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
	// 递归边界
	if (!len_in || !len_pre){
		sub_root = NULL;
		return;
	}

	// 先序序列的首元素一定是根节点
	sub_root = new Binary_node<Entry>(preorder[0]);
	int in = 0;
	// 找到根节点在中序序列中的下标
	while (preorder[0] != inorder[in])
		in++;
	// 复制后便可以删除首元素
	preorder.erase(preorder.begin());

	// 迭代器
	vector<Entry>::iterator it_in = inorder.begin();
	// 两个临时向量，存放将inorder拆分后的两个序列
	vector<Entry> inorder_left, inorder_right;
	// 按照之前找到的根节点的下标将序列拆分并赋值
	if (in != 0) {
		inorder_left = vector<Entry>(it_in, it_in + in);   // vector的构造函数，it_in存的是inorder的首元素的下标
	}
	if (in != len_in - 1) {
		inorder_right = vector<Entry>(it_in + in + 1, inorder.end());
	}
	// 递归调用
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
	// 递归边界
	if (sub_root == NULL)
		return 0;
	// 递归执行主体
	else if (sub_root->left != NULL && sub_root->right != NULL) {
		return 1;
	}
	// 递归调用
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


template<class Entry>
int Binary_tree<Entry>::breadth() {
	return count_leaf();
}

template<class Entry>
int Binary_tree<Entry>::find_arrangement(const Entry& target) {
	return recursive_find_arrangement(root, target);
}

template<class Entry>
int Binary_tree<Entry>::recursive_find_arrangement(Binary_node<Entry>* sub_root, const Entry& target) {
	if (sub_root == NULL)
		return 0;
	if (sub_root->data == target)
		return 1;
	int i = recursive_find_arrangement(sub_root->left, target);
	int j = recursive_find_arrangement(sub_root->right, target);
	if (i != 0)
		return i + 1;
	else if (j != 0)
		return j + 1;
	else
		return 0;
		
}


template<class Entry>
bool Binary_tree<Entry>::is_binary_tree() {
	return recursive_is_binary_tree(root);
}

template<class Entry>
bool Binary_tree<Entry>::recursive_is_binary_tree(Binary_node<Entry>* sub_root) {
	if (sub_root == NULL)
		return true;
	// 如果左子树最大值大于根节点，则返回false
	if (sub_root->left != NULL && maxValue(sub_root->left) > sub_root->data)
		return false;
	// 如果右子树最小值小于根节点，则返回false
	if (sub_root->right != NULL && minValue(sub_root->right) < sub_root->data)
		return false;

	// 递归判断
	if (!recursive_is_binary_tree(sub_root->left) || !recursive_is_binary_tree(sub_root->right))
		return false;
	return true;
}

template<class Entry>
Entry Binary_tree<Entry>::maxValue(Binary_node<Entry>* sub_root) {
		while (sub_root->right)
			sub_root = sub_root->right;
	return sub_root->data;
}

template<class Entry>
Entry Binary_tree<Entry>::minValue(Binary_node<Entry>* sub_root) {
		while (sub_root->left)
			sub_root = sub_root->left;
	return sub_root->data;
}

void print(int &x) {
	cout << x << ' ';
}

void print(char &x) {
	cout << x << ' ';
}


int main()
{
	Binary_tree<int> a;

	cout << "根据先序遍历序列中序遍历序列创建树" << endl;
	a.create_by_preorder_and_inorder();

	cout << "统计度为2的结点数" << endl;
	cout << a.two_degree_count() << endl;

	cout << "统计二叉树的宽度" << endl;
	cout << a.breadth() << endl;

	cout << "计算二叉树中指定结点p所在层次" << endl;
	cout << a.find_arrangement(20) << endl;

	cout << "判断当前二叉树是否为二叉查找树" << endl;
	if (a.is_binary_tree())
		cout << "是二叉查找树" << endl;
	else
		cout << "不是二叉查找树" << endl;


	system("pause");
	return 0;
}

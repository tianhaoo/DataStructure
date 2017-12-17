#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct item
{
	string word;
	int wordCount;
	item* next;
};

class Hash
{
private:
	static const int tableSize = 100;
	item* hashTable[tableSize];

public:
	Hash();
	int hashFunction(string word);
	void addUp(string word);
	//bool isExist(string word);
	item* find(string word);
	void printTable();
	void printTable(int frequency);

};


Hash::Hash() {
	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = new item;
		hashTable[i]->word = "#";
		hashTable[i]->wordCount = 0;
		hashTable[i]->next = NULL;
	}
}

int Hash::hashFunction(string key) {
	int sum = 0;
	int index = 0;

	for (int i = 0; i < key.length(); i++) {
		sum += static_cast<int>(key[i]);
	}

	index = sum % tableSize;
	return index;
}

//bool Hash::isExist(string word) {
//	int index = hashFunction(word);			// 用哈希函数算出单词索引
//
//	item* p = hashTable[index]->next;
//		 
//	while (p != NULL) {                      // 遍历该索引下面的所有单词
//		if (p->word == word)                 // 如果相等就返回true
//			return true;
//		p = p->next;
//	}
//	return false;
//}


item* Hash::find(string word) {
	int index = hashFunction(word);

	if (hashTable[index]->word == "#") {
		return NULL;
	}
	else if (hashTable[index]->word == word) {
		return hashTable[index];
	}
	else {
		item* p = hashTable[index]->next;

		while (p != NULL) {
			if (p->word == word)
				return p;
			p = p->next;
		}

	}
	return NULL;
}


void Hash::addUp(string word) {					 // 统计单词个数

	item* p = find(word);
	if (p != NULL) {						 // 如果单词存在， 那么单词个数加一
		p->wordCount++;
		return;
	}

	else {                                        // 如果单词不存在，那么就新增这个单词
		int index = hashFunction(word);			  // 用哈希函数算出单词索引
		if (hashTable[index]->word == "#") {      // 如果单词没有冲突， 那么直接给这个条目赋值
			hashTable[index]->word = word;
			hashTable[index]->wordCount = 1;
			return;
		}
		else {                                    // 如果产生冲突， 那么用链式结构存储在已经存在的条目的后方
			item* ptr = hashTable[index];         // 临时指针
			item* n = new item;                   // 临时指针

			n->word = word;
			n->wordCount = 1;
			n->next = NULL;

			while (ptr->next != NULL) {
				ptr = ptr->next;
			}

			ptr->next = n;
			return;
		}
	}

}

void Hash::printTable() {
	for (int i = 0; i < tableSize; i++) {
		item* p = hashTable[i];
		if (p->word != "#")
			cout << p->word << ':' << p->wordCount << endl;
		else {
			p = p->next;
			while (p != NULL) {
				cout << p->word << ':' << p->wordCount << endl;
				p = p->next;
			}
		}

	}
	return;
}

void Hash::printTable(int frequency) {
	for (int i = 0; i < tableSize; i++) {
		item* p = hashTable[i];
		if (p->word != "#" && p->wordCount >= frequency)
			cout << p->word << ':' << p->wordCount << endl;
		else {
			p = p->next;
			while (p != NULL && p->wordCount >= frequency) {
				cout << p->word << ':' << p->wordCount << endl;
				p = p->next;
			}
		}

	}
	return;
}

int main()
{
	int number = 0;
	string s;
	Hash dic;
	ifstream in("Text.txt");

	while (in >> s) {
		dic.addUp(s);
	}
	in.close();

	cout << "所有的单词的词频：" << endl;
	dic.printTable();

	cout << "请输入目标频率：" << endl;
	cin >> number;
	cout << "词频大于" << number << "的单词:" << endl;
	dic.printTable(number);
	return 0;
}
	
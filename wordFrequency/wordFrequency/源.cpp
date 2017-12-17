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
//	int index = hashFunction(word);			// �ù�ϣ���������������
//
//	item* p = hashTable[index]->next;
//		 
//	while (p != NULL) {                      // ������������������е���
//		if (p->word == word)                 // �����Ⱦͷ���true
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


void Hash::addUp(string word) {					 // ͳ�Ƶ��ʸ���

	item* p = find(word);
	if (p != NULL) {						 // ������ʴ��ڣ� ��ô���ʸ�����һ
		p->wordCount++;
		return;
	}

	else {                                        // ������ʲ����ڣ���ô�������������
		int index = hashFunction(word);			  // �ù�ϣ���������������
		if (hashTable[index]->word == "#") {      // �������û�г�ͻ�� ��ôֱ�Ӹ������Ŀ��ֵ
			hashTable[index]->word = word;
			hashTable[index]->wordCount = 1;
			return;
		}
		else {                                    // ���������ͻ�� ��ô����ʽ�ṹ�洢���Ѿ����ڵ���Ŀ�ĺ�
			item* ptr = hashTable[index];         // ��ʱָ��
			item* n = new item;                   // ��ʱָ��

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

	cout << "���еĵ��ʵĴ�Ƶ��" << endl;
	dic.printTable();

	cout << "������Ŀ��Ƶ�ʣ�" << endl;
	cin >> number;
	cout << "��Ƶ����" << number << "�ĵ���:" << endl;
	dic.printTable(number);
	return 0;
}
	
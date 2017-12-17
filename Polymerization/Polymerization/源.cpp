#include <iostream>
#include <cctype> //for tolower()
using namespace std;
#include "polynomial.h"
#include "stack.h"

typedef Stack<Polynomial> MyStack;
typedef Polynomial MyPolynomial;

void introduction();
bool do_command(char command, Stack<Polynomial> &stored_polynomials);
char get_command();

int main()
{
	Stack<Polynomial> stored_polynomial;
	introduction();
	while (do_command(get_command(), stored_polynomial));
	system("pause");
	return 0;
}

bool do_command(char command, Stack<Polynomial> &stored_polynomials)
//ǰ̬����һ��������һ���Ϸ���calculator command
//��̬��ִ���ɵ�һ�����������Ĳ��������������ǵĶ���ʽ��ջ���档
//������������Ҫʹ�����������е����巨����뷨�ķ�������������Щ���顣��
// ���command=='q' ����false�����򷵻�true
//ʹ����Щ������typedef Polynomial<double> MyPolynomial;
//              typedef Stack<MyPolynomial> MyStack;
// utility�е� Error_code,���utility��linked_queue.h��stack.h��������
// ��Ȼ�����ظ�������Error_code��������utility.h������һ�仰��
//#ifndef UTILITY_H_INCLUDED
//#define UTILITY_H_INCLUDED
//.....
//#endif
//���ԣ�Error_code��ʵ���ᱻ�ظ�����ġ�
{
	MyPolynomial p;
	MyPolynomial q;
	MyPolynomial r;
	Error_code outcome;
	switch (command) {
	case '?':
		p.read();
		outcome = stored_polynomials.push(p);
		if (outcome == overflow)
			cout << "Warning: Stack full, lost polynomial" << endl;
		break;
	case '=':
		if (stored_polynomials.empty())
			cout << "Stack empty" << endl;
		else {
			stored_polynomials.top(p);
			p.print();
		}
		break;
	case '+':
		if (stored_polynomials.empty())
			cout << "Stack empty" << endl;
		else {
			stored_polynomials.top(p);
			stored_polynomials.pop();
			if (stored_polynomials.empty()) {
				cout << "Stack has just one polynomial" << endl;
				stored_polynomials.push(p);
			}
			else {
				stored_polynomials.top(q);
				stored_polynomials.pop();
				r.equals_sum(p, q);
				if (stored_polynomials.push(r) == overflow)
					cout << "Warning: Stack full, lost polynomial" << endl;
			}
		}
		break;
	case '-':
		if (stored_polynomials.empty())
			cout << "Stack empty" << endl;
		else {
			stored_polynomials.top(p);
			stored_polynomials.pop();
			if (stored_polynomials.empty()) {
				cout << "Stack has just one polynomial" << endl;
				stored_polynomials.push(p);
			}
			else {
				stored_polynomials.top(q);
				stored_polynomials.pop();
				r.equals_difference(q, p);// ջ���Ķ���ʽӦ����Ϊ����
				if (stored_polynomials.push(r) == overflow)
					cout << "Warning: Stack full, lost polynomial" << endl;
			}
		}
		break;
	case '*':
		if (stored_polynomials.empty())
			cout << "Stack empty" << endl;
		else {
			stored_polynomials.top(p);
			stored_polynomials.pop();
			if (stored_polynomials.empty()) {
				cout << "Stack has just one polynomial" << endl;
				stored_polynomials.push(p);
			}
			else {
				stored_polynomials.top(q);
				stored_polynomials.pop();
				r.equals_product(p, q);
				if (stored_polynomials.push(r) == overflow)
					cout << "Warning: Stack full, lost polynomial" << endl;
			}
		}
		break;
		//��Ҫʵ��һ������

	case 'q':
		cout << "Calculation finished." << endl;
		return false;
	}
	return true;
}

char get_command() {
	char command;
	bool waiting = true;
	cout << "����ѡ��һ������Ҫִ�е�����:";
	while (waiting) {
		cin >> command;
		if (command == '?' || command == '=' ||
			command == '+' || command == '-' ||
			command == '*' || command == 'q')
			waiting = false;
		else {
			cout << "\n��ѡ������������������������\n"
				<< "[?] ����һ������ʽ" << endl
				<< "[=] ����ջ���Ķ���ʽ" << endl
				<< "[+] ��ջ������2������ʽ���" << endl
				<< "[-] ���� ע�⣺��ջ��������һ��ǰȥջ���Ķ���ʽ" << endl
				<< "[*] ��ջ������������ʽ���" << endl
				<< "[q] �˳��������" << endl;
		}
	}
	return command;
}

void introduction() {
	cout << "����һ������ʽ���沨����������ʵ���˶���ʽ֮��ļӼ��ͳ˷�." << endl
		<< "������һ���Ϸ��������:" << endl
		<< "[?] ����һ������ʽ" << endl
		<< "[=] ����ջ���Ķ���ʽ" << endl
		<< "[+] ��ջ������2������ʽ���" << endl
		<< "[-] ���� ע�⣺��ջ��������һ����ȥջ���Ķ���ʽ" << endl
		<< "[*] ��ջ������������ʽ���" << endl
		<< "[q] �˳��������" << endl;
}

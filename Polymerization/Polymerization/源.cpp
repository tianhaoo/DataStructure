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
//前态：第一个参数是一个合法的calculator command
//后态：执行由第一个参数决定的操作，作用在我们的多项式的栈上面。
//（在这里我们要使用类似物理中的整体法与隔离法的方法来做看待这些事情。）
// 如果command=='q' 返回false，否则返回true
//使用哪些东西：typedef Polynomial<double> MyPolynomial;
//              typedef Stack<MyPolynomial> MyStack;
// utility中的 Error_code,这个utility由linked_queue.h和stack.h都包含了
// 虽然这里重复定义了Error_code，但是在utility.h里面有一句话：
//#ifndef UTILITY_H_INCLUDED
//#define UTILITY_H_INCLUDED
//.....
//#endif
//所以，Error_code其实不会被重复定义的。
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
				r.equals_difference(q, p);// 栈顶的多项式应该作为减数
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
		//还要实现一个除法

	case 'q':
		cout << "Calculation finished." << endl;
		return false;
	}
	return true;
}

char get_command() {
	char command;
	bool waiting = true;
	cout << "请你选择一个你想要执行的命令:";
	while (waiting) {
		cin >> command;
		if (command == '?' || command == '=' ||
			command == '+' || command == '-' ||
			command == '*' || command == 'q')
			waiting = false;
		else {
			cout << "\n您选择的命令有误，请输入下列命令：\n"
				<< "[?] 读入一个多项式" << endl
				<< "[=] 返回栈顶的多项式" << endl
				<< "[+] 将栈顶部的2个多项式相加" << endl
				<< "[-] 做差 注意：是栈顶的下面一个前去栈顶的多项式" << endl
				<< "[*] 将栈顶的两个多项式相乘" << endl
				<< "[q] 退出计算过程" << endl;
		}
	}
	return command;
}

void introduction() {
	cout << "这是一个多项式的逆波兰计算器，实现了多项式之间的加减和乘法." << endl
		<< "请输入一个合法的运算符:" << endl
		<< "[?] 读入一个多项式" << endl
		<< "[=] 返回栈顶的多项式" << endl
		<< "[+] 将栈顶部的2个多项式相加" << endl
		<< "[-] 做差 注意：是栈顶的下面一个减去栈顶的多项式" << endl
		<< "[*] 将栈顶的两个多项式相乘" << endl
		<< "[q] 退出计算过程" << endl;
}

#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

//为了使得Polynomial类可以输入输出
#include <iostream>
using namespace std;
#include <stdio.h>  ////为了使得Polynomial类可以输入输出
#include "extendedQueue.h"

struct Term {
	int degree;
	double coefficient;
	Term(int exponent = 0, double scalar = 0.0) {
		degree = exponent;
		coefficient = scalar;
	}
	void operator=(const Term &item) {
		degree = item.degree;
		coefficient = item.coefficient;
	}
};


class Polynomial : private ExtendedQueue<Term> {
public:
	void read();
	void print() const;
	void equals_sum(Polynomial p, Polynomial q);// 这里没有使用引用的方式，而是使用直接传值的方式
												// 因为我们这个方法需要修改形参p,q的值，但是我们不打算修改实参的值，所以这么做。
												// 可以说这个开销是由封装带来的。
												//（因为我们无法直接使用对象p的front和rear指针，而是需要通过对象p的公共方法来操控数据）
	void equals_difference(Polynomial p, Polynomial q);
	void equals_product(Polynomial p, Polynomial q);
	//Error_code equals_quotient(Polynomial p, Polynomial q);
	/*!!!safety!!!*/    void clear() { while (!this->empty()) { this->serve(); } }
	//这一句话非常的重要，如果如果栈pop的时候，节点(Node)里面的
	// Polymonial类申请过的空间就无法回收回来。
	int degree() const;
private:
	void mult_term(Polynomial p, Term t);
	//只要实现了mult_term,那么让equals_product调用一下这个就可以啦
};


void Polynomial::read() {
	clear();
	double coefficient;
	int last_exponent, exponent;
	bool first_term = true;
	cout << "输入多项式的系数和指数,\n"
		<< "每一行输入一个多项式里面的一个项，按照指数递减的方式输入" << endl;
	cout << "当输入的系数为零的时候，或者指数为0的时候，默认输入结束。" << endl;
	do {
		cout << "系数？（double类型的） " << flush;
		//cin >> coefficient;
		scanf_s("%lf", &coefficient);
		if (coefficient != 0.0) {
			cout << "指数（unsigned int）" << flush;
			//cin>>exponent;
			scanf_s("%d", &exponent);
			//使用scanf而不使用cin可以方式输入一串乱七八糟的东西进来使得程序崩溃
			if ((!first_term && exponent >= last_exponent) || exponent < 0) {
				exponent = 0;
				cout << "检测到指数的顺序没有按照递减的方式输入，终止输入，截取有效的输入作为多项式的输入放入栈顶"
					<< endl;
			}
			else {
				Term new_term(exponent, coefficient); // 利用了复制构造函数
				append(new_term);
				first_term = false;
			}
			last_exponent = exponent;
		}
	} while (coefficient != 0.0 && exponent != 0);
}

void Polynomial::print() const
{
	Node<Term> *print_node = front;
	bool first_term = true;
	while (print_node != NULL) {
		Term &print_term = print_node->entry; // print_term现在就是Term

											  //处理首项的符号
		if (first_term) { //如果现在正在处理第一项,那么要注意第一项的+不要输出
			first_term = false;
			if (print_term.coefficient<0) cout << " -";
		}
		else if (print_term.coefficient<0)cout << "-";
		else cout << " + ";
		//处理系数
		double r = (print_term.coefficient >= 0) ? //获取系数的绝对值
			print_term.coefficient : -(print_term.coefficient);
		if (r != 1) cout << r; //如果系数是1的话，那就不要输出了
		if (print_term.degree>1) cout << " X^" << print_term.degree;
		if (print_term.degree == 1) cout << " X";
		if (r == 1 && print_term.degree == 0) cout << "1";
		print_node = print_node->next;
	}
	if (first_term) cout << "0";//给一个空的多项式输出一个0，注意这里的空的多项式 != 0多项式
	cout << endl;
}

void Polynomial::equals_sum(Polynomial p, Polynomial q)
/* Post: The Polynomial object is reset as the sum of the two parameters. */
{
	clear();
	while (!p.empty() || !q.empty()) {
		Term p_term, q_term;
		if (p.degree() > q.degree()) {
			p.serve_and_retrieve(p_term);
			append(p_term);
		}
		else if (q.degree() > p.degree()) {
			q.serve_and_retrieve(q_term);
			append(q_term);
		}
		else {
			p.serve_and_retrieve(p_term);
			q.serve_and_retrieve(q_term);
			if (p_term.coefficient + q_term.coefficient != 0) {
				Term answer_term(p_term.degree,
					p_term.coefficient + q_term.coefficient);
				append(answer_term);
			}
		}
	}
}

void Polynomial::equals_difference(Polynomial p, Polynomial q) {
	clear();
	//p-q = p+(-q)
	Polynomial tmp;
	tmp.clear();
	//tmp = -q;
	while (!q.empty()) {
		Term q_term;
		q.serve_and_retrieve(q_term);
		(q_term).coefficient *= (-1);
		tmp.append(q_term);
	}
	equals_sum(p, tmp);

}

/*
void Polynomial::equals_product(Polynomial p, Polynomial q){
value = p.value * q.value;
}
*/
/*
Error_code Polynomial::equals_quotient(Polynomial p, Polynomial q){
Error_code outcome = success;
if(q.value>-1e-10 && q.value<1e-10){
outcome = overflow;
return outcome;
}
value = p.value/q.value;
return outcome;
}
*/

int Polynomial::degree() const
{
	if (empty())return -1;
	Term lead;
	retrieve(lead);
	return lead.degree;
}

//这是一个私有的方法
void Polynomial::mult_term(Polynomial p, Term t)
// 前态：传进来符合标准类型的2个参数
// 后态：使得this所指向的Polynomial类加上  多项式p乘以这个Term t
//      不过这样写的效率比较低
{
	if (t.coefficient == 0) return; //如果乘以一个0，那么我们什么也不加
	Polynomial tmp;
	Term p_term;
	tmp.clear();
	while (!p.empty()) {
		p.serve_and_retrieve(p_term);
		p_term.coefficient *= t.coefficient;
		p_term.degree += t.degree;
		tmp.append(p_term);
	}
	Polynomial self(*this);//调用复制构造函数
	this->equals_sum(self, tmp);
}


void Polynomial::equals_product(Polynomial p, Polynomial q) {
	this->clear();
	Term q_term;
	while (!q.empty()) {
		q.serve_and_retrieve(q_term);
		this->mult_term(p, q_term); //写上this只是为了增加可读性
	}
}
#endif // POLYNOMIAL_H_INCLUDED

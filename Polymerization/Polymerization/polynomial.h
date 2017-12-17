#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

//Ϊ��ʹ��Polynomial������������
#include <iostream>
using namespace std;
#include <stdio.h>  ////Ϊ��ʹ��Polynomial������������
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
	void equals_sum(Polynomial p, Polynomial q);// ����û��ʹ�����õķ�ʽ������ʹ��ֱ�Ӵ�ֵ�ķ�ʽ
												// ��Ϊ�������������Ҫ�޸��β�p,q��ֵ���������ǲ������޸�ʵ�ε�ֵ��������ô����
												// ����˵����������ɷ�װ�����ġ�
												//����Ϊ�����޷�ֱ��ʹ�ö���p��front��rearָ�룬������Ҫͨ������p�Ĺ����������ٿ����ݣ�
	void equals_difference(Polynomial p, Polynomial q);
	void equals_product(Polynomial p, Polynomial q);
	//Error_code equals_quotient(Polynomial p, Polynomial q);
	/*!!!safety!!!*/    void clear() { while (!this->empty()) { this->serve(); } }
	//��һ�仰�ǳ�����Ҫ��������ջpop��ʱ�򣬽ڵ�(Node)�����
	// Polymonial��������Ŀռ���޷����ջ�����
	int degree() const;
private:
	void mult_term(Polynomial p, Term t);
	//ֻҪʵ����mult_term,��ô��equals_product����һ������Ϳ�����
};


void Polynomial::read() {
	clear();
	double coefficient;
	int last_exponent, exponent;
	bool first_term = true;
	cout << "�������ʽ��ϵ����ָ��,\n"
		<< "ÿһ������һ������ʽ�����һ�������ָ���ݼ��ķ�ʽ����" << endl;
	cout << "�������ϵ��Ϊ���ʱ�򣬻���ָ��Ϊ0��ʱ��Ĭ�����������" << endl;
	do {
		cout << "ϵ������double���͵ģ� " << flush;
		//cin >> coefficient;
		scanf_s("%lf", &coefficient);
		if (coefficient != 0.0) {
			cout << "ָ����unsigned int��" << flush;
			//cin>>exponent;
			scanf_s("%d", &exponent);
			//ʹ��scanf����ʹ��cin���Է�ʽ����һ�����߰���Ķ�������ʹ�ó������
			if ((!first_term && exponent >= last_exponent) || exponent < 0) {
				exponent = 0;
				cout << "��⵽ָ����˳��û�а��յݼ��ķ�ʽ���룬��ֹ���룬��ȡ��Ч��������Ϊ����ʽ���������ջ��"
					<< endl;
			}
			else {
				Term new_term(exponent, coefficient); // �����˸��ƹ��캯��
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
		Term &print_term = print_node->entry; // print_term���ھ���Term

											  //��������ķ���
		if (first_term) { //����������ڴ����һ��,��ôҪע���һ���+��Ҫ���
			first_term = false;
			if (print_term.coefficient<0) cout << " -";
		}
		else if (print_term.coefficient<0)cout << "-";
		else cout << " + ";
		//����ϵ��
		double r = (print_term.coefficient >= 0) ? //��ȡϵ���ľ���ֵ
			print_term.coefficient : -(print_term.coefficient);
		if (r != 1) cout << r; //���ϵ����1�Ļ����ǾͲ�Ҫ�����
		if (print_term.degree>1) cout << " X^" << print_term.degree;
		if (print_term.degree == 1) cout << " X";
		if (r == 1 && print_term.degree == 0) cout << "1";
		print_node = print_node->next;
	}
	if (first_term) cout << "0";//��һ���յĶ���ʽ���һ��0��ע������ĿյĶ���ʽ != 0����ʽ
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

//����һ��˽�еķ���
void Polynomial::mult_term(Polynomial p, Term t)
// ǰ̬�����������ϱ�׼���͵�2������
// ��̬��ʹ��this��ָ���Polynomial�����  ����ʽp�������Term t
//      ��������д��Ч�ʱȽϵ�
{
	if (t.coefficient == 0) return; //�������һ��0����ô����ʲôҲ����
	Polynomial tmp;
	Term p_term;
	tmp.clear();
	while (!p.empty()) {
		p.serve_and_retrieve(p_term);
		p_term.coefficient *= t.coefficient;
		p_term.degree += t.degree;
		tmp.append(p_term);
	}
	Polynomial self(*this);//���ø��ƹ��캯��
	this->equals_sum(self, tmp);
}


void Polynomial::equals_product(Polynomial p, Polynomial q) {
	this->clear();
	Term q_term;
	while (!q.empty()) {
		q.serve_and_retrieve(q_term);
		this->mult_term(p, q_term); //д��thisֻ��Ϊ�����ӿɶ���
	}
}
#endif // POLYNOMIAL_H_INCLUDED

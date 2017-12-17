#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "utility.h" // Error_code
#include "node.h"

/*
struct Term{
int degree;
double coefficient;
Term(int exponent, double scalar){
degree = exponent;
coefficient = scalar;
}
};
*/

// �����ǵ����Ӧ�����棬Queue_entry������廯��ΪTerm
template <class Queue_entry>
class Queue {
public:
	Queue();
	bool empty() const;
	Error_code append(const Queue_entry &item);
	Error_code serve();
	Error_code retrieve(Queue_entry &item) const;
	// safety features for linked structures;
	~Queue();
	Queue(const Queue<Queue_entry> &original);
	void operator=(const Queue<Queue_entry> &original);

protected:
	Node<Queue_entry> *front, *rear;
};




template <class Queue_entry>
Queue<Queue_entry>::Queue()

{
	front = rear = NULL;
}

template <class Queue_entry>
bool Queue<Queue_entry>::empty() const
//���Ϊ�գ��򷵻�true�����򷵻�false
{
	return (front == NULL);
}


template <class Queue_entry>
Error_code Queue<Queue_entry>::append(const Queue_entry &item)
{
	Node<Queue_entry> *new_rear = new Node<Queue_entry>(item); //����ҪΪNode<Queue_entry>д���ƹ��캯��
	if (new_rear == NULL) return overflow;
	if (rear == NULL) front = rear = new_rear;
	else {
		rear->next = new_rear;
		rear = new_rear;
	}
	return success;
}

template <class Queue_entry>
Error_code Queue<Queue_entry>::serve()

{
	if (front == NULL) return underflow;
	Node<Queue_entry> *old_front = front;
	front = old_front->next;
	if (front == NULL) rear = NULL;
	delete old_front;
	return success;
}

template <class Queue_entry>
Error_code Queue<Queue_entry>::retrieve(Queue_entry &item) const

{
	if (front == NULL) return underflow;
	item = front->entry; //ҪΪQueue_entryдһ����ֵ�ŵ�����
	return success;
}

template <class Queue_entry>
Queue<Queue_entry>::~Queue()
{
	while (!empty()) {
		serve();
	}
}

template <class Queue_entry>
Queue<Queue_entry>::Queue(const Queue<Queue_entry> &original)
// ����Ǹ��ƹ��캯��
{
	Node<Queue_entry> *new_rear, *original_node = original.front;
	if (original_node == NULL) {
		front = rear = NULL;
	}
	else {
		front = new Node<Queue_entry>(original_node->entry);
		new_rear = front;

		while (original_node->next != NULL) {
			original_node = original_node->next;
			new_rear->next = new Node<Queue_entry>(original_node->entry);
			new_rear = new_rear->next;
		}
		rear = new_rear;
		rear->next = NULL;
	}
}

template <class Queue_entry>
void Queue<Queue_entry>::operator=(const Queue<Queue_entry> &original)
{
	Node<Queue_entry> *new_front, *new_rear, *original_node = original.front;
	if (original_node == NULL) {
		new_front = new_rear = NULL;
		return;
	}
	else {
		new_front = new_rear = new Node<Queue_entry>(original_node->entry);
		while (original_node->next != NULL) {
			original_node = original_node->next;
			new_rear->next = new Node<Queue_entry>(original_node->entry);
			new_rear = new_rear->next;
		}
	}
	while (!empty()) {
		serve();
	}
	front = new_front;
	rear = new_rear;
	rear->next = NULL;
}
#endif // QUEUE_H_INCLUDED
#pragma once

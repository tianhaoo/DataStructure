#ifndef EXTENDEDQUEUE_H_INCLUDED
#define EXTENDEDQUEUE_H_INCLUDED

#include "queue.h"

template <class Queue_entry>
class ExtendedQueue : public Queue<Queue_entry>
{
public:
	bool full() const;
	int size() const;

	Error_code serve_and_retrieve(Queue_entry &item);
};

template <class Queue_entry>
bool ExtendedQueue<Queue_entry>::full() const
// ����޷������뵽�ռ�Ļ�����ô�ͷ���true˵�����ǵĶ����Ѿ�������
// �޷��������¸����Ԫ���ˡ�
{
	Node<Queue_entry> *tmp;
	tmp = new Node<Queue_entry>;
	if (tmp == NULL) return true;
	else return false;
}

template <class Queue_entry>
int ExtendedQueue<Queue_entry>::size() const

{
	Node<Queue_entry> *window = this->front;
	int count = 0;
	while (window != NULL) {
		window = window->next;
		count++;
	}
	return count;
}

template <class Queue_entry>
Error_code ExtendedQueue<Queue_entry>::serve_and_retrieve(Queue_entry &item)
{
	this->retrieve(item);
	return this->serve();
}
#endif // EXTENDEDQUEUE_H_INCLUDED
#pragma once

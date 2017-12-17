#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "utility.h"
template <class Node_entry>
struct Node {
	Node_entry entry;
	Node *next;
	Node() { next = NULL; } //���������Ĺ��캯��
	Node(Node_entry item, Node * add_on = NULL);  //���ƹ��캯��
};


template <class Node_entry>
//Node<Node_entry>::Node(Node_entry item, Node * add_on = 0)
//һ��ʼ���ǰ��������д��д�ġ�����Ĭ�ϵ���ֵֻ�����ඨ�������д��=0��
Node<Node_entry>::Node(Node_entry item, Node * add_on)
{
	entry = item;
	/*===========================================*/
	// ��Ϊ�������ڶ�����Node_entry��Ķ�����и�ֵ����������
	//�����ڶ���Node_entry�����͵�ʱ��ҪΪNode_entry�����дһ����ֵ������
	// �������Node_entryΪ����֮��ģ�����int�� double��long֮��ģ��Ͳ���Ҫ��
	// ��Ϊ��Щ�����Ѿ�д���˸�ֵ�ŵĺ���
	// ���������ǵ�����������棬������Ҫ��Polynomial��Termд��ֵ�ŵ�����
	/*===========================================*/
	next = add_on;
}

#endif // NODE_H_INCLUDED
#pragma once

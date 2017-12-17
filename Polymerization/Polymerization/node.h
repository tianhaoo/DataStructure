#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "utility.h"
template <class Node_entry>
struct Node {
	Node_entry entry;
	Node *next;
	Node() { next = NULL; } //不带参数的构造函数
	Node(Node_entry item, Node * add_on = NULL);  //复制构造函数
};


template <class Node_entry>
//Node<Node_entry>::Node(Node_entry item, Node * add_on = 0)
//一开始我是按照上面的写法写的。但是默认的数值只能在类定义的里面写（=0）
Node<Node_entry>::Node(Node_entry item, Node * add_on)
{
	entry = item;
	/*===========================================*/
	// 因为这里是在对两个Node_entry类的对象进行赋值操作，所以
	//这里在定义Node_entry的类型的时候，要为Node_entry这个类写一个赋值号重载
	// 但是如果Node_entry为数字之类的，比如int， double，long之类的，就不需要。
	// 因为这些类型已经写好了赋值号的含义
	// 所以在我们的这个例子里面，我们需要对Polynomial和Term写赋值号的重载
	/*===========================================*/
	next = add_on;
}

#endif // NODE_H_INCLUDED
#pragma once

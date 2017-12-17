#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "utility.h" // for cstddef and Error_code
#include "node.h"

template <class Stack_entry>
class Stack
	// Stack由一个一个的Node结构体链接而成，每个结构体里面存放的东西才是我们真正想要的东西
	// 而Stack_entry是如何存放的，应该对用户隐藏起来。
	// 所以，Stack_entry这个类应该和Node_entry的类是同样的类型。
{
public:
	// Standard Stack methods.
	Stack(); //构造函数
	bool empty() const;
	Error_code push(const Stack_entry &item); // 这个地方我们应该是要将item复制一份然后压到栈里面去。
	Error_code pop(); //弹出一个来以后,需要将Node节点delete掉，但是要注意还需要把Stack_entry先delete掉
	Error_code top(Stack_entry &item) const;
	// Safety features for linked structures
	~Stack();
	Stack(const Stack<Stack_entry> &original);
	void operator=(const Stack<Stack_entry> &original);
protected:
	Node<Stack_entry> *top_node;
};


template <class Stack_entry>
Stack<Stack_entry>::Stack()
// 前态：没有
// 后态：头结点top_node定义为NULL
{
	top_node = NULL; //将头结点接地
}


template <class Stack_entry>
bool Stack<Stack_entry>::empty() const
// 前态： 没有
// 后态： 如果栈为空，则返回true，否则返回false
{
	return ((top_node) == NULL);
}

template <class Stack_entry>
Error_code Stack<Stack_entry>::push(const Stack_entry &item)
// 前态：没有
// 后态：动态申请一个节点用来保存Stack_entry，如果申请不到的话，返回overflow的Error_code
// 在这个题目中，我们的Stack_entry将会成为Polynomial类
{
	Node<Stack_entry> *new_top = new Node<Stack_entry>(item, top_node);
	/*
	*我们将会用到的是Polynomial类的对象作为item，那么在Node的复制构造函数里面就需要
	*对这个item做一个硬拷贝。
	*/
	if (new_top == NULL) return overflow;
	top_node = new_top;
	return success;
}

template <class Stack_entry>
Error_code Stack<Stack_entry>::pop()

{
	Node<Stack_entry> *old_top = top_node;
	if (top_node == NULL) return underflow;
	top_node = top_node->next;
	(old_top->entry).clear();
	//这就要求Stack_entry类型必须要有一个public的方法clear()
	//这就要求Stack_entry类型必须要有一个public的方法clear()
	//这就要求Stack_entry类型必须要有一个public的方法clear()
	//这就要求Stack_entry类型必须要有一个public的方法clear()
	//这就要求Stack_entry类型必须要有一个public的方法clear()
	//这就要求Stack_entry类型必须要有一个public的方法clear()
	//这就要求Stack_entry类型必须要有一个public的方法clear()
	//这就要求Stack_entry类型必须要有一个public的方法clear()
	//这就要求Stack_entry类型必须要有一个public的方法clear()

	delete old_top;
	//这个时候是将Node节点的空间删除掉。但是这个会调用到Polynomial的析构函数吗？？？？？？？
	//这个时候是将Node节点的空间删除掉。但是这个会调用到Polynomial的析构函数吗？？？？？？？
	//这个时候是将Node节点的空间删除掉。但是这个会调用到Polynomial的析构函数吗？？？？？？？
	//这个时候是将Node节点的空间删除掉。但是这个会调用到Polynomial的析构函数吗？？？？？？？
	//这个时候是将Node节点的空间删除掉。但是这个会调用到Polynomial的析构函数吗？？？？？？？
	//这个时候是将Node节点的空间删除掉。但是这个会调用到Polynomial的析构函数吗？？？？？？？
	//这个时候是将Node节点的空间删除掉。但是这个会调用到Polynomial的析构函数吗？？？？？？？
	//这个时候是将Node节点的空间删除掉。但是这个会调用到Polynomial的析构函数吗？？？？？？？
	return success;
}


template <class Stack_entry>
Error_code Stack<Stack_entry>::top(Stack_entry &item) const

{
	if (top_node == NULL) return underflow;
	item = top_node->entry;
	//这里要为item这个类编写赋值号的重载
	//而且先要将item里面的节点都删除掉
	return success;
}

template <class Stack_entry>
Stack<Stack_entry>::~Stack()

{
	while (!empty())
		pop();
}

template <class Stack_entry>
void Stack<Stack_entry>::operator=(const Stack<Stack_entry> &original)

{
	Node<Stack_entry> *new_top, *new_copy, *original_node = original.top_node;
	if (original_node == NULL) new_top = NULL;
	else {
		new_copy = new_top = new Node<Stack_entry>(original_node->entry);
		while (original_node->next != NULL) {
			original_node = original_node->next;
			new_copy->next = new Node<Stack_entry>(original_node->entry);
			new_copy = new_copy->next;
		}
	}
	while (!empty()) // Clean out old Stack entries.
		pop();
	new_copy->next = NULL;
	top_node = new_top;  // And replace them with new entries.
}

template <class Stack_entry>
Stack<Stack_entry>::Stack(const Stack<Stack_entry> &original)

{
	Node<Stack_entry> *new_copy, *original_node = original.top_node;
	if (original_node == NULL) top_node = NULL;
	else {
		top_node = new_copy = new Node<Stack_entry>(original_node->entry);
		while (original_node->next != NULL) {
			original_node = original_node->next;
			new_copy->next = new Node<Stack_entry>(original_node->entry);
			new_copy = new_copy->next;
		}
	}
}
//  疑问： 在构造函数里面申请空间，如果没有申请成功怎么办，这不是很难受吗？
//  疑问： 在构造函数里面申请空间，如果没有申请成功怎么办，这不是很难受吗？
//  疑问： 在构造函数里面申请空间，如果没有申请成功怎么办，这不是很难受吗？
//  疑问： 在构造函数里面申请空间，如果没有申请成功怎么办，这不是很难受吗？
//  疑问： 在构造函数里面申请空间，如果没有申请成功怎么办，这不是很难受吗？
//  疑问： 在构造函数里面申请空间，如果没有申请成功怎么办，这不是很难受吗？
//  疑问： 在构造函数里面申请空间，如果没有申请成功怎么办，这不是很难受吗？
//  疑问： 在构造函数里面申请空间，如果没有申请成功怎么办，这不是很难受吗？


#endif // STACK_H_INCLUDED
#pragma once

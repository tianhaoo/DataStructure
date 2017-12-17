#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "utility.h" // for cstddef and Error_code
#include "node.h"

template <class Stack_entry>
class Stack
	// Stack��һ��һ����Node�ṹ�����Ӷ��ɣ�ÿ���ṹ�������ŵĶ�����������������Ҫ�Ķ���
	// ��Stack_entry����δ�ŵģ�Ӧ�ö��û�����������
	// ���ԣ�Stack_entry�����Ӧ�ú�Node_entry������ͬ�������͡�
{
public:
	// Standard Stack methods.
	Stack(); //���캯��
	bool empty() const;
	Error_code push(const Stack_entry &item); // ����ط�����Ӧ����Ҫ��item����һ��Ȼ��ѹ��ջ����ȥ��
	Error_code pop(); //����һ�����Ժ�,��Ҫ��Node�ڵ�delete��������Ҫע�⻹��Ҫ��Stack_entry��delete��
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
// ǰ̬��û��
// ��̬��ͷ���top_node����ΪNULL
{
	top_node = NULL; //��ͷ���ӵ�
}


template <class Stack_entry>
bool Stack<Stack_entry>::empty() const
// ǰ̬�� û��
// ��̬�� ���ջΪ�գ��򷵻�true�����򷵻�false
{
	return ((top_node) == NULL);
}

template <class Stack_entry>
Error_code Stack<Stack_entry>::push(const Stack_entry &item)
// ǰ̬��û��
// ��̬����̬����һ���ڵ���������Stack_entry��������벻���Ļ�������overflow��Error_code
// �������Ŀ�У����ǵ�Stack_entry�����ΪPolynomial��
{
	Node<Stack_entry> *new_top = new Node<Stack_entry>(item, top_node);
	/*
	*���ǽ����õ�����Polynomial��Ķ�����Ϊitem����ô��Node�ĸ��ƹ��캯���������Ҫ
	*�����item��һ��Ӳ������
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
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()
	//���Ҫ��Stack_entry���ͱ���Ҫ��һ��public�ķ���clear()

	delete old_top;
	//���ʱ���ǽ�Node�ڵ�Ŀռ�ɾ�����������������õ�Polynomial�����������𣿣�����������
	//���ʱ���ǽ�Node�ڵ�Ŀռ�ɾ�����������������õ�Polynomial�����������𣿣�����������
	//���ʱ���ǽ�Node�ڵ�Ŀռ�ɾ�����������������õ�Polynomial�����������𣿣�����������
	//���ʱ���ǽ�Node�ڵ�Ŀռ�ɾ�����������������õ�Polynomial�����������𣿣�����������
	//���ʱ���ǽ�Node�ڵ�Ŀռ�ɾ�����������������õ�Polynomial�����������𣿣�����������
	//���ʱ���ǽ�Node�ڵ�Ŀռ�ɾ�����������������õ�Polynomial�����������𣿣�����������
	//���ʱ���ǽ�Node�ڵ�Ŀռ�ɾ�����������������õ�Polynomial�����������𣿣�����������
	//���ʱ���ǽ�Node�ڵ�Ŀռ�ɾ�����������������õ�Polynomial�����������𣿣�����������
	return success;
}


template <class Stack_entry>
Error_code Stack<Stack_entry>::top(Stack_entry &item) const

{
	if (top_node == NULL) return underflow;
	item = top_node->entry;
	//����ҪΪitem������д��ֵ�ŵ�����
	//������Ҫ��item����Ľڵ㶼ɾ����
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
//  ���ʣ� �ڹ��캯����������ռ䣬���û������ɹ���ô�죬�ⲻ�Ǻ�������
//  ���ʣ� �ڹ��캯����������ռ䣬���û������ɹ���ô�죬�ⲻ�Ǻ�������
//  ���ʣ� �ڹ��캯����������ռ䣬���û������ɹ���ô�죬�ⲻ�Ǻ�������
//  ���ʣ� �ڹ��캯����������ռ䣬���û������ɹ���ô�죬�ⲻ�Ǻ�������
//  ���ʣ� �ڹ��캯����������ռ䣬���û������ɹ���ô�죬�ⲻ�Ǻ�������
//  ���ʣ� �ڹ��캯����������ռ䣬���û������ɹ���ô�죬�ⲻ�Ǻ�������
//  ���ʣ� �ڹ��캯����������ռ䣬���û������ɹ���ô�죬�ⲻ�Ǻ�������
//  ���ʣ� �ڹ��캯����������ռ䣬���û������ɹ���ô�죬�ⲻ�Ǻ�������


#endif // STACK_H_INCLUDED
#pragma once

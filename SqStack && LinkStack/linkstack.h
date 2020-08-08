#pragma once
#include "stdafx.h"

/**
 * @brief 创建一个链栈类
 */
template <typename ElemType>
class LinkStack
{
public:
	LinkStack();
	~LinkStack();

	bool isEmpty(); // 判断链栈是否为空
	bool push(ElemType val); // 向链栈压入一个元素
	bool pop(); // 删除链栈顶端的元素
	ElemType top(); // 返回链栈顶端的元素但不删除

private:
	StackNode<ElemType>* top_; // 声明链栈的头结点
	int length_; // 声明链栈的长度
};

// 构造函数，初始化链栈的头结点
template <typename ElemType>
LinkStack<ElemType>::LinkStack()
{
	top_ = new StackNode<ElemType>();
	if (!top_)
		cerr << "Space allocating falied! Error in LinkStack<ElemType>::LinkStack()!" << endl;
	length_ = 0;
}

// 析构函数，销毁链栈
template <typename ElemType>
LinkStack<ElemType>::~LinkStack()
{
	while (top_)
	{
		StackNode<ElemType>* cur = top_;
		top_ = top_->next;
		delete cur;
	}
}

// 判断链栈是否为空
template <typename ElemType>
bool LinkStack<ElemType>::isEmpty()
{
	return top_->next == nullptr;
}

// 向链栈压入一个元素
template <typename ElemType>
bool LinkStack<ElemType>::push(ElemType val)
{
	StackNode<ElemType>* new_node = new StackNode<ElemType>(val);
	if (!new_node) {
		cerr << "Space allocating falied!" << endl;
		return false;
	}
	else {
		new_node->next = top_;
		top_ = new_node;
		++length_;
	}
	return true;
}

// 删除链栈顶端的元素
template <typename ElemType>
bool LinkStack<ElemType>::pop()
{
	if (isEmpty())
		return false; 
	else {
		StackNode<ElemType>* tmp = top_;
		top_ = top_->next;
		delete tmp;
		--length_;
	}
	return true;
}

// 返回链栈顶端的元素但不删除
template <typename ElemType>
ElemType LinkStack<ElemType>::top()
{
	if (isEmpty()) {
		return NULL;
	}
	else
		return top_->val;
}

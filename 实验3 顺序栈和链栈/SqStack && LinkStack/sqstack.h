#pragma once
#include "stdafx.h"

/**
 * @brief 创建一个顺序栈类
 */
template <typename ElemType>
class SqStack
{
public:
	SqStack();
	~SqStack();

	bool isEmpty(); // 判断顺序栈是否为空
	bool isFull();	// 判断顺序栈是否已满
	bool push(ElemType val); // 向顺序栈压入一个元素
	bool pop(); // 删除顺序栈顶端的元素
	ElemType top(); // 返回顺序栈顶端的元素但不删除

private:
	ElemType* elem_; // 声明顺序栈的基地址
	int top_; // 声明顺序栈的栈顶索引
};

// 构造函数，初始化基地址和栈顶索引
template <typename ElemType>
SqStack<ElemType>::SqStack():top_(-1)
{
	elem_ = new ElemType[kMaxSize];   // 开辟空间
	if (!elem_) {                     // 当溢出时报异常
		exit(OVERFLOW);
	}
}

// 构造函数，销毁顺序栈
template <typename ElemType>
SqStack<ElemType>::~SqStack()
{
	delete[] elem_;
}

// 判断顺序栈是否为空
template <typename ElemType>
bool SqStack<ElemType>::isEmpty()
{
	return top_ == -1;
}

// 判断顺序栈是否已满
template <typename ElemType>
bool SqStack<ElemType>::isFull()
{
	return top_ == kMaxSize - 1;
}

// 向顺序栈压入一个元素
template <typename ElemType>
bool SqStack<ElemType>::push(ElemType val)
{
	if (isFull()) {
		return false;
	}
	else {
		elem_[++top_] = val;
		return true;
	}
}

// 删除顺序栈顶端的元素
template <typename ElemType>
bool SqStack<ElemType>::pop()
{
	if (isEmpty()) {
		return false;
	}
	else {
		top_--;
		return true;
	}
}

// 返回顺序栈顶端的元素但不删除
template <typename ElemType>
ElemType SqStack<ElemType>::top()
{
	if (isEmpty()) {
		return NULL;
	}
	else
		return elem_[top_];
}


#pragma once
#include "stdafx.h"

/**
 * @brief 创建一个链式队列类
 */
template<typename ElemType>
class LinkQueue
{
public:
	LinkQueue();
	~LinkQueue();

	bool isEmpty(); // 判断队列是否为空
	bool isFull(); // 判断队列是否已满
	int GetLength(); // 返回队列长度

	bool EnQueue(ElemType elem); // 入队
	bool DeQueue(ElemType& elem); // 队头出队
	bool GetFront(ElemType& elem); // 得到队头元素
	void OddOrEven(ElemType elem); // 输入：奇数——入队；偶数——队头出队。

	template <typename ElemType>
	friend ostream& operator << (ostream& os, LinkQueue<ElemType>*& lq); // 重载 << 运算符，输出队列元素个数，队头元素，全部元素等信息


private:
	int length_; // 声明队列长度
	QueueNode<ElemType>* front_; // 声明队头结点指针
	QueueNode<ElemType>* rear_; // 声明队尾结点指针
};

// 构造函数，初始化队列
template <typename ElemType>
LinkQueue<ElemType>::LinkQueue() :length_(0), front_(nullptr), rear_(nullptr) {}

// 析构函数，销毁队列
template <typename ElemType>
LinkQueue<ElemType>::~LinkQueue()
{
	while (front_)
	{
		rear_ = front_->next;
		delete front_;
		front_ = rear_;
	}
}

// 判断队列是否为空
template <typename ElemType>
bool LinkQueue<ElemType>::isEmpty()
{
	return front_ == nullptr;
}

// 判断队列是否已满
template <typename ElemType>
bool LinkQueue<ElemType>::isFull()
{
	return length_ == kMaxSize;
}

// 返回队列长度
template <typename ElemType>
int LinkQueue<ElemType>::GetLength()
{
	return length_;
}

// 入队
template <typename ElemType>
bool LinkQueue<ElemType>::EnQueue(ElemType elem)
{
	if (isFull()) return false;

	QueueNode<ElemType>* new_node = new QueueNode<ElemType>(elem);
	if (isEmpty())
		front_ = new_node;
	else
		rear_->next = new_node;
	rear_ = new_node;
	++length_;
	return true;
}

// 队头出队
template <typename ElemType>
bool LinkQueue<ElemType>::DeQueue(ElemType& elem)
{
	if (isEmpty()) return false;

	elem = front_->val;
	QueueNode<ElemType>* tmp = front_->next;
	delete front_;
	front_ = tmp;
	--length_;
	return true;
}

// 得到队头元素
template <typename ElemType>
bool LinkQueue<ElemType>::GetFront(ElemType& elem)
{
	if (isEmpty()) return false;

	elem = front_->val;
	return true;
}

// 输入：奇数——入队；偶数——队头出队。
template <typename ElemType>
void LinkQueue<ElemType>::OddOrEven(ElemType elem)
{
	if (elem % 2 == 1) {
		if (isFull())
			cout << "队列已满，入队失败！" << endl;
		else {
			cout << "输入为奇数，入队！" << endl;
			EnQueue(elem);
		}
	}
	else {
		if (isEmpty())
			cout << "队列为空，出队失败！" << endl;
		else {
			cout << "输入为偶数，队头出队！" << endl;
			DeQueue(elem);
		}
	}
}

// 重载 << 运算符，输出队列元素个数，队头元素，全部元素等信息
template <typename ElemType>
ostream& operator << (ostream& os, LinkQueue<ElemType>*& lq) {
	if (lq->isEmpty()) {
		os << "队列为空，打印元素失败！" << endl;
		return os;
	}

	ElemType elem_front;
	lq->GetFront(elem_front);
	os << "队列元素个数：" << lq->GetLength() << "，队头元素：" << elem_front << endl;
	os << "队列元素：" << endl;
	int col = 0;
	QueueNode<ElemType>* cur = lq->front_;
	while (cur)
	{
		os << setw(3) << cur->val << " ";
		if (++col % 10 == 0) os << endl;
		cur = cur->next;
	}
	os << endl;
	return os;
};
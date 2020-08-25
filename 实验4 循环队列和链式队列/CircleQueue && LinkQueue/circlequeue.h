#pragma once
#include "stdafx.h"

/**
 * @brief 创建一个循环队列类
 */
template <typename ElemType>
class CircleQueue
{
public:
	CircleQueue();
	~CircleQueue();

	bool isEmpty(); // 判断队列是否为空
	bool isFull(); // 判断队列是否已满
	int GetLength(); // 返回队列长度

	bool EnQueue(ElemType elem); // 入队
	bool DeQueue(ElemType& elem); // 队头出队
	bool GetFront(ElemType& elem); // 得到队头元素
	void OddOrEven(ElemType elem); // 输入：奇数——入队；偶数——队头出队。

	template <typename ElemType>
	friend ostream& operator << (ostream& os, CircleQueue<ElemType>*& cq); // 重载 << 运算符，输出队列元素个数，队头元素，全部元素等信息

private:
	ElemType* elem_; // 声明循环队列的基地址
	int front_; // 声明队头指针
	int rear_; // 声明队尾指针
};

// 构造函数，初始化队列
template <typename ElemType>
CircleQueue<ElemType>::CircleQueue() :front_(0), rear_(0)
{
	elem_ = new ElemType[kMaxSize];   // 开辟空间
	if (!elem_) {                     // 当溢出时报异常
		exit(OVERFLOW);
	}
}

// 析构函数，销毁队列
template <typename ElemType>
CircleQueue<ElemType>::~CircleQueue()
{
	delete[] elem_;
	elem_ = nullptr;
}

// 判断队列是否为空
template <typename ElemType>
bool CircleQueue<ElemType>::isEmpty()
{
	return front_ == rear_;
}

// 判断队列是否已满
template <typename ElemType>
bool CircleQueue<ElemType>::isFull()
{
	return (rear_ + 1) % kMaxSize == front_;
}

// 返回队列长度
template <typename ElemType>
int CircleQueue<ElemType>::GetLength()
{
	return (rear_ - front_ + kMaxSize) % kMaxSize;
}

// 入队
template <typename ElemType>
bool CircleQueue<ElemType>::EnQueue(ElemType elem)
{
	if (isFull()) return false;

	elem_[rear_] = elem;
	rear_ = (rear_ + 1) % kMaxSize;
	return true;
}

// 队头出队
template <typename ElemType>
bool CircleQueue<ElemType>::DeQueue(ElemType& elem)
{
	if (isEmpty()) return false;

	elem = elem_[front_];
	front_ = (front_ + 1) % kMaxSize;
	return true;
}

// 得到队头元素
template <typename ElemType>
bool CircleQueue<ElemType>::GetFront(ElemType& elem)
{
	if (isEmpty()) return false;
	elem = elem_[front_];
	return true;
}

// 输入：奇数——入队；偶数——队头出队。
template <typename ElemType>
void CircleQueue<ElemType>::OddOrEven(ElemType elem)
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
ostream& operator << (ostream& os, CircleQueue<ElemType>*& cq) {
	if (cq->isEmpty()) {
		os << "队列元素个数：" << 0 << "，队头元素：无"  << "，front = " << cq->front_ << ", rear = " << cq->rear_ << endl;
		cout << "队列为空，打印元素失败！" << endl;
		return os;
	}

	// 输出队列中元素的重载操作 <<
	ElemType elem_front;
	cq->GetFront(elem_front);
	os << "队列元素个数：" << cq->GetLength() << "，队头元素：" << elem_front << "，front = " << cq->front_ << ", rear = " << cq->rear_ << endl;
	os << "队列元素：" << endl;

	int col = 0;
	for (int i = cq->front_; i % kMaxSize != cq->rear_; i = (i + 1) % kMaxSize)
	{
		os << setw(3) << cq->elem_[i] << " ";
		if (++col % 10 == 0) os << endl;
	}
	os << endl;
	return os;
};
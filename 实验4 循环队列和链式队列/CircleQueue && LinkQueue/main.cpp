/**
 *  @Copyright (C) 2020 March. All rights reserved.
 *  @license   GNU General Public License (GPL)
 *  @author	   March
 *  @email	   345916208@qq.com
 *  @file	   main.cpp
 *  @brief	   队列的C++实现主文件
 *  @version   1.0
 *  @date	   2020-08-10
 */

#include "stdafx.h"
#include "circlequeue.h"
#include "linkqueue.h"

int main()
{
	ios::sync_with_stdio(false); // 让c风格的输入输出流和c++的输入输出流分开,使cin读入的更快

// 	// 示例一：用循环方式将0到98这99个元素入队，同时判断是否队满（LinkQueue和CircleQueue都可以实现，下同）。
// 	LinkQueue<int>* Q1 = new LinkQueue<int>();
// 	for (int i = 0; i < 101; ++i) {
// 		if (!Q1->isFull()) {
// 			Q1->EnQueue(i);
// 			cout << "队列未满，" << i << "已入列！" << endl;
// 		}
// 		else {
// 			cout << "队列已满！"<< endl;
// 			cout << Q1 << endl;
// 			break;
// 		}
// 	}
// 	delete Q1;

// 	// 示例二：元素的入队出队操作，打印元素个数，队头元素和全部元素。
// 	LinkQueue<char>* Q1 = new LinkQueue<char>();
// 	Q1->EnQueue('a');
// 	Q1->EnQueue('b');
// 	Q1->EnQueue('c');
// 	Q1->EnQueue('d');
// 	cout << Q1 << endl;
// 
// 	char ch;
// 	Q1->DeQueue(ch);
// 	cout << endl << Q1 << endl;
// 	Q1->DeQueue(ch);
// 	cout << Q1 << endl;
// 	Q1->DeQueue(ch);
// 	cout << Q1 << endl;
// 	Q1->DeQueue(ch);
// 	cout << Q1 << endl;
// 	delete Q1;

	// 示例三：键盘输入：奇数——入队；偶数——队头出队；0——结束。每次输入结束后，打印队列。
	LinkQueue<int>* Q1 = new LinkQueue<int>();
	int num = 0;
	while (cin >> num) {
		if (num == 0) {
			cout << "输入为0，程序结束！" << endl;
			break;
		}
		Q1->OddOrEven(num);
		cout << Q1 << endl;
	}
	delete Q1;

	return 0;
}
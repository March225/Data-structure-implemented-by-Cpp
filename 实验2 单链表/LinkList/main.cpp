/**
 *  @Copyright (C) 2020 March. All rights reserved.
 *  @license   GNU General Public License (GPL)
 *  @author	   March
 *  @email	   345916208@qq.com
 *  @file	   main.cpp
 *  @brief	   单链表的C++实现主文件
 *  @version   1.0
 *  @date	   2020-08-07
 */

#include "stdafx.h"
#include "linklist.h"

int main()
{
	FILE* stream1;
	ios::sync_with_stdio(false); // 让c风格的输入输出流和c++的输入输出流分开,使cin读入的更快
	freopen_s(&stream1, "10_1.in", "r", stdin); // 直接从文档中读取待输入的数据，不同文档代表不同实验任务的输入


	// 示例：实验任务<10>将单链表Ｌ中的奇数项和偶数项结点分解开（元素值为奇数、偶数）
	LinkList* L1 = new LinkList();
	int len;
	cin >> len;
	L1->CreateLinkListByInsertAtEnd(len);
	L1->PrintLinkList();

	LinkList* L1_odd = new LinkList();
	LinkList* L1_even = new LinkList();

	L1->SplitLinkListByParityOfVal(L1_odd, L1_even); // 实现分离
	L1_odd->PrintLinkList(); // 打印奇数部分链表
	L1_even->PrintLinkList(); // 打印偶数部分链表

	L1->PrintLinkList(); // 打印原链表（由于原链表已经分解，因此打印出来为空）

	delete L1;
	delete L1_odd;
	delete L1_even;

	return 0;
}


/**                                     
 *  @Copyright (C) 2020 March. All rights reserved.
 *  @license  GNU General Public License (GPL)
 *  @author	  March
 *  @email	  345916208@qq.com
 *  @file	  main.cpp
 *  @brief	  顺序表的C++实现主文件
 *  @version  1.0
 *  @date	  2020-07-31
 */

#include "stdafx.h"
#include "sqlist.h"

int main(int argc, char* argv[])
{
	FILE* stream1;
	ios::sync_with_stdio(false); // 让c风格的输入输出流和c++的输入输出流分开,使cin读入的更快
	freopen_s(&stream1, "7_3.in", "r", stdin); // 直接从文档中读取待输入的数据

	//freopen( "output.out", "w", stdout ); // 直接输出到文档

	// 下面是展示顺序表的删除重复元素函数DeleteRepeatedElem()的功能
	SqList* l1 = new SqList();
	int len;
	cin >> len;
	l1->CreatSqList(len);
	cout << "原始顺序表:" << endl;
	cout << "************************************************************" << endl;
	l1->PrintSqList();
	cout << "************************************************************" << endl << endl;

	l1->DeleteRepeatedElem();
	cout << "删除重复元素之后的顺序表:" << endl;
	cout << "************************************************************" << endl;
	l1->PrintSqList();
	cout << "************************************************************" << endl<< endl;

	delete l1;
	return 0;
}
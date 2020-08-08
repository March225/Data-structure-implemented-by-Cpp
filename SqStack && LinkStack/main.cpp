/**
 *  @Copyright (C) 2020 March. All rights reserved.
 *  @license   GNU General Public License (GPL)
 *  @author	   March
 *  @email	   345916208@qq.com
 *  @file	   main.cpp
 *  @brief	   顺序栈和链栈的C++实现主文件
 *  @version   1.0
 *  @date	   2020-07-31
 */

#include "stdafx.h"
#include "solution.h"


int main()
{
	FILE* stream1;
	ios::sync_with_stdio(false); // 让c风格的输入输出流和c++的输入输出流分开,使cin读入的更快
	freopen_s(&stream1, "1.in", "r", stdin); // 直接从文档中读取待输入的数据

	// 利用顺序栈或链栈将10进制数转换为16进制数，输入文件为“1.in”
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int num = 0;
		cin >> num;
		cout << num << " 转换为16进制为：" << Solution().DecToHex(num) << endl;
	}

// 	// 利用顺序栈或链栈判断一个表达式是否有效（即：三种括号是否匹配），输入文件为“2.in”
// 	string s = "";
// 	int cnt = 0;
// 	while (getline(cin, s)) {
// 		if (Solution().isValidOfExpression(s))
// 			cout << ++cnt << ": yes！" << endl;
// 		else
// 			cout << ++cnt << ": no！" << endl;
// 	}

	return 0;
}
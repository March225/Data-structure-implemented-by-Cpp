#pragma once
#include "stdafx.h"
#include "sqstack.h"
#include "linkstack.h"

class Solution
{
public:
	// 利用顺序栈或链栈将10进制数转换为16进制数
	string DecToHex(int num) {
		if (num == 0) return "0";

		int N = abs(num);
		LinkStack<string> st;
		string res_hex = "";
		while (N != 0) {
			int tmp = N % 16;
			if (tmp < 10)
				st.push(to_string(tmp));
			else {
				switch (tmp) {
				case 10:st.push("A"); break;
				case 11:st.push("B"); break;
				case 12:st.push("C"); break;
				case 13:st.push("D"); break;
				case 14:st.push("E"); break;
				case 15:st.push("F"); break;
				}
			}
			N = N / 16;
		}
		while (!st.isEmpty()) {
			res_hex += st.top();
			st.pop();
		}

		return num < 0 ? res_hex = "-" + res_hex : res_hex;
	}

	// 利用顺序栈或链栈判断一个表达式是否有效（即：三种括号是否匹配）
	bool isValidOfExpression(string s) {
		LinkStack<char> st;
		for (auto ch : s) {
			if (!isdigit(ch) && !isalpha(ch)) {
				int tmp = ch - st.top();
				if (!st.isEmpty() && (tmp == 1 || tmp == 2)) 
					st.pop();
				else 
					st.push(ch);
			}
		}
		return	st.isEmpty() ? true : false;
	}
};


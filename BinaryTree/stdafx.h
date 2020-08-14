#pragma once
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if !defined(AFX_STDAFX_H__D36E9D40_3BCB_4A85_9D48_AC876E7A2942__INCLUDED_)
#define AFX_STDAFX_H__D36E9D40_3BCB_4A85_9D48_AC876E7A2942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <bits/stdc++.h> // 万能的头文件,可能需要手动加入include文件夹中

/**
 * @brief 定义二叉树的结点
 */
template <typename ElemType>
struct BiTNode {
	ElemType val;
	BiTNode<ElemType>* left;
	BiTNode<ElemType>* right;
	BiTNode() : left(nullptr), right(nullptr) {}
	BiTNode(ElemType x) : val(x), left(nullptr), right(nullptr) {}
};

using namespace std;

#endif // !defined(AFX_STDAFX_H__D36E9D40_3BCB_4A85_9D48_AC876E7A2942__INCLUDED_)
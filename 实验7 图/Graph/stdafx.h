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

enum class GraphKind { None, UDG, UDN, DG, DN }; // 图类型枚举变量
typedef char VertexType;  // 顶点类型应
typedef int EdgeType;     // 边的权值类型
const int kMAXVEX = 1000; // 最大顶点数
const int INF = 100000;   // 表示无穷大

/**
 * @brief 定义边表结点
 */
struct EdgeNode
{
	int adjvex;     /* 邻接点域,存储该顶点对应的下标 */
	EdgeType info;  /* 用于存储权值,可以不需要 */
	EdgeNode* next; /* 链域,指向下一个邻接点 */
};

/**
 * @brief 定义顶点表结点
 */
struct VertexNode
{
	VertexType data;     /* 顶点域,存储顶点信息 */
	EdgeNode* firstEdge; /* 边表头指针 */
};

using namespace std;

#endif // !defined(AFX_STDAFX_H__D36E9D40_3BCB_4A85_9D48_AC876E7A2942__INCLUDED_)
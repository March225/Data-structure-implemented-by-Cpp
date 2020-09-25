#pragma once
#include "stdafx.h"

/**
 * @brief 创建一个graph类
 */
class Graph {

private:
	VertexType* vexs_; // 顶点数组
	EdgeType** arc_;   // 邻接矩阵数组
	int nVertexes_, nEdges_; // 图中当前的顶点数和边数
	GraphKind graphType_; // 图的类型

	VertexNode* adjList_; // 存放顶点表结点的数组
	bool* visited_; // 访问标志的数组

public:
	Graph(); // 构造函数
	~Graph(); // 析构函数
	bool createAdjMatrixGraph(string fileName); // 由图的邻接矩阵创建图
	bool createAdjListGraph(string fileName); // 由图的邻接表创建图
	void strTrim(string& s); // 删除字符串s左边和右边的空格
	void printAdjMatrixGraph(); // 打印图的类型、顶点和邻接矩阵
	void printAdjListGraph(); // 打印图的类型、顶点和邻接表
	void DFSAdjMatTraverse(); // 邻接矩阵的深度优先遍历
	void DFSAdjListTraverse(); // 邻接表的深度优先遍历
	void BFSAdjMatTraverse(); // 邻接矩阵的广度优先遍历
	void BFSAdjListTraverse(); // 邻接表的广度优先遍历

protected:
	void DFSAdjMat(int i); // 邻接矩阵的深度优先递归算法
	void DFSAdjList(int i); // 邻接表的深度优先递归算法
};

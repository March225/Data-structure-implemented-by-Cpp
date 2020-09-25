/**
 *  @Copyright (C) 2020 March. All rights reserved.
 *  @license   GNU General Public License (GPL)
 *  @author	   March
 *  @email	   345916208@qq.com
 *  @file	   main.cpp
 *  @brief	   图的C++实现主文件
 *  @version   1.0
 *  @date	   2020-09-23
 */
#include "stdafx.h"
#include "graph.h"

int main() {
	// 文件存放路径（按照需求进行修改）
	string fileName = "E:\\Program Files (x86)\\Microsoft Visual Studio\\workplace\\Graph\\grpData\\udg8.grp";
	Graph* g = new Graph();

	g->createAdjMatrixGraph(fileName); // 由图的邻接矩阵创建图
	g->printAdjMatrixGraph(); // 打印图的类型、顶点和邻接矩阵

	g->createAdjListGraph(fileName); // 由图的邻接表创建图
	g->printAdjListGraph(); // 打印图的类型、顶点和邻接表

	g->DFSAdjMatTraverse(); // 邻接矩阵的深度优先遍历
	g->DFSAdjListTraverse(); // 邻接表的深度优先遍历

	g->BFSAdjMatTraverse(); // 邻接矩阵的广度优先遍历
	g->BFSAdjListTraverse(); // 邻接表的广度优先遍历

	delete g;
	return 0;
}
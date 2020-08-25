/**
 *  @Copyright (C) 2020 March. All rights reserved.
 *  @license   GNU General Public License (GPL)
 *  @author	   March
 *  @email	   345916208@qq.com
 *  @file	   main.cpp
 *  @brief	   二叉树的C++实现主文件
 *  @version   1.0
 *  @date	   2020-08-14
 */

#include "stdafx.h"
#include "binarytree.h"

int main()
{
	FILE* stream1;
	ios::sync_with_stdio(false); // 让c风格的输入输出流和c++的输入输出流分开,使cin读入的更快
	freopen_s(&stream1, "1.in", "r", stdin); // 直接从文档中读取待输入的数据

	/************** 以下为示例，程序的实现没有按照实验任务的顺序 **************/

	BinaryTree<char>* BiT1 = new BinaryTree<char>;
	BiT1->CreatByPreOrderOfExtBiT(); // 通过扩展二叉树的前序遍历创建二叉树

	// 递归遍历
	cout << "前序遍历（递归）：";
	BiT1->PreOrderTraverse(0);
	cout << "中序遍历（递归）：";
	BiT1->InOrderTraverse(0);
	cout << "后序遍历（递归）：";
	BiT1->PostOrderTraverse(0);
	cout << "层次遍历（递归）：";
	BiT1->LevelOrderTraverse(0);

	// 非递归遍历
	cout << endl << "前序遍历（非递）：";
	BiT1->PreOrderTraverse(1);
	cout << "中序遍历（非递）：";
	BiT1->InOrderTraverse(1);
	cout << "后序遍历（非递）：";
	BiT1->PostOrderTraverse(1);
	cout << "层次遍历（非递）：";
	BiT1->LevelOrderTraverse(1);

	// 中序遍历输出各结点的值及对应层次
	cout << endl << "中序输出各结点的值及对应层次：" << endl;
	BiT1->PrintLeveInOrderTra();

	// 交换每个结点的左右子结点
	cout << "交换每个结点的左右子结点后：" << endl;
	BiT1->ExchangeValOfLAndRChild();
	cout << "层次遍历（递归）：";
	BiT1->LevelOrderTraverse(0);

	// 打印二叉树中值为val的结点的层次
	char val1 = 'C';
	cout << endl << "二叉树中结点 " << val1 << " 的层次：" << BiT1->GetLevelByVal(val1) << endl;

	// 打印二叉树结点总数
	cout << endl << "二叉树结点总数：" << BiT1->NumberOfBiTNode() << endl;

	// 打印二叉树叶子结点数
	cout << endl << "二叉树叶子结点数：" << BiT1->NumberOfBiTLeafNode() << endl;

	// 打印二叉树中度为2的结点数
	cout << endl << "二叉树中度为2的结点数：" << BiT1->NumberOfNodeWithTwoDeg() << endl;

	// 返回值为val的结点的父结点
	char val2 = 'C';
	BiTNode<char>* parent = BiT1->GetParent(val2);
	if(parent)
		cout << endl << "二叉树中结点 " << val2 << " 的父结点："  << parent->val << endl;
	else
		cout << endl << "结点 " << val2 << " 不存在，或无父节点" << endl;

	// 返回值为val的结点的兄弟结点
	char val3 = 'E';
	BiTNode<char>* sibling = BiT1->GetSibling(val3);
	if (sibling)
		cout << endl << "二叉树中结点 " << val3 << " 的兄弟结点：" << sibling->val << endl;
	else
		cout << endl << "结点 " << val3 << " 不存在，或无兄弟结点" << endl;

	// 返回值为val的结点的左子结点
	char val4 = 'B';
	BiTNode<char>* left_child = BiT1->GetLeftChild(val4);
	if (left_child)
		cout << endl << "二叉树中结点 " << val4 << " 的左子结点：" << left_child->val << endl;
	else
		cout << endl << "结点 " << val4 << " 不存在，或无左子结点" << endl;

	// 打印二叉树高度
	cout << endl << "二叉树的高度：" << BiT1->GetHeight() << endl;

	delete BiT1;
	return 0;
}
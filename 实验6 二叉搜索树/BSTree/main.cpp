/**
 *  @Copyright (C) 2020 March. All rights reserved.
 *  @license   GNU General Public License (GPL)
 *  @author	   March
 *  @email	   345916208@qq.com
 *  @file	   main.cpp
 *  @brief	   二叉搜索树的C++实现主文件
 *  @version   1.0
 *  @date	   2020-08-25
 */

#include "stdafx.h"
#include "bstree.h"
#include "binsearch.h"

int main() {
	ios::sync_with_stdio(false); // 让c风格的输入输出流和c++的输入输出流分开,使cin读入的更快
	FILE* stream1;
	freopen_s(&stream1, "2.in", "r", stdin); // 直接从文档中读取待输入的数据，不同文档代表不同实验任务的输入
	
	string s = "", num = "";
	stringstream ss;

// 	// 实验任务(1)：二分查找（运行此段程序要注释掉实验任务(2)~(5)的程序）
// 	vector<int> nums;
// 	while (1) {
// 		if (getline(cin, s)) {
// 			ss << s;
// 			cout << "排序数组为：";
// 			while (getline(ss, num, ',')) {
// 				nums.push_back(stoi(num));
// 				cout << num << ",";
// 			}
// 			cout << endl;
// 		}
// 
// 		if (getline(cin, s)) {
// 			ss.clear();
// 			ss << s;
// 			while (getline(ss, num, ','))
// 				cout << setw(3) << num << " 索引：" << setw(2) << BinarySearch(nums, stoi(num)) << endl;
// 			cout << endl;
// 			ss.clear();
// 		}
// 		else break;
// 	}

	// 实验任务(2)：创建BST
	BSTree<int>* BST1 = new BSTree<int>();
	getline(cin, s);
	ss << s;
	cout << "待创建BST的输入序列：" << endl;
	vector<int> nums1;
	while (getline(ss, num, ',')) {
		cout << num << " " ;
		nums1.push_back(stoi(num));
	}
	cout << endl;

	BST1->CreateBSTree(nums1);
	cout << "BST创建成功，且中序遍历（升序）为：";
	BST1->InOrderTraverse(0);
	cout << endl;

	// 实验任务(3)：在BST中查找元素，并输出待查找元素的父结点或潜在父结点(如果可以插入BST，插入之后的父结点)
	getline(cin, s);
	ss.clear();
	ss << s;
	BSTNode<int>* node = nullptr, * father = nullptr;
	while (getline(ss, num, ',')) {
		int w_num = stoi(num);
		node = BST1->SearchByIter(w_num, father);
		if (node) cout << setw(3) << w_num << " 在BST中存在，值为：" << setw(3) << node->val;
		else cout << setw(3) << w_num << " 在BST中不存在" ;
		if (father) cout << " 父结点或潜在的父结点为：" << setw(3) << father->val << endl;
		else cout<< " 且为根结点，不存在父结点" << endl;
	}
	cout << endl;
	
	// 实验任务(4)：删除BST中的结点
	getline(cin, s);
	ss.clear();
	ss << s;
	while (getline(ss, num, ',')) {
		int w_num = stoi(num);
		if (BST1->Delete(w_num)) {
			cout << setw(3) << w_num << " 已从BST中删除" << endl;
			cout << "删除后BST的中序遍历（应为升序）：";
			BST1->InOrderTraverse(0);
		}
	}
	cout << endl;

	// 实验任务(5)：创建AVL树
	BSTree<int>* BST2 = new BSTree<int>();
	getline(cin, s);
	ss.clear();
	ss << s;
	cout << "待创建AVL树的输入序列：" << endl;
	vector<int> nums2;
	while (getline(ss, num, ',')) {
		cout << num << " ";
		nums2.push_back(stoi(num));
	}
	cout << endl;
	BST2->CreateAVL(nums2);
	cout << "AVL树创建成功，且中序遍历（升序）为：" << endl;
	BST2->InOrderTraverse(0);

	delete BST1,BST2;
}
#pragma once
#include "stdafx.h"

/**
 * @brief 创建一个二叉搜索树类
 */
template <typename ElemType>
class BSTree
{
private:
	BSTNode<ElemType>* root_;

public:
	BSTree() :root_(nullptr) {};
	~BSTree() { Destroy(); };

	void CreateBSTree(vector<ElemType> data) { CreateBSTree(root_, data); } // 创建BST
	void CreateAVL(vector<ElemType> data) { CreateAVL(root_, data, 0, int(data.size()) - 1); } // 创建AVL
	void Destroy() { Destroy(root_); } // 销毁BST
	bool Insert(ElemType val) { return Insert(root_, val); } // 插入结点
	bool Delete(ElemType val) { return Delete(root_, val); } // 删除结点

	// 中序遍历（mode：0递归，1非递归）
	void InOrderTraverse(char mode) { mode == 0 ? InOrderByRecur(root_) : InOrderByNonRecur(root_); cout << endl; };
	// 递归查找(father：待查找元素的父结点或潜在父结点(如果可以插入BST，插入之后的父结点))
	BSTNode<ElemType>* SearchByRecur(ElemType val, BSTNode<ElemType>*& father) { return SearchByRecur(root_, val, father); }
	// 迭代查找(father：待查找元素的父结点或潜在父结点(如果可以插入BST，插入之后的父结点))
	BSTNode<ElemType>* SearchByIter(ElemType val, BSTNode<ElemType>*& father) { return SearchByIter(root_, val, father); }
	BSTNode<ElemType>* GetRoot() { return root_; }; // 获取根结点


protected:
	// 创建BST
	void CreateBSTree(BSTNode<ElemType>*& root, vector<ElemType> data) {
		for (auto num : data) Insert(num);
	}

	// 创建AVL
	BSTNode<ElemType>* CreateAVL(BSTNode<ElemType>*& root, vector<ElemType> data, int l, int r) {
		if (l > r) return nullptr;
		int m = l + (r - l) / 2;
		root = new BSTNode<ElemType>(data[m]);
		root->left = CreateAVL(root->left, data, l, m - 1);
		root->right = CreateAVL(root->right, data, m + 1, r);
		return root;
	}

	// 销毁BST
	void Destroy(BSTNode<ElemType>*& root) {
		if (root) {
			Destroy(root->left);
			Destroy(root->right);
			delete root;
			root = nullptr;
		}
	}

	// 插入结点
	bool Insert(BSTNode<ElemType>*& root, ElemType val) {
		BSTNode<ElemType>* node = new BSTNode<ElemType>(val);
		if (!node) {
			cerr << "申请内存失败！" << endl;
			return false;
		}

		if (!root) {
			root = node;
			return true;
		}
		BSTNode<ElemType>* father = nullptr;
		if (SearchByIter(root, val, father)) {
			cout << "BST中已存在值为：" << val << " 的结点，插入失败！" << endl;
			return false;
		}
		else {
			if (father->val > val) father->left = node;
			else father->right = node;
			return true;
		}
	}

	// 删除结点
	bool Delete(BSTNode<ElemType>*& root, ElemType val) {
		BSTNode<ElemType>* dele_node = nullptr, * father = nullptr;
		dele_node = SearchByIter(val, father);
		if (dele_node) {
			// 待删除结点只有一个孩子结点
			if (!dele_node->left || !dele_node->right) {
				if (father->val < dele_node->val)
					father->right = dele_node->left ? dele_node->left : dele_node->right;
				else
					father->left = dele_node->left ? dele_node->left : dele_node->right;
			}
			// 待删除结点有两个孩子结点
			else if (dele_node->left && dele_node->right) {
				if (father) {
					if (father->val > dele_node->val) father->left = dele_node->right;
					else father->right = dele_node->right;
				}
				else root_ = dele_node->right;

				BSTNode<ElemType>* left_node = dele_node->right;
				while (left_node->left) left_node = left_node->left;
				left_node->left = dele_node->left;
			}
			// 删除结点
			delete dele_node;
			dele_node = nullptr;
			return true;
		}
		else {
			cout << "BST中不存在值为：" << val << " 的结点，删除失败！" << endl;
			return false;
		}
	}

	// 中序遍历（递归）
	void InOrderByRecur(BSTNode<ElemType>*& root)
	{
		if (root) {
			InOrderByRecur(root->left);
			cout << root->val << " ";
			InOrderByRecur(root->right);
		}
	}

	// 中序遍历（非递归）
	void InOrderByNonRecur(BSTNode<ElemType>*& root)
	{
		stack<BSTNode<ElemType>*> st;
		BSTNode<ElemType>* cur = root;
		while (!st.empty() || cur) {
			while (cur) {
				st.push(cur);
				cur = cur->left;
			}
			cur = st.top(); st.pop();
			cout << cur->val << " ";
			cur = cur->right;
		}
	}

	// 递归查找(father：待查找元素的父结点或潜在父结点(如果可以插入BST，插入之后的父结点))
	BSTNode<ElemType>* SearchByRecur(BSTNode<ElemType>*& root, ElemType val, BSTNode<ElemType>*& father) {
		if (!root) return nullptr;
		if (root->val == val) {
			father = nullptr;
			return root;
		}

		father = root;
		if (root->left && root->left->val == val) return root->left;
		if (root->right && root->right->val == val) return root->right;

		if (root->val > val) return SearchByRecur(root->left, val, father);
		else return SearchByRecur(root->right, val, father);
	}

	// 迭代查找(father：待查找元素的父结点或潜在父结点(如果可以插入BST，插入之后的父结点))
	BSTNode<ElemType>* SearchByIter(BSTNode<ElemType>*& root, ElemType val, BSTNode<ElemType>*& father) {
		BSTNode<ElemType>* cur = root, * pre = nullptr;
		while (cur) {
			if (cur->val == val) {
				father = pre;
				return cur;
			}
			else if (cur->val > val) {
				pre = cur;
				cur = cur->left;
			}
			else {
				pre = cur;
				cur = cur->right;
			}
		}
		father = pre;
		return nullptr;
	}
};


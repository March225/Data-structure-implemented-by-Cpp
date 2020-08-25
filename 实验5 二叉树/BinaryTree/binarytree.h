#pragma once
#include"stdafx.h"

/**
 * @brief 创建一个二叉树类
 */
template <typename ElemType>
class BinaryTree
{
private:
	BiTNode<ElemType>* root_;

public:
	BinaryTree() :root_(nullptr) {};
	~BinaryTree() { Destroy(); };

	void CreatByPreOrderOfExtBiT() { CreatByPreOrderOfExtBiT(root_); } // 创建二叉树
	void Destroy() { Destroy(root_); }; // 销毁二叉树
	void PreOrderTraverse(char mode) { mode == 0 ? PreOrderByRecur(root_) : PreOrderByNonRecur(root_); cout << endl; }; // 前序遍历（mode：0递归，1非递归）
	void InOrderTraverse(char mode) { mode == 0 ? InOrderByRecur(root_) : InOrderByNonRecur(root_); cout << endl; }; // 中序遍历（mode：0递归，1非递归）
	void PostOrderTraverse(char mode) { mode == 0 ? PostOrderByRecur(root_) : PostOrderByNonRecur(root_); cout << endl; }; // 后序遍历（mode：0递归，1非递归）
	void LevelOrderTraverse(char mode) { mode == 0 ? LevelOrderByRecur() : LevelOrderByNonRecur(root_); cout << endl; }; // 层次遍历（mode：0递归，1非递归）
	void PrintLeveInOrderTra() { PrintLeveInOrderTra(root_, 1); cout << endl; }; // 中序遍历输出各结点的值及对应层次
	void ExchangeValOfLAndRChild() { ExchangeValOfLAndRChild(root_); }; // 交换每个结点的左右子结点

	bool isEmpty() { return root_ == nullptr; }; // 判断二叉树是否为空
	int GetHeight() { return GetHeight(root_); }; // 返回二叉树的高度
	int GetLevelByVal(ElemType val) { return GetLevelByVal(root_, val, 1); }; // 返回二叉树中值为val的结点的层次
	int NumberOfBiTNode() { return NumberOfBiTNode(root_); }; // 返回二叉树结点总数
	int NumberOfBiTLeafNode() { return NumberOfBiTLeafNode(root_); } // 返回二叉树叶子结点数
	int NumberOfNodeWithTwoDeg() { return NumberOfNodeWithTwoDeg(root_); }; // 返回二叉树中度为2的结点数

	BiTNode<ElemType>* GetRoot() { return root_; }; // 返回二叉树的根结点
	BiTNode<ElemType>* GetParent(ElemType val) { return GetParent(root_, val); }; // 返回值为val的结点的父结点
	BiTNode<ElemType>* GetSibling(ElemType val) { bool isExist = false; return GetSibling(root_, val, isExist); }; // 返回值为val的结点的兄弟结点
	BiTNode<ElemType>* GetLeftChild(ElemType val) { bool isExist = false; return GetLeftChild(root_, val, isExist); }; // 返回值为val的结点的左子结点
 
protected:
	// 通过扩展二叉树的前序遍历创建二叉树
	void CreatByPreOrderOfExtBiT(BiTNode<ElemType>*& root)
	{
		ElemType val;
		cin >> val;
		if (val != '#') {
			root = new BiTNode<ElemType>(val);
			if (!root) exit(OVERFLOW);
			CreatByPreOrderOfExtBiT(root->left);
			CreatByPreOrderOfExtBiT(root->right);
		}
		else root = nullptr;
	}

	// 销毁二叉树
	void Destroy(BiTNode<ElemType>*& root)
	{
		if (root) {
			Destroy(root->left);
			Destroy(root->right);
			delete root;
			root = nullptr;
		}
	}

	// 前序遍历（递归）
	void PreOrderByRecur(BiTNode<ElemType>*& root)
	{
		if (root) {
			cout << root->val << " ";
			PreOrderByRecur(root->left);
			PreOrderByRecur(root->right);
		}
	}

	// 前序遍历（非递归）
	void PreOrderByNonRecur(BiTNode<ElemType>*& root)
	{
		if (!root) return;
		stack<BiTNode<ElemType>*> st;
		st.push(root);
		while (!st.empty()) {
			BiTNode<ElemType>* cur = st.top(); st.pop();
			cout << cur->val << " ";
			if (cur->right) st.push(cur->right);
			if (cur->left) st.push(cur->left);
		}
	}

	// 中序遍历（递归）
	void InOrderByRecur(BiTNode<ElemType>*& root)
	{
		if (root) {
			InOrderByRecur(root->left);
			cout << root->val << " ";
			InOrderByRecur(root->right);
		}
	}

	// 中序遍历（非递归）
	void InOrderByNonRecur(BiTNode<ElemType>*& root)
	{
		stack<BiTNode<ElemType>*> st;
		BiTNode<ElemType>* cur = root;
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

	// 后序遍历（递归）
	void PostOrderByRecur(BiTNode<ElemType>*& root)
	{
		if (root) {
			PostOrderByRecur(root->left);
			PostOrderByRecur(root->right);
			cout << root->val << " ";
		}
	}

	// 后序遍历（非递归）
	void PostOrderByNonRecur(BiTNode<ElemType>*& root)
	{
		if (!root) return;
		stack<BiTNode<ElemType>*> st;
		BiTNode<ElemType>* pre = nullptr, * cur = root;
		st.push(cur);
		while (!st.empty()) {
			cur = st.top();
			if ((!cur->left && !cur->right) ||
				(pre && (pre == cur->left || pre == cur->right))) {
				cout << cur->val << " "; st.pop();
				pre = cur;
			}
			else {
				if (cur->right) st.push(cur->right);
				if (cur->left) st.push(cur->left);
			}
		}
	}

	// 层次遍历（递归）
	void LevelOrderByRecur()
	{
		int h = GetHeight();
		for (int i = 0; i < h; ++i)
			LevelOrder(root_, i);
	}

	// 层次遍历递归子程序
	void LevelOrder(BiTNode<ElemType>*& root, int h)
	{
		if (root == nullptr) return;
		if (h == 0) {
			cout << root->val << " "; return;
		}
		LevelOrder(root->left, h - 1);
		LevelOrder(root->right, h - 1);
	}

	// 层次遍历（非递归）
	void LevelOrderByNonRecur(BiTNode<ElemType>*& root)
	{
		if (!root) return;
		queue<BiTNode<ElemType>*> q;
		q.push(root);
		while (!q.empty()) {
			if (q.front()->left) q.push(q.front()->left);
			if (q.front()->right) q.push(q.front()->right);
			cout << q.front()->val << " "; q.pop();
		}
	}

	// 中序遍历输出各结点的值及对应层次
	void PrintLeveInOrderTra(BiTNode<ElemType>*& root, int n)
	{
		if (root) {
			PrintLeveInOrderTra(root->left, n + 1);
			cout << "结点：" << root->val << "  该节点层次：" << n << endl;
			PrintLeveInOrderTra(root->right, n + 1);
		}
	}

	// 交换每个结点的左右子结点
	void ExchangeValOfLAndRChild(BiTNode<ElemType>*& root)
	{
		BiTNode<ElemType>* cur = root;
		if (cur && (cur->left || cur->right)) {
			BiTNode<ElemType>* tmp = cur->left;
			cur->left = cur->right;
			cur->right = tmp;
		}
		else return;
		ExchangeValOfLAndRChild(cur->left);
		ExchangeValOfLAndRChild(cur->right);
	}

	// 返回二叉树的高度
	int GetHeight(BiTNode<ElemType>*& root)
	{
		if (!root) return 0;
		else {
			int LeftTHeight = GetHeight(root->left);
			int RightTHeight = GetHeight(root->right);
			return LeftTHeight > RightTHeight ? LeftTHeight + 1 : RightTHeight + 1;
		}
	}

	// 返回二叉树中值为val的结点的层次
	int GetLevelByVal(BiTNode<ElemType>*& root, ElemType val, int n)
	{
		if (!root) return -1;
		else {
			if (root->val == val) return n;
			int level = GetLevelByVal(root->left, val, n + 1);
			return level == -1 ? GetLevelByVal(root->right, val, n + 1) : level;
		}
	}

	// 返回二叉树结点总数
	int NumberOfBiTNode(BiTNode<ElemType>*& root)
	{
		if (!root) return 0;
		else {
			int num_left = NumberOfBiTNode(root->left);
			int num_right = NumberOfBiTNode(root->right);
			return num_left + num_right + 1;
		}
	}

	// 返回二叉树叶子结点数
	int NumberOfBiTLeafNode(BiTNode<ElemType>*& root)
	{
		if (!root) return 0;
		else if (root && (!root->left && !root->right)) return 1;
		else {
			int num_left = NumberOfBiTLeafNode(root->left);
			int num_right = NumberOfBiTLeafNode(root->right);
			return num_left + num_right;
		}
	}

	// 返回二叉树中度为2的结点数
	int NumberOfNodeWithTwoDeg(BiTNode<ElemType>*& root)
	{
		if (!root) return 0;
		else {
			int num_left = NumberOfNodeWithTwoDeg(root->left);
			int num_right = NumberOfNodeWithTwoDeg(root->right);
			if (root->left && root->right)
				return num_left + num_right + 1;
			else
				return num_left + num_right;
		}
	}

	// 返回值为val的结点的父结点
	BiTNode<ElemType>* GetParent(BiTNode<ElemType>*& root, ElemType val)
	{
		if (!root || root->val == val) return nullptr;
		if ((root->left && root->left->val == val) || (root->right && root->right->val == val))
			return root;
		else
			return GetParent(root->left, val) == nullptr ? GetParent(root->right, val) : GetParent(root->left, val);
	}

	// 返回值为val的结点的兄弟结点
	BiTNode<ElemType>* GetSibling(BiTNode<ElemType>*& root, ElemType val, bool& isExist)
	{
		if (!root || root->val == val) return nullptr;
		if (root->left && root->left->val == val) {
			isExist = true;
			return root->right;
		}
		else if (root->right && root->right->val == val) {
			isExist = true;
			return root->left;
		}
		else {
			BiTNode<ElemType>* left_half = GetSibling(root->left, val, isExist);
			if (isExist) return left_half;
			return GetSibling(root->right, val, isExist);
		}
	}

	// 返回值为val的结点的左子结点
	BiTNode<ElemType>* GetLeftChild(BiTNode<ElemType>*& root, ElemType val, bool& isExist)
	{
		if (!root) return nullptr;
		if (root->val == val) {
			isExist = true;
			return root->left;
		}
		else {
			BiTNode<ElemType>* left_half = GetLeftChild(root->left, val, isExist);
			if (isExist) return left_half;
			return GetLeftChild(root->right, val, isExist);
		}
	}
};



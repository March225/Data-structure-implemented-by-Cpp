#include "stdafx.h"
#include "linklist.h"

// 构造函数，初始化单链表
LinkList::LinkList() :head_(nullptr), length_(0)
{
	cout << this << "单链表已被初始化！" << endl;
}

// 析构函数，销毁单链表
LinkList::~LinkList()
{
	while (head_)
	{
		ListNode* cur = head_;
		head_ = head_->next;
		delete cur;
	}
	cout << this << "单链表已被销毁！" << endl;
}

// 返回单链表的长度
int LinkList::GetLength()
{
	return length_;
}

// 根据位置返回单链表的元素
bool LinkList::GetElemByPosition(int pos, ElemType& val)
{
	if (head_ == nullptr) {
		cout << "单链表为空，获取元素失败！" << endl;
		return false;
	}
	else if (pos <= 0 || pos > length_) {
		cout << "位置 " << setw(2) << pos << " 有误！" << "获取元素失败!" << endl;
		return false;
	}
	else {
		ListNode* cur = head_;
		while (cur)
		{
			if (--pos == 0) {
				val = cur->val;
				return true;
			}
			cur = cur->next;
		}
		cout << "未知原因，获取元素失败！" << endl;
		return false;
	}
}

// 尾插法创建单链表
bool LinkList::CreateLinkListByInsertAtEnd(int len)
{
	ListNode* dummy_node = new ListNode(0), * cur = dummy_node;
	for (int i = 0; i < len; ++i)
	{
		ElemType num;
		cin >> num;
		ListNode* new_node = new ListNode(num);
		cur->next = new_node;
		cur = cur->next;
		++length_;
	}
	head_ = dummy_node->next;
	return true;
}

// 头插法创建单链表
bool LinkList::CreateLinkListByInsertAtBeg(int len)
{
	ListNode* cur = nullptr;
	for (int i = 0; i < len; ++i)
	{
		ElemType num;
		cin >> num;
		ListNode* new_node = new ListNode(num);
		new_node->next = cur;
		cur = new_node;
		++length_;
	}
	head_ = cur;
	return true;
}

// 在第pos个结点前插入值为val的结点
bool LinkList::InsertElemBeforePosition(int pos, ElemType val)
{
	if (head_ == nullptr) {
		cout << "单链表为空，插入元素失败！" << endl;
		return false;
	}
	else if (pos <= 0 || pos > length_) {
		cout << "位置 " << setw(2) << pos << " 有误！" << "插入元素失败!" << endl;
		return false;
	}
	else {
		ListNode* dummy_node = new ListNode(0), * cur = dummy_node;
		dummy_node->next = head_;
		while (cur->next) {
			if (--pos == 0) {
				ListNode* tmp = cur->next;
				cur->next = new ListNode(val);
				cur->next->next = tmp;

				head_ = dummy_node->next;
				++length_;
				return true;
			}
			cur = cur->next;
		}
		cout << "未知原因，插入元素失败！" << endl;
		return false;
	}
}

// 返回单链表中值为val的元素位置
bool LinkList::FindElemByValue(int& pos, ElemType val)
{
	if (head_ == nullptr) {
		cout << "单链表为空，查找元素失败！" << endl;
		return false;
	}

	ListNode* cur = head_;
	int cnt = 1;
	while (cur) {
		if (cur->val == val) {
			pos = cnt;
			return true;
		}
		++cnt;
		cur = cur->next;
	}
	cout << "没有查找到值为 " << val << " 的元素！" << endl;
	return false;
}

// 根据位置删除单链表的元素
bool LinkList::DeleteElemByPosition(int pos)
{
	if (head_ == nullptr) {
		cout << "单链表为空，删除元素失败！" << endl;
		return false;
	}
	else if (pos <= 0 || pos > length_) {
		cout << "位置 " << setw(2) << pos << " 有误！" << "删除元素失败!" << endl;
		return false;
	}
	else {
		ListNode* dummy_node = new ListNode(0), * cur = dummy_node;
		dummy_node->next = head_;
		while (cur->next) {
			if (--pos == 0) {
				ListNode* tmp = cur->next;
				cur->next = cur->next->next;
				delete tmp;

				head_ = dummy_node->next;
				--length_;
				return true;
			}
			cur = cur->next;
		}
		cout << "未知原因，删除元素失败！" << endl;
		return false;
	}
}

// 在一个有序单链表中插入元素,并保证链表还是有序的
bool LinkList::InsertElemInOrder(ElemType val)
{
	if (!head_) {
		head_ = new ListNode(val);
		++length_;
		return true;
	}

	ListNode* dummy_node = new ListNode(0);
	dummy_node->next = head_;
	ListNode* pre = dummy_node;
	while (pre->next) {
		if (val <= pre->next->val) {
			ListNode* tmp = pre->next;
			pre->next = new ListNode(val);
			pre->next->next = tmp;
			break;
		}
		else {
			if (!pre->next->next) {
				ListNode* cur = pre->next;
				cur->next = new ListNode(val);
				cur->next->next = nullptr;
				break;
			}
			else
				pre = pre->next;
		}
	}
	head_ = dummy_node->next;
	++length_;
	return true;
}

// 根据元素的奇偶性分离单链表
bool LinkList::SplitLinkListByParityOfVal(LinkList*& l_odd, LinkList*& l_even)
{
	ListNode* cur = head_;
	ListNode* dummy_node_odd = new ListNode(0), * dummy_node_even = new ListNode(0);
	ListNode* cur_odd = dummy_node_odd, * cur_even = dummy_node_even;

	while (cur) {
		if (cur->val % 2 == 1) {
			cur_odd->next = cur;
			cur = cur->next;
			cur_odd->next->next = nullptr;
			cur_odd = cur_odd->next;
			++l_odd->length_;
		}
		else {
			cur_even->next = cur;
			cur = cur->next;
			cur_even->next->next = nullptr;
			cur_even = cur_even->next;
			++l_even->length_;
		}
		
	}
	l_odd->head_ = dummy_node_odd->next;
	l_even->head_ = dummy_node_even->next;
	head_ = nullptr;
	length_ = 0;
	return true;
}

// 打印单链表的长度和元素
void LinkList::PrintLinkList()
{
	ListNode* cur = head_;
	cout << "单链表长度：" << length_ << endl;
	cout << "单链表元素：";
	while (cur)
	{
		cout << cur->val << "->";
		cur = cur->next;
	}

	cout << "nullptr" << endl << endl;
}


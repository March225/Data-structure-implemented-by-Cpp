#pragma once
/**
 * @brief 创建一个单链表类
 */

class LinkList
{
public:
	LinkList();
	~LinkList();

	int GetLength(); // 返回单链表的长度
	bool GetElemByPosition(int pos, ElemType& val); // 根据位置返回单链表的元素
	bool CreateLinkListByInsertAtEnd(int len); // 尾插法创建单链表
	bool CreateLinkListByInsertAtBeg(int len); // 头插法创建单链表
	bool InsertElemBeforePosition(int pos, ElemType val); // 在第pos个结点前插入值为val的结点
	bool FindElemByValue(int& pos, ElemType val); // 返回单链表中值为val的元素位置
	bool DeleteElemByPosition(int pos); // 根据位置删除单链表的元素
	bool InsertElemInOrder(ElemType val); // 在一个有序单链表中插入元素,并保证链表还是有序的
	bool SplitLinkListByParityOfVal(LinkList*& l_odd, LinkList*& l_even); // 根据元素的奇偶性分离单链表
	void PrintLinkList(); // 打印单链表的长度和元素



private:
	ListNode* head_; // 单链表的哑结点
	int length_; // 单链表的长度
};

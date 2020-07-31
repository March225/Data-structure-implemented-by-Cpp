#pragma once
/**
 * @brief 创建一个顺序表类
 */

class SqList
{
public:
	SqList();
	~SqList();

	void CreatSqList(int len); // 创建一个顺序表
	ElemType GetElemByIdx(int idx); // 根据下标查找顺序表中的元素
	void PrintSqList(); // 打印顺序表
	void SortSqList(); // 排序顺序表
	void SplitSqListByParityOfVal(SqList*& l_odd, SqList*& l_even); // 根据顺序表元素的奇偶性分离顺序表
	void GetCommonElem(const SqList* const& l, SqList*& l_com); // 查找两个顺序表的共同元素,保存在第三个顺序表中
	void DeleteRepeatedElem(); // 删除顺序表里的重复元素
	int GetLength(); // 返回顺序表的长度
	bool isEmpty(); // 判断顺序表是否为空
	bool isFull(); // 判断顺序表是否已满
	bool InsertSqListAtEnd(ElemType data); // 在尾部插入元素
	bool InsertSqListBeforeIdx(int idx, ElemType data); // 在idx位置前插入元素
	bool InsertSqListInOrder(ElemType data); // 插入元素,并保证顺序表还是有序的
	bool DeleteElem(int idx); // 删除idx位置处的元素

private:
	ElemType* elem_; // 顺序表的基地址
	int length_; // 顺序表的长度
};
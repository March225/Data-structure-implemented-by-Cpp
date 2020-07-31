#include "stdafx.h"
#include "sqlist.h"

/**
 * @brief 构造函数,初始化顺序表
 */
SqList::SqList()
{
	elem_ = new ElemType[kMaxSize];   // 开辟空间
	if (!elem_) {                     // 当溢出时报异常
		exit(OVERFLOW);
	}
	length_ = 0;                      // 定义顺序表的长度
}

/**
 * @brief 析构函数,销毁顺序表
 */
SqList::~SqList()
{
	delete[] elem_;
	cout << this << " 顺序表已销毁！" << endl;
}

/**
 * @brief	  根据输入数据,创建一个顺序表
 * @param[in] len 顺序表的长度
 */
void SqList::CreatSqList(int len)
{
	if (len < 0) {
		cout << "创建失败，输入的结点个数有误！" << endl;
		exit(EXIT_FAILURE);
	}
	else if (len > kMaxSize) {
		cout << "创建失败，输入的结点个数超过最大值！" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		for (int i = 0; i < len; ++i) {
			ElemType num;
			cin >> num;
			InsertSqListAtEnd(num);
		}
		length_ = len;
	}
}

/**
 * @brief	  根据下标查找顺序表中的元素
 * @param[in] idx 输入的下标,从1开始
 * @return	  查找到的元素(ElemType类型) 
 * @note	  如果输入下标不存在,则强制退出程序	
 */
ElemType SqList::GetElemByIdx(int idx) {
	if (idx < 1 || idx > length_) {
		cout << "查询的下标不存在！" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		return elem_[idx - 1];
	}
}

/**
 * @brief 打印顺序表的长度和元素
 */
void SqList::PrintSqList()
{
	cout << "顺序表长度：" << length_ << endl;
	cout << "顺序表元素：" << endl;
	for (int i = 0; i < length_; ++i) {
		cout << setw(5) << elem_[i] << " ";
		if ((i + 1) % 10 == 0 || i == length_ - 1)
			cout << endl;
	}
}

/**
 * @brief 对线性表由小到大进行排序
 */
void SqList::SortSqList()
{
	sort(elem_, elem_ + length_);
}

/**
 * @brief	   根据顺序表元素的奇偶性分离顺序表
 * @param[out] l_odd 输出分离后的奇顺序表
 * @param[out] l_even 输出分离后的偶顺序表
 */
void SqList::SplitSqListByParityOfVal(SqList*& l_odd, SqList*& l_even)
{
	for (int i = 0; i < length_; ++i) {
		if (elem_[i] % 2 == 0) {
			l_even->elem_[l_even->length_++] = elem_[i];
		}
		else {
			l_odd->elem_[l_odd->length_++] = elem_[i];
		}
	}
}

/**
 * @brief	   查找两个顺序表的共同元素,保存在第三个顺序表中
 * @param[in]  l 输入的线性表,将查找当前线性表和它的共同元素
 * @param[out] l_com 输出的线性表,保存两个顺序表的共同元素
 */
void SqList::GetCommonElem(const SqList* const& l, SqList*& l_com)
{
	if (length_ == 0 || l->length_ == 0 || elem_[0] > l->elem_[l->length_ - 1] || elem_[length_ - 1] < l->elem_[0]) {
		cout << "没有共同元素！" << endl << endl;
	}
	else {
		cout << "有共同元素！" << endl << endl;
		int i = 0, j = 0;
		while (i < length_ && j < l->length_) {
			if (elem_[i] == l->elem_[j]) {
				l_com->elem_[l_com->length_++] = elem_[i];
				++i;
			}
			else if (elem_[i] > l->elem_[j]) {
				++j;
			}
			else {
				++i;
			}
		}
	}
}

/**
 * @brief 删除顺序表里的重复元素
 */
void SqList::DeleteRepeatedElem()
{
	int idx = 0;
	for (int i = 0; i < length_;) {
		elem_[idx++] = elem_[i];
		if (elem_[i] == elem_[i + 1]) {
			int tmp = elem_[i++];
			while (i < length_ && elem_[i] == tmp) {
				++i;
			}
		}
		else {
			++i;
		}
	}
	length_ = idx;
}

/**
 * @brief  返回顺序表的长度
 * @return length_ 顺序表的长度
 */
int SqList::GetLength()
{
	return length_;
}

/**
 * @brief  判断顺序表是否为空
 * @return 返回说明：
 *         true  顺序表为空
 *         false 顺序表非空
 */
bool SqList::isEmpty()
{
	if (length_ == 0) {
		cout << "顺序表为空！" << endl;
		return true;
	}
	else {
		cout << "顺序表非空！" << endl;
		return false;
	}
}

/**
 * @brief  判断顺序表是否已满
 * @return 返回说明：
 *         true  顺序表已满
 *         false 顺序表未满
 */
bool SqList::isFull()
{
	if (length_ >= kMaxSize) {
		cout << "顺序表已满！" << endl;
		return true;
	}
	else {
		cout << "顺序表未满！" << endl;
		return false;
	}
}

/**
 * @brief     在顺序表尾部插入元素
 * @param[in] data 待插入的数据元素
 * @return    返回说明：
 *            true  元素插入成功
 *            false 元素插入失败
 */
bool SqList::InsertSqListAtEnd(ElemType data)
{
	if (length_ >= kMaxSize) {
		cout << "顺序表已满，无法插入！" << endl;
		return false;
	}
	else {
		elem_[length_++] = data;
		return true;
	}
}

/**
 * @brief     在顺序表idx位置前插入元素
 * @param[in] idx  需要在位置idx(从1开始)之前插入元素
 * @param[in] data 待插入的数据元素
 * @return    返回说明：
 *            true  元素插入成功
 *            false 元素插入失败
 */
bool SqList::InsertSqListBeforeIdx(int idx, ElemType data)
{
	if (idx < 1 || idx > length_) {
		cout << "输入的下标不合法！" << endl;
		return false;
	}
	else if (length_ >= kMaxSize) {
		cout << "顺序表已满，无法插入！" << endl;
		return false;
	}
	else {
		for (int i = length_; i >= idx; --i) {
			elem_[i] = elem_[i - 1];
		}
		elem_[idx - 1] = data;
		++length_;
		return true;
	}
}

/**
 * @brief     在顺序表中插入元素,并保证插入后顺序表仍是有序的
 * @param[in] data 待插入的数据元素
 * @return    返回说明：
 *            true  元素插入成功
 *            false 元素插入失败
 */
bool SqList::InsertSqListInOrder(ElemType data)
{
	SortSqList();

	if (data <= elem_[0]) {
		return InsertSqListBeforeIdx(1, data);
	}
	else if (data >= elem_[length_ - 1]) {
		return InsertSqListAtEnd(data);
	}
	else {
		int l = 0, r = length_ - 1;
		while (l <= r) {
			int m = (l + r) / 2;
			if (data < elem_[m])
				r = m - 1;
			else
				l = m + 1;
		}
		return InsertSqListBeforeIdx(l + 1, data);
	}
}

/**
 * @brief     删除idx位置处的元素
 * @param[in] idx 待删除的数据元素位置,从1开始
 * @return    返回说明：
 *            true  元素插入成功
 *            false 元素插入失败
 */
bool SqList::DeleteElem(int idx)
{
	if (idx < 1 || idx > length_) {
		cout << "输入的下标不合法！" << endl;
		return false;
	}
	else {
		for (int i = idx; i < length_; ++i) {
			elem_[i - 1] = elem_[i];
		}
		elem_[--length_] = NULL;
		return true;
	}
}



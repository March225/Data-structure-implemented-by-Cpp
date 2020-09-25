#include "graph.h"

// 构造函数
Graph::Graph() : nVertexes_(0), nEdges_(0), graphType_(GraphKind::None) {
	vexs_ = new VertexType[kMAXVEX]; // 顶点数组
	arc_ = new EdgeType * [kMAXVEX]; // 邻接矩阵数组
	for (int i = 0; i < kMAXVEX; ++i) {
		arc_[i] = new EdgeType[kMAXVEX](); // 初始化为0
	}

	adjList_ = new VertexNode[kMAXVEX](); // 存放顶点表结点的数组
	visited_ = new bool[kMAXVEX]; // 访问标志的数组
};

// 析构函数
Graph::~Graph() {
	delete[]vexs_;
	for (int i = 0; i < kMAXVEX; ++i) {
		delete[]arc_[i];
	}
	delete[]arc_;

	delete[]adjList_;
};

// 删除字符串s左边和右边的空格
void Graph::strTrim(string& s) {
	if (!s.empty()) {
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}
}

// 由图的邻接矩阵创建图
bool Graph::createAdjMatrixGraph(string fileName) {
	string str;		     // 存放读出一行文本的字符串
	string strTemp;      // 判断是否注释行
	EdgeType eWeight;    // 边的信息，常为边的权值

	ifstream fin(fileName.c_str());
	if (!fin)
	{
		cout << "错误：文件" << fileName << "打开失败。" << endl;
		return false;
	}

	while (!fin.eof())
	{
		getline(fin, str);
		strTrim(str); // 删除字符串左边和右边的空格，这是一个自定义的函数
		if (str.empty()) continue;	   // 空行，继续读取下一行
		strTemp = str.substr(0, 2);
		if (strTemp == "//") continue; // 跳过注释行
		else break;	 // 非注释行、非空行，跳出循环
	}

	// 循环结束，str中应该已经是图的标识Graph，判断标识是否正确
	if (str.find("Graph") == string::npos)
	{
		cout << "错误：打开的文件格式错误！" << endl;
		fin.close(); // 关闭文件
		return false;
	}

	// 读取图的类型，跳过空行
	while (!fin.eof())
	{
		getline(fin, str);
		strTrim(str); // 删除字符串左边和右边空格，这是一个自定义函数
		if (str.empty()) continue;	   // 空行，继续读取下一行
		strTemp = str.substr(0, 2);
		if (strTemp == "//") continue; // 跳过注释行
		else break;	 // 非空行，也非注释行，即图的类型标识
	}

	// 设置图的类型
	if (str.find("UDG") != string::npos)
		graphType_ = GraphKind::UDG; // 无向图
	else if (str.find("UDN") != string::npos)
		graphType_ = GraphKind::UDN; // 无向网
	else if (str.find("DG") != string::npos)
		graphType_ = GraphKind::DG;  // 有向图
	else if (str.find("DN") != string::npos)
		graphType_ = GraphKind::DN;  // 有向网
	else
	{
		cout << "错误：读取图的类型标记失败" << endl;
		fin.close(); // 关闭文件
		return false;
	}

	// 读取顶点行数据到str，跳过空行
	while (!fin.eof())
	{
		getline(fin, str);
		strTrim(str); // 删除字符串左边和右边空格，这是一个自定义函数
		if (str.empty()) continue;	   // 空行，继续读取下一行
		strTemp = str.substr(0, 2);
		if (strTemp == "//") continue; // 跳过注释行
		else break;	 // 非空行，也非注释行，即图的顶点元素行
	}

	// 顶点数据存入图的顶点数组
	VertexType ver;
	stringstream ss(str);
	unordered_map<VertexType, int> vex_map; // 建立顶点索引哈希表，方便查找索引
	nVertexes_ = 0;
	while (ss >> ver) {
		vex_map[ver] = nVertexes_;
		// nVertexes_为图的顶点数
		vexs_[nVertexes_++] = ver;
	}

	// 图的邻接矩阵初始化
	int nRow = 0; // 矩阵行下标
	int nCol = 0; // 矩阵列下标
	if (graphType_ == GraphKind::UDN || graphType_ == GraphKind::DN) // 如果是网
	{
		for (nRow = 0; nRow < kMAXVEX; nRow++)
			for (nCol = 0; nCol < kMAXVEX; nCol++)
				arc_[nRow][nCol] = INF; // INF表示无穷大
	}

	// 循环读取边的数据到邻接矩阵
	int edgeNum = 0;   // 边的数量
	VertexType Vf, Vs; // 边或弧的2个相邻顶点
	while (!fin.eof())
	{
		getline(fin, str);
		strTrim(str); // 删除字符串左边和右边空格，这是一个自定义函数
		if (str.empty()) continue;	   // 空行，继续读取下一行
		strTemp = str.substr(0, 2);
		if (strTemp == "//") continue; // 跳过注释行

		// 分割边的数据
		stringstream ss(str);

		// 获取边的第一个顶点的索引（行索引）
		if (ss >> Vf) {
			nRow = vex_map[Vf];
		}
		else {
			cout << "错误：读取图的边数据失败！" << endl;
			fin.close(); // 关闭文件
			return false;
		}

		// 获取边的第二个顶点的索引（列索引）
		if (ss >> Vs) {
			nCol = vex_map[Vs];
		}
		else {
			cout << "错误：读取图的边数据失败！" << endl;
			fin.close(); // 关闭文件
			return false;
		}

		// 如果为网，读取权值
		if (graphType_ == GraphKind::UDN || graphType_ == GraphKind::DN)
		{   // 读取下一个子串，即边的附加信息，常为边的权重
			string edgeTmp;
			if (ss >> edgeTmp) {
				eWeight = stoi(edgeTmp);
			}
			else {
				cout << "错误：读取图的边数据失败！" << endl;
				fin.close(); // 关闭文件
				return false;
			}
		}

		// 如果为网，邻接矩阵中对应的边设置权值，否则置为1
		if (graphType_ == GraphKind::UDN || graphType_ == GraphKind::DN)
			arc_[nRow][nCol] = eWeight;
		else
			arc_[nRow][nCol] = 1;
		edgeNum++; // 边数加1
	}

	if (graphType_ == GraphKind::UDG || graphType_ == GraphKind::UDN)
		nEdges_ = edgeNum / 2; // 无向图或无向网的边数等于统计的数字除2
	else
		nEdges_ = edgeNum;

	fin.close(); // 关闭文件
	return true;
}

// 由图的邻接表创建图
bool Graph::createAdjListGraph(string fileName) {
	string str;          // 存放读出一行文本的字符串
	string strTemp;      // 判断是否注释行
	EdgeType eWeight;    //边的信息，常为边的权值

	ifstream fin(fileName.c_str());
	if (!fin)
	{
		cout << "错误：文件" << fileName << "打开失败。" << endl;
		return false;
	}

	while (!fin.eof())
	{
		getline(fin, str);
		strTrim(str); // 删除字符串左边和右边的空格，这是一个自定义的函数
		if (str.empty()) continue;     // 空行，继续读取下一行
		strTemp = str.substr(0, 2);
		if (strTemp == "//") continue; // 跳过注释行
		else break;  // 非注释行、非空行，跳出循环
	}

	// 循环结束，str中应该已经是图的标识Graph，判断标识是否正确
	if (str.find("Graph") == string::npos)
	{
		cout << "错误：打开的文件格式错误！" << endl;
		fin.close(); // 关闭文件
		return false;
	}

	// 读取图的类型，跳过空行
	while (!fin.eof())
	{
		getline(fin, str);
		strTrim(str); // 删除字符串左边和右边空格，这是一个自定义函数
		if (str.empty()) continue;     // 空行，继续读取下一行
		strTemp = str.substr(0, 2);
		if (strTemp == "//") continue; // 跳过注释行
		else break;  // 非空行，也非注释行，即图的类型标识
	}

	// 设置图的类型
	if (str.find("UDG") != string::npos)
		graphType_ = GraphKind::UDG; // 无向图
	else if (str.find("UDN") != string::npos)
		graphType_ = GraphKind::UDN; // 无向网
	else if (str.find("DG") != string::npos)
		graphType_ = GraphKind::DG;  // 有向图
	else if (str.find("DN") != string::npos)
		graphType_ = GraphKind::DN;  // 有向网
	else
	{
		cout << "错误：读取图的类型标记失败" << endl;
		fin.close(); // 关闭文件
		return false;
	}

	// 读取顶点行数据到str，跳过空行
	while (!fin.eof())
	{
		getline(fin, str);
		strTrim(str); // 删除字符串左边和右边空格，这是一个自定义函数
		if (str.empty()) continue;     // 空行，继续读取下一行
		strTemp = str.substr(0, 2);
		if (strTemp == "//") continue; // 跳过注释行
		else break;  // 非空行，也非注释行，即图的顶点元素行
	}

	// 顶点数据存入顶点表结点
	VertexType ver;
	stringstream ss(str);
	unordered_map<VertexType, int> vex_map; // 建立顶点索引哈希表，方便查找索引
	nVertexes_ = 0;
	while (ss >> ver) {
		vex_map[ver] = nVertexes_;
		// nVertexes_为图的顶点数
		adjList_[nVertexes_].data = ver;
		++nVertexes_;
	}

	//循环读取边（顶点对）数据
	int nRow = 0;      //矩阵行下标
	int nCol = 0;      //矩阵列下标
	int edgeNum = 0;   // 边的数量
	VertexType Vf, Vs; // 边或弧的2个相邻顶点
	while (!fin.eof())
	{
		getline(fin, str);
		strTrim(str); // 删除字符串左边和右边空格，这是一个自定义函数
		if (str.empty()) continue;     // 空行，继续读取下一行
		strTemp = str.substr(0, 2);
		if (strTemp == "//") continue; // 跳过注释行

		// 分割边的数据
		stringstream ss(str);

		// 获取边的第一个顶点的索引（行索引）
		if (ss >> Vf) {
			nRow = vex_map[Vf];
		}
		else {
			cout << "错误：读取图的边数据失败！" << endl;
			fin.close(); // 关闭文件
			return false;
		}

		// 获取边的第二个顶点的索引（列索引）
		if (ss >> Vs) {
			nCol = vex_map[Vs];
		}
		else {
			cout << "错误：读取图的边数据失败！" << endl;
			fin.close(); // 关闭文件
			return false;
		}

		// 如果为网，读取权值
		if (graphType_ == GraphKind::UDN || graphType_ == GraphKind::DN)
		{   // 读取下一个子串，即边的附加信息，常为边的权重
			string edgeTmp;
			if (ss >> edgeTmp) {
				eWeight = stoi(edgeTmp);
			}
			else {
				cout << "错误：读取图的边数据失败！" << endl;
				fin.close(); // 关闭文件
				return false;
			}
		}
		auto p = new EdgeNode; // 申请新的边结点
		p->adjvex = nCol; // 第二个顶点的索引

		//边的附加信息（权值），对有权图保存权值，无权图为1
		if (graphType_ == GraphKind::UDN || graphType_ == GraphKind::DN)
			p->info = eWeight;
		else
			p->info = 1;
		p->next = NULL;

		EdgeNode* eR = adjList_[nRow].firstEdge; // 边表尾指针
		if (eR == nullptr) adjList_[nRow].firstEdge = p;
		else {
			while (eR && eR->next)
			{
				eR = eR->next; // 后移边表指针，直至尾节点
			}
			eR->next = p;
		}
		edgeNum++; //边数加1
	}
	if (graphType_ == GraphKind::UDG || graphType_ == GraphKind::UDN)
		nEdges_ = edgeNum / 2;   //无向图或网的边数等于统计的数字除2
	else
		nEdges_ = edgeNum;
	fin.close(); // 关闭文件
	return true;
}

// 打印图的类型、顶点和邻接矩阵
void Graph::printAdjMatrixGraph() {
	cout << "/*******打印图的类型、顶点和邻接矩阵*******/" << endl << endl;
	string graphType;
	switch (graphType_) {
	case(GraphKind::DG):graphType = "DG"; break;
	case(GraphKind::DN):graphType = "DN"; break;
	case(GraphKind::UDG):graphType = "UDG"; break;
	case(GraphKind::UDN):graphType = "UDN"; break;
	default:cout << "错误：图为空！"; return;
	}
	cout << "图的类型：" << graphType << endl << endl;
	cout << "顶点个数：" << nVertexes_ << "，边个数：" << nEdges_ << endl << endl;

	cout << "顶点：";
	for (int i = 0; i < nVertexes_; ++i) cout << vexs_[i] << " ";
	cout << endl << endl;

	cout << "邻接矩阵：" << endl;
	cout << "  ";
	for (int i = 0; i < nVertexes_; ++i) cout << setw(2) << vexs_[i] << " ";
	cout << endl;
	for (int i = 0; i < nVertexes_; ++i) {
		cout << vexs_[i] << " ";
		for (int j = 0; j < nVertexes_; ++j) {
			if (arc_[i][j] == INF) cout << setw(2) << "∞" << " ";
			else cout << setw(2) << arc_[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// 打印图的类型、顶点和邻接表
void Graph::printAdjListGraph() {
	cout << "/*******打印图的类型、顶点和邻接表*******/" << endl << endl;
	string graphType;
	switch (graphType_) {
	case(GraphKind::DG):graphType = "DG"; break;
	case(GraphKind::DN):graphType = "DN"; break;
	case(GraphKind::UDG):graphType = "UDG"; break;
	case(GraphKind::UDN):graphType = "UDN"; break;
	default:cout << "错误：图为空！"; return;
	}
	cout << "图的类型：" << graphType << endl << endl;
	cout << "顶点个数：" << nVertexes_ << "，边个数：" << nEdges_ << endl << endl;

	cout << "顶点：";
	for (int i = 0; i < nVertexes_; ++i) cout << adjList_[i].data << " ";
	cout << endl << endl;

	cout << "邻接表：" << endl;
	for (int i = 0; i < nVertexes_; ++i) {
		auto VNode = adjList_[i];
		auto p = VNode.firstEdge;
		cout << setw(2) << i << " " << VNode.data << "->";
		while (p) {
			cout << setw(2) << p->adjvex << "(" << setw(2) << p->info << ")";
			if (p->next) cout << "->";
			p = p->next;
		}
		cout << endl;
	}
	cout << endl;
}

// 邻接矩阵的深度优先遍历
void Graph::DFSAdjMatTraverse() {
	if (graphType_ == GraphKind::None) {
		cout << "错误：图为空！"; return;
	}
	cout << "邻接矩阵的深度优先遍历：" << endl;
	int i;
	for (i = 0; i < nVertexes_; ++i)
		visited_[i] = false;
	for (i = 0; i < nVertexes_; ++i) {
		if (!visited_[i])
			DFSAdjMat(i);
	}
	cout << endl << endl;
}

// 邻接矩阵的深度优先递归算法
void Graph::DFSAdjMat(int i) {
	int j;
	visited_[i] = true;
	cout << vexs_[i] << " ";
	for (j = 0; j < nVertexes_; ++j) {
		// 如果图的类型是网
		if (graphType_ == GraphKind::DN || graphType_ == GraphKind::UDN) {
			if (arc_[i][j] != INF && !visited_[j])
				DFSAdjMat(j);
		}
		// 如果图的类型不是网
		else {
			if (arc_[i][j] == 1 && !visited_[j])
				DFSAdjMat(j);
		}
	}
}

// 邻接表的深度优先遍历
void  Graph::DFSAdjListTraverse() {
	if (graphType_ == GraphKind::None) {
		cout << "错误：图为空！"; return;
	}
	cout << "邻接表的深度优先遍历：" << endl;
	int i;
	for (i = 0; i < nVertexes_; ++i)
		visited_[i] = false;
	for (i = 0; i < nVertexes_; ++i) {
		if (!visited_[i])
			DFSAdjList(i);
	}
	cout << endl << endl;
}

// 邻接表的深度优先递归算法
void  Graph::DFSAdjList(int i) {
	EdgeNode* p = nullptr;
	visited_[i] = true;
	cout << adjList_[i].data << " ";
	p = adjList_[i].firstEdge;
	while (p) {
		if (!visited_[p->adjvex])
			DFSAdjList(p->adjvex);
		p = p->next;
	}
}

// 邻接矩阵的广度优先遍历
void Graph::BFSAdjMatTraverse() {
	if (graphType_ == GraphKind::None) {
		cout << "错误：图为空！"; return;
	}
	cout << "邻接矩阵的广度优先遍历：" << endl;
	for (int i = 0; i < nVertexes_; ++i)
		visited_[i] = false;

	queue<int> q;
	for (int i = 0; i < nVertexes_; ++i) {
		if (!visited_[i]) {
			visited_[i] = true;
			cout << vexs_[i] << " ";
			q.push(i);
			while (!q.empty()) {
				int k = q.front(); q.pop();
				for (int j = 0; j < nVertexes_; ++j) {
					// 如果图的类型是网
					if (graphType_ == GraphKind::DN || graphType_ == GraphKind::UDN) {
						if (arc_[k][j] != INF && !visited_[j]) {
							visited_[j] = true;
							cout << vexs_[j] << " ";
							q.push(j);
						}
					}
					// 如果图的类型不是网
					else {
						if (arc_[k][j] == 1 && !visited_[j]) {
							visited_[j] = true;
							cout << vexs_[j] << " ";
							q.push(j);
						}
					}
				}
			}
		}
	}
	cout << endl << endl;
}

// 邻接表的广度优先遍历
void Graph::BFSAdjListTraverse() {
	if (graphType_ == GraphKind::None) {
		cout << "错误：图为空！"; return;
	}
	cout << "邻接表的广度优先遍历：" << endl;
	for (int i = 0; i < nVertexes_; ++i)
		visited_[i] = false;

	queue<EdgeNode*> q;
	for (int i = 0; i < nVertexes_; ++i) {
		if (!visited_[i]) {
			visited_[i] = true;
			cout << adjList_[i].data << " ";
			auto p = adjList_[i].firstEdge;
			q.push(p);
			while (!q.empty()) {
				p = q.front(); q.pop();
				while (p) {
					int j = p->adjvex;
					if (!visited_[j]) {
						visited_[j] = true;
						cout << adjList_[j].data << " ";
						q.push(adjList_[j].firstEdge);
					}
					p = p->next;
				}
			}
		}
	}
	cout << endl << endl;
}

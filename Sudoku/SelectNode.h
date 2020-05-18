#ifndef _SELECTNODE_H_
#define _SELECTNODE_H_

#include<graphics.h>
#include<vector>
#include "const.h"
#include"CreatGrid.h"

using namespace std;

extern IMAGE bg, bk, wrongbk, numImg[3][9];

struct Node
{
	int x, y, num;
	int type;
};

class SelectNode
{

	Node selectNum;
	vector<Node>* wrong;
	int remain;
	const int ORI;
public:
	
	SelectNode();

	void setRemain(int x);

	int getRemain();

	void addSelectNode(int x, int y, int num);

	void addSelectNode(Node select);

	void clearWrongVector();

	void addWrongNode(int x, int y, int num, int type);

	void addWrongNode(Node wrong);

	void setSelectNum(int x, int y, int num);

	void setSelectNum(Node select);

	void drawSelectGrid();

	int getWrongSize();
	~SelectNode();
};

#endif // !SELECTNODE_H
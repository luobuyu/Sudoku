#include "SelectNode.h"


SelectNode::SelectNode(): remain(0), ORI(0)
{
	this->selectNum = { 0,0,-1 };
	this->wrong = new vector<Node>;
}


void SelectNode::setRemain(int x)
{
	this->remain = x;
}
int SelectNode::getRemain()
{
	return this->remain;
}
void SelectNode::addSelectNode(int x, int y, int num)
{
	Node temp;
	temp.x = x;
	temp.y = y;
	temp.num = num;
}
void SelectNode::addSelectNode(Node select)
{
	select.type = 1;
}

void SelectNode::clearWrongVector()
{
	this->wrong->clear();
}
void SelectNode::addWrongNode(int x, int y, int num, int type)
{
	Node temp;
	temp.x = x;
	temp.y = y;
	temp.num = num;
	temp.type = type;
	this->wrong->push_back(temp);
}
void SelectNode::addWrongNode(Node wrong)
{
	this->wrong->push_back(wrong);
}
void SelectNode::setSelectNum(int x, int y, int num)
{
	this->selectNum.x = x;
	this->selectNum.y = y;
	this->selectNum.num = num;
	this->selectNum.type = 1;
}
void SelectNode::setSelectNum(Node select)
{
	select.type = 1;
	this->selectNum = select;
}
void SelectNode::drawSelectGrid()
{
	if (selectNum.num != -1)
	{
		putimage(this->selectNum.x, this->selectNum.y, &bk);
		putimage(this->selectNum.x, this->selectNum.y, &numImg[1][this->selectNum.num - 1], SRCAND);
		putimage(this->selectNum.x, this->selectNum.y, &numImg[0][this->selectNum.num - 1], SRCPAINT);
	}
	if (this->wrong->size() > 0)
	{
		vector<Node>::iterator it;
		for (it = this->wrong->begin(); it != this->wrong->end(); it++)
		{
			if ((*it).type == this->ORI)
			{
				putimage((*it).x, (*it).y, &wrongbk);
				putimage((*it).x, (*it).y, &numImg[1][(*it).num - 1], SRCAND);
				putimage((*it).x, (*it).y, &numImg[2][(*it).num - 1], SRCPAINT);
			}
			else
			{
				putimage((*it).x, (*it).y, &wrongbk);
				putimage((*it).x, (*it).y, &numImg[1][(*it).num - 1], SRCAND);
				putimage((*it).x, (*it).y, &numImg[0][(*it).num - 1], SRCPAINT);
			}
		}
	}
}

int SelectNode::getWrongSize()
{
	return this->wrong->size();
}

SelectNode::~SelectNode()
{
	delete this->wrong;
}

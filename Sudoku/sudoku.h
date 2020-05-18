#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include<graphics.h>
#include "SelectNode.h"
#include "const.h"


class SuDoKu
{
public:
	CreatGrid* creatGrid;
	SelectNode* selectNode;

public:
	SuDoKu();
	~SuDoKu();
	void loadImg();
	int welcome();
	void initWin();
	void putGridImg(int grid[][COL], int isExistNum[][9]);
	
	void drawSelectNum();
	void isCorr(int x, int y, int num, int grid[][9], int isExistNum[][9]);
	bool check(int grid[][9]);
	int mouseControl(int grid[][9], int isExistNum[][9], clock_t t1);
	int gameover(clock_t t1);
	void initGame(int mode);
};


#endif // !_SUDOKU_H_





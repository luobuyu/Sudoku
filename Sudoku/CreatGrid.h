#ifndef _CREATGRID_H_
#define _CREATGRID_H_
#include<cstdlib>
#include<ctime>
#include "const.h"
#include<iostream>

using namespace std;

class CreatGrid
{
private:
	int flag[FLAG_ROW][COL] = { 0 };
	int grid[ROW][COL] = { 0 };
	int gridCopy[ROW][COL] = { 0 };
	bool visit[ROW][COL] = { false };
	bool isFind;
	int backTime;
	int totalTimes;		// 用来计数
	int blankCounts;
public:
	CreatGrid();
	~CreatGrid();
	bool check(int i, int x, int y);
	void makeFlag(int i, int x, int y);
	void deleteFlag(int i, int x, int y);
	void dfs(int x, int y, int step);
	void show();
	void copyArr(int grid[][9], int isExistNum[][9]);
	void eraseArr();
	void setbackTime(int times);
	void setblankCounts(int num);
};

#endif // !_CREATGRID_H_




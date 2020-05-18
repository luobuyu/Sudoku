#include "CreatGrid.h"



extern const int NONE;

CreatGrid::CreatGrid(): isFind(false), totalTimes(0)
{
	memset(this->flag, 0, sizeof(this->flag));
	memset(this->grid, 0, sizeof(this->grid));
	memset(this->gridCopy, 0, sizeof(this->gridCopy));
	memset(this->visit, false, sizeof(this->visit));
}

CreatGrid::~CreatGrid()
{

}

bool CreatGrid::check(int i, int x, int y)
{
	return (this->flag[HORIZONTAL][x] & (1 << i)) == false &&
		(this->flag[VERTICAL][y] & (1 << i)) == false &&
		(this->flag[BLOCK][x / 3 * 3 + y / 3] & (1 << i)) == false;
}

void CreatGrid::makeFlag(int i, int x, int y)
{
	this->flag[HORIZONTAL][x] ^= (1 << i);
	this->flag[VERTICAL][y] ^= (1 << i);
	this->flag[BLOCK][x / 3 * 3 + y / 3] ^= (1 << i);
	this->visit[x][y] = true;
}


void CreatGrid::deleteFlag(int i, int x, int y)
{
	this->visit[x][y] = false;
	this->flag[HORIZONTAL][x] ^= (1 << i);
	this->flag[VERTICAL][y] ^= (1 << i);
	this->flag[BLOCK][x / 3 * 3 + y / 3] ^= (1 << i);
}

void CreatGrid::dfs(int x, int y, int step)
{
	if (step == MAX && this->totalTimes >= this->backTime)
	{
		show();
		this->isFind = true;
		return;
	}
	else
	{
		if (this->isFind == true)
			return;
		int begin = rand() % 9;
		for (int i = 0; i < 9; i++)
		{
			int num = (begin + i) % 9;
			if (this->check(num, x, y))
			{
				this->grid[x][y] = num + 1;	// 1 - 9
				this->makeFlag(num, x, y);
				this->totalTimes++;
				this->dfs(x + (y + 1) / 9, (y + 1) % 9, step + 1);
				this->deleteFlag(num, x, y);
			}
		}
	}
}

void CreatGrid::show()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			this->gridCopy[i][j] = this->grid[i][j];
			cout << this->grid[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "****************************" << endl;
}

void CreatGrid::copyArr(int grid[][9], int isExistNum[][9])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			grid[i][j] = this->gridCopy[i][j];
			if (grid[i][j] == 0)
			{
				isExistNum[i][j] = NONE;
			}
			else
			{
				isExistNum[i][j] = ORI;
			}
		}
	}
}

void CreatGrid::eraseArr()
{
	int x, y;
	int temp = 0;
	while (temp < this->blankCounts)
	{
		x = rand() % ROW;
		y = rand() % COL;
		if (this->gridCopy[x][y] != 0)
		{
			gridCopy[x][y] = 0;
			temp++;
		}
	}

}

void CreatGrid::setbackTime(int times)
{
	this->backTime = times;
}

void CreatGrid::setblankCounts(int num)
{
	this->blankCounts = num;
}

#include "sudoku.h"
#include "CreatGrid.h"

// 图形界面
IMAGE bg, bk, wrongbk, welcomebg, win;

Node selectNum = { 0, 0, -1 };


SuDoKu::SuDoKu()
{
	this->creatGrid = new CreatGrid();
	this->selectNode = new SelectNode();
}

SuDoKu::~SuDoKu()
{
	delete this->creatGrid;
	delete this->selectNode;
}

void SuDoKu::loadImg()
{
	char s[20];
	char sy[20];
	char sr[20];
	loadimage(&bg, _T("./img/bg.jpg"), WIN_WIDTH, WIN_HEIGHT);
	loadimage(&welcomebg, _T("./img/welcome.jpg"), WIN_WIDTH, WIN_HEIGHT);
	loadimage(&win, _T("./img/win.jpg"), WIN_WIDTH, WIN_HEIGHT);
	loadimage(&bk, _T("./img/numbg.png"), WIDTH, WIDTH);
	loadimage(&wrongbk, _T("./img/wrongbg.png"), WIDTH, WIDTH);
	for (int i = 1; i <= 9; i++)
	{
		sprintf(s, "./img/%d.png", i);
		sprintf(sy, "./img/%dy.png", i);
		sprintf(sr, "./img/%dr.png", i);
		loadimage(&numImg[0][i - 1], (LPCTSTR)s, WIDTH, WIDTH);
		loadimage(&numImg[1][i - 1], (LPCTSTR)sy, WIDTH, WIDTH);
		loadimage(&numImg[2][i - 1], (LPCTSTR)sr, WIDTH, WIDTH);
	}
}

void SuDoKu::initWin()
{
	// 每个格子 50*50
	// 25 - 475    450
	// 显示时间
	loadImg();
	setlinecolor(LIGHTGRAY);
}

int SuDoKu::welcome()
{
	MOUSEMSG m;
	setbkcolor(BLACK);
	cleardevice();
	putimage(0, 0, &welcomebg);
	FlushBatchDraw();
	while (true)
	{
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		// 175 270 325 310
		// 175 325 325 365
		// 175 375	   410
		//     430     465
		if (m.x >= 180 && m.x <= 325 && m.mkLButton)
		{
			if (m.y >= 295 && m.y <= 335)
			{
				// 简单模式
				return EASY;
			}
			else if (m.y >= 350 && m.y <= 390)
			{
				// 一般模式
				return MEDI;
			}
			else if (m.y >= 410 && m.y <= 450)
			{
				// 困难模式
				return HARD;
			}
			else if (m.y >= 465 && m.y <= 500)
			{
				// 退出游戏
				return EXIT;
			}
		}
		Sleep(FPS);
	}
}

void SuDoKu::drawSelectNum()
{
	// 25, 475 
	// 550, 600
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	for (int i = 0; i < 2; i++)
	{
		line(25, 550 + i * WIDTH, 475, 550 + i * WIDTH);
	}
	for (int i = 0; i < 10; i++)
	{
		if (i % 9 == 0)
		{
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
			line(25 + i * WIDTH, 550, 25 + i * WIDTH, 550 + WIDTH);
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		}
		else
		{
			line(25 + i * WIDTH, 550, 25 + i * WIDTH, 550 + WIDTH);
		}
	}
	for (int i = 0; i < 9; i++)
	{
		putimage(25 + i * WIDTH, 550, &numImg[1][i], SRCAND);
		putimage(25 + i * WIDTH, 550, &numImg[0][i], SRCPAINT);
	}
}

void SuDoKu::isCorr(int x, int y, int num, int grid[][9], int isExistNum[][9])
{
	// 列
	for (int i = 0; i < ROW; i++)
	{
		if (grid[i][y] == num && i != x)
		{
			if (isExistNum[i][y] == ORI)
			{
				this->selectNode->addWrongNode(y * WIDTH + 25, i * WIDTH + 50, num, ORI);
			}
			else
			{
				this->selectNode->addWrongNode(y * WIDTH + 25, i * WIDTH + 50, num, NEW_FILLED);
			}
		}
	}
	// 行
	for (int i = 0; i < COL; i++)
	{
		if (grid[x][i] == num && i != y)
		{
			if (isExistNum[x][i] == ORI)
			{
				this->selectNode->addWrongNode(i * WIDTH + 25, x * WIDTH + 50, num, ORI);
			}
			else
			{
				this->selectNode->addWrongNode(i * WIDTH + 25, x * WIDTH + 50, num, NEW_FILLED);
			}
		}
	}
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++)
	{
		for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
		{
			if (grid[i][j] == num && i != x && j != y)
			{
				if (isExistNum[i][j] == ORI)
				{
					this->selectNode->addWrongNode(j * WIDTH + 25, i * WIDTH + 50, num, ORI);
				}
				else
				{
					this->selectNode->addWrongNode(j * WIDTH + 25, i * WIDTH + 50, num, NEW_FILLED);
				}
			}
		}
	}
}

bool SuDoKu::check(int grid[][9])
{
	int flag[ROW][COL] = { 0 };
	int num;
	bool corr = true;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			num = grid[i][j];
			flag[HORIZONTAL][i] ^= (1 << (num - 1));
			flag[VERTICAL][j] ^= (1 << (num - 1));
			flag[BLOCK][i / 3 * 3 + j / 3] ^= (1 << (num - 1));
			corr = (flag[HORIZONTAL][i] & (1 << (num - 1))) &&
				(flag[VERTICAL][j] & (1 << (num - 1))) &&
				(flag[BLOCK][i / 3 * 3 + j / 3] & (1 << (num - 1)));
			if (corr == false)
			{
				return corr;
			}
		}
	}
	return corr;
}

int SuDoKu::mouseControl(int grid[][9], int isExistNum[][9], clock_t t1)
{
	MOUSEMSG m;
	int x;
	int y;
	FlushMouseMsgBuffer();
	m = GetMouseMsg();
	if (m.x >= 25 && m.x <= 475 && m.y >= 50 && m.y <= 500 && m.mkLButton)
	{
		y = (m.x - 25) / WIDTH;
		x = (m.y - 50) / WIDTH;
		if (selectNum.num != -1 && isExistNum[x][y] != ORI)
		{
			if (selectNum.num == grid[x][y])
			{
				return 0;
			}
			if (grid[x][y] == 0)
			{
				this->selectNode->setRemain(this->selectNode->getRemain() - 1);
			}
			this->selectNode->clearWrongVector();
			grid[x][y] = selectNum.num;
			isExistNum[x][y] = NEW_FILLED;
			isCorr(x, y, selectNum.num, grid, isExistNum);
		}
	}
	else if (m.x >= 25 && m.x <= 475 && m.y >= 550 && m.y <= 600 && m.mkLButton)
	{
		y = (m.x - 25) / WIDTH;
		if (y + 1 != selectNum.num)
		{
			selectNum.num = y + 1;
			selectNum.x = 25 + y * WIDTH;
			selectNum.y = 550;
			this->selectNode->setSelectNum(selectNum);
		}
	}
	// 445 10   490 35
	else if (m.x >= 445 && m.x <= 490 && m.y >= 10 && m.y <= 35 && m.mkLButton)
	{
		if (check(grid) && this->selectNode->getRemain() == 0)
		{
			// 游戏结束
			return gameover(t1);
		}
	}
	return 0;
}

int SuDoKu::gameover(clock_t t1)
{
	clock_t t2 = clock();
	putimage(0, 0, &win);
	TCHAR s[10];
	settextstyle(37, 0, _T("华文彩云"));
	_stprintf(s, _T("%d秒"), (t2 - t1) / CLOCKS_PER_SEC);
	outtextxy(275, 248, s);
	FlushBatchDraw();
	MOUSEMSG m;
	while (true)
	{
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		if (m.y >= 430 && m.y <= 470 && m.mkLButton)
		{
			if (m.x >= 100 && m.x <= 175)
			{
				// 继续
				return CONTINUE;
			}
			else if (m.x >= 330 && m.x <= 405)
			{
				return BACK;
			}
		}
		Sleep(FPS);
	}
}

void SuDoKu::initGame(int mode)
{
	int backTimes;
	int blanks;
	if (mode == EASY)
	{
		backTimes = rand() % RAND_TIMES + EASY_BACK_TIMES;
		blanks = rand() % RAND_COUNTS + EASY_BLANK_COUNTS;
		this->selectNode->setRemain(blanks);
	}
	else if (mode == MEDI)
	{
		backTimes = rand() % RAND_TIMES + MEDI_BACK_TIMES;
		blanks = rand() % RAND_COUNTS + MEDI_BLANK_COUNTS;
	}
	else
	{
		backTimes = rand() % RAND_TIMES + HARD_BACK_TIMES;
		blanks = rand() % RAND_COUNTS + HARD_BLANK_COUNTS;
	}
	this->creatGrid->setbackTime(backTimes);
	this->creatGrid->setblankCounts(blanks);
}

void SuDoKu::putGridImg(int grid[][COL], int isExistNum[][9])
{
	// 50 - 500
	// 25 - 475
	int num;
	clock_t t2 = clock();
	//70 15
	putimage(0, 0, &bg);


	for (int i = 0; i < 10; i++)
	{
		if (i % 3 == 0)
		{
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
			line(25, 50 + i * WIDTH, 475, 50 + i * WIDTH);
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		}
		else
		{
			line(25, 50 + i * WIDTH, 475, 50 + i * WIDTH);
		}

	}
	for (int i = 0; i < 10; i++)
	{
		if (i % 3 == 0)
		{
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
			line(25 + i * WIDTH, 50, 25 + i * WIDTH, 500);
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		}
		else
		{
			line(25 + i * WIDTH, 50, 25 + i * WIDTH, 500);
		}

	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			num = grid[i][j];
			if (num - 1 == -1)
			{
				continue;
			}
			if (isExistNum[i][j] == ORI)
			{
				putimage(25 + j * WIDTH, 50 + i * WIDTH, &numImg[1][num - 1], SRCAND);
				putimage(25 + j * WIDTH, 50 + i * WIDTH, &numImg[2][num - 1], SRCPAINT);
			}
			else if (isExistNum[i][j] == NEW_FILLED)
			{
				putimage(25 + j * WIDTH, 50 + i * WIDTH, &numImg[1][num - 1], SRCAND);
				putimage(25 + j * WIDTH, 50 + i * WIDTH, &numImg[0][num - 1], SRCPAINT);
			}
		}
	}
}

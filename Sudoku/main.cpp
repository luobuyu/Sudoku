#include "sudoku.h"
#include "SelectNode.h"
using namespace std;


IMAGE numImg[3][9];


// 检测行,列,宫格是否放过i
// 如果可以放返回true
// 如果i在横排,竖排,宫格内都没有出现过,则赋值
// 打标记
// 删除标记





int main()
{
	srand((unsigned int)time(NULL));
	freopen("answer.txt", "w", stdout);
	int grid[ROW][COL] = { 0 };
	int isExistNum[ROW][COL] = { 0 };
	int choice1, choice2 = 0;
	SuDoKu* sudoku = NULL;
	clock_t t1;
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	setbkmode(TRANSPARENT);
	
	while (true)
	{
		if (sudoku != NULL)
		{
			delete sudoku;
		}
		sudoku = new SuDoKu();
		sudoku->initWin();
		if (choice2 == 0 || choice2 == BACK)
		{
			choice1 = sudoku->welcome();
			if (choice1 == EXIT)
			{
				break;
			}
		}
		sudoku->initGame(choice1);
		sudoku->creatGrid->dfs(0, 0, 0);
		sudoku->creatGrid->eraseArr();
		sudoku->creatGrid->copyArr(grid, isExistNum);
		
		t1 = clock();
		BeginBatchDraw();
		while (true)
		{
			sudoku->putGridImg(grid, isExistNum);
			sudoku->drawSelectNum();
			choice2 = sudoku->mouseControl(grid, isExistNum, t1);
			sudoku->selectNode->drawSelectGrid();
			if (choice2 != 0)
			{
				break;
			}
			FlushBatchDraw();
			Sleep(FPS);
		}
		
	}
	EndBatchDraw();
	closegraph();
	return 0;
}



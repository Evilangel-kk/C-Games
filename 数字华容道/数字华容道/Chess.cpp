#include "Chess.h"
#include<iostream>
#include<math.h>
#include<graphics.h>
#include<Windows.h>
using namespace std;

void Chess::Init()
{
	step = -1;

	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = 0;
			}
		}

		srand((unsigned)time(NULL));

		for (int i = 1; i <= 16; i++)
		{
			int m = rand() % 4;
			int n = rand() % 4;
			while (map[m][n] != 0)
			{
				m = rand() % 4;
				n = rand() % 4;
			}
			map[m][n] = i;
		}
		if (Setright())
		{
			break;
		}
	}

	initgraph(650, 780);
	loadimage(0, "broad.jpg");
	for (int i = 1; i < 17; i++)
	{
		char fileName[10] = "";
		sprintf_s(fileName, "%d.jpg", i);
		loadimage(&num[i], fileName, imgSize, imgSize);
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			putimage(margin_x + j * imgSize, margin_y + i * imgSize, &num[map[i][j]]);
		}
	}
}

bool Chess::Setright()
{
	int numlist[16];
	for (int i = 0; i < 16; i++)
	{
		numlist[i] = map[i / 4][i % 4];
	}
	int flag_1 = 0;
	int flag_2 = 0;
	for (int i = 0; i < 15; i++)
	{
		if (numlist[i] == 16)
		{
			flag_2 = 4 - (i / 4 + 1);
		}
		if (i < 14 && numlist[i + 1] == 16)
		{
			if (numlist[i] > numlist[i + 2])
			{
				flag_1++;
			}
		}
		else if (numlist[i] != 16 && numlist[i] > numlist[i + 1])
		{
			flag_1++;
		}
	}
	if ((flag_1 + flag_2) % 2 == 0)
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

void Chess::Grade()
{
}

bool Chess::Move(int x, int y)
{
	int tmp = 0;
	//下空格
	if (map[x + 1][y] == 16)
	{
		map[x + 1][y] = map[x][y];
		putimage(margin_x + y * imgSize, margin_y + (x + 1) * imgSize, &num[map[x][y]]);
	}
	//右空格
	else if (map[x][y + 1] == 16)
	{
		map[x][y + 1] = map[x][y];
		putimage(margin_x + (y + 1) * imgSize, margin_y + x * imgSize, &num[map[x][y]]);
	}
	//左空格
	else if (map[x][y - 1] == 16)
	{
		map[x][y - 1] = map[x][y];
		putimage(margin_x + (y - 1) * imgSize, margin_y + x * imgSize, &num[map[x][y]]);
	}
	//上空格
	else if (map[x - 1][y] == 16)
	{
		map[x - 1][y] = map[x][y];
		putimage(margin_x + y * imgSize, margin_y + (x - 1) * imgSize, &num[map[x][y]]);
	}
	else
	{
		return false;
	}
	map[x][y] = 16;
	putimage(margin_x + y * imgSize, margin_y + x * imgSize, &num[map[x][y]]);
	return true;
}

void Chess::Steps()
{
	step++;
	//写出步数
	setbkmode(TRANSPARENT);//去掉文字背景
	char temp[20] = "";
	sprintf_s(temp, "Steps：%d", step);
	settextstyle(35, 0, _T("微软雅黑"));
	settextcolor(RGB(4, 109, 95));		//文字颜色
	setlinecolor(RGB(193, 208, 206));	//方框线条颜色
	setfillcolor(RGB(193, 208, 206));	//方框填充颜色
	fillrectangle(20, 20, 200, 55);		//方框位置
	outtextxy(20, 20, temp);
}

void Chess::Time()
{
}

bool Chess::Judge()
{
	for (int i=0;i<4;i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] != 4 * i + j + 1)
			{
				return false;
			}
		}
	}
	return true;
}



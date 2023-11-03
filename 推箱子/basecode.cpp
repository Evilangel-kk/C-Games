#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include<graphics.h>
#include<mmsystem.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define ROW 10
#define COL 10

//#define SPACE 0
//#define WALL 1
//#define DEST 2
//#define BOX 3
//#define PLAYER 4
enum
{
	SPACE,    //空地
	WALL,     //墻
	DEST,     //目的地
	BOX,      //箱子
	PLAYER,   //玩家
};

//当前关卡
int level = 0;

void ShowMap(int map[3][ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			switch (map[level][i][j])
			{
			case SPACE:
				printf("  ");
				break;
			case WALL:
				printf("* ");
				break;
			case DEST:
				printf("# ");
				break;
			case BOX:
				printf("0");
				break;
			case PLAYER:
				printf("& ");
				break;
			case DEST + PLAYER:
				printf("+ ");
				break;
			case DEST + BOX:
				printf("$ ");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
	return;
}

void PushBox(int map[3][ROW][COL])
{
	int r, c;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[level][i][j] == PLAYER || map[level][i][j] == PLAYER + DEST)
			{
				r = i;
				c = j;
				break;
			}
		}
	}
	//获取键盘
	int order = _getch();
	switch (order)
	{
	case 72:
		//如果上面是空地或者目的地
		if (map[level][r - 1][c] == SPACE || map[level][r - 1][c] == DEST)
		{
			map[level][r - 1][c] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//如果上面是箱子
		else if (map[level][r - 1][c] == BOX)
		{
			//移动箱子
			map[level][r - 2][c] += BOX;
			map[level][r - 1][c] -= BOX;
			//移动玩家
			map[level][r - 1][c] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		break;
	case 80:
		//如果下面是空地或者目的地
		if (map[level][r + 1][c] == SPACE || map[level][r + 1][c] == DEST)
		{
			map[level][r + 1][c] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//如果下面是箱子
		else if (map[level][r + 1][c] == BOX)
		{
			//移动箱子
			map[level][r + 2][c] += BOX;
			map[level][r + 1][c] -= BOX;
			//移动玩家
			map[level][r + 1][c] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		break;
	case 75:
		//如果左侧是空地或者目的地
		if (map[level][r][c - 1] == SPACE || map[level][r][c - 1] == DEST)
		{
			map[level][r][c - 1] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//如果左侧是箱子
		else if (map[level][r][c - 1] == BOX)
		{
			//移动箱子
			map[level][r][c - 2] += BOX;
			map[level][r][c - 1] -= BOX;
			//移动玩家
			map[level][r][c - 1] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		break;
	case 77:
		//如果右侧是空地或者目的地
		if (map[level][r][c + 1] == SPACE || map[level][r][c + 1] == DEST)
		{
			map[level][r][c + 1] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		//如果右侧是箱子
		else if (map[level][r][c + 1] == BOX)
		{
			//移动箱子
			map[level][r][c + 2] += BOX;
			map[level][r][c + 1] -= BOX;
			//移动玩家
			map[level][r][c + 1] += PLAYER;
			map[level][r][c] -= PLAYER;
		}
		break;
	default:
		break;
	}
}

IMAGE Img[7];
//加载图片到变量
void loadImg()
{
	for (int i = 0; i < 7; i++)
	{
		char str[10] = { 0 };
		sprintf_s(str, "%d.jpg", i);
		loadimage(Img + i, str);
	}
	return;
}

//
void DrawMap(int map[3][ROW][COL])
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			putimage(x + j * 50, y + i * 50, Img + map[level][i][j]);
		}
	}
	return;
}


//去数组里找箱子
bool judge(int map[3][ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[level][i][j] == BOX)
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	int map[3][ROW][COL] =
	{
		//第一关
		{
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,0,0,0,0},
			{0,0,0,1,2,1,0,0,0,0},
			{0,0,0,1,0,1,1,1,1,1},
			{0,1,1,1,3,0,3,0,2,1},
			{0,1,2,3,4,0,0,1,1,1},
			{0,1,1,1,1,1,3,1,0,0},
			{0,0,0,0,0,1,2,1,0,0},
			{0,0,0,0,0,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		},
		//第二关
		{
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,0,0,1,1,0,0},
			{0,1,0,0,1,1,0,2,1,0},
			{1,0,0,0,0,0,0,3,2,1},
			{1,2,3,0,4,0,0,3,0,1},
			{0,1,0,0,0,3,0,0,1,0},
			{0,0,1,0,3,0,0,1,0,0},
			{0,0,0,1,2,2,1,0,0,0},
			{0,0,0,0,1,1,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		},
		//第三关
		{
			{0,0,0,0,1,1,0,0,0,0},
			{0,0,0,1,2,0,1,0,0,0},
			{0,0,1,0,3,0,0,1,0,0},
			{0,1,0,0,0,0,0,0,1,0},
			{1,2,0,0,3,3,0,0,2,1},
			{1,1,1,1,4,0,1,1,1,1},
			{1,2,0,0,0,3,0,0,2,1},
			{0,1,0,0,3,0,0,0,1,0},
			{0,0,1,0,0,0,0,1,0,0},
			{0,0,0,1,1,1,1,0,0,0}
		}
	};


	//创建可视化窗口
	initgraph(500, 500/*两个窗口,EW_SHOWCONSOLE*/);

	//播放音乐
	mciSendString("open music.mp3 alias music", 0, 0, 0);
	mciSendString("play music repeat", 0, 0, 0);

	while (true)
	{
		system("cls");
		//ShowMap(map);
		loadImg();
		if (level < 3)
		{
			DrawMap(map);
		}
		else if (level == 3)
		{
			IMAGE win;
			loadimage(&win, "win.jpg");
			putimage(0, 0, &win);
			Sleep(1000);
		}
		if (judge(map))
		{
			//printf("恭喜你，过关了!");
			Sleep(100);
			level++;
			if (level > 3)
			{
				exit(0);
			}
		}
		PushBox(map);
	}
	return 0;
}
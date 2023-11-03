#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<graphics.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define SIZE 4

int map[SIZE][SIZE] = { 0 };
IMAGE Background;
IMAGE Fail;
IMAGE num[2049];

//加载图片变量
void loadImg()
{
	loadimage(&Background, "background.jpg");

	loadimage(&Fail, "fail.jpg");

	loadimage(&num[0], "0.jpg");
	loadimage(&num[2], "2.jpg");
	loadimage(&num[4], "4.jpg");
	loadimage(&num[8], "8.jpg");
	loadimage(&num[16], "16.jpg");
	loadimage(&num[32], "32.jpg");
	loadimage(&num[64], "64.jpg");
	loadimage(&num[128], "128.jpg");
	loadimage(&num[256], "256.jpg");
	loadimage(&num[512], "512.jpg");
	loadimage(&num[1024], "1024.jpg");
	loadimage(&num[2048], "2048.jpg");

	return;
}


//生成随机数2或者4
int putNewNum()
{
	srand((unsigned int)time(NULL));
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		if (map[i][j] == 0)
	//		{
	//			map[i][j] = (rand() % 2 + 1) * 2;
	//			return 0;
	//		}
	//	}
	//}
	while (1)
	{
		int x = rand() % SIZE;
		int y = rand() % SIZE;
		if (map[x][y] == 0)
		{
			map[x][y] = (rand() % 2 + 1) * 2;
			break;
		}
	}
	return 0;
}

//左移
int moveLift()
{
	int i, j, score = 0, flag = -1;
	int cnt = 0;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			int cell = map[i][j];
			if (cell != 0)
			{
				int k = j + 1;
				while (k < SIZE)
				{
					int nextcell = map[i][k];
					if (nextcell != 0)
					{
						if (cell == nextcell)
						{
							flag = 0;//相邻两个元素相同，就说明能移动，所以改变flag的值
							map[i][j] += map[i][k];
							score += map[i][j];
							map[i][k] = 0;
							cnt = 1;
						}
						k = SIZE;
						break;
					}
					k++;
				}
			}
		}
	}
	//修改部分：for循环中的i或者j的循环条件

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE - 1; j++)
		{
			int cell = map[i][j];
			if (cell == 0)
			{
				int k = j + 1;
				while (k < SIZE)
				{
					int nextcell = map[i][k];
					if (nextcell != 0)
					{
						flag = 0;
						map[i][j] = nextcell;
						map[i][k] = 0;
						k = SIZE;
						cnt = 1;
					}
					k++;
				}
			}
		}
	}
	return cnt;
};

//右移
int moveRight()
{
	int i, j, score = 0, flag = -1;
	int cnt=0;
	for (i = 0; i < SIZE; i++)
	{
		for (j = SIZE - 1; j >= 0; j--)
		{
			int cell = map[i][j];
			if (cell != 0)
			{
				int k = j - 1;
				while (k >= 0)
				{
					int nextcell = map[i][k];
					if (nextcell != 0)
					{
						if (cell == nextcell)
						{
							flag = 0;
							map[i][j] += map[i][k];
							score += map[i][j];
							map[i][k] = 0;
							cnt = 1;
						}
						k = -1;
						break;
					}
					k--;
				}
			}
		}
	}

	//修改部分：for循环中的i或者j的循环条件

	for (i = 0; i < SIZE; i++)
	{
		for (j = SIZE - 1; j > 0; j--)
		{
			int cell = map[i][j];
			if (cell == 0)
			{

				int k = j - 1;
				while (k >= 0)
				{
					int nextcell = map[i][k];
					if (nextcell != 0)
					{
						flag = 0;//当前元素为0，说明能移动，改变flag的值
						map[i][j] = nextcell;
						map[i][k] = 0;
						k = -1;
						cnt = 1;
					}
					k--;
				}
			}
		}
	}
	return cnt;
};

//上移
int moveUp()
{
	int i, j, score = 0, flag = -1;
	int cnt=0;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			int cell = map[i][j];

			if (cell != 0)
			{
				int k = i + 1;
				while (k < SIZE)
				{
					int nextcell = map[k][j];
					if (nextcell != 0)
					{
						if (cell == nextcell)
						{
							flag = 0;
							map[i][j] += map[k][j];
							score += map[i][j];
							map[k][j] = 0;
							cnt = 1;
						}
						k = SIZE;
						break;
					}
					k++;
				}
			}
		}
	}

	//修改部分：for循环中的i或者j的循环条件
	for (i = 0; i < SIZE - 1; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			int cell = map[i][j];
			if (cell == 0)
			{

				int k = i + 1;
				while (k < SIZE)
				{
					int nextcell = map[k][j];
					if (nextcell != 0)
					{
						flag = 0;
						map[i][j] = nextcell;
						map[k][j] = 0;
						k = SIZE;
						cnt = 1;
					}
					k++;
				}
			}
		}
	}
	return cnt;
};

//下移
int moveDown()
{
	int i, j, score = 0, flag = -1;
	int cnt = 0;
	for (i = SIZE - 1; i >= 0; i--)
	{
		for (j = 0; j < SIZE; j++)
		{
			int cell = map[i][j];

			if (cell != 0)
			{
				int k = i - 1;
				while (k >= 0)
				{
					int nextcell = map[k][j];
					if (nextcell != 0)
					{
						if (map[i][j] == map[k][j])
						{
							flag = 0;
							map[i][j] += map[k][j];
							score += map[i][j];
							map[k][j] = 0;
							cnt = 1;
						}
						k = 0;
						break;
					}
					k--;
				}
			}
		}
	}

	//修改部分：for循环中的i或者j的循环条件
	for (i = SIZE - 1; i > 0; i--)
	{
		for (j = 0; j < SIZE; j++)
		{
			int cell = map[i][j];
			if (cell == 0)
			{
				int k = i - 1;
				while (k >= 0)
				{
					int nextcell = map[k][j];
					if (nextcell != 0)
					{
						flag = 0;
						map[i][j] = nextcell;
						map[k][j] = 0;
						k = 0;
						cnt = 1;
					}
					k--;
				}
			}
		}
	}
	return cnt;
};

//贴图操作
void putImg()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			putimage(4+j * 104, 4+i * 104, num + map[i][j]);
		}
	}
	return;
}

//移动命令
void move()
{
	int order = _getch();
	switch (order)
	{
		//左
	case 75:
		if (moveLift() == 0)
		{
			move();
		}
		else
		{
			putImg();
			Sleep(200);
			putNewNum();
		}
		break;
		//右
	case 77:
		if (moveRight() == 0)
		{
			move();
		}
		else
		{
			putImg();
			Sleep(200);
			putNewNum();
		}
		break;
		//上
	case 72:
		if (moveUp() == 0)
		{
			move();
		}
		else
		{
			putImg();
			Sleep(200);
			putNewNum();
		}
		break;
		//下
	case 80:
		if (moveDown() == 0)
		{
			move();
		}
		else
		{
			putImg();
			Sleep(200);
			putNewNum();
		}
		break;
	default:break;
	}
	return;
}


//判断游戏结束
bool Judge()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
			{
				return true;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (map[i][j] == map[i + 1][j] || map[i][j] == map[i][j + 1])
			{
				return true;
			}
		}
	}
	for (int j = 0; j < 3; j++)
	{
		if (map[3][j] == map[3][j + 1])
		{
			return true;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (map[i][3] == map[i + 1][3])
		{
			return true;
		}
	}
	return false;
}

//主函数
int main()
{
	loadImg();
	initgraph(420, 420);
	putimage(0, 0, &Background);
	mciSendString("open music.mp3 alias music", 0, 0, 0);
	mciSendString("play music repeat", 0, 0, 0);
	putNewNum();
	putNewNum();
	putImg();
	while (true)
	{
		move();
		putImg();
		if (Judge() == false)
		{
			putImg();
			mciSendString("close music", 0, 0, 0);
			break;
		}
	}
	Sleep(600);
	putImg();
	Sleep(1000);
	putimage(0, 0, &Fail);
	Sleep(4000);

	closegraph();
	system("pause");
	return 0;
}
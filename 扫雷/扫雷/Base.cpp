#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<easyx.h>
#include<stdbool.h>
#include<conio.h>
#include<graphics.h>
#define WIDE 20
#define THUNDER 50
#define SIZE 35

//枚举类型
enum State
{
	OPEN,
	CLOSE,
	FLAGE
};

struct NODE
{
	int num;
	int state;
	int flag;
}NODE;

struct NODE map[WIDE][WIDE];

IMAGE paper[11];
IMAGE background;
IMAGE YES;
IMAGE NO;
IMAGE NON;
IMAGE WIN;

int Flag = 1;
//-1:游戏失败
//0:踩到雷了
//1:游戏正常/重新开始
//2:游戏胜利

//加载图片变量
void loading()
{
	for (int i = 0; i < 11; i++)
	{
		int j = i - 2;
		char filename[10] = "";
		sprintf(filename, "%d.jpg", j);
		loadimage(&paper[i], filename, SIZE, SIZE);
	}
	loadimage(&background, "background.jpg", 830, 740);
	loadimage(&YES,"YES.jpg",80,80);
	loadimage(&NO,"NO.jpg",80,80);
	loadimage(&NON, "-3.jpg",SIZE,SIZE);
	loadimage(&WIN, "WIN.jpg");
}

//贴图
void putting()
{
	putimage(0, 0, &background);
	putimage(13, 280, &YES);
	for (int i = 0; i < WIDE; i++)
	{
		for (int j = 0; j < WIDE; j++)
		{
			if (map[i][j].state == CLOSE)
			{
				putimage(110 + j * SIZE, 20 + i * SIZE, &paper[2]);
			}
			else if (map[i][j].state == FLAGE)
			{
				putimage(110 + j * SIZE, 20 + i * SIZE, &paper[1]);
			}
		}
	}
}

//判断游戏胜利
int GameWin()
{
	for (int i = 0; i < WIDE; i++)
	{
		for (int j = 0; j < WIDE; j++)
		{
			if (map[i][j].state == CLOSE)
			{
				return 0;
			}
		}
	}
	return 1;
}


//连开
void OpenNode(int x, int y)
{
	if (x - 1 >= 0 && map[x - 1][y].state == CLOSE && map[x - 1][y].num == 0)
	{
		map[x - 1][y].state = OPEN;
		putimage(110 + (x - 1) * SIZE, 20 + y * SIZE, &NON);
		OpenNode(x - 1, y);
	}
	if (x - 1 >= 0 && map[x - 1][y].state == CLOSE && map[x - 1][y].num != 0)
	{
		map[x - 1][y].state = OPEN;
		putimage(110 + (x - 1) * SIZE, 20 + y * SIZE, &paper[map[x - 1][y].num + 2]);
	}
	if (x + 1 < WIDE && map[x + 1][y].state == CLOSE && map[x + 1][y].num == 0)
	{
		map[x + 1][y].state = OPEN;
		putimage(110 + (x + 1) * SIZE, 20 + y * SIZE, &NON);
		OpenNode(x+1,y);
	}
	if (x + 1 < WIDE && map[x + 1][y].state == CLOSE && map[x + 1][y].num != 0)
	{
		map[x + 1][y].state = OPEN;
		putimage(110 + (x + 1) * SIZE, 20 + y * SIZE, &paper[map[x + 1][y].num + 2]);
	}
	if (y - 1 >= 0 && map[x][y - 1].state == CLOSE && map[x][y - 1].num == 0)
	{
		map[x][y - 1].state = OPEN;
		putimage(110 + x * SIZE, 20 + (y - 1) * SIZE, &NON);
		OpenNode(x, y - 1);
	}
	if (y - 1 >= 0 && map[x][y - 1].state == CLOSE && map[x][y - 1].num != 0)
	{
		map[x][y - 1].state = OPEN;
		putimage(110 + x * SIZE, 20 + (y - 1) * SIZE, &paper[map[x][y-1].num + 2]);
	}
	if (y + 1 < WIDE && map[x][y + 1].state == CLOSE && map[x][y + 1].num == 0)
	{
		map[x][y + 1].state = OPEN;
		putimage(110 + x * SIZE, 20 + (y + 1) * SIZE, &NON);
		OpenNode(x, y + 1);
	}
	if (y + 1 < WIDE && map[x][y + 1].state == CLOSE && map[x][y + 1].num != 0)
	{
		map[x][y + 1].state = OPEN;
		putimage(110 + x * SIZE, 20 + (y + 1) * SIZE, &paper[map[x][y + 1].num + 2]);
	}
}

//状态转换
void ChangeState()
{
	int i = 0;

	MOUSEMSG m; //存放鼠标的值
	m = GetMouseMsg();
	switch (m.uMsg)
	{
		case WM_LBUTTONDOWN:
			if (m.x > 110 && m.x <= 810 && m.y > 20 && m.y < 720)
			{
				int x = (m.x - 110) / SIZE;
				int y = (m.y - 20) / SIZE;
				if (map[x][y].state == CLOSE)
				{
					map[x][y].state = OPEN;
					if (map[x][y].num == -2)
					{
						putimage(110 + x * SIZE, 20 + y * SIZE, &paper[0]);
						Flag = 0;
					}
					else if (map[x][y].num == 0)
					{
						putimage(110 + x * SIZE, 20 + y * SIZE, &NON);
						OpenNode(x, y);
					}
					else
					{
						putimage(110 + x * SIZE, 20 + y * SIZE, &paper[map[x][y].num + 2]);
					}
				}
				else if (map[x][y].state == FLAGE)
				{
					map[x][y].state = CLOSE;
					putimage(110 + x * SIZE, 20 + y * SIZE, &paper[2]);
				}
			}
			break;
		case WM_RBUTTONDOWN:
			if (m.x > 110 && m.x <= 810 && m.y > 20 && m.y < 720)
			{
				int x = (m.x - 110) / SIZE;
				int y = (m.y - 20) / SIZE;
				if (map[x][y].state == CLOSE)
				{
					map[x][y].state = FLAGE;
					putimage(110 + x * SIZE, 20 + y * SIZE, &paper[1]);
				}
				else if (map[x][y].state == FLAGE)
				{
					map[x][y].state = CLOSE;
					putimage(110 + x * SIZE, 20 + y * SIZE, &paper[2]);
				}
			}
			break;
		default:
			break;
	}
	if (GameWin() == 1)
	{
		Flag = 2;
	}
}

//随机产生雷
void Crate()
{
	for (int i = 0; i < WIDE; i++)
	{
		for (int j = 0; j < WIDE; j++)
		{
			map[i][j].flag = 0;
			map[i][j].num = 0;
			map[i][j].state = CLOSE;
		}
	}

	srand((unsigned)time(NULL));

	for (int i = 0; i < THUNDER;)
	{
		int x, y;
		x = rand() % WIDE;
		y = rand() % WIDE;
		if (map[x][y].flag == 0)
		{
			map[x][y].flag = 1;
			i++;
		}
	}

	for (int i = 0; i < WIDE; i++)
	{
		for (int j = 0; j < WIDE; j++)
		{
			if (i - 1 >= 0)
			{
				map[i][j].num += map[i - 1][j].flag;
				if (j - 1 >= 0)
				{
					map[i][j].num += map[i - 1][j - 1].flag;
				}
				if (j + 1 < WIDE)
				{
					map[i][j].num += map[i - 1][j + 1].flag;
				}
			}
			if (i + 1 < WIDE)
			{
				map[i][j].num += map[i + 1][j].flag;
				if (j - 1 >= 0)
				{
					map[i][j].num += map[i + 1][j - 1].flag;
				}
				if (j + 1 < WIDE)
				{
					map[i][j].num += map[i + 1][j + 1].flag;
				}
			}
			if (j - 1 >= 0)
			{
				map[i][j].num += map[i][j - 1].flag;
			}
			if (j + 1 < WIDE)
			{
				map[i][j].num += map[i][j + 1].flag;
			}
		}
	}
	for (int i = 0; i < WIDE; i++)
	{
		for (int j = 0; j < WIDE; j++)
		{
			if (map[i][j].flag == 1)
			{
				map[i][j].num = -2;
			}
		}
	}
}

//判断游戏重新开始
int ReplayGame()
{
	MOUSEMSG m;
	m = GetMouseMsg();
	switch (m.uMsg)
	{
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONDOWN:
		if (m.x > 13 && m.x < 93 && m.y>280 && m.y < 360)
		{
			Flag = -1;
			return 1;
		}
		break;
	default:
		break;
	}
	return 0;
}

int main()
{
	
	loading();
	initgraph(830, 740/*,EW_SHOWCONSOLE*/);
	Crate();
	putting();
	while(Flag==1)
	{
		while(Flag==1)
		{
			ChangeState();
		}
		if (Flag==0)
		{
			putimage(13, 280, &NO);
		}
		if (Flag == 2)
		{
			putimage(13, 280, &WIN);
		}
		while (1)
		{
			if (ReplayGame() == 1)
			{
				Crate();
				putting();
				Flag = 1;
				break;
			}
		}
	}
	system("pause");
	closegraph();
	return 0;
}
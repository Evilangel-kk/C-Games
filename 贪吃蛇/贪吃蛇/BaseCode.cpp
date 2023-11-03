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
#define WIN_WIDTH 1000
#define WIN_HEIGHT 700 //窗口宽高
#define MAX_SNAKE 20000  //蛇的最大节数

//枚举方向
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//蛇的结构体
struct Snake_tlg
{
	int num;//长度
	int dir;//方向
	int score;//分数
	int size;//蛇的宽度和高度
	POINT coor[MAX_SNAKE];
}snake;

//食物结构体
struct Food_tlg
{
	POINT fd;
	int flag;
	DWORD color;
	int size;
}food;

//初始化蛇
void SnakeInit()
{
	snake.num = 3;
	snake.dir = RIGHT;
	snake.size = 10;
	snake.score = 0;
	
	for (int i = 2; i >= 0; i--)
	{
		snake.coor[i].x = snake.size * (2 - i);
		snake.coor[i].y = 0;
	}	
}

//初始化食物
void FoodInit()
{
	srand(GetTickCount());
	food.fd.x = (rand() % (WIN_WIDTH / 10)) * 10;
	food.fd.y = (rand() % (WIN_HEIGHT / 10)) * 10;
	for (int i = 0; i < snake.num; i++)
	{
		if (food.fd.x == snake.coor[i].x && food.fd.y == snake.coor[i].y)
		{
			food.fd.x = (rand() % (WIN_WIDTH / 10)) * 10;
			food.fd.y = (rand() % (WIN_HEIGHT / 10)) * 10;
		}
	}
	food.flag = 1;
	food.size = 10;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

//地图
void GameDraw()
{
	//设置背景
	setbkcolor(RGB(105,160,141));
	cleardevice();
	//画🐍
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(YELLOW);
		if (i == 0)
		{
			setfillcolor(RGB(73, 235, 250));
		}
		else
		{
			setfillcolor(RGB(205, 156, 251));
		}
		fillrectangle(snake.coor[i].x,snake.coor[i].y,snake.coor[i].x+snake.size,snake.coor[i].y+snake.size);
	}
	//画食物
	if (food.flag == 1)
	{
		setfillcolor(food.color);
		fillellipse(food.fd.x, food.fd.y, food.fd.x + food.size, food.fd.y + food.size);
	}
	//显示分数
	char temp[20] = "";
	sprintf(temp, "Score:%d", snake.score);
	setbkmode(TRANSPARENT);
	outtextxy(20, 20, temp);
}

//运动
void SnakeMove()
{
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.size;
		if (snake.coor[0].y + snake.size <= 0)
		{
			snake.coor[0].y = WIN_HEIGHT-snake.size;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.size;
		if (snake.coor[0].x + snake.size <= 0)
		{
			snake.coor[0].x = WIN_WIDTH-snake.size;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.size;
		if (snake.coor[0].y + snake.size > WIN_HEIGHT)
		{
			snake.coor[0].y = 0;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.size;
		if (snake.coor[0].x + snake.size > WIN_WIDTH)
		{
			snake.coor[0].x = 0;
		}
		break;
	default:
		break;
	}
}

//键盘控制方向
void KeyControl()
{
	//使用win32API获取键盘值
	if ((GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) && snake.dir != DOWN)
	{
		snake.dir = UP;
	}
	if ((GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) && snake.dir != RIGHT)
	{
		snake.dir = LEFT;
	}
	if ((GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) && snake.dir != UP)
	{
		snake.dir = DOWN;
	}
	if ((GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) && snake.dir != LEFT)
	{
		snake.dir = RIGHT;
	}
}

//吃
void EatFood()
{
	if (snake.coor[0].x == food.fd.x && snake.coor[0].y == food.fd.y && food.flag==1)
	{
		snake.num++;
		snake.score += 10;
		food.flag = 0;
	}
	if (food.flag == 0)
	{
		FoodInit();
	}
}

//咬自己
void DontEatSelf()
{
	for (int i = 3; i < snake.num; i++)
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			setbkmode(TRANSPARENT);
			settextcolor(WHITE);
			settextstyle(25, 0, _T("微软雅黑"));
			outtextxy(100, 100, _T("GAME OVER!"));
			setlinecolor(RGB(0,0,0));
			fillrectangle(220, 245, 520, 270);
			settextstyle(15, 0, _T("微软雅黑"));
			outtextxy(240, 240, _T("Play again"));
		}
	}
}

//变速
int Speed()
{
	return 100 - snake.score / 50;
}

int main()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	SnakeInit();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();
	BeginBatchDraw();
	while (1)
	{
		if (t2 - t1 > Speed())
		{
			SnakeMove();
			t1 = t2;
		}
		t2 = GetTickCount();

		GameDraw();
		EatFood();
		
		KeyControl();
		DontEatSelf();
		FlushBatchDraw();
	}
	getchar();
	closegraph();
	return 0;
}
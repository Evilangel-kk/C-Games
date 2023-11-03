#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>
#include<stdbool.h>
#include<graphics.h>
#define NUM 5

IMAGE img_jump;
IMAGE img_move[8];
IMAGE img_roll[8];

//玩家的行动状态
enum State
{
	Move,
	Jump,
	Roll
};

struct Gamer
{
	int x;
	int y;
	IMAGE* curImg;          //当前绘制的哪套图片
	int img_i;             
	int inity;             //始终保持初始y坐标
	State state;            //玩家当前状态
}gamer;

//定时器
bool Timer(clock_t ms, int id)
{
	static clock_t start[10] = { 0 };
	clock_t end = clock();
	if (end - start[id] >= ms)
	{
		start[id] = end;
		return true;
	}
	return false;
}

//障碍物
struct Bricks
{
	int x;
	int y;
	int w;
	int h;
	char color;
}brick;

//定义砖块参数
void initBricks()
{
	brick.w = 50;
	brick.h = 50;
	brick.x = 550;
	brick.y = 360 - brick.h;
}

//画砖块
void drawBricks()
{
	setfillcolor(GREEN);
	solidrectangle(brick.x, brick.y, brick.x + brick.w, brick.y + brick.h);
}

//移动砖块
void moveBricks()
{
	brick.x--;
	if (brick.x + brick.w <= 0)
	{
		brick.x = getwidth();
	}

}

//检测玩家是否与砖块发生了碰撞
void collision()
{
	//1.坐标判断

}

void loadImg()
{
	for (int i = 0; i < 8; i++)
	{
		char fileName[30] = { 0 };
		sprintf_s(fileName,"move_%d.jpg",i);
		loadimage(img_move + i, fileName,70,100);	
		sprintf_s(fileName, "roll_%d.jpg", i);
		loadimage(img_roll + i,fileName,50,50);
	}
	loadimage(&img_jump, "jump.jpg",70,100);
}

void init()
{
	loadImg();

	gamer.x = 50;
	gamer.y = 360 - 100;
	gamer.inity = gamer.y;
	gamer.curImg = img_move;
	gamer.img_i = 0;
	gamer.state = Move;
}

void draw()
{
	//绘制地板 高度40
	setfillcolor(RGB(200,191,231));
	solidrectangle(0,getheight()-40, getwidth(), getheight());
	//绘制玩家图片
	putimage(gamer.x, gamer.y, gamer.curImg + gamer.img_i);
}

//玩家跑动动画
void moveGamer()
{
	//i++;
	//if (i > 7)
	//{
	//	i = 0;
	//}
	gamer.curImg = img_move;
	gamer.img_i = (gamer.img_i + 1) % 8;//0-7循环
	//Sleep(60);副作用：群体睡眠
}

//玩家跳跃动画
void jumpGamer()
{
	static bool isJump = true;   //true 上升 false 下降
	gamer.curImg = &img_jump;
	
	//向下掉的条件
	if (gamer.y <= gamer.inity - 150)
	{
		isJump = false;
	}

	if (isJump)              //上升
	{
		gamer.y -= 30;
	}
	else                     //下降
	{
		gamer.y += 30;
		//下降到原来的位置就停止下降，回复奔跑状态
		if (gamer.y >= gamer.inity)
		{
			gamer.state = Move;
			gamer.y = gamer.inity;
			isJump = true;
		}
	}
}

//玩家滚动动画
void rollGamer()
{
	gamer.curImg = img_roll;

	if (gamer.img_i++ == 7)
	{
		gamer.img_i = 0;
		gamer.state = Move;
		gamer.y = gamer.inity;
	}
}

//玩家状态切换处理
void GamerStateDeal()
{
	switch (gamer.state)
	{
	case Move:
		if (Timer(100, 0))
		{
			moveGamer();
		}
		break;
	case Jump:
		if (Timer(100, 1))
		{
			jumpGamer();
		}
		break;
	case Roll:
		if (Timer(125, 2))
		{
			rollGamer();
		}
		break;
	default:
		break;
	}
}

//按键消息处理
void keyContorl()
{
	//获取异步按键状态，不会阻塞，vk virtual key 虚拟键值
	if (GetAsyncKeyState(VK_SPACE) && gamer.state==Move)      //空格滚动
	{
		gamer.y = 310;
		gamer.state = Roll;
		gamer.img_i = 0;
	}
	if (GetAsyncKeyState(VK_UP))         //上键跳跃
	{
		gamer.y = 260;
		gamer.state = Jump;
		gamer.img_i = 0;
	}
}

int main()
{
	//1.创建窗口
	initgraph(640,400/*,EW_SHOWCONSOLE*/);
	//2.设置窗口背景颜色
	setbkcolor(RGB(252,253,255));
	//清屏（图形窗口）system("cls")清除控制台
	cleardevice();

	init();	
	initBricks();
	BeginBatchDraw();
	while (1)
	{
		cleardevice();
		GamerStateDeal();
		
		draw();
		keyContorl();
	
		drawBricks();
		if (Timer(3, 3))
		{
			moveBricks();
		}
		
		FlushBatchDraw();

	}
	EndBatchDraw();
	
	getchar();

	return 0;
}
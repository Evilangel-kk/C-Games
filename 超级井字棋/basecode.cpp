#include<stdio.h>
#include<stdlib.h>
#include<easyx.h>
#include<stdbool.h>
#include<conio.h>
#include<math.h>
#include<Windows.h>
#include<graphics.h>
#define ROW 9                     //行数
#define COL 9                     //列数
#define GRID_W 40                 //格子宽度
#define INTERVAL_UP (2*GRID_W)    //上边的空隙大小
#define INTERVAL_LEFT (7*GRID_W)  //左边的空隙大小

//存储数据的二维数组
int map[ROW][COL] = { 0 };
int big_map[3][3] = { 0 };

//存储上一次的数据
struct BEFORE
{
	int x = 0;
	int y = 0;
	int time = 0;
}before;

//枚举类型
enum Chess
{
	Full,
	None,
	Circle,
	Cross
};

//记录当前的数据结构
struct
{
	int x = 0;
	int y = 0;
	//鼠标当前所在的数组对应的下标
	int row = 0;
	int col = 0;
	bool is_show = false;  //是否显示框
	Chess chessPlayer = Circle;
}op;

//鼠标开始
int mouse()
{
	//定义消息结构体变量
	ExMessage msg;
	//获取鼠标消息
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.x > 750 && msg.x < 860 && msg.y > 440 && msg.y < 475 && msg.message == WM_LBUTTONDOWN)
			{
				break;
			}
		}
	}
	return 1;
}

//画棋盘
void draw()
{
	setlinestyle(PS_SOLID, 1);
	//设置线条颜色
	setlinecolor(BLACK);
	//绘制棋盘
	for (int i = 0; i < ROW; i++)
	{
		if (i == 3 || i == 6)
		{
			setlinestyle(PS_SOLID, 2);
		}
		else
		{
			setlinestyle(PS_SOLID, 1);
		}
		line(INTERVAL_LEFT, INTERVAL_UP + i * GRID_W, GRID_W * 9 + INTERVAL_LEFT, INTERVAL_UP + i * GRID_W);
		line(INTERVAL_LEFT + i * GRID_W, INTERVAL_UP, INTERVAL_LEFT + i * GRID_W, GRID_W * 9 + INTERVAL_UP);
	}
	setlinestyle(PS_SOLID, 3);
	rectangle(INTERVAL_LEFT, INTERVAL_UP, GRID_W * 9 + INTERVAL_LEFT, GRID_W * 9 + INTERVAL_UP);

	setlinestyle(PS_SOLID, 2);
	rectangle(750, 440, 860, 475);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(755, 445, _T("重新开始"));
	setbkmode(TRANSPARENT);//去掉文字背景


	//绘制下棋选择框
	if (op.is_show)
	{
		setlinecolor(RGB(127, 127, 127));
		rectangle(op.x - 10, op.y - 10, op.x + 10, op.y + 10);
	}

	//绘制小棋子
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			switch (map[i][j])
			{
			case Circle:
				setlinecolor(WHITE);
				solidcircle(j * GRID_W + INTERVAL_LEFT + 20, i * GRID_W + INTERVAL_UP + 20, 15);
				break;
			case Cross:
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID, 4);
				line(INTERVAL_LEFT + j * GRID_W + 8, i * GRID_W + INTERVAL_UP + 8, INTERVAL_LEFT + j * GRID_W + 32, i * GRID_W + INTERVAL_UP + 32);
				line(INTERVAL_LEFT + j * GRID_W + 32, i * GRID_W + INTERVAL_UP + 8, INTERVAL_LEFT + j * GRID_W + 8, i * GRID_W + INTERVAL_UP + 32);
				break;
			default:
				break;
			}
		}
	}

	//绘制大棋子
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (big_map[i][j])
			{
			case Circle:
				setlinecolor(WHITE);
				solidcircle(j * GRID_W * 3 + INTERVAL_LEFT + 60, i * GRID_W * 3 + INTERVAL_UP + 60, 45);
				break;
			case Cross:
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID, 6);
				line(INTERVAL_LEFT + j * GRID_W * 3 + 18, i * GRID_W * 3 + INTERVAL_UP + 18, INTERVAL_LEFT + j * GRID_W * 3 + 102, i * GRID_W * 3 + INTERVAL_UP + 102);
				line(INTERVAL_LEFT + j * GRID_W * 3 + 102, i * GRID_W * 3 + INTERVAL_UP + 18, INTERVAL_LEFT + j * GRID_W * 3 + 18, i * GRID_W * 3 + INTERVAL_UP + 102);
				break;
			default:
				break;
			}
		}
	}


}

//释放数组中的数据
void clean(int i, int j, int chess)
{
	big_map[i / 3][j / 3] = chess;
	for (int a = i; a < i + 3; a++)
	{
		for (int b = j; b < j + 3; b++)
		{
			map[a][b] = Full;
		}
	}
}

//判断小格 true-胜利
bool judge_map(int i, int j)
{
	if (map[i][j] == map[i + 1][j] && map[i][j] == map[i + 2][j] && map[i][j] != None)
	{
		return true;
	}
	else if (map[i][j] == map[i][j + 1] && map[i][j] == map[i][j + 2] && map[i][j] != None)
	{
		return true;
	}
	else if (map[i + 1][j] == map[i + 1][j + 1] && map[i + 1][j] == map[i + 1][j + 2] && map[i + 1][j] != None)
	{
		return true;
	}
	else if (map[i + 2][j] == map[i + 2][j + 1] && map[i + 2][j] == map[i + 2][j + 2] && map[i + 2][j] != None)
	{
		return true;
	}
	else if (map[i][j + 1] == map[i + 1][j + 1] && map[i][j + 1] == map[i + 2][j + 1] && map[i][j + 1] != None)
	{
		return true;
	}
	else if (map[i][j + 2] == map[i + 1][j + 2] && map[i][j + 2] == map[i + 2][j + 2] && map[i][j + 2] != None)
	{
		return true;
	}
	else if (map[i][j] == map[i + 1][j + 1] && map[i][j] == map[i + 2][j + 2] && map[i][j] != None)
	{
		return true;
	}
	else if (map[i][j + 2] == map[i + 1][j + 1] && map[i][j + 2] == map[i + 2][j] && map[i][j + 2] != None)
	{
		return true;
	}
	return false;
}

//判断大格 true-胜利
bool judge_big_map()
{
	int i = 0;
	int j = 0;
	if (big_map[i][j] == big_map[i + 1][j] && big_map[i][j] == big_map[i + 2][j] && big_map[i][j] != None)
	{
		return true;
	}
	else if (big_map[i][j] == big_map[i][j + 1] && big_map[i][j] == big_map[i][j + 2] && big_map[i][j] != None)
	{
		return true;
	}
	else if (big_map[i + 1][j] == big_map[i + 1][j + 1] && big_map[i + 1][j] == big_map[i + 1][j + 2] && big_map[i + 1][j] != None)
	{
		return true;
	}
	else if (big_map[i + 2][j] == big_map[i + 2][j + 1] && big_map[i + 2][j] == big_map[i + 2][j + 2] && big_map[i + 2][j] != None)
	{
		return true;
	}
	else if (big_map[i][j + 1] == big_map[i + 1][j + 1] && big_map[i][j + 1] == big_map[i + 2][j + 1] && big_map[i][j + 1] != None)
	{
		return true;
	}
	else if (big_map[i][j + 2] == big_map[i + 1][j + 2] && big_map[i][j + 2] == big_map[i + 2][j + 2] && big_map[i][j + 2] != None)
	{
		return true;
	}
	else if (big_map[i][j] == big_map[i + 1][j + 1] && big_map[i][j] == big_map[i + 2][j + 2] && big_map[i][j] != None)
	{
		return true;
	}
	else if (big_map[i][j + 2] == big_map[i + 1][j + 1] && big_map[i][j + 2] == big_map[i + 2][j] && big_map[i][j + 2] != None)
	{
		return true;
	}
	return false;
}

//鼠标
void mouseEvent()
{
	//定义消息结构体变量
	ExMessage msg;
	//获取鼠标消息
	if (peekmessage(&msg, EM_MOUSE))
	{
		op.is_show = false;
		//坐标校准
		if (before.time == 0)
		{
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					//求每个格子左上角坐标
					int gridx = (j + 7) * GRID_W + 20;
					int gridy = (i + 2) * GRID_W + 20;
					if (abs(msg.x - gridx) < 18 && abs(msg.y - gridy) < 18)
					{
						op.x = gridx;
						op.y = gridy;
						op.row = i;
						op.col = j;
						op.is_show = true;
					}

				}
			}
		}
		if (before.time == 1 && msg.x > before.x * GRID_W * 3 + INTERVAL_LEFT && msg.x < (before.x + 1) * GRID_W * 3 + INTERVAL_LEFT && msg.y > before.y * GRID_W * 3 + INTERVAL_UP && msg.y < (before.y + 1) * GRID_W * 3 + INTERVAL_UP)
		{
			if (big_map[(msg.y - INTERVAL_UP) / (3 * GRID_W)][(msg.x - INTERVAL_LEFT) / (3 * GRID_W)] == None)
			{
				for (int i = 0; i < ROW; i++)
				{
					for (int j = 0; j < COL; j++)
					{
						//求每个格子左上角坐标
						int gridx = (j + 7) * GRID_W + 20;
						int gridy = (i + 2) * GRID_W + 20;
						if (abs(msg.x - gridx) < 18 && abs(msg.y - gridy) < 18)
						{
							op.x = gridx;
							op.y = gridy;
							op.row = i;
							op.col = j;
							op.is_show = true;
						}

					}
				}
			}
		}

		//左键点击下棋
		if (msg.message == WM_LBUTTONDOWN && map[op.row][op.col] == None)
		{
			map[op.row][op.col] = op.chessPlayer;
			int x = op.col / 3;
			x *= 3;
			int y = op.row / 3;
			y *= 3;

			before.time = 1;
			before.x = op.col % 3;
			before.y = op.row % 3;


			if (judge_map(y, x) == true)
			{
				clean(y, x, op.chessPlayer);
			}

			if (map[before.y * 3][before.x * 3] == Full)
			{
				before.time = 0;
			}

			if (judge_big_map())
			{

				draw();

				FlushBatchDraw();
				MessageBox(GetHWnd(), "  你赢了\n是否要再来一局", op.chessPlayer == Circle ? "Circle" : "Cross", MB_OK);
			}
			op.chessPlayer = (op.chessPlayer == Circle ? Cross : Circle);
		}

		//判断重新开始
		if (msg.x > 750 && msg.x < 860 && msg.y > 440 && msg.y < 475)
		{
			before.time = 0;
			if (msg.message == WM_LBUTTONDOWN)
			{
				for (int i = 0; i < ROW; i++)
				{
					for (int j = 0; j < COL; j++)
					{
						map[i][j] = None;
					}
				}
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						big_map[i][j] = None;
					}
				}
				cleardevice();
				draw();
			}
		}
	}
}

int main()
{
	//创建窗口
	initgraph(1000, 561);

	//写游戏规则
	IMAGE instruction_img;
	loadimage(&instruction_img, "instruction.jpg", 1000, 561);
	putimage(0, 0, &instruction_img);

	while (1)
	{
		if (mouse() == 1)
		{
			break;
		}
	}

	IMAGE background_img;
	loadimage(&background_img, "background.jpg", 1000, 561);
	putimage(0, 0, &background_img);

	//双缓冲绘图
	BeginBatchDraw();
	while (1)
	{
		//清屏
		cleardevice();
		putimage(0, 0, &background_img);
		draw();
		mouseEvent();
		FlushBatchDraw();   //刷新
	}
	EndBatchDraw();         //结束绘图
	system("pause");
	return 0;
}

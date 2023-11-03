#include<stdio.h>
#include<stdlib.h>
#include<easyx.h>
#include<stdbool.h>
#include<conio.h>
#include<math.h>
#include<Windows.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")
#define ROW 15
#define COL 15
#define GRID_W 25            //格子宽度
#define INTERVAL (3*GRID_W)  //上边和左边的空隙大小

//存储数据的二维数组
int map[ROW][COL] = { 0 };

enum Chess
{
	None,
	White,
	Black
};

//胜利判定
bool judge(int r, int c);

//记录当前的数据结构
struct
{
	int x = 0;
	int y = 0;
	//鼠标当前所在的数组对应的下标
	int row = 0;
	int col = 0;
	bool is_show = false;  //是否显示框
	Chess chessPlayer = Black;
}op;


//绘制界面
void draw()
{
	setlinestyle(PS_SOLID, 1);
	//设置线条颜色
	setlinecolor(BLACK);
	//绘制棋盘
	for (int i = 0; i < 15; i++)
	{
		line(INTERVAL, INTERVAL + i * GRID_W, GRID_W * 14 + INTERVAL, INTERVAL + i * GRID_W);
		line(INTERVAL + i * GRID_W, INTERVAL, INTERVAL + i * GRID_W, GRID_W * 14 + INTERVAL);
	}
	setlinestyle(PS_SOLID, 2);
	rectangle(INTERVAL, INTERVAL, GRID_W * 14 + INTERVAL, GRID_W * 14 + INTERVAL);

	rectangle(460, 210, 570, 245);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(465, 215, _T("重新开始"));
	setbkmode(TRANSPARENT);//去掉文字背景

	//绘制五个点
	setfillcolor(BLACK);
	solidcircle(7 * GRID_W + INTERVAL, 7 * GRID_W + INTERVAL, 5);
	solidcircle(3 * GRID_W + INTERVAL, 3 * GRID_W + INTERVAL, 5);
	solidcircle(3 * GRID_W + INTERVAL, 11 * GRID_W + INTERVAL, 5);
	solidcircle(11 * GRID_W + INTERVAL, 11 * GRID_W + INTERVAL, 5);
	solidcircle(11 * GRID_W + INTERVAL, 3 * GRID_W + INTERVAL, 5);

	//绘制下棋选择框
	if (op.is_show)
	{
		setlinecolor(BLUE);

		rectangle(op.x - 12, op.y - 12, op.x + 12, op.y + 12);
	}

	//绘制棋子
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			switch (map[i][j])
			{
			case None:
				break;
			case White:
				setfillcolor(WHITE);
				solidcircle(j * GRID_W + INTERVAL, i * GRID_W + INTERVAL, 10);
				break;
			case Black:
				setfillcolor(BLACK);
				solidcircle(j * GRID_W + INTERVAL, i * GRID_W + INTERVAL, 10);
				break;
			default:
				break;
			}
		}
	}
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
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				//求每个格子左上角坐标
				int gridx = (j + 3) * GRID_W;
				int gridy = (i + 3) * GRID_W;
				if (abs(msg.x - gridx) < 12 && abs(msg.y - gridy) < 12)
				{
					op.x = gridx;
					op.y = gridy;
					op.row = i;
					op.col = j;
					op.is_show = true;
				}
				
			}
		}
		
		//左键点击下棋
		if (msg.message == WM_LBUTTONDOWN && map[op.row][op.col] == None)
		{
			/*mciSendString("open lz.wav alias music", 0, 0, 0);
			mciSendString("play music", 0, 0, 0);*/
			//PlaySound(_T("lz.mp3"), NULL, SND_FILENAME | SND_ASYNC);
			map[op.row][op.col] = op.chessPlayer;
			if (judge(op.row, op.col) == true)
			{
				draw();
				FlushBatchDraw();

				MessageBox(GetHWnd(), "你赢了", op.chessPlayer==White?"White":"Black", MB_OK);

			}
			op.chessPlayer = (op.chessPlayer == Black ? White : Black);
		}
		rectangle(460, 210, 570, 245);
		if (msg.x > 460 && msg.x < 570 && msg.y>210 && msg.y < 245)
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				for (int i = 0; i < ROW; i++)
				{
					for (int j = 0; j < COL; j++)
					{
						map[i][j] = None;
					}
				}
				cleardevice();
				draw();
			}
		}
	}
}

//判断输赢
bool judge(int r, int c)
{
	//判断横向
	for (int i = c - 4; i <= c + 4; i++)
	{
		if (i >= 0 && i <= COL - 4)
		{
			if (op.chessPlayer == map[r][i] 
				&& op.chessPlayer == map[r][i + 1] 
				&& op.chessPlayer == map[r][i + 2] 
				&& op.chessPlayer == map[r][i + 3] 
				&& op.chessPlayer == map[r][i + 4])
			{
				return true;
			}
		}
	}

	//判断纵向
	for (int i = r - 4; i <= r + 4; i++)
	{
		if (i >= 0 && i <= ROW - 4)
		{
			if (op.chessPlayer == map[i][c]
				&& op.chessPlayer == map[i + 1][c]
				&& op.chessPlayer == map[i + 2][c]
				&& op.chessPlayer == map[i + 3][c]
				&& op.chessPlayer == map[i + 4][c])
			{
				return true;
			}
		}
	}

	//判断斜向
	int i = r - 4;
	int j = c - 4;
	for (; i < r + 4 && j < c + 4; i++, j++)
	{
		if (i >= 0 && i <= ROW - 4 && j >= 0 && j <= COL - 4)
		{
			if (op.chessPlayer == map[i][j]
				&& op.chessPlayer == map[i + 1][j + 1]
				&& op.chessPlayer == map[i + 2][j + 2]
				&& op.chessPlayer == map[i + 3][j + 3]
				&& op.chessPlayer == map[i + 4][j + 4])
			{
				return true;
			}
		}
	}
	int a = r - 4;
	int b = c + 4;
	for (; a < r + 4 && b >= c - 4; a++, b--)
	{
		if (a >= 0 && a <= ROW - 4 && b >= 0 && b <= COL - 4)
		{
			if (op.chessPlayer == map[a][b]
				&& op.chessPlayer == map[a + 1][b - 1]
				&& op.chessPlayer == map[a + 2][b - 2]
				&& op.chessPlayer == map[a + 3][b - 3]
				&& op.chessPlayer == map[a + 4][b - 4])
			{
				return true;
			}
		}
	}
	return false;
}


int main()
{
	//创建窗口
	initgraph(620, 550);

	IMAGE background_img;
	loadimage(&background_img, "background_3.jpg",620,550);
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
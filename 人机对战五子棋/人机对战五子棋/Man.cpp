#include "Man.h"

void Man::Init(Chess* chess)
{
	this->chess = chess;
}

void Man::Go()
{
	MOUSEMSG msg;
	ChessPos pos;

	while (1)
	{
		//获取鼠标点击消息
		msg = GetMouseMsg();

		//通过chess对象，来调用 判断落子是否有效
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			bool flag = chess->ClickBoard(msg.x, msg.y, &pos);
			if (flag)
			{
				break;
			}
			else
			{
				mciSendString("play res/无效点击.mp3", 0, 0, 0);
			}
		}
	}

	//人落黑子
	chess->ChessDown(&pos, CHESS_BLACK);
	Sleep(500);
	
}

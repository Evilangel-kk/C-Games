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
		//��ȡ�������Ϣ
		msg = GetMouseMsg();

		//ͨ��chess���������� �ж������Ƿ���Ч
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			bool flag = chess->ClickBoard(msg.x, msg.y, &pos);
			if (flag)
			{
				break;
			}
			else
			{
				mciSendString("play res/��Ч���.mp3", 0, 0, 0);
			}
		}
	}

	//�������
	chess->ChessDown(&pos, CHESS_BLACK);
	Sleep(500);
	
}

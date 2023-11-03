#include "Chess.h"
#include<iostream>
#include<mmsyscom.h>
#include<Windows.h>
#include<vector>
#include<conio.h>
#pragma comment(lib,"winmm.lib")

void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

Chess::Chess(int gradeSize, int margin_x, int margin_y, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = margin_x;
	this->margin_y = margin_y;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;
	for (int i = 0; i < gradeSize; i++)
	{
		vector<int> row;
		for (int j = 0; j < gradeSize; j++)
		{
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::Init()
{
	//������Ϸ����
	initgraph(780, 778, EW_SHOWCONSOLE);

	//��ʾ����
	loadimage(0, "res/����2.jpg");

	//���ſ�ʼ��ʾ����
	mciSendString("play res/start.wav", 0, 0, 0);
	loadimage(&chessBlackImg, "res/black.png",chessSize,chessSize,true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);

	//������������
	for (int i = 0; i < gradeSize; i++)
	{
		for (int j = 0; j < gradeSize; j++)
		{
			chessMap[i][j] = 0;
		}
	}

	//��������
	playerFlag = true;
}

bool Chess::ClickBoard(int x, int y, ChessPos* pos)
{
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;
	int offset = chessSize * 0.4;

	bool ret = false;

	int len;
	do {
		//���Ͻ�
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset)
		{
			pos->col = col;
			pos->row = row;
			if (chessMap[pos->row][pos->col] == 0)
			{
				ret = true;
			}
			break;
		}
		//���Ͻ�
		len = sqrt((x - (leftTopPosX + chessSize)) * (x - (leftTopPosX + chessSize)) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset)
		{
			pos->col = col + 1;
			pos->row = row;
			if (chessMap[pos->row][pos->col] == 0)
			{
				ret = true;
			}
			break;
		}
		//���½�
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - (leftTopPosY + chessSize)) * (y - (leftTopPosY + chessSize)));
		if (len < offset)
		{
			pos->col = col;
			pos->row = row + 1;
			if (chessMap[pos->row][pos->col] == 0)
			{
				ret = true;
			}
			break;
		}
		//���½�
		len = sqrt((x - (leftTopPosX + chessSize)) * (x - (leftTopPosX + chessSize)) + (y - (leftTopPosY + chessSize)) * (y - (leftTopPosY + chessSize)));
		if (len < offset)
		{
			pos->col = col + 1;
			pos->row = row + 1;
			if (chessMap[pos->row][pos->col] == 0)
			{
				ret = true;
			}
			break;
		}
	} while (0);
	
	return ret;
}

void Chess::ChessDown(ChessPos* pos, chess_kind__t kind)
{
	int x = margin_x + pos->col * chessSize - 0.5 * chessSize;
	int y = margin_y + pos->row * chessSize - 0.5 * chessSize;

	if (kind == CHESS_WHITE)
	{
		putimagePNG(x, y, &chessWhiteImg);
	}
	else
	{
		putimagePNG(x, y, &chessBlackImg);
	}
	mciSendString("play res/down7.WAV", 0, 0, 0);
	UpdateGameMap(pos);
}

int Chess::GetGradeSize()
{
	return gradeSize;
}

int Chess::GetChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::GetChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::CheckOver()
{
	if (CheckWin())
	{
		if (!playerFlag)	//����ʤ��
		{
			Win();
		}
		else				//����ʤ��
		{
			Lose();
		}

		return true;
	}
	
	return false;
}

void Chess::UpdateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;//����

}

bool Chess::CheckWin()
{
	//������ӵ�λ��
	int row = lastPos.row;
	int col = lastPos.col;

	int size = GetGradeSize();
	int num = 0;
	int flag = chessMap[row][col];

	//ˮƽ����
	for (int i = -4; i <= 4; i++)
	{
		if (col + i >= 0 && col + i < size && chessMap[row][col + i] == flag)
		{
			num++;
		}
		else
		{
			num = 0;
		}
		if (num >= 5)
		{
			return true;
		}
	}


	//��ֱ����
	for (int i = -4; i <= 4; i++)
	{

		if (row + i >= 0 && row + i < size && chessMap[row + i][col] == flag)
		{
			num++;
		}
		else
		{
			num = 0;
		}
		if (num >= 5)
		{
			return true;
		}
	}


	//��������
	for (int i = -4; i <= 4; i++)
	{
		if (col + i >= 0 && col + i < size && row + i >= 0 && row + i < size && chessMap[row + i][col + i] == flag)
		{
			num++;
		}
		else
		{
			num = 0;
		}
		if (num >= 5)
		{
			return true;
		}
	}


	//��������
	for (int i = -4; i <= 4; i++)
	{
		if (col - i >= 0 && col - i < size && row + i >= 0 && row + i < size && chessMap[row + i][col - i] == flag)
		{
			num++;
		}
		else
		{
			num = 0;
		}
		if (num >= 5)
		{
			return true;
		}
	}

	return false;
}

void Chess::Win()
{
	Sleep(1500);
	mciSendString("play res/ʤ��.mp3", 0, 0, 0);
	IMAGE win;
	loadimage(&win, "res/win.png");
	putimagePNG(0, 0, &win);
	_getch();
}

void Chess::Lose()
{
	Sleep(1500);
	mciSendString("play res/ʧ��.mp3", 0, 0, 0);
	IMAGE lose;
	loadimage(&lose, "res/lose.png");
	putimagePNG(0, 0, &lose);
	_getch();
}

void Chess::Forbidden_Lose()
{
	Sleep(1500);
	mciSendString("play res/ʧ��.mp3", 0, 0, 0);
	IMAGE forbidden_lose;
	loadimage(&forbidden_lose, "res/forbidden_lose.png");
	putimagePNG(0, 0, &forbidden_lose);
	_getch();
}

bool Chess::ForbiddenHands()
{
	int row = lastPos.row;
	int col = lastPos.col;

	int size = GetGradeSize();
	int num = 0;

	int link = 0;

	for (int y = -1; y <= 0; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			if (y == 0 && x == 0)continue;
			if (y == 0 && x != -1)continue;

			int curRow = 0;
			int curCol = 0;
			int personNum = 0;
			int emptyNum = 0;

			for (int i = 1; i <= 4; i++)
			{
				curRow = row + i * y;
				curCol = col + i * x;
				if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
				{
					if (chessMap[curRow][curCol] == CHESS_BLACK)		//����
					{
						personNum++;
					}
					else if (chessMap[curRow][curCol] == 0)
					{
						emptyNum++;
						break;
					}
					else if (chessMap[curRow][curCol] == CHESS_WHITE)
					{
						personNum = 0;
						break;
					}
				}
			}
			//����
			for (int i = 1; i <= 4; i++)
			{
				curRow = row - i * y;
				curCol = col - i * x;
				if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
				{
					if (chessMap[curRow][curCol] == CHESS_BLACK)		//����
					{
						personNum++;
					}
					else if (chessMap[curRow][curCol] == 0)
					{
						emptyNum++;
						break;
					}
					else if(chessMap[curRow][curCol] == CHESS_WHITE)
					{
						personNum = 0;
						break;
					}
				}
			}

			if (personNum >= 2 && emptyNum == 2)
			{
				link++;
			}
		}
	}

	//�ж�Ƕ��
	if (link == 1)
	{
		for (int y = -1; y <= 0; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				int curRow = 0;
				int curCol = 0;
				int chessNum1[4] = { 0 };
				int chessNum2[4] = { 0 };

				if (y == 0 && x == 0)continue;
				if (y == 0 && x != -1)continue;

				//����
				for(int i = 1; i <= 4; i++)
				{
					curRow = row + i * y;
					curCol = col + i * x;
					if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
					{
						if (chessMap[curRow][curCol] == CHESS_BLACK)
						{
							chessNum1[i - 1] = 1;
						}
						else if (chessMap[curRow][curCol] == 0)
						{
							chessNum1[i - 1] = 0;
						}
						else
						{
							chessNum1[i - 1] = -1;
						}
					}
				}

				//����
				for (int i = 1; i <= 4; i++)
				{
					curRow = row - i * y;
					curCol = col - i * x;
					if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
					{
						if (chessMap[curRow][curCol] == CHESS_BLACK)
						{
							chessNum2[i - 1] = 1;
						}
						else if (chessMap[curRow][curCol] == 0)
						{
							chessNum2[i - 1] = 0;
						}
						else
						{
							chessNum2[i - 1] = -1;
						}
					}
				}
				if (chessNum2[0] == 0 && chessNum2[1] == 1 && chessNum2[2] == 0)
				{
					if (chessNum1[0] == 1 && chessNum1[1] == 0)
					{
						link++;
					}
				}
				else if (chessNum1[0] == 0 && chessNum1[1] == 1 && chessNum1[2] == 0)
				{
					if (chessNum2[0] == 1 && chessNum2[1] == 0)
					{
						link++;
					}
				}
				else if (chessNum1[0] == 0 && chessNum1[1] == 1 && chessNum1[2] == 1 && chessNum1[3] == 0)
				{
					if (chessNum2[0] == 0)
					{
						link++;
					}
				}
				else if (chessNum2[0] == 0 && chessNum2[1] == 1 && chessNum2[2] == 1 && chessNum2[3] == 0)
				{
					if (chessNum1[0] == 0)
					{
						link++;
					}
				}
			}
		}
	}
	


	if (link >= 2)
	{
		Forbidden_Lose();
		return true;
	}

	return false;
}

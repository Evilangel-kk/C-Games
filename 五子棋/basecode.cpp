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
#define GRID_W 25            //���ӿ��
#define INTERVAL (3*GRID_W)  //�ϱߺ���ߵĿ�϶��С

//�洢���ݵĶ�ά����
int map[ROW][COL] = { 0 };

enum Chess
{
	None,
	White,
	Black
};

//ʤ���ж�
bool judge(int r, int c);

//��¼��ǰ�����ݽṹ
struct
{
	int x = 0;
	int y = 0;
	//��굱ǰ���ڵ������Ӧ���±�
	int row = 0;
	int col = 0;
	bool is_show = false;  //�Ƿ���ʾ��
	Chess chessPlayer = Black;
}op;


//���ƽ���
void draw()
{
	setlinestyle(PS_SOLID, 1);
	//����������ɫ
	setlinecolor(BLACK);
	//��������
	for (int i = 0; i < 15; i++)
	{
		line(INTERVAL, INTERVAL + i * GRID_W, GRID_W * 14 + INTERVAL, INTERVAL + i * GRID_W);
		line(INTERVAL + i * GRID_W, INTERVAL, INTERVAL + i * GRID_W, GRID_W * 14 + INTERVAL);
	}
	setlinestyle(PS_SOLID, 2);
	rectangle(INTERVAL, INTERVAL, GRID_W * 14 + INTERVAL, GRID_W * 14 + INTERVAL);

	rectangle(460, 210, 570, 245);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("����"));
	outtextxy(465, 215, _T("���¿�ʼ"));
	setbkmode(TRANSPARENT);//ȥ�����ֱ���

	//���������
	setfillcolor(BLACK);
	solidcircle(7 * GRID_W + INTERVAL, 7 * GRID_W + INTERVAL, 5);
	solidcircle(3 * GRID_W + INTERVAL, 3 * GRID_W + INTERVAL, 5);
	solidcircle(3 * GRID_W + INTERVAL, 11 * GRID_W + INTERVAL, 5);
	solidcircle(11 * GRID_W + INTERVAL, 11 * GRID_W + INTERVAL, 5);
	solidcircle(11 * GRID_W + INTERVAL, 3 * GRID_W + INTERVAL, 5);

	//��������ѡ���
	if (op.is_show)
	{
		setlinecolor(BLUE);

		rectangle(op.x - 12, op.y - 12, op.x + 12, op.y + 12);
	}

	//��������
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


//���
void mouseEvent()
{
	//������Ϣ�ṹ�����
	ExMessage msg;
	//��ȡ�����Ϣ
	if (peekmessage(&msg, EM_MOUSE))
	{
		op.is_show = false;
		//����У׼
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				//��ÿ���������Ͻ�����
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
		
		//����������
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

				MessageBox(GetHWnd(), "��Ӯ��", op.chessPlayer==White?"White":"Black", MB_OK);

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

//�ж���Ӯ
bool judge(int r, int c)
{
	//�жϺ���
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

	//�ж�����
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

	//�ж�б��
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
	//��������
	initgraph(620, 550);

	IMAGE background_img;
	loadimage(&background_img, "background_3.jpg",620,550);
	putimage(0, 0, &background_img);
	//˫�����ͼ
	BeginBatchDraw();
	while (1)
	{
		//����
		cleardevice();

		putimage(0, 0, &background_img);
		draw();
		mouseEvent();
		FlushBatchDraw();   //ˢ��
	}
	EndBatchDraw();         //������ͼ
	system("pause");
	return 0;
}
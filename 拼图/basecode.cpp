#include<stdio.h>
#include<easyx.h>
#include<time.h>
#include<graphics.h>
#define GRIND_W 150
#define ROW 4
#define COL 4

int map[ROW][COL] = { 0 };   //�洢���
IMAGE img[ROW * COL];        //�洢��Ŷ�Ӧ��ͼƬ
IMAGE img_total;

//��ʼ������
void gameInit()
{
	//��map��������ݴ�С������и�ֵ 4*4
	int cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] = cnt++;
		}
	}
	//��������
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 64; i++)
	{
		int r1, c1, r2, c2;
		r1 = rand() % ROW;
		c1 = rand() % COL;
		r2 = rand() % ROW;
		c2 = rand() % COL;

		int t = map[r1][c1];
		map[r1][c1] = map[r2][c2];
		map[r2][c2] = t;
	}
	loadimage(&img_total, "./ziyuan/mm_1.jpg");
	//�и�ͼƬ
	SetWorkingImage(&img_total);
	int num = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			getimage(&img[num++], j * GRIND_W, i * GRIND_W, GRIND_W, GRIND_W);
		}
	}

	SetWorkingImage();

	loadimage(&img[ROW * COL - 1], "./ziyuan/white.jpg", GRIND_W, GRIND_W);
}

void gameDraw()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			putimage(j * GRIND_W + j + 1, i * GRIND_W + i + 1, img+map[i][j]);
			//��֪����ʲô���⣿��������
		}
	}
}

//�жϰ׿鸽���Ŀ�
int judge_white(int r,int c,int wr,int wc)
{
	if (r == wr - 1 && c == wc)
	{
		return 1;
	}
	else if (r == wr + 1 && c == wc)
	{
		return 1;
	}
	else if (r == wr && c == wc - 1)
	{
		return 1;
	}
	else if (r == wr && c == wc + 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void MouseEvent()
{
	MOUSEMSG msg = GetMouseMsg();
	//��Բ�ͬ�������Ϣ���д���
	if (msg.uMsg == WM_LBUTTONDOWN)
	{
		int c = msg.x / GRIND_W;
		int r = msg.y / GRIND_W;

		//��ð׿��±�
		int wr = -1;
		int wc = -1;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (map[i][j] == 15)
				{
					wr = i;
					wc = j;
					break;
				}
			}
		}

		//�Ѱ׿��뵱ǰ����н���
		if (judge_white(r, c, wr, wc) == 1)
		{
			int t = map[r][c];
			map[r][c] = map[wr][wc];
			map[wr][wc] = t;
		}
	}
	else if (msg.uMsg == WM_RBUTTONDOWN)
	{
		int* p = (int*)map;
		for (int i = 0; i < ROW * COL - 1; i++)
		{
			for (int j = 0; j < ROW * COL - 1 - i; j++)
			{
				if (p[j] > p[j + 1])
				{
					int t = p[j];
					p[j] = p[j + 1];
					p[j + 1] = t;
				}
			}
		}
	}
}

//�жϹ���
int judge()
{
	int cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] != cnt++)
			{
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	initgraph(4 * GRIND_W + ROW + 1, 4 * GRIND_W + COL + 1);

	gameInit();

	BeginBatchDraw();
	while (1)
	{
		gameDraw();
		FlushBatchDraw();
		if (judge())
		{
			MessageBox(GetHWnd(), _T("��ϲ�㣬�����ˣ�"), _T("boom"), MB_OK);
			exit(0);
		}
		MouseEvent();
	}
	EndBatchDraw();

	getchar();
	system("pause");
	return 0;
}
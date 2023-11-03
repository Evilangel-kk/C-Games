//������ by �ܳ��� 2021 12 04
# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<graphics.h>
# include<mmsystem.h>
# include<Windows.h>
#pragma comment(lib,"winmm.lib")
//��֪1900��1��1��������һ


//�������������
int month_calcu(int year, int month)
{
	int num;
	if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			num = 29;
		else
			num = 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		num = 30;
	else
		num = 31;
	return num;
}

//���㱾��1�����ڼ�����Zeller��ʽ
int date_calcu(int year, int month)
{
	if (month < 3)
	{
		month += 12;
		year--;
	}
	int a = year / 100;
	int b = year % 100;
	int c = month;
	int start = b + (b / 4) + (a / 4) - 2 * a + (26 * (c + 1) / 10) / 1;
	start %= 7;
	return start;
}
int map[10][9] = { 0 };

//1.�����洢ͼƬ�ı���
IMAGE dateImg[32];
IMAGE weekdayImg[7];
IMAGE massage[8];
IMAGE back;
IMAGE bk;
IMAGE Year;
IMAGE Month;
IMAGE Kong;
IMAGE Start;
IMAGE Bai;

//2.����ͼƬ������
void make()
{
	loadimage(&back, "back.jpg");
	loadimage(&Year, "��.jpg");
	loadimage(&Month, "��.jpg");
	loadimage(&Kong, "0.jpg");
	loadimage(&Bai, "0.jpg");
	loadimage(&Start, "1.jpg");
	loadimage(&bk, "123.jpg");
}

//��������
void loadResource()
{
	for (int i = 0; i < 32; i++)
	{
		char fileName[20] = "";
		sprintf_s(fileName, "%d.jpg", i);
		loadimage(dateImg + i, fileName);
	}
	for (int i = 61; i < 68; i++)
	{
		char fileName[20] = "";
		sprintf_s(fileName, "%d.jpg", i);
		loadimage(weekdayImg + i - 61, fileName);
	}
	for (int i = 70; i < 80; i++)
	{
		char fileName[20] = "";
		sprintf_s(fileName, "%d.jpg", i);
		loadimage(massage + i - 70, fileName);
	}
}

//��ӡ����
void dateLayout()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int x = 50 * j + 10;
			int y = 50 * i + 10;
			if (i == 0 && j < 8)
			{
				putimage(x + 20, y, massage + map[i][j]);
			}

			else if (i == 1 || i == 9 || j == 0 || j == 8)
			{
				putimage(x, y, &bk);
			}
			else if (i == 2)
			{
				putimage(x, y, weekdayImg + map[i][j] - 61);
			}
			else if (i >= 3 && i <= 9)
			{
				if (map[i][j] == 0)
				{
					putimage(x, y, &Bai);
				}
				else if (map[i][j] == 1)
				{
					putimage(x, y, &Start);
				}
				else
				{
					putimage(x, y, dateImg + map[i][j]);
				}
			}
		}
	}
}

//���ֲ���д������
void textLayout()
{
	int x = 480;
	int y = 500;
	settextstyle(35, 0, "STXINWEI");
	settextcolor(BLACK);
	const char* name[3] = { "��", "��", "��" };
	for (int i = 0; i < 3; i++)
	{
		outtextxy(x + 50 * i, y - 50, name[i]);
		Sleep(800);
	}
}

//��ֱ��ӡ��̬Ч��
void textAction()
{
	int x = 550;
	int y = 30;
	settextstyle(35, 0, "FZSTK");
	settextcolor(RGB(227, 222, 2));
	const char* text[20] = { "��", "ϧ", "ʱ", "��", "��", "��", "ѧ", "ϰ", "��", "��", "��", "��", };

	for (int i = 0; i < 12; i++)
	{
		if (i < 4)
		{
			outtextxy(x, y + 50 * i + 80, text[i]);
		}
		else
		{
			outtextxy(x - 50, y + 50 * (i - 4) + 10, text[i]);
		}
		Sleep(1000);
	}
}


int main()
{
	int year, month;
	printf("Please enter the year and the month.\nThe year should be later than 1900.\n");
	scanf_s("%d%d", &year, &month);
	int y = year;
	int m = month;
	//The year shouble be earlier than 1900.			
	int day = month_calcu(year, month);

	//��һ�д�ӡ" xxxx��xx�� "
	for (int i = 3; i >= 0; i--)
	{
		map[0][i] = y % 10;
		y /= 10;
	}
	for (int i = 6; i >= 5; i--)
	{
		map[0][i] = m % 10;
		m /= 10;
	}

	//��ӡ�߿�
	for (int i = 0; i < 9; i++)
	{
		map[1][i] = 123;
	}
	for (int i = 2; i < 10; i++)
	{
		map[i][0] = 123;
		map[i][8] = 123;
	}
	for (int i = 0; i < 9; i++)
	{
		map[9][i] = 123;
	}

	//�����д�ӡ����
	int cnt = 61;
	for (int i = 1; i < 8; i++)
	{
		map[2][i] = cnt++;//����Ϊ61����һΪ62
	}

	//������
	int k = date_calcu(year, month);
	int w = k + 1;
	int i = 3;
	for (int j = 1; j <= day; j++, w++)
	{
		if ((j == 1 + (7 - k)) || (j == 8 + (7 - k)) || (j == 15 + (7 - k)) || (j == 22 + (7 - k)) || (j == 29 + (7 - k)))
		{
			i++;
			w = 1;
		}
		map[i][w] = j;
	}
	fflush(stdin);


	//�������ӻ�����
	initgraph(630, 517);

	//��������
	mciSendString("open music.mp3 alias music", 0, 0, 0);
	mciSendString("play music", 0, 0, 0);

	//��ͼ����
	setbkmode(TRANSPARENT);//ȥ�����ֱ���

	//2.����ͼƬ������

	//3.��ʾͼƬ
	make();
	putimage(0, 0, &back);
	putimage(10, 10, &Kong);


	loadResource();

	dateLayout();
	putimage(410, 10, &Kong);
	putimage(240, 10, &Year);
	putimage(390, 10, &Month);
	textAction();
	textLayout();

	getchar();
	getchar();
	getchar();
	getchar();
	getchar();
	getchar();
	getchar();
	Sleep(30000);
	closegraph();
	system("pause");//��ֹ����
	return 0;
}
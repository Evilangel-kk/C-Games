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

//��ҵ��ж�״̬
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
	IMAGE* curImg;          //��ǰ���Ƶ�����ͼƬ
	int img_i;             
	int inity;             //ʼ�ձ��ֳ�ʼy����
	State state;            //��ҵ�ǰ״̬
}gamer;

//��ʱ��
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

//�ϰ���
struct Bricks
{
	int x;
	int y;
	int w;
	int h;
	char color;
}brick;

//����ש�����
void initBricks()
{
	brick.w = 50;
	brick.h = 50;
	brick.x = 550;
	brick.y = 360 - brick.h;
}

//��ש��
void drawBricks()
{
	setfillcolor(GREEN);
	solidrectangle(brick.x, brick.y, brick.x + brick.w, brick.y + brick.h);
}

//�ƶ�ש��
void moveBricks()
{
	brick.x--;
	if (brick.x + brick.w <= 0)
	{
		brick.x = getwidth();
	}

}

//�������Ƿ���ש�鷢������ײ
void collision()
{
	//1.�����ж�

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
	//���Ƶذ� �߶�40
	setfillcolor(RGB(200,191,231));
	solidrectangle(0,getheight()-40, getwidth(), getheight());
	//�������ͼƬ
	putimage(gamer.x, gamer.y, gamer.curImg + gamer.img_i);
}

//����ܶ�����
void moveGamer()
{
	//i++;
	//if (i > 7)
	//{
	//	i = 0;
	//}
	gamer.curImg = img_move;
	gamer.img_i = (gamer.img_i + 1) % 8;//0-7ѭ��
	//Sleep(60);�����ã�Ⱥ��˯��
}

//�����Ծ����
void jumpGamer()
{
	static bool isJump = true;   //true ���� false �½�
	gamer.curImg = &img_jump;
	
	//���µ�������
	if (gamer.y <= gamer.inity - 150)
	{
		isJump = false;
	}

	if (isJump)              //����
	{
		gamer.y -= 30;
	}
	else                     //�½�
	{
		gamer.y += 30;
		//�½���ԭ����λ�þ�ֹͣ�½����ظ�����״̬
		if (gamer.y >= gamer.inity)
		{
			gamer.state = Move;
			gamer.y = gamer.inity;
			isJump = true;
		}
	}
}

//��ҹ�������
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

//���״̬�л�����
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

//������Ϣ����
void keyContorl()
{
	//��ȡ�첽����״̬������������vk virtual key �����ֵ
	if (GetAsyncKeyState(VK_SPACE) && gamer.state==Move)      //�ո����
	{
		gamer.y = 310;
		gamer.state = Roll;
		gamer.img_i = 0;
	}
	if (GetAsyncKeyState(VK_UP))         //�ϼ���Ծ
	{
		gamer.y = 260;
		gamer.state = Jump;
		gamer.img_i = 0;
	}
}

int main()
{
	//1.��������
	initgraph(640,400/*,EW_SHOWCONSOLE*/);
	//2.���ô��ڱ�����ɫ
	setbkcolor(RGB(252,253,255));
	//������ͼ�δ��ڣ�system("cls")�������̨
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
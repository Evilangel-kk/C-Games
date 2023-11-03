#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<stdbool.h>
#include<graphics.h>
#include<Windows.h>
//using namespace std;
#pragma comment(lib,"Winmm.lib")
#define R 26
#define L 26
#define ENEMY_NUM 10
#define DRIECT 4

IMAGE logo_img;
IMAGE begin_img;
IMAGE victory_img;
IMAGE failure_img;
IMAGE my_tank_img[4];
IMAGE enemy_tank_img[4];
IMAGE home_img;
IMAGE home_fail_img;
IMAGE wall1_img;
IMAGE wall2_img;
IMAGE stop_img;
IMAGE hit_img;
IMAGE movekey_img;
IMAGE pause_img;

MOUSEMSG mouse;
enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//̹�˽ṹ��
struct tank_s
{
	int x;
	int y;
	int direction;   //̹�˷���
	int live;        //���״̬ 1-��� 0-����
	int aka;
};

//�ӵ��ṹ��
struct bullet_s 
{
	int pox_x;             //�ӵ�����Ļ�ϵ�x����
	int pox_y;             //�ӵ�����Ļ�ϵ�y����
	int status;            //�ӵ��Ƿ����
	int direction;         //�ӵ�����
	int aka;               //�ӵ�����
};

//��Ƶ�ͼ
int map[L][R] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,1,1,1,0,0,0,0,2,2,0,0,0,0,1,1,1,1,0,0,0,0},
	{0,0,1,1,0,0,2,2,0,0,1,1,0,0,1,1,0,0,2,2,0,0,1,1,0,0},
	{0,0,1,1,0,0,2,2,0,0,1,1,0,0,1,1,0,0,2,2,0,0,1,1,0,0},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1},
	{0,0,1,1,0,0,2,2,0,0,1,1,0,0,1,1,0,0,2,2,0,0,1,1,0,0},
	{0,0,1,1,0,0,2,2,0,0,1,1,0,0,1,1,0,0,2,2,0,0,1,1,0,0},
	{2,2,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,2,2},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,2,2,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,2,2,1,1,0,0,1,1,0,0,1,1,0,0},
	{2,2,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,2,2},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0},
	{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
	{2,2,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,2,2},
	{0,0,1,1,0,0,0,0,0,0,0,1,3,3,1,0,0,0,0,0,0,0,1,1,0,0},
	{0,0,1,1,0,0,0,0,0,0,0,1,3,3,1,0,0,0,0,0,0,0,1,1,0,0},
};

//����ͼƬ������
void loadimg()
{
	loadimage(&logo_img, "logo.jpg",433,147);
	loadimage(&begin_img, "begin.jpg");
	loadimage(&victory_img, "victory.jpg");
	loadimage(&failure_img, "failure.jpg");
	loadimage(&my_tank_img[UP], "tank_up.jpg",50,50);
	loadimage(&my_tank_img[DOWN], "tank_down.jpg",50, 50);
	loadimage(&my_tank_img[LEFT], "tank_left.jpg",50, 50);
	loadimage(&my_tank_img[RIGHT], "tank_right.jpg", 50, 50);
	loadimage(&enemy_tank_img[UP], "enemy_tank_up.jpg", 50, 50);
	loadimage(&enemy_tank_img[DOWN], "enemy_tank_down.jpg", 50, 50);
	loadimage(&enemy_tank_img[LEFT], "enemy_tank_left.jpg", 50, 50);
	loadimage(&enemy_tank_img[RIGHT], "enemy_tank_right.jpg", 50, 50);
	loadimage(&home_img, "home.jpg");
	loadimage(&home_fail_img, "home_fail.jpg");
	loadimage(&wall1_img, "wall1.jpg");
	loadimage(&wall2_img, "wall2.jpg");
	loadimage(&stop_img, "stop.jpg");
	loadimage(&hit_img, "hit.jpg");
	loadimage(&movekey_img, "movekey.jpg");
	loadimage(&pause_img, "pause.jpg");
}

//ʵ�ֵ�����ť
void drawBegin()
{
	//setlinecolor(WHITE);
	setfillcolor(BLACK);

	fillrectangle(210, 200, 290, 240);
	settextstyle(25, 0, _T("����"));
	outtextxy(220, 210, _T("˵ ��"));


	fillrectangle(350, 200, 430, 240);
	settextstyle(25, 0, _T("����"));
	outtextxy(360, 210, _T("�� ʼ"));

}

//��˵��ָ��
void drawInstruction()
{
	putimage(100, 290, &movekey_img);
	putimage(400, 310, &stop_img);
	putimage(400, 390, &hit_img);
	settextstyle(25, 0, _T("����"));
	settextcolor(GREEN);
	outtextxy(200, 280, _T("����"));
	settextstyle(25, 0, _T("����"));
	outtextxy(200, 460, _T("����"));
	settextstyle(25, 0, _T("����"));
	outtextxy(125, 355, _T("����"));
	settextstyle(25, 0, _T("����"));
	outtextxy(275, 355, _T("����"));
	settextstyle(25, 0, _T("����"));
	outtextxy(478, 415, _T("����"));
	settextcolor(RED);
	settextstyle(25, 0, _T("����"));
	outtextxy(478, 330, _T("ֹͣ"));
}

//��ʼ����
void drawStart()
{
	drawBegin();

	while (true)
	{
		mouse = GetMouseMsg();

		switch (mouse.uMsg)
		{
		case WM_MOUSEMOVE:
			if ((mouse.x > 210 && mouse.x < 290) && (mouse.y > 200 && mouse.y < 240))
			{
				drawInstruction();
			}
			else
			{
				//���ƺ�ɫ���θ���˵��ͼƬ
				solidrectangle(100, 270, 600, 500);
			}
			break;
		case WM_LBUTTONDOWN:
			if ((mouse.x > 350 && mouse.x < 430) && (mouse.y > 200 && mouse.y < 240))
			{
				cleardevice();
				return;
			}
			break;
		default:
			break;
		}
	}
}

//������Ϸ��ͼ
void drawMap()
{
	//PlaySound(_T("background.wav"), NULL, SND_FILENAME | SND_ASYNC);
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < R; j++)
		{
			switch (map[i][j])
			{
			case 1:
				putimage(j * 25, i * 25, &wall1_img);
				break;
			case 2:
				putimage(j * 25, i * 25, &wall2_img);
				break;
			case 3:
				if (map[i + 1][j] == 3 && map[i][j + 1] == 3 && map[i + 1][j + 1] == 3)
				{
					putimage(j * 25, i * 25, &home_img);
				}
				break;
			default:
				break;
			}
		}
	}
}

//���ӵ���
//���أ�0 ��Ϸ������1 ��Ӫ�����ˣ�2 ������� 
int bullet_fly(int* enemy_alive,tank_s* enemy_tank, bullet_s* bullet, int type)
{
	int x = bullet->pox_x / 25;
	int y = bullet->pox_y / 25;
	int x1 = x;
	int y1 = y;

	//������һ�λ��Ƶ��ӵ�
	if (bullet->status)
	{
		setfillcolor(BLACK);
		solidrectangle(bullet->pox_x, bullet->pox_y, bullet->pox_x + 3, bullet->pox_y + 3);
	}
	//���ݷ�������ӵ�����
	if (bullet->direction == UP)
	{
		bullet->pox_y -= 2;
		x1 += 1;
	}
	else if (bullet->direction == DOWN)
	{
		bullet->pox_y += 2;
		x1 += 1;
	}
	else if (bullet->direction == LEFT)
	{
		bullet->pox_x -= 2;
		y1 += 1;
	}
	else if (bullet->direction == RIGHT)
	{
		bullet->pox_x += 2;
		y1 += 1;
	}

	if (bullet->pox_x > 650 || bullet->pox_x < 0 || bullet->pox_y>650 || bullet->pox_y < 0)
	{
		bullet->status = 0;
		return 0;
	}

	//��ײ���
	//�һ�
	if (map[y][x] == 3 || map[y1][x1] == 3)
	{
		PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		bullet->status = 0;
		return 2;
	}
	//�ҷ�̹�˱�����
	if (map[y][x] == 200 && type == 0)
	{
		PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		bullet->status = 0;
		return 1;
	}
	if (map[y1][x1] == 200 && type == 0)
	{
		PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		bullet->status = 0;
		return 1;
	}
	//�з�̹�˱�����
	if ((map[y][x] >= 100 && map[y][x] < 200) || map[y1][x1] >= 100 && map[y1][x1] < 200)
	{
		tank_s* tank = NULL;
		if (map[y][x] >= 100 && map[y][x] < 200)
		{
			tank = enemy_tank + (map[y][x] - 100);
		}
		else
		{
			tank = enemy_tank + (map[y1][x1] - 100);
		}
		if (tank->aka != bullet->aka)
		{
			PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
			bullet->status = 0;
			enemy_alive--;
			setfillcolor(BLACK);
			solidrectangle(tank->x * 25, tank->y * 25, tank->x * 25 + 50, tank->y * 25 + 50);

			tank->live = 0;
			map[tank->y][tank->x] = 0;
			map[tank->y + 1][tank->x] = 0;
			map[tank->y][tank->x + 1] = 0;
			map[tank->y + 1][tank->x + 1] = 0;
		}
	}
	//ǽ��
	if (map[y][x] == 1)
	{
		/*if (type)
		{
			PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}*/
		map[y][x] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x * 25, y * 25, x * 25 + 25 - 1, y * 25 + 25 - 1);
	}
	else if (map[y][x] == 2)
	{
		bullet->status = 0;
	}
	
	if (map[y1][x1] == 1)
	{
		/*if (type)
		{
			PlaySound(_T("paoji.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}*/
		map[y1][x1] = 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25, x1 * 25 + 25 - 1, y1 * 25 + 25 - 1);

	}
	else if (map[y1][x1] == 2)
	{
		bullet->status = 0;
	}

	//���»����ӵ�
	if (bullet->status == 1)
	{
		setfillcolor(WHITE);
		solidrectangle(bullet->pox_x, bullet->pox_y, bullet->pox_x + 3, bullet->pox_y + 3);
	}
	return 0;
}

//����
void tank_fire(tank_s* tank, bullet_s* bullet,int type)
{
	if (bullet->status == 0)
	{
		if (type)
		{
			PlaySound(_T("shoot_2.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		if (tank->direction == UP)
		{
			bullet->pox_x = tank->x * 25 + 23;
			bullet->pox_y = tank->y * 25 - 3;
		}
		else if (tank->direction == DOWN)
		{
			bullet->pox_x = tank->x * 25 + 23;
			bullet->pox_y = tank->y * 25 + 50;
		}
		else if (tank->direction == LEFT)
		{
			bullet->pox_x = tank->x * 25 - 3;
			bullet->pox_y = tank->y * 25 + 23;
		}
		else if (tank->direction == RIGHT)
		{
			bullet->pox_x = tank->x * 25 + 50;
			bullet->pox_y = tank->y * 25 + 23;
		}
		bullet->direction = tank->direction;
		bullet->status = 1;
	}
}

/*******************************
 * ̹������
 * ����ֵ��ʧ�� - 0 �ɹ� - 1
 *******************************/
int walk_Tank(tank_s* tank, int direction, IMAGE* img)
{
	int new_x = tank->x;
	int new_y = tank->y;

	setfillcolor(BLACK);
	solidrectangle(tank->x * 25, tank->y * 25, 25 * tank->x + 49, 25 * tank->y + 49);

	if (direction == UP)
	{
		new_y -= 1;
	}
	else if (direction == DOWN)
	{
		new_y += 1;
	}
	else if (direction == LEFT)
	{
		new_x -= 1;
	}
	else if (direction == RIGHT)
	{
		new_x += 1;
	}
	else
	{
		return 0;
	}

	map[tank->y][tank->x] = 0;
	map[tank->y+1][tank->x] = 0;
	map[tank->y][tank->x+1] = 0;
	map[tank->y+1][tank->x+1] = 0;

	map[new_y][new_x] = tank->aka;
	map[new_y+1][new_x] = tank->aka;
	map[new_y][new_x+1] = tank->aka;
	map[new_y+1][new_x+1] = tank->aka;

	tank->x = new_x;
	tank->y = new_y;

	putimage(tank->x * 25, tank->y * 25, img);
	return 1;
}

/*******************************
 * �ƶ��ҷ�̹��
 * ����ֵ��ʧ�� - 0 �ɹ� - 1
 *******************************/
void move_my_tank(tank_s* tank, int direction,bullet_s* bullet)
{
	if (_kbhit())    //�������û�
	{
		int key = _getch();
		switch (key)
		{
			//Left
		case 'a':
			tank->direction = LEFT;
			if (tank->x - 1 >= 0 && map[tank->y][tank->x - 1] == 0 && map[tank->y + 1][tank->x - 1] == 0)
			{
				walk_Tank(tank, LEFT, &my_tank_img[tank->direction]);
			}
			else
			{
				putimage(tank->x * 25, tank->y * 25, &my_tank_img[tank->direction]);
			}
			break;
			//Up
		case 'w':
			tank->direction = UP;
			if (tank->y - 1 >= 0 && map[tank->y - 1][tank->x] == 0 && map[tank->y - 1][tank->x + 1] == 0)
			{
				walk_Tank(tank, UP, &my_tank_img[tank->direction]);
			}
			else
			{
				putimage(tank->x * 25, tank->y * 25, &my_tank_img[tank->direction]);
			}
			break;
			//Down
		case 's':
			tank->direction = DOWN;
			if (tank->y + 2 < L && map[tank->y + 2][tank->x] == 0 && map[tank->y + 2][tank->x + 1] == 0)
			{
				walk_Tank(tank, DOWN, &my_tank_img[tank->direction]);
			}
			else
			{
				putimage(tank->x * 25, tank->y * 25, &my_tank_img[tank->direction]);
			}
			break;
			//Right
		case 'd':
			tank->direction = RIGHT;
			if (tank->x + 2 < R && map[tank->y][tank->x + 2] == 0 && map[tank->y + 1][tank->x + 2] == 0)
			{
				walk_Tank(tank, RIGHT, &my_tank_img[tank->direction]);
			}
			else
			{
				putimage(tank->x * 25, tank->y * 25, &my_tank_img[tank->direction]);
			}
			break;
			//����
		case 'j':
			tank_fire(tank, bullet,200);
			break;
			//��ͣ
		case 'p':
			system("pause");
			break;
		default:
			break;
		}
	}
}

/*******************************
 * �ƶ��з�̹��
 * ����ֵ��ʧ�� - 0 �ɹ� - 1
 *******************************/
int move_enemy_Tank(tank_s* tank, int direction, IMAGE* img)
{
	switch (direction)
	{
		//Left
	case LEFT:
		tank->direction = LEFT;
		if (tank->x - 1 >= 0 && map[tank->y][tank->x - 1] == 0 && map[tank->y + 1][tank->x - 1] == 0)
		{
			walk_Tank(tank, LEFT, img);
		}
		else
		{
			putimage(tank->x * 25, tank->y * 25, img);
		}
		break;
		//Up
	case UP:
		tank->direction = UP;
		if (tank->y - 1 >= 0 && map[tank->y - 1][tank->x] == 0 && map[tank->y - 1][tank->x + 1] == 0)
		{
			walk_Tank(tank, UP, img);
		}
		else
		{
			putimage(tank->x * 25, tank->y * 25, img);
		}
		break;
		//Down
	case DOWN:
		tank->direction = DOWN;
		if (tank->y + 2 < L && map[tank->y + 2][tank->x] == 0 && map[tank->y + 2][tank->x + 1] == 0)
		{
			walk_Tank(tank, DOWN, img);
		}
		else
		{
			putimage(tank->x * 25, tank->y * 25, img);
		}
		break;
		//Right
	case RIGHT:
		tank->direction = RIGHT;
		if (tank->x + 2 < R && map[tank->y][tank->x + 2] == 0 && map[tank->y + 1][tank->x + 2] == 0)
		{
			walk_Tank(tank, RIGHT, img);
		}
		else
		{
			putimage(tank->x * 25, tank->y * 25, img);
		}
		break;
	default:
		return 0;
		break;
	}
	return 1;
}

/********************************
 *����Ŀ��λ�ã������з�̹�˷��� 
 * �����н�����
 ********************************/
DIRECTION enemy_direction(tank_s* tank, int x, int y)
{
	int r = rand() % 100;
	
	if (tank->x > x)
	{
		if (tank->y > y)
		{
			//Ŀ�������Ϸ�
			if (r <= 40)
			{
				return UP;
			}
			else if(r <= 80)
			{
				return LEFT;
			}
			else if (r <= 90)
			{
				return DOWN;
			}
			else
			{
				return RIGHT;
			}
		}
		//Ŀ�������·�
		else if(tank->y < y)
		{
			if (r <= 40)
			{
				return DOWN;
			}
			else if(r <= 80)
			{
				return LEFT;
			}
			else if (r <= 90)
			{
				return UP;
			}
			else
			{
				return RIGHT;
			}
		}
		//Ŀ������
		else
		{
			return LEFT;
		}
	}
	else if(tank->x < x)
	{
		if (tank->y > y)
		{
			//Ŀ�������Ϸ�
			if (r <= 40)
			{
				return UP;
			}
			else if(r <= 80)
			{
				return RIGHT;
			}
			else if (r <= 90)
			{
				return DOWN;
			}
			else
			{
				return RIGHT;
			}
		}
		//Ŀ�������·�
		else if (tank->y < y)
		{
			if (r <= 40)
			{
				return DOWN;
			}
			else if(r <= 80)
			{
				return RIGHT;
			}
			else if(r <= 90)
			{
				return LEFT;
			}
			else
			{
				return UP;
			}
		}
		//Ŀ�����ҷ�
		else
		{
			return RIGHT;
		}
	}
	else
	{
		//Ŀ�������·�
		if (tank->y < y)
		{
			if (map[tank->y + 2][tank->x] == 2 || map[tank->y + 2][tank->x + 1] == 2)
			{
				return RIGHT;
			}
			else
			{
				return DOWN;
			}
		}
		//Ŀ�������Ϸ�
		else
		{
			return UP;
		}
	}
}

//�����Ϸ�Ƿ�ʤ��
int judge(tank_s* enemy_tank)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy_tank[i].live)
		{
			return 1;
		}
	}
	return 0;
}

/*****************************
* ����̹��
* �ҷ������������1
* �ҷ���Ӫ�����з���2
*****************************/
int play()
{
	tank_s my_tank;
	bullet_s my_bullet;
	
	tank_s enemy_tank[ENEMY_NUM];
	bullet_s enemy_bullet[ENEMY_NUM];

	int times=0;                     //��¼��ǰ��������ߴ�����ÿ��10ms
	int enemy_total = 3;             //��ǰ���ϵз�̹����
	int enemy_alive = enemy_total;   //��ǰ���ϵз����̹����

	srand((unsigned int)time(NULL));

	//�����ҷ�̹�˲���
	my_tank.x = 8;
	my_tank.y = 24;
	my_tank.live = 1;
	my_tank.direction = UP;
	my_tank.aka = 200;
	map[my_tank.y][my_tank.x] = my_tank.aka;
	map[my_tank.y+1][my_tank.x] = my_tank.aka;
	map[my_tank.y][my_tank.x+1] = my_tank.aka;
	map[my_tank.y+1][my_tank.x+1] = my_tank.aka;

	putimage(my_tank.x * 25, my_tank.y * 25, &my_tank_img[my_tank.direction]);

	my_bullet.status = 0;

	//���õз�̹�˲���
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//̹�˲���
		if (i % 3 == 0)
		{
			enemy_tank[i].x = 0;
		}
		else if (i % 3 == 1)
		{
			enemy_tank[i].x = 12;
		}
		else if (i % 3 == 2)
		{
			enemy_tank[i].x = 24;
		}
		enemy_tank[i].y = 0;
		enemy_tank[i].live = 1;
		enemy_tank[i].aka = 100 + i;
		map[enemy_tank[i].y][enemy_tank[i].x] = enemy_tank[i].aka;
		map[enemy_tank[i].y+1][enemy_tank[i].x] = enemy_tank[i].aka;
		map[enemy_tank[i].y][enemy_tank[i].x+1] = enemy_tank[i].aka;
		map[enemy_tank[i].y+1][enemy_tank[i].x+1] = enemy_tank[i].aka;
		enemy_tank[i].direction = DOWN;

		//�ӵ�����
		enemy_bullet[i].status = 0;
		enemy_bullet[i].aka = enemy_tank[i].aka;
	}

	//��������
	mciSendString(_T("open background.wav alias music wait"), NULL, 1, NULL);
	mciSendString(_T("play music"), 0, 0, 0);

	//�з�̹�������ǳ�
	for (int i = 0; i < enemy_total; i++)
	{
		putimage(enemy_tank[i].x * 25, enemy_tank[i].y * 25, &enemy_tank_img[enemy_tank[i].direction]);
	}

	while (judge(enemy_tank))
	{
		if (times % 700 == 0 && enemy_total < ENEMY_NUM)
		{
			if (times > 0)
			{
				enemy_total++;
			}
		}
		for (int i = enemy_alive; i < enemy_total; i++)
		{
			if (enemy_tank[i].live)
			{
				if (map[enemy_tank[i].y][enemy_tank[i].x] != 0&& map[enemy_tank[i].y+1][enemy_tank[i].x] != 0 && map[enemy_tank[i].y][enemy_tank[i].x+1] != 0 && map[enemy_tank[i].y+1][enemy_tank[i].x+1] != 0)
				{
					putimage(enemy_tank[i].x * 25, enemy_tank[i].y * 25, &enemy_tank_img[enemy_tank[i].direction]);
				}
			}
		}
		//�ƶ��ҷ�̹��
		move_my_tank(&my_tank,my_tank.direction,&my_bullet);

		//�ƶ������ĵз�̹��
		if (times % 30 == 0)
		{
			for (int i = 0; i < enemy_total; i++)
			{
				if (enemy_tank[i].live)
				{
					move_enemy_Tank(&enemy_tank[i], enemy_tank[i].direction, &enemy_tank_img[enemy_tank[i].direction]);
				}
			}
		}

		//�з�̹��תͷ
		if (times % 150 == 0)
		{
			for (int i = 0;i < enemy_total; i++)
			{
				//�����ҷ��ϳ�
				if (enemy_tank[i].live == 1 && i % 2 == 0)
				{
					enemy_tank[i].direction = enemy_direction(&enemy_tank[i], 12, 24);
					move_enemy_Tank(&enemy_tank[i], enemy_tank[i].direction, &enemy_tank_img[enemy_tank[i].direction]);
				}
				//�����ҷ�̹��
				else if(enemy_tank[i].live == 1 && i % 2 == 1)
				{
					enemy_tank[i].direction = enemy_direction(&enemy_tank[i], my_tank.x, my_tank.y);
					move_enemy_Tank(&enemy_tank[i], enemy_tank[i].direction, &enemy_tank_img[enemy_tank[i].direction]);
				}
			}
		}

		if (times % 200 == 0)
		{
			if (times > 200)
			{
				for (int i = 0; i < enemy_total; i++)
				{
					if (enemy_tank[i].live)
					{
						tank_fire(&enemy_tank[i], &enemy_bullet[i], 0);
					}
				}
			}
		}
		if (my_bullet.status == 1)
		{
			if (bullet_fly(&enemy_alive, enemy_tank, &my_bullet, 200) == 1)
			{
				mciSendString(_T("close music"), 0, 0, 0);
				return 1;
			}
			else if (bullet_fly(&enemy_alive, enemy_tank, &my_bullet, 200) == 2)
			{
				mciSendString(_T("close music"), 0, 0, 0);
				return 2;
			}
		}
		for (int i = 0; i < enemy_total; i++)
		{
			if (enemy_bullet[i].status == 1)
			{
				if (bullet_fly(&enemy_alive, enemy_tank, &enemy_bullet[i], 0) == 1)
				{
					mciSendString(_T("close music"), 0, 0, 0);
					return 1;
				}
				else if (bullet_fly(&enemy_alive, enemy_tank, &enemy_bullet[i], 0) == 2)
				{
					mciSendString(_T("close music"), 0, 0, 0);
					return 2;
				}
			}
		}
		Sleep(10);
		times++;
	}
	mciSendString(_T("close music"), 0, 0, 0);
	return 3;
}

int main()
{
	loadimg();
	initgraph(650, 650/*,EW_SHOWCONSOLE*/);

	//��ʾlogo
	putimage(110,20,&logo_img);
	//��ʼ����
	drawStart();
	//��ʼ����ͼ
	drawMap();
	//����̹��
	int r = play();
	if (r == 1)
	{
		mciSendString("open failure.mp3 alias music", 0, 0, 0);
		mciSendString("play music", 0, 0, 0);
		putimage(80, 120, &failure_img);
	}
	else if (r == 2)
	{
		mciSendString("open failure.mp3 alias music", 0, 0, 0);
		mciSendString("play music", 0, 0, 0);
		putimage(12 * 25, 24 * 25, &home_fail_img);
		Sleep(1000);
		putimage(80, 120, &failure_img);
	}
	else if (r == 3)
	{
		mciSendString("open victory.mp3 alias music", 0, 0, 0);
		mciSendString("play music", 0, 0, 0);
		putimage(80, 120, &victory_img);
	}

	system("pause");
	closegraph();
	return 0;
}
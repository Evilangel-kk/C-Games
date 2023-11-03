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

//坦克结构体
struct tank_s
{
	int x;
	int y;
	int direction;   //坦克方向
	int live;        //存活状态 1-存活 0-死亡
	int aka;
};

//子弹结构体
struct bullet_s 
{
	int pox_x;             //子弹在屏幕上的x坐标
	int pox_y;             //子弹在屏幕上的y坐标
	int status;            //子弹是否存在
	int direction;         //子弹方向
	int aka;               //子弹主人
};

//设计地图
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

//加载图片到变量
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

//实现导航按钮
void drawBegin()
{
	//setlinecolor(WHITE);
	setfillcolor(BLACK);

	fillrectangle(210, 200, 290, 240);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(220, 210, _T("说 明"));


	fillrectangle(350, 200, 430, 240);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(360, 210, _T("开 始"));

}

//画说明指导
void drawInstruction()
{
	putimage(100, 290, &movekey_img);
	putimage(400, 310, &stop_img);
	putimage(400, 390, &hit_img);
	settextstyle(25, 0, _T("宋体"));
	settextcolor(GREEN);
	outtextxy(200, 280, _T("上移"));
	settextstyle(25, 0, _T("宋体"));
	outtextxy(200, 460, _T("下移"));
	settextstyle(25, 0, _T("宋体"));
	outtextxy(125, 355, _T("左移"));
	settextstyle(25, 0, _T("宋体"));
	outtextxy(275, 355, _T("右移"));
	settextstyle(25, 0, _T("宋体"));
	outtextxy(478, 415, _T("开火"));
	settextcolor(RED);
	settextstyle(25, 0, _T("宋体"));
	outtextxy(478, 330, _T("停止"));
}

//开始界面
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
				//绘制黑色矩形覆盖说明图片
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

//绘制游戏地图
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

//让子弹飞
//返回：0 游戏继续；1 大本营被端了；2 玩家死亡 
int bullet_fly(int* enemy_alive,tank_s* enemy_tank, bullet_s* bullet, int type)
{
	int x = bullet->pox_x / 25;
	int y = bullet->pox_y / 25;
	int x1 = x;
	int y1 = y;

	//擦除上一次绘制的子弹
	if (bullet->status)
	{
		setfillcolor(BLACK);
		solidrectangle(bullet->pox_x, bullet->pox_y, bullet->pox_x + 3, bullet->pox_y + 3);
	}
	//根据方向计算子弹坐标
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

	//碰撞检测
	//家毁
	if (map[y][x] == 3 || map[y1][x1] == 3)
	{
		PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
		bullet->status = 0;
		return 2;
	}
	//我方坦克被击中
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
	//敌方坦克被击中
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
	//墙倒
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

	//重新绘制子弹
	if (bullet->status == 1)
	{
		setfillcolor(WHITE);
		solidrectangle(bullet->pox_x, bullet->pox_y, bullet->pox_x + 3, bullet->pox_y + 3);
	}
	return 0;
}

//开火
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
 * 坦克行走
 * 返回值：失败 - 0 成功 - 1
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
 * 移动我方坦克
 * 返回值：失败 - 0 成功 - 1
 *******************************/
void move_my_tank(tank_s* tank, int direction,bullet_s* bullet)
{
	if (_kbhit())    //检测键盘敲击
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
			//开火
		case 'j':
			tank_fire(tank, bullet,200);
			break;
			//暂停
		case 'p':
			system("pause");
			break;
		default:
			break;
		}
	}
}

/*******************************
 * 移动敌方坦克
 * 返回值：失败 - 0 成功 - 1
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
 *根据目标位置，调整敌方坦克方向 
 * 返回行进方向
 ********************************/
DIRECTION enemy_direction(tank_s* tank, int x, int y)
{
	int r = rand() % 100;
	
	if (tank->x > x)
	{
		if (tank->y > y)
		{
			//目标在左上方
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
		//目标在左下方
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
		//目标在左方
		else
		{
			return LEFT;
		}
	}
	else if(tank->x < x)
	{
		if (tank->y > y)
		{
			//目标在右上方
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
		//目标在右下方
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
		//目标在右方
		else
		{
			return RIGHT;
		}
	}
	else
	{
		//目标在正下方
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
		//目标在正上方
		else
		{
			return UP;
		}
	}
}

//检测游戏是否胜利
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
* 产生坦克
* 我方玩家死亡返回1
* 我方大本营被击中返回2
*****************************/
int play()
{
	tank_s my_tank;
	bullet_s my_bullet;
	
	tank_s enemy_tank[ENEMY_NUM];
	bullet_s enemy_bullet[ENEMY_NUM];

	int times=0;                     //记录当前程序的休眠次数，每次10ms
	int enemy_total = 3;             //当前场上敌方坦克数
	int enemy_alive = enemy_total;   //当前场上敌方存活坦克数

	srand((unsigned int)time(NULL));

	//设置我防坦克参数
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

	//设置敌方坦克参数
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//坦克参数
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

		//子弹参数
		enemy_bullet[i].status = 0;
		enemy_bullet[i].aka = enemy_tank[i].aka;
	}

	//背景音乐
	mciSendString(_T("open background.wav alias music wait"), NULL, 1, NULL);
	mciSendString(_T("play music"), 0, 0, 0);

	//敌方坦克闪亮登场
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
		//移动我方坦克
		move_my_tank(&my_tank,my_tank.direction,&my_bullet);

		//移动还存活的敌方坦克
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

		//敌方坦克转头
		if (times % 150 == 0)
		{
			for (int i = 0;i < enemy_total; i++)
			{
				//攻击我方老巢
				if (enemy_tank[i].live == 1 && i % 2 == 0)
				{
					enemy_tank[i].direction = enemy_direction(&enemy_tank[i], 12, 24);
					move_enemy_Tank(&enemy_tank[i], enemy_tank[i].direction, &enemy_tank_img[enemy_tank[i].direction]);
				}
				//攻击我方坦克
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

	//显示logo
	putimage(110,20,&logo_img);
	//开始界面
	drawStart();
	//初始化地图
	drawMap();
	//画出坦克
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
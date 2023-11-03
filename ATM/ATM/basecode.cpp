#include<iostream>
#include<string>
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<math.h>
using namespace std;

//控制全局变量
int flag = 0;

//定义图片变量
IMAGE background;
IMAGE blue;
IMAGE litblue;
IMAGE bankcard;
IMAGE qian;
IMAGE white;

//鼠标结构体
MOUSEMSG mouse;

//用户信息类（可完善）
class Users
{
private:
	float deposit;
	const char* name[3];
public:
	char password[6];
	void Define();
	void Putin();
	void Getout();
	void Inquire();
	void PasswordJudge(char tmp[]);
};

class Machine
{
public:
	void inputPassword();
	void decode();
	void mouse();
	void windows();
};

Users user;

//初始化用户信息
void Users::Define()
{
	user.deposit = 100.00;
	user.name[0] = "寇";
	user.name[1] = "长";
	user.name[2] = "鹏";
	user.password[0] = '1';
	user.password[1] = '2';
	user.password[2] = '3';
	user.password[3] = '4';
	user.password[4] = '5';
	user.password[5] = '6';
}

//字符串解码
void Decode(char tmp[],float &temp,int i)
{
	for (int j = 0; j < i; j++)
	{
		if (tmp[j] == '.')
		{
			for (int k = j + 1; k < i; k++)
			{
				switch (tmp[k])
				{
				case '0':
					temp += pow(0.1, (k - j)) * 0;
					break;
				case '1':
					temp += pow(0.1, (k - j)) * 1;
					break;
				case '2':
					temp += pow(0.1, (k - j)) * 2;
					break;
				case '3':
					temp += pow(0.1, (k - j)) * 3;
					break;
				case '4':
					temp += pow(0.1, (k - j)) * 4;
					break;
				case '5':
					temp += pow(0.1, (k - j)) * 5;
					break;
				case '6':
					temp += pow(0.1, (k - j)) * 6;
					break;
				case '7':
					temp += pow(0.1, (k - j)) * 7;
					break;
				case '8':
					temp += pow(0.1, (k - j)) * 8;
					break;
				case '9':
					temp += pow(0.1, (k - j)) * 9;
					break;
				default:break;
				}
			}
			break;
		}
		else
		{
			switch (tmp[j])
			{
			case '1':
				temp = temp * 10 + 1;
				break;
			case '2':
				temp = temp * 10 + 2;
				break;
			case '3':
				temp = temp * 10 + 3;
				break;
			case '4':
				temp = temp * 10 + 4;
				break;
			case '5':
				temp = temp * 10 + 5;
				break;
			case '6':
				temp = temp * 10 + 6;
				break;
			case '7':
				temp = temp * 10 + 7;
				break;
			case '8':
				temp = temp * 10 + 8;
				break;
			case '9':
				temp = temp * 10 + 9;
				break;
			case '0':
				temp = temp * 10;
				break;
			case '!':
				temp = temp * 100;
				break;
			default:break;
			}
		}
	}
}

//密码匹配
int PasswordJudge(char tmp[])
{
	for (int i = 0; i < 6; i++)
	{
		if (tmp[i] != user.password[i])
		{
			return 0;
		}
	}
	return 1;
}

//鼠标点击获取数字
int Getnumber(float &temp,char c)
{
	char tmp[20] = "";
	int i = 0;
	while (1)
	{
		mouse = GetMouseMsg();
		switch (mouse.uMsg)
		{
		case WM_LBUTTONDOWN:
			//1
			if (mouse.x > 273 && mouse.x < 307 && mouse.y > 565 && mouse.y < 595)
			{
				tmp[i] = '1';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//2
			else if (mouse.x > 311 && mouse.x < 346 && mouse.y > 565 && mouse.y < 595)
			{
				tmp[i] = '2';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//3
			else if (mouse.x > 349 && mouse.x < 384 && mouse.y > 565 && mouse.y < 595)
			{
				tmp[i] = '3';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//4
			else if (mouse.x > 273 && mouse.x < 307 && mouse.y > 601 && mouse.y < 631)
			{
				tmp[i] = '4';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//5
			else if (mouse.x > 311 && mouse.x < 346 && mouse.y > 601 && mouse.y < 631)
			{
				tmp[i] = '5';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//6
			else if (mouse.x > 349 && mouse.x < 384 && mouse.y > 601 && mouse.y < 631)
			{
				tmp[i] = '6';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//7
			else if (mouse.x > 273 && mouse.x < 307 && mouse.y > 637 && mouse.y < 667)
			{
				tmp[i] = '7';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//8
			else if (mouse.x > 311 && mouse.x < 346 && mouse.y > 637 && mouse.y < 667)
			{
				tmp[i] = '8';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//9
			else if (mouse.x > 349 && mouse.x < 384 && mouse.y > 637 && mouse.y < 667)
			{
				tmp[i] = '9';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//00
			else if (mouse.x > 273 && mouse.x < 307 && mouse.y > 673 && mouse.y < 703)
			{
				tmp[i] = '0';
				tmp[i + 1] = '0';
				outtextxy(230 + i * 15, 245, "0");
				outtextxy(230 + (i + 1) * 15, 245, "0");
				i += 2;
			}
			//.
			else if (mouse.x > 311 && mouse.x < 346 && mouse.y > 673 && mouse.y < 703)
			{
				tmp[i] = '.';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//0
			else if (mouse.x > 349 && mouse.x < 384 && mouse.y > 673 && mouse.y < 703)
			{
				tmp[i] = '0';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//清除
			else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 601 && mouse.y < 631)
			{
				if (i != 0)
				{
					i--;
					tmp[i] = '\0';
				}
				putimage(230 + i * 15, 246, &litblue);
			}
			//重置
			else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 637 && mouse.y < 667)
			{
				for (int j = 0; j < i; j++)
				{
					tmp[j] = '\0';
				}
				setfillcolor(RGB(4, 55, 160));
				fillrectangle(220, 245, 520, 270);
				i = 0;
			}
			//取消
			else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 565 && mouse.y < 595)
			{
				putimage(210, 210, &blue);
				return 1;
			}
			//确认
			else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 673 && mouse.y < 703)
			{
				switch (c)
				{
				case 's':
					Decode(tmp, temp, i);
					break;
				case 'p':
					if(!PasswordJudge(tmp))
					{
						outtextxy(230, 275, _T("密码错误，请重新输入!"));
						for (int j = 0; j < i; j++)
						{
							tmp[j] = '\0';
						}
						setfillcolor(RGB(4, 55, 160));
						fillrectangle(220, 245, 420, 270);
						i = 0;
						Getnumber(temp,'p');
					}
					break;
				}
				return 0;
			}
			break;
		default:break;
		}
		if (i >= 20)
		{
			break;
		}
	}
}

//存款
void Users::Putin()
{
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);//去掉文字背景
	settextstyle(25, 0, _T("宋体"));
	outtextxy(220, 220, _T("请输入存入金额："));
	setfillcolor(RGB(4, 55, 160));
	fillrectangle(220, 245, 520, 270);
	float temp=0.00;
	char c = 's';
	if (Getnumber(temp, c) == 0)
	{
		user.deposit += temp;
		putimage(210, 210, &blue);
		outtextxy(220, 275, _T("存款成功！"));
	}
}

//取款
void Users::Getout()
{
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);//去掉文字背景
	settextstyle(25, 0, _T("宋体"));
	outtextxy(220, 220, _T("请输入取出金额："));
	setfillcolor(RGB(4,55,160));
	fillrectangle(220, 245, 520, 270);
	float temp = 0.00;
	char c = 's';
	if (Getnumber(temp, c) == 0)
	{
		if (user.deposit < temp)
		{
			outtextxy(220, 275, _T("余额不足！"));
		}
		else
		{
			user.deposit -= temp;
			putimage(210, 210, &blue);
			outtextxy(220, 275, _T("取款成功！"));
			putimage(29, 547, &qian);
			int yuan = 0;
			while (!yuan)
			{
				mouse = GetMouseMsg();
				switch (mouse.uMsg)
				{
				case WM_LBUTTONDOWN:
					if (mouse.x > 50 && mouse.x < 207 && mouse.y > 609 && mouse.y < 671)
					{
						yuan = 1;
						putimage(29, 547, &white);
					}
					break;
				default:break;
				}
			}
		}
	}
	else
	{
		putimage(210, 210, &blue);
	}
}

//查询
void Users::Inquire()
{
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);//去掉文字背景
	settextstyle(25, 0, _T("宋体"));
	outtextxy(220, 220, _T("您好，"));
	for (int i = 0; i < 3; i++)
	{
		outtextxy(295 + i * 25, 220, user.name[i]);
	}
	outtextxy(220, 245, _T("您账户的余额为："));
	char temp[20] = "";
	sprintf(temp, "%.2f元", user.deposit);
	outtextxy(220, 270, temp);
}

//插卡
void Card()
{
	int card = 0;
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);//去掉文字背景
	settextstyle(25, 0, _T("宋体"));
	if (!card)
	{
		outtextxy(220, 220, _T("请插入银行卡"));
	}
	while (!card)
	{
		mouse = GetMouseMsg();
		switch (mouse.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (mouse.x > 575 && mouse.x < 715 && mouse.y > 595 && mouse.y < 615)
			{
				card = 1;
				putimage(570, 547, &bankcard);
			}
			break;
		}
	}
	if (card)
	{
		putimage(210, 210, &blue);
		outtextxy(220, 220, _T("请输入密码"));
		setfillcolor(RGB(4, 55, 160));
		fillrectangle(220, 245, 420, 270);
		float i = 0;
		char c = 'p';
		if (Getnumber(i,c) == 0)
		{
			flag = 1;
		}
	}
}

//获取鼠标信息：执行操作
void Mouse()
{
	mouse = GetMouseMsg();
	if (mouse.uMsg == WM_LBUTTONDOWN)
	{
		//查询
		if (mouse.x > 28 && mouse.x < 115 && mouse.y > 390 && mouse.y < 430)
		{
			putimage(210, 210, &blue);
			if (!flag)
			{
				Card();
			}
			putimage(210, 210, &blue);
			user.Inquire();
		}
		//存款
		else if (mouse.x > 634 && mouse.x < 720 && mouse.y >390 && mouse.y < 430)
		{
			if (!flag)
			{
				Card();
			}
			putimage(210, 210, &blue);
			user.Putin();
		}
		//取款
		else if (mouse.x > 634 && mouse.x < 720 && mouse.y > 460 && mouse.y < 500)
		{
			if (!flag)
			{
				Card();
			}
			putimage(210, 210, &blue);
			user.Getout();
		}
		//结束
		else if (mouse.x > 28 && mouse.x < 115 && mouse.y > 460 && mouse.y < 500)
		{
			putimage(0, 0, &background);
			flag = 0;
		}
		//取消
		else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 565 && mouse.y < 595)
		{
			putimage(210, 210, &blue);
		}
	}
}

//加载图片
void LoadImg()
{
	loadimage(&background, "ATM.jpg", 750, 750);
	loadimage(&blue,"blue.jpg",320,290);
	loadimage(&litblue, "lightblue.jpg", 15, 23);
	loadimage(&bankcard, "card.png");
	loadimage(&qian, "qian.jpg");
	loadimage(&white, "white.jpg");
}

int main()
{
	LoadImg();
	initgraph(750, 750/*,EW_SHOWCONSOLE*/);
	putimage(0, 0, &background);
	user.Define();
	while (1)
	{
		Mouse();
	}
	system("pause");
	closegraph();
	return 0;
}
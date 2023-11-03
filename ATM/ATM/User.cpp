#include "User.h"
#include<graphics.h>
#include<Windows.h>
using namespace std;

void User::Define()
{
	deposit = 100.00;
	name[0] = "寇";
	name[1] = "长";
	name[2] = "鹏";
	password[0] = '1';
	password[1] = '2';
	password[2] = '3';
	password[3] = '4';
	password[4] = '5';
	password[5] = '6';
}

void User::Putin()
{
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);//去掉文字背景
	settextstyle(25, 0, _T("宋体"));
	outtextxy(220, 220, _T("请输入存入金额："));
	setfillcolor(RGB(4, 55, 160));
	fillrectangle(220, 245, 520, 270);
	float temp = 0.00;
	char c = 's';
	if (Getnumber(temp, c) == 0)
	{
		user.deposit += temp;
		putimage(210, 210, &blue);
		outtextxy(220, 275, _T("存款成功！"));
	}
}

void User::Getout()
{
}

void User::Inquire()
{
}

#pragma once
#include<graphics.h>

class Chess
{
private:
	int step = 0;
	int map[4][4];
	int margin_x = 25;
	int margin_y = 156;
	int imgSize = 150;
	IMAGE num[17];
public:
	//初始化棋盘
	void Init();
	//设置数成功
	bool Setright();
	//难度等级 4x4 5x5 6x6
	void Grade();
	//移动操作
	bool Move(int x,int y);
	//计算步数
	void Steps();
	//游戏时间
	void Time();
	//判断游戏胜利
	bool Judge();
	
};


#pragma once
#include"Chess.h"
#include"Man.h"
#include"AI.h"
#include<graphics.h>


class GameControl
{
public:
	//构造函数
	GameControl(Man* man, AI* ai, Chess* chess);
	//开始对局
	void Play();
	//添加数据成员
private:
	Man* man;
	AI* ai;
	Chess* chess;
};


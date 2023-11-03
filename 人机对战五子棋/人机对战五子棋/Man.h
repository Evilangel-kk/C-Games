#pragma once
#include"Chess.h"
#include<graphics.h>

class Man
{
public:
	//³õÊ¼»¯
	void Init(Chess* chess);
	//ÏÂÆå
	void Go();

private:
	Chess* chess;

};


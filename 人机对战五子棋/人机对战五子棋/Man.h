#pragma once
#include"Chess.h"
#include<graphics.h>

class Man
{
public:
	//��ʼ��
	void Init(Chess* chess);
	//����
	void Go();

private:
	Chess* chess;

};


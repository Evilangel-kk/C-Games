#pragma once
#include"Chess.h"
#include"Man.h"
#include"AI.h"
#include<graphics.h>


class GameControl
{
public:
	//���캯��
	GameControl(Man* man, AI* ai, Chess* chess);
	//��ʼ�Ծ�
	void Play();
	//������ݳ�Ա
private:
	Man* man;
	AI* ai;
	Chess* chess;
};


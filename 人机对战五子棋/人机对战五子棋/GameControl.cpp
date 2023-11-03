#include "GameControl.h"

GameControl::GameControl(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->Init(chess);
	ai->Init(chess);
}

//开始对局
void GameControl::Play()
{
	chess->Init();
	while (1)
	{
		//先由棋手落子
		man->Go();
		
		if (chess->CheckOver())
		{
			chess->Init();
			continue;
		}

		if (chess->ForbiddenHands())
		{
			chess->Init();
			continue;
		}

		//换手
		ai->Go();

		if (chess->CheckOver())
		{
			chess->Init();
			continue;
		}
	}
}

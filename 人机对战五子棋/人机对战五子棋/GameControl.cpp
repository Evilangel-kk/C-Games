#include "GameControl.h"

GameControl::GameControl(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->Init(chess);
	ai->Init(chess);
}

//��ʼ�Ծ�
void GameControl::Play()
{
	chess->Init();
	while (1)
	{
		//������������
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

		//����
		ai->Go();

		if (chess->CheckOver())
		{
			chess->Init();
			continue;
		}
	}
}

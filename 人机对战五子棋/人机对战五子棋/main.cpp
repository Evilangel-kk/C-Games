/* 
	������־��
	1.������Ŀ�������ز�
	2.�����Ŀ�Ŀ�ܣ�����ࣩ
	3.
*/
#include<iostream>
#include"AI.h"
#include"Chess.h"
#include"GameControl.h"
#include"Man.h"
#include<graphics.h>


int main(void)
{
	Man man;
	AI ai;
	Chess chess(13,39,38,58.45);

	GameControl game(&man, &ai, &chess);

	game.Play();

	return 0;
}
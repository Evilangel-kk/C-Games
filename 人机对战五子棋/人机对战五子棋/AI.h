#pragma once
#include"Chess.h"
#include<graphics.h>

class AI
{
public:
	//��ʼ��
	void Init(Chess* chess);
	//����
	void Go();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;
	
	void CalculateScore();
	ChessPos Think();
};


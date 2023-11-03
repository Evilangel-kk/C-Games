#pragma once
#include"Chess.h"
#include<graphics.h>

class AI
{
public:
	//³õÊ¼»¯
	void Init(Chess* chess);
	//ÏÂÆå
	void Go();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;
	
	void CalculateScore();
	ChessPos Think();
};


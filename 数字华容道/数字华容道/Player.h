#pragma once
#include<Windows.h>
class Player
{
private:
	int margin_x = 25;
	int margin_y = 156;
	int margin_w = 764;
	int margin_v = 634;
	int imgSize = 150;
public:
	//初始化
	void Init();
	//点击是否有效
	bool Click(int &x,int &y);
	//开始新的游戏
	bool Replay();
};


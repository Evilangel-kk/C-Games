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
	//��ʼ��
	void Init();
	//����Ƿ���Ч
	bool Click(int &x,int &y);
	//��ʼ�µ���Ϸ
	bool Replay();
};


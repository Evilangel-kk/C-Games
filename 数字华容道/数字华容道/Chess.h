#pragma once
#include<graphics.h>

class Chess
{
private:
	int step = 0;
	int map[4][4];
	int margin_x = 25;
	int margin_y = 156;
	int imgSize = 150;
	IMAGE num[17];
public:
	//��ʼ������
	void Init();
	//�������ɹ�
	bool Setright();
	//�Ѷȵȼ� 4x4 5x5 6x6
	void Grade();
	//�ƶ�����
	bool Move(int x,int y);
	//���㲽��
	void Steps();
	//��Ϸʱ��
	void Time();
	//�ж���Ϸʤ��
	bool Judge();
	
};


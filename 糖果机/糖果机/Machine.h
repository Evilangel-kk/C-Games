#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"Candy.h"
using namespace std;

class Machine
{
private:
	int kind = 0;
	vector<Candy>candys;
	float allprofit = 0;
public:
	Machine();
	void InitCandys();	//��ʼ����Ʒ
	void Do();			//ѡ�����
	void NewIn();		//������Ʒ
	void SellOut();		//������Ʒ
	void GetIn();		//���ӿ��
	int Choose();		//ѡ����Ʒ
	void Profit();		//�鿴����
	void Inventory();	//��ʾ���
	bool Done();		//��������
};
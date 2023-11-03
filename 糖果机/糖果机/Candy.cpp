#include<iostream>
#include<vector>
#include<string>
#include "Candy.h"
using namespace std;

Candy::Candy()
{
	cout << "糖果名称：";
	cin >> this->name;
	cout << "    进价：";
	cin >> this->price_in;
	cout << "    售价：";
	cin >> this->price_out;
	cout << "    库存：";
	cin >> this->inventory;
	this->one_profit = this->price_out - this->price_in;
}

void Candy::In()
{
	int number;
	while (1)
	{
		cout << "您要存入" << name << "多少份：";
		cin >> number;
		if (number > 0)
		{
			cout << "添加完成" << endl;
			inventory += number;
			break;
		}
		else
		{
			cout << "请输入大于0的数" << endl;
		}
	}
}

float Candy::Out()
{
	int num = 0;
	while (1)
	{
		cout << "您要买多少份" << name << "：";
		cin >> num;
		if (num <= inventory)
		{
			inventory -= num;
			cout << "出库成功，请取走商品" << endl;
			float profit = inventory * one_profit;
			return profit;
		}
		else if (inventory == 0)
		{
			cout << "对不起，已售罄, 请选择其他商品购买" << endl;
			return -1;
		}
		else
		{
			cout << "对不起，库存不足" << endl;
			cout << "您想要: (1)减少购买量 (2)更换其他商品";
			int ch = 0;
			cin >> ch;
			if (ch == 2)
			{
				return -2;
			}
		}
	}
}

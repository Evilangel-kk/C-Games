#include<iostream>
#include<vector>
#include<string>
#include "Candy.h"
using namespace std;

Candy::Candy()
{
	cout << "�ǹ����ƣ�";
	cin >> this->name;
	cout << "    ���ۣ�";
	cin >> this->price_in;
	cout << "    �ۼۣ�";
	cin >> this->price_out;
	cout << "    ��棺";
	cin >> this->inventory;
	this->one_profit = this->price_out - this->price_in;
}

void Candy::In()
{
	int number;
	while (1)
	{
		cout << "��Ҫ����" << name << "���ٷݣ�";
		cin >> number;
		if (number > 0)
		{
			cout << "������" << endl;
			inventory += number;
			break;
		}
		else
		{
			cout << "���������0����" << endl;
		}
	}
}

float Candy::Out()
{
	int num = 0;
	while (1)
	{
		cout << "��Ҫ����ٷ�" << name << "��";
		cin >> num;
		if (num <= inventory)
		{
			inventory -= num;
			cout << "����ɹ�����ȡ����Ʒ" << endl;
			float profit = inventory * one_profit;
			return profit;
		}
		else if (inventory == 0)
		{
			cout << "�Բ���������, ��ѡ��������Ʒ����" << endl;
			return -1;
		}
		else
		{
			cout << "�Բ��𣬿�治��" << endl;
			cout << "����Ҫ: (1)���ٹ����� (2)����������Ʒ";
			int ch = 0;
			cin >> ch;
			if (ch == 2)
			{
				return -2;
			}
		}
	}
}

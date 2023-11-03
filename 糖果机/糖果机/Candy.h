#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Candy
{
public:
	string name;
	float price_in;
	float price_out;
	float one_profit;
	int inventory;	//库存

	Candy();
	void In();	//进货
	float Out();	//出货
};
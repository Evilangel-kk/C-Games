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
	void InitCandys();	//初始化商品
	void Do();			//选择操作
	void NewIn();		//增加新品
	void SellOut();		//卖出商品
	void GetIn();		//增加库存
	int Choose();		//选择商品
	void Profit();		//查看利润
	void Inventory();	//显示库存
	bool Done();		//结束操作
};
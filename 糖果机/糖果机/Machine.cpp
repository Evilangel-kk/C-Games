#include<iostream>
#include "Machine.h"
#include"Candy.h"
using namespace std;

Machine::Machine()
{
    cout << "糖果机内糖果品种数量：";
    cin >> this->kind;
    allprofit = 0;

    InitCandys();
}

void Machine::InitCandys()
{
    for (int i = 0; i < kind; i++)
    {
        Candy candy;
        candys.push_back(candy);
    }
}

void Machine::Do()
{
    int order;
    while (1)
    {
        cout << "请选择要进行的操作：\n(1)选择购买\t(2)添加库存\t(3)显示库存\t(4)查看利润\t(5)增加新品\n";
    
        cin >> order;
        switch (order)
        {
        case 1:
            SellOut();
            return;
        case 2:
            GetIn();
            return;
        case 3:
            Inventory();
            return;
        case 4:
            Profit();
            return;
        case 5:
            NewIn();
            return;
        default:
            cout << "请输入1-5之间的数字" << endl;
            break;
        }
    }
}

void Machine::NewIn()
{
    kind++;
    cout << "请输入新品信息" << endl;
    Candy candy;
    candys.push_back(candy);
}

void Machine::SellOut()
{

    while (1)
    {
        int number = Choose();
        float i = candys[number].Out();
        if (i >= 0)
        {
            allprofit += i;
            break;
        }
    }
}

void Machine::GetIn()
{
    int chosen = Choose();
    candys[chosen].In();
}

int Machine::Choose()
{
    for (int i = 1; i <= kind; i++)
    {
        cout << "（" << i << "）" << candys[i - 1].name << endl;
    }

    int chosen = 0;
    while (1)
    {
        cin >> chosen;
        if (chosen >= 1 && chosen <= kind)
        {
            return chosen - 1;
        }
        else
        {
            cout << "请输入1-" << kind << "之间的数字" << endl;
        }
    }
}

void Machine::Profit()
{
    cout << "当前总利润：" << allprofit << endl;
}

void Machine::Inventory()
{
    for (int i = 1; i <= kind; i++)
    {
        cout << "（" << i << "）" << candys[i - 1].name << "：" << candys[i - 1].inventory << endl;
    }
}

bool Machine::Done()
{
    cout << "是否结束操作？\n(1)是\t(2)否\t";
    int i = 0;
    cin >> i;
    if (i == 1)
    {
        return true;
    }
    return false;
}

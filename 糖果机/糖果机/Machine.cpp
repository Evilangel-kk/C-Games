#include<iostream>
#include "Machine.h"
#include"Candy.h"
using namespace std;

Machine::Machine()
{
    cout << "�ǹ������ǹ�Ʒ��������";
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
        cout << "��ѡ��Ҫ���еĲ�����\n(1)ѡ����\t(2)��ӿ��\t(3)��ʾ���\t(4)�鿴����\t(5)������Ʒ\n";
    
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
            cout << "������1-5֮�������" << endl;
            break;
        }
    }
}

void Machine::NewIn()
{
    kind++;
    cout << "��������Ʒ��Ϣ" << endl;
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
        cout << "��" << i << "��" << candys[i - 1].name << endl;
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
            cout << "������1-" << kind << "֮�������" << endl;
        }
    }
}

void Machine::Profit()
{
    cout << "��ǰ������" << allprofit << endl;
}

void Machine::Inventory()
{
    for (int i = 1; i <= kind; i++)
    {
        cout << "��" << i << "��" << candys[i - 1].name << "��" << candys[i - 1].inventory << endl;
    }
}

bool Machine::Done()
{
    cout << "�Ƿ����������\n(1)��\t(2)��\t";
    int i = 0;
    cin >> i;
    if (i == 1)
    {
        return true;
    }
    return false;
}

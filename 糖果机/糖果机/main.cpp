#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
#include"Machine.h"
#include"Candy.h"
using namespace std;

int main()
{
	Machine machine;
	while (1)
	{
		machine.Do();
		Sleep(1500);
		if (machine.Done())
		{
			break;
		}
		Sleep(1000);
	}
	return 0;
}
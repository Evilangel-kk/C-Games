#include<iostream>
#include<Windows.h>
#include"Chess.h"
#include"Player.h"
using namespace std;

int main()
{
	Chess chess;
	Player player;
	while (1)
	{
		chess.Init();
		chess.Steps();
		player.Init();
		while (1)
		{
			int x = 0, y = 0, i = 0;
			if (player.Click(x,y))
			{
				if (chess.Move(x, y))
				{
					chess.Steps();
				}
			}
			if (chess.Judge())
			{
				break;
			}
		}
		if(!player.Replay())
		{
			break;
		}
	}
	return 0;
}
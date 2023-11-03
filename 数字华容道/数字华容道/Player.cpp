#include "Player.h"
#include<graphics.h>
#include<Windows.h>

void Player::Init()
{

}

bool Player::Click(int &x,int &y)
{
	MOUSEMSG msg;
	msg = GetMouseMsg();
	if (msg.uMsg == WM_LBUTTONDOWN)
	{
		if (msg.x > margin_x && msg.y > margin_y && msg.x < margin_v && msg.y < margin_w)
		{
			y = (msg.x - margin_x) / imgSize;
			x = (msg.y - margin_y) / imgSize;
			return true;
		}
		return false;
	}
	return false;
}

bool Player::Replay()
{
	loadimage(0, "win.jpg");
	MOUSEMSG msg;
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x > 207 && msg.y > 455 && msg.x < 443 && msg.y < 521)
			{
				return true;
			}
			return false;
		}
	}
}
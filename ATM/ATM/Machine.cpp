#include "Machine.h"
#include<graphics.h>
#include<Windows.h>
#include<math.h>
using namespace std;

void Machine::Decode(char tmp[], float& temp, int i)
{
	for (int j = 0; j < i; j++)
	{
		if (tmp[j] == '.')
		{
			for (int k = j + 1; k < i; k++)
			{
				switch (tmp[k])
				{
				case '0':
					temp += pow(0.1, (k - j)) * 0;
					break;
				case '1':
					temp += pow(0.1, (k - j)) * 1;
					break;
				case '2':
					temp += pow(0.1, (k - j)) * 2;
					break;
				case '3':
					temp += pow(0.1, (k - j)) * 3;
					break;
				case '4':
					temp += pow(0.1, (k - j)) * 4;
					break;
				case '5':
					temp += pow(0.1, (k - j)) * 5;
					break;
				case '6':
					temp += pow(0.1, (k - j)) * 6;
					break;
				case '7':
					temp += pow(0.1, (k - j)) * 7;
					break;
				case '8':
					temp += pow(0.1, (k - j)) * 8;
					break;
				case '9':
					temp += pow(0.1, (k - j)) * 9;
					break;
				default:break;
				}
			}
			break;
		}
		else
		{
			switch (tmp[j])
			{
			case '1':
				temp = temp * 10 + 1;
				break;
			case '2':
				temp = temp * 10 + 2;
				break;
			case '3':
				temp = temp * 10 + 3;
				break;
			case '4':
				temp = temp * 10 + 4;
				break;
			case '5':
				temp = temp * 10 + 5;
				break;
			case '6':
				temp = temp * 10 + 6;
				break;
			case '7':
				temp = temp * 10 + 7;
				break;
			case '8':
				temp = temp * 10 + 8;
				break;
			case '9':
				temp = temp * 10 + 9;
				break;
			case '0':
				temp = temp * 10;
				break;
			case '!':
				temp = temp * 100;
				break;
			default:break;
			}
		}
	}
}

int Machine::PasswordJudge(User user,char tmp[])
{
	for (int i = 0; i < 6; i++)
	{
		if (tmp[i] != user.password[i])
		{
			return 0;
		}
	}
	return 1;
}

int Machine::Getnumber(float& temp, char c)
{
	char tmp[20] = "";
	int i = 0;
	MOUSEMSG mouse;
	while (1)
	{
		mouse = GetMouseMsg();
		switch (mouse.uMsg)
		{
		case WM_LBUTTONDOWN:
			//1
			if (mouse.x > 273 && mouse.x < 307 && mouse.y > 565 && mouse.y < 595)
			{
				tmp[i] = '1';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//2
			else if (mouse.x > 311 && mouse.x < 346 && mouse.y > 565 && mouse.y < 595)
			{
				tmp[i] = '2';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//3
			else if (mouse.x > 349 && mouse.x < 384 && mouse.y > 565 && mouse.y < 595)
			{
				tmp[i] = '3';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//4
			else if (mouse.x > 273 && mouse.x < 307 && mouse.y > 601 && mouse.y < 631)
			{
				tmp[i] = '4';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//5
			else if (mouse.x > 311 && mouse.x < 346 && mouse.y > 601 && mouse.y < 631)
			{
				tmp[i] = '5';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//6
			else if (mouse.x > 349 && mouse.x < 384 && mouse.y > 601 && mouse.y < 631)
			{
				tmp[i] = '6';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//7
			else if (mouse.x > 273 && mouse.x < 307 && mouse.y > 637 && mouse.y < 667)
			{
				tmp[i] = '7';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//8
			else if (mouse.x > 311 && mouse.x < 346 && mouse.y > 637 && mouse.y < 667)
			{
				tmp[i] = '8';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//9
			else if (mouse.x > 349 && mouse.x < 384 && mouse.y > 637 && mouse.y < 667)
			{
				tmp[i] = '9';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//00
			else if (mouse.x > 273 && mouse.x < 307 && mouse.y > 673 && mouse.y < 703)
			{
				tmp[i] = '0';
				tmp[i + 1] = '0';
				outtextxy(230 + i * 15, 245, "0");
				outtextxy(230 + (i + 1) * 15, 245, "0");
				i += 2;
			}
			//.
			else if (mouse.x > 311 && mouse.x < 346 && mouse.y > 673 && mouse.y < 703)
			{
				tmp[i] = '.';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//0
			else if (mouse.x > 349 && mouse.x < 384 && mouse.y > 673 && mouse.y < 703)
			{
				tmp[i] = '0';
				outtextxy(230 + i * 15, 245, tmp[i]);
				i++;
			}
			//清除
			else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 601 && mouse.y < 631)
			{
				i--;
				tmp[i] = '\0';
				putimage(230 + i * 15, 246, &litblue);
			}
			//重置
			else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 637 && mouse.y < 667)
			{
				for (int j = 0; j < i; j++)
				{
					tmp[j] = '\0';
				}
				setfillcolor(RGB(4, 55, 160));
				fillrectangle(220, 245, 520, 270);
				i = 0;
			}
			//取消
			else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 565 && mouse.y < 595)
			{
				putimage(210, 210, &blue);
				return 1;
			}
			//确认
			else if (mouse.x > 400 && mouse.x < 476 && mouse.y > 673 && mouse.y < 703)
			{
				switch (c)
				{
				case 's':
					Decode(tmp, temp, i);
					break;
				case 'p':
					if (!PasswordJudge(tmp))
					{
						outtextxy(230, 275, _T("密码错误，请重新输入!"));
						for (int j = 0; j < i; j++)
						{
							tmp[j] = '\0';
						}
						setfillcolor(RGB(4, 55, 160));
						fillrectangle(220, 245, 420, 270);
						i = 0;
						Getnumber(temp, 'p');
					}
					break;
				}
				return 0;
			}
			break;
		default:break;
		}
	}
}

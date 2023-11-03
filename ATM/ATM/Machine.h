#pragma once
#include"User.h"

class Machine
{
private:
	User user;
public:
	void Decode(char tmp[], float& temp, int i);
	int PasswordJudge(User user, char tmp[]);
	int Getnumber(float& temp, char c);
};


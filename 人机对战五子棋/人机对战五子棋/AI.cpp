#include "AI.h"

void AI::Init(Chess* chess)
{
	this->chess = chess;
	int size = chess->GetGradeSize();
	for (int i = 0; i < size; i++)
	{
		vector<int>row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
		}

		scoreMap.push_back(row);
	}
}

void AI::Go()
{
	ChessPos pos = Think();
	Sleep(500);		//���ߣ���װ˼��
	chess->ChessDown(&pos, CHESS_WHITE);
}

void AI::CalculateScore()
{
	int personNum = 0;	//������ĳ�����ж���������
	int aiNum = 0;		//AI��ĳ�����ж���������
	int emptyNum = 0;	//�÷����Ͽհ�λ����

	//����������������
	for(int i = 0; i < scoreMap.size(); i++)
	{
		for (int j = 0; j < scoreMap[i].size(); j++)
		{
			scoreMap[i][j] = 0;
		}
	}


	int size = chess->GetGradeSize();
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			//��ÿ������м���
			if (chess->GetChessData(row, col) == 0)
			{
				for (int y = -1; y <= 0; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						if (y == 0 && x == 0)continue;
						if (y == 0 && x != -1)continue;
						//����׼��
						personNum = 0;
						aiNum = 0;
						emptyNum = 0;

						int curRow = 0;
						int curCol = 0;

						//��������ڸ�λ�����ӣ��ṹ��ʲô����
						for (int i = 1; i <= 4; i++)
						{
							curRow = row + i * y;
							curCol = col + i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow, curCol) == CHESS_BLACK)		//����
								{
									personNum++;
								}
								else if (chess->GetChessData(curRow, curCol) == 0)	//�հ�
								{
									emptyNum++;
									break;
								}
								else	//����
								{
									break;
								}
							}
						}

						//����
						for (int i = 1; i <= 4; i++)
						{
							curRow = row - i * y;
							curCol = col - i * x;

							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow, curCol) == CHESS_BLACK)		//����
								{
									personNum++;
								}
								else if (chess->GetChessData(curRow, curCol) == 0)	//�հ�
								{
									emptyNum++;
									break;
								}
								else	//����
								{
									break;
								}
							}
						}

						//����
						if (personNum == 1)			//����
						{
							scoreMap[row][col] += 7;
						}
						else if (personNum == 2)	//����
						{
							if (emptyNum == 1)		//����
							{
								scoreMap[row][col] += 25;
							}
							else if (emptyNum == 2)	//����
							{
								scoreMap[row][col] += 55;
							}
						}
						else if (personNum == 3)	//����
						{
							if (emptyNum == 1)		//����
							{
								scoreMap[row][col] += 40;
							}
							else if (emptyNum == 2)	//����
							{
								scoreMap[row][col] += 500;
							}
						}
						else if (personNum >= 4)	//����
						{
							scoreMap[row][col] += 20000;
						}

						emptyNum = 0;

						//����AI�ڸ�λ�����壬���γ�ʲô����
						for (int i = 1; i <= 4; i++)
						{
							curRow = row + i * y;
							curCol = col + i * x;

							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow, curCol) == CHESS_WHITE)		//����
								{
									aiNum++;
								}
								else if (chess->GetChessData(curRow, curCol) == 0)	//�հ�
								{
									emptyNum++;
									break;
								}
								else	//����
								{
									break;
								}
							}
						}
						//����
						for (int i = 1; i <= 4; i++)
						{
							curRow = row - i * y;
							curCol = col - i * x;

							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow, curCol) == CHESS_WHITE)		//����
								{
									aiNum++;
								}
								else if (chess->GetChessData(curRow, curCol) == 0)	//�հ�
								{
									emptyNum++;
									break;
								}
								else	//����
								{
									break;
								}
							}
						}

						//����
						
						if (aiNum == 1)		//����
						{
							scoreMap[row][col] += 17;
						}
						else if (aiNum == 2)		//����
						{
							if (emptyNum == 1)		//����
							{
								scoreMap[row][col] += 30;
							}
							else if (emptyNum == 2)	//����
							{
								scoreMap[row][col] += 300;
							}
						}
						else if (aiNum == 3)		//����
						{
							if (emptyNum == 1)		//����
							{
								scoreMap[row][col] += 75;
							}
							else if (emptyNum == 2)	//����
							{
								scoreMap[row][col] += 10000;
							}
						}
						else if (aiNum >= 4)		//����
						{
							scoreMap[row][col] += 30000;
						}
					}
				}

				int link = 0;
				for (int y = -1; y <= 0; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						if (y == 0 && x == 0)continue;
						if (y == 0 && x != -1)continue;

						int curRow = 0;
						int curCol = 0;
						personNum = 0;
						emptyNum = 0;

						for (int i = 1; i <= 4; i++)
						{
							curRow = row + i * y;
							curCol = col + i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow,curCol) == CHESS_BLACK)		//����
								{
									personNum++;
								}
								else if (chess->GetChessData(curRow,curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else if (chess->GetChessData(curRow,curCol) == CHESS_WHITE)
								{
									personNum = 0;
									break;
								}
							}
						}

						//����
						for (int i = 1; i <= 4; i++)
						{
							curRow = row - i * y;
							curCol = col - i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow,curCol) == CHESS_BLACK)		//����
								{
									personNum++;
								}
								else if (chess->GetChessData(curRow,curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else if (chess->GetChessData(curRow,curCol) == CHESS_WHITE)
								{
									personNum = 0;
									break;
								}
							}
						}

						if (personNum >= 2 && emptyNum == 2)
						{
							link++;
						}
					}
				}

				//�ж�Ƕ��
				if (link == 1)
				{
					for (int y = -1; y <= 0; y++)
					{
						for (int x = -1; x <= 1; x++)
						{
							int curRow = 0;
							int curCol = 0;
							int chessNum1[4] = { 0 };
							int chessNum2[4] = { 0 };

							if (y == 0 && x == 0)continue;
							if (y == 0 && x != -1)continue;

							//����
							for (int i = 1; i <= 4; i++)
							{
								curRow = row + i * y;
								curCol = col + i * x;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
								{
									if (chess->GetChessData(curRow,curCol) == CHESS_BLACK)
									{
										chessNum1[i - 1] = 1;
									}
									else if (chess->GetChessData(curRow,curCol) == 0)
									{
										chessNum1[i - 1] = 0;
									}
									else
									{
										chessNum1[i - 1] = -1;
									}
								}
							}

							//����
							for (int i = 1; i <= 4; i++)
							{
								curRow = row - i * y;
								curCol = col - i * x;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
								{
									if (chess->GetChessData(curRow,curCol) == CHESS_BLACK)
									{
										chessNum2[i - 1] = 1;
									}
									else if (chess->GetChessData(curRow,curCol) == 0)
									{
										chessNum2[i - 1] = 0;
									}
									else
									{
										chessNum2[i - 1] = -1;
									}
								}
							}
							if (chessNum2[0] == 0 && chessNum2[1] == 1 && chessNum2[2] == 0)
							{
								if (chessNum1[0] == 1 && chessNum1[1] == 0)
								{
									link++;
								}
							}
							else if (chessNum1[0] == 0 && chessNum1[1] == 1 && chessNum1[2] == 0)
							{
								if (chessNum2[0] == 1 && chessNum2[1] == 0)
								{
									link++;
								}
							}
							else if (chessNum1[0] == 0 && chessNum1[1] == 1 && chessNum1[2] == 1 && chessNum1[3] == 0)
							{
								if (chessNum2[0] == 0)
								{
									link++;
								}
							}
							else if (chessNum2[0] == 0 && chessNum2[1] == 1 && chessNum2[2] == 1 && chessNum2[3] == 0)
							{
								if (chessNum1[0] == 0)
								{
									link++;
								}
							}
						}
					}
				}

				if (link >= 2)
				{
					scoreMap[row][col] = 0;
				}
			}
		}
	}
}

ChessPos AI::Think()
{
	CalculateScore();

	vector<ChessPos>maxPoints;

	int maxScore = 0;
	int x = 0, y = 0;

	int size = chess->GetGradeSize();
	
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->GetChessData(row, col) == 0)
			{
				if (scoreMap[row][col] > maxScore)
				{
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore)
				{
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}
	int index = rand() % maxPoints.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%4d  ", scoreMap[i][j]);
		}
		printf("\n");
	}
	return maxPoints[index];
}

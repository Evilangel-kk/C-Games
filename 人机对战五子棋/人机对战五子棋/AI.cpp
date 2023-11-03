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
	Sleep(500);		//休眠：假装思考
	chess->ChessDown(&pos, CHESS_WHITE);
}

void AI::CalculateScore()
{
	int personNum = 0;	//棋手在某方向有多少子连续
	int aiNum = 0;		//AI在某方向有多少子连续
	int emptyNum = 0;	//该方向上空白位个数

	//评分向量数组清零
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
			//对每个点进行计算
			if (chess->GetChessData(row, col) == 0)
			{
				for (int y = -1; y <= 0; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						if (y == 0 && x == 0)continue;
						if (y == 0 && x != -1)continue;
						//清零准备
						personNum = 0;
						aiNum = 0;
						emptyNum = 0;

						int curRow = 0;
						int curCol = 0;

						//假设黑子在该位置落子，会构成什么棋形
						for (int i = 1; i <= 4; i++)
						{
							curRow = row + i * y;
							curCol = col + i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow, curCol) == CHESS_BLACK)		//黑棋
								{
									personNum++;
								}
								else if (chess->GetChessData(curRow, curCol) == 0)	//空白
								{
									emptyNum++;
									break;
								}
								else	//白棋
								{
									break;
								}
							}
						}

						//反向
						for (int i = 1; i <= 4; i++)
						{
							curRow = row - i * y;
							curCol = col - i * x;

							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow, curCol) == CHESS_BLACK)		//黑棋
								{
									personNum++;
								}
								else if (chess->GetChessData(curRow, curCol) == 0)	//空白
								{
									emptyNum++;
									break;
								}
								else	//白棋
								{
									break;
								}
							}
						}

						//评分
						if (personNum == 1)			//二连
						{
							scoreMap[row][col] += 7;
						}
						else if (personNum == 2)	//三连
						{
							if (emptyNum == 1)		//死三
							{
								scoreMap[row][col] += 25;
							}
							else if (emptyNum == 2)	//活三
							{
								scoreMap[row][col] += 55;
							}
						}
						else if (personNum == 3)	//四连
						{
							if (emptyNum == 1)		//死四
							{
								scoreMap[row][col] += 40;
							}
							else if (emptyNum == 2)	//活四
							{
								scoreMap[row][col] += 500;
							}
						}
						else if (personNum >= 4)	//五连
						{
							scoreMap[row][col] += 20000;
						}

						emptyNum = 0;

						//假设AI在该位置下棋，会形成什么棋形
						for (int i = 1; i <= 4; i++)
						{
							curRow = row + i * y;
							curCol = col + i * x;

							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow, curCol) == CHESS_WHITE)		//白棋
								{
									aiNum++;
								}
								else if (chess->GetChessData(curRow, curCol) == 0)	//空白
								{
									emptyNum++;
									break;
								}
								else	//黑棋
								{
									break;
								}
							}
						}
						//反向
						for (int i = 1; i <= 4; i++)
						{
							curRow = row - i * y;
							curCol = col - i * x;

							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow, curCol) == CHESS_WHITE)		//白棋
								{
									aiNum++;
								}
								else if (chess->GetChessData(curRow, curCol) == 0)	//空白
								{
									emptyNum++;
									break;
								}
								else	//黑棋
								{
									break;
								}
							}
						}

						//评分
						
						if (aiNum == 1)		//二连
						{
							scoreMap[row][col] += 17;
						}
						else if (aiNum == 2)		//三连
						{
							if (emptyNum == 1)		//死三
							{
								scoreMap[row][col] += 30;
							}
							else if (emptyNum == 2)	//活三
							{
								scoreMap[row][col] += 300;
							}
						}
						else if (aiNum == 3)		//四连
						{
							if (emptyNum == 1)		//死四
							{
								scoreMap[row][col] += 75;
							}
							else if (emptyNum == 2)	//活四
							{
								scoreMap[row][col] += 10000;
							}
						}
						else if (aiNum >= 4)		//五连
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
								if (chess->GetChessData(curRow,curCol) == CHESS_BLACK)		//黑棋
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

						//反向
						for (int i = 1; i <= 4; i++)
						{
							curRow = row - i * y;
							curCol = col - i * x;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size)
							{
								if (chess->GetChessData(curRow,curCol) == CHESS_BLACK)		//黑棋
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

				//判断嵌四
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

							//正向
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

							//反向
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

#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

//表示落子位置
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0, int c = 0):row(r),col(c){}
};

typedef enum {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1,
}chess_kind__t;

class Chess
{
public:
	Chess(int gradeSize,int margin_x,int margin_y,float chessSize);
	//棋盘初始化
	void Init();
	//点击是否有效
	bool ClickBoard(int x, int y, ChessPos* pos);
	//val表示棋子颜色
	void ChessDown(ChessPos* pos, chess_kind__t kind);
	//获取棋盘大小（13，15，19）
	int GetGradeSize();
	//获取指定位置是黑是白还是空
	int GetChessData(ChessPos* pos);
	int GetChessData(int row, int col);
	//检查是否结束
	bool CheckOver();
	bool ForbiddenHands();
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	
	int gradeSize;	//棋盘大小（线数）
	int margin_x;	//左边界
	int margin_y;	//上边界
	float chessSize;//棋子大小

	//存储当前棋局的棋子分布数据 0：空白 1：黑子 -1：白子
	vector<vector<int>>chessMap;

	//下棋方
	bool playerFlag;	//true:黑棋 false:白棋

	void UpdateGameMap(ChessPos* pos);
	//最近一次落子位置
	ChessPos lastPos;
	//检查是否赢棋
	bool CheckWin();
	void Win();
	void Lose();
	void Forbidden_Lose();
};
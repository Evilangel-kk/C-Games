#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

//��ʾ����λ��
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
	//���̳�ʼ��
	void Init();
	//����Ƿ���Ч
	bool ClickBoard(int x, int y, ChessPos* pos);
	//val��ʾ������ɫ
	void ChessDown(ChessPos* pos, chess_kind__t kind);
	//��ȡ���̴�С��13��15��19��
	int GetGradeSize();
	//��ȡָ��λ���Ǻ��ǰ׻��ǿ�
	int GetChessData(ChessPos* pos);
	int GetChessData(int row, int col);
	//����Ƿ����
	bool CheckOver();
	bool ForbiddenHands();
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	
	int gradeSize;	//���̴�С��������
	int margin_x;	//��߽�
	int margin_y;	//�ϱ߽�
	float chessSize;//���Ӵ�С

	//�洢��ǰ��ֵ����ӷֲ����� 0���հ� 1������ -1������
	vector<vector<int>>chessMap;

	//���巽
	bool playerFlag;	//true:���� false:����

	void UpdateGameMap(ChessPos* pos);
	//���һ������λ��
	ChessPos lastPos;
	//����Ƿ�Ӯ��
	bool CheckWin();
	void Win();
	void Lose();
	void Forbidden_Lose();
};
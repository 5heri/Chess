
#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "Piece.h"

class MoveGen {
public:
	MoveGen(Piece*);
	virtual ~MoveGen();
	bool generateMoves(int, int);
	int getWhiteKing();
	int getBlackKing();
	bool isInCheck(color_p);
	bool isCheckMate(color_p);
	bool diffColorCanMoveTo(color_p, int);
	bool canInterfere(color_p);
	bool isStaleMate(color_p);
	

private:
	Piece* chess_board;

	bool checkPawn(int,int);
	bool checkKnight(int,int);
	bool checkQueen(int,int);
	bool checkBishop(int,int);
	bool checkRook(int,int);
	bool checkKing(int,int);
	bool checkAllSides(int,int,bool,bool);
	bool checkNonSliding(int,int,bool,bool);
	bool sameColor(int,int);
	int getRequiredKing(color_p);

};

#endif /* MOVEGEN_H_ */

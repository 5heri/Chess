
#include <set>
#include "MoveGen.h"
#include "Parts.h"

using namespace std;

	Piece* chess_board;
	const int knightAndKingIndexes[20] = {-21, -19, -12, -8, 0, 8, 12, 19, 21,
		                                    0, -11, -10, -9, -1, 0, 1, 9, 10, 11, 0};
    
    const int kingCheckMateIndexes[9] = {-11, 1, 1, 8, 1, 1, 8, 1, 1}; 


MoveGen::MoveGen(Piece* board) {
	chess_board = board;
}

MoveGen::~MoveGen() {
	
}

int MoveGen::getWhiteKing()
{
	for (int i = START; i < END; i++) {
		if (chess_board[i].getType() == KING 
			&& chess_board[i].getColor() == WHITE) {
			return i;
		}
	}
	return NOT_FOUND;
}

int MoveGen::getBlackKing()
{
	for (int i = START; i < END; i++) {
		if (chess_board[i].getType() == KING 
			&& chess_board[i].getColor() == BLACK) {
			return i;
		}
	}
	return NOT_FOUND;
}

bool MoveGen::isInCheck(color_p color)
{
	int requiredKing = getRequiredKing(color);
	return diffColorCanMoveTo(color, requiredKing);
}

bool MoveGen::isStaleMate(color_p color)
{
	return !canInterfere(color);
}

bool MoveGen::isCheckMate(color_p color)
{
	int requiredKing = getRequiredKing(color);
	int count = KING_INDEX;

	if (diffColorCanMoveTo(color, requiredKing)) {
		while (count < 20) {
			int moveTo = requiredKing + knightAndKingIndexes[count];
			type_p otherType = chess_board[moveTo].getType();
			color_p otherColor = chess_board[moveTo].getColor();
		
			if (otherType == EMPTY || (!sameColor(requiredKing, moveTo) 
				&& otherColor != NONE)) {

				chess_board[moveTo] = Piece(KING, color);
				chess_board[requiredKing] = Piece(EMPTY, NONE);
				bool canStillBeChecked = diffColorCanMoveTo(color, moveTo);
				chess_board[moveTo] = Piece(otherType, otherColor);
				chess_board[requiredKing] = Piece(KING, color);

				if (!canStillBeChecked) {
					return canStillBeChecked;
				}
			}
			count++;
		}	
		return true;
	} else {
		return false;
	}
}

bool MoveGen::canInterfere(color_p color)
{
	for (int i = START; i < END; i++) {
		for (int j = START; j < END; j++) {
			if (chess_board[i].getColor() == color) {
				if (generateMoves(i, j)) {

				type_p iType = chess_board[i].getType();
				color_p iColor = chess_board[i].getColor();
				type_p jType = chess_board[j].getType();
				color_p jColor = chess_board[j].getColor();
				chess_board[j] = Piece(iType, iColor);
				chess_board[i] = Piece(EMPTY, NONE);

				if (!isInCheck(color)) {
					chess_board[i] = Piece(iType, iColor);
					chess_board[j] = Piece(jType, jColor);
					return true;
				}
				chess_board[i] = Piece(iType, iColor);
				chess_board[j] = Piece(jType, jColor);
				}
			}
		}
	}
	return false;
}

bool MoveGen::diffColorCanMoveTo(color_p color, int to)
{
	for (int i = START; i < END; i++) {
		if (chess_board[i].getColor() != color) {
			if (generateMoves(i, to)) {
				return true;
			}
		}
	}
	return false;
}

bool MoveGen::generateMoves(int from, int to) 
{
	type_p type = chess_board[from].getType();
	switch(type)
	{
		case PAWN :
			return checkPawn(from, to);
		case KNIGHT :
			return checkKnight(from, to);
		case QUEEN :
			return checkQueen(from, to);
		case BISHOP :
			return checkBishop(from, to);
		case ROOK :
			return checkRook(from, to);
		case KING :
			return checkKing(from, to);
		default :
			return false;
	
	}
}

bool MoveGen::checkPawn(int from, int to)
{
	set<int> s;

	//WHITE PAWN
	if (chess_board[from].getColor() == WHITE) {
		if (chess_board[from-10].getType() == EMPTY) {
			s.insert(from-10);
		}
		if (chess_board[from-11].getType() != EMPTY 
			&& chess_board[from-11].getColor() == BLACK) {
			s.insert(from-11);
		}
		if (chess_board[from-9].getType() != EMPTY 
			&& chess_board[from-9].getColor() == BLACK) {
			s.insert(from-9);
		}
		if (chess_board[from-20].getType() == EMPTY
				&& chess_board[from-10].getType() == EMPTY
				&& from >= 81 && from <= 88) {
			s.insert(from-20);
		}
	}

	//BLACK PAWN
	if (chess_board[from].getColor() == BLACK) {
		if (chess_board[from+10].getType() == EMPTY) {
			s.insert(from+10);
		}
		if (chess_board[from+11].getType() != EMPTY 
			&& chess_board[from+11].getColor() == WHITE) {
			s.insert(from+11);
		}
		if (chess_board[from+9].getType() != EMPTY 
			&& chess_board[from+9].getColor() == WHITE) {
			s.insert(from+9);
		}
		if (chess_board[from+20].getType() == EMPTY 
				&& chess_board[from+10].getType() == EMPTY
				&& from >= 31 && from <= 38) {
			s.insert(from+20);
		}
	}

	return (s.find(to) != s.end()); 
}

bool MoveGen::checkKnight(int from, int to)
{
	if (to < from) {
		return checkNonSliding(from, to, false, false);
	} else if (to > from) {
		return checkNonSliding(from, to, true, false);
	}
	return false;
}

bool MoveGen::checkQueen(int from, int to)
{
	if (to < from) {
		return checkAllSides(from, to, false, false) 
			|| checkAllSides(from, to, false, true);
	} else if (to > from) {
		return checkAllSides(from, to, true, false)
			|| checkAllSides(from, to, true, true);
	}
	return false;
}

bool MoveGen::checkBishop(int from, int to) 
{
	if (to < from) {
		return checkAllSides(from, to, false, true);
	} else if (to > from) {
		return checkAllSides(from, to, true, true);
	}
	return false;
}

bool MoveGen::checkRook(int from, int to)
{

	if (to < from) {
		return checkAllSides(from, to, false, false);
	} else if (to > from) {
		return checkAllSides(from, to, true, false);
	}
	return false;
}

bool MoveGen::checkKing(int from, int to)
{
	if (to < from) {
		return checkNonSliding(from, to, false, true);
	} else if (to > from) {
		return checkNonSliding(from, to, true, true);
	}
	return false;
}

bool MoveGen::checkAllSides(int from, int to, bool side, bool checkDiagonals)
{
	set<int> s;
	int trackerLeftRight = from;
	int positionControl1 = 1;
	if (checkDiagonals) {
		positionControl1 = 9;
	}
	if (side) {
		trackerLeftRight+=positionControl1;
	} else {
		trackerLeftRight-=positionControl1;
	}

	while(chess_board[trackerLeftRight].getType() != OUT) {
		if (chess_board[trackerLeftRight].getType() == EMPTY) {
			s.insert(trackerLeftRight);
			if (side) {
				trackerLeftRight+=positionControl1;
			} else {
				trackerLeftRight-=positionControl1;
			}
		} else if (!sameColor(from, trackerLeftRight)) {
			s.insert(trackerLeftRight);
			break;
		} else {
			break;
		}
	}

	if (!(s.find(to) != s.end())) {
		int trackerUpDown = from;
		int positionControl2 = 10;
		if (checkDiagonals) {
			positionControl2 = 11;
		}
		if (side) {
			trackerUpDown+=positionControl2;
		} else {
			trackerUpDown-=positionControl2;
		}
		while(chess_board[trackerUpDown].getType() != OUT) {
			if (chess_board[trackerUpDown].getType() == EMPTY) {
				s.insert(trackerUpDown);
				if (side) {
					trackerUpDown+=positionControl2;
				} else {
					trackerUpDown-=positionControl2;
				}
			} else if (!sameColor(from, trackerUpDown)) {
				s.insert(trackerUpDown);
				break;
			} else {
				break;
			}
		}
	}
	return (s.find(to) != s.end());
}

bool MoveGen::checkNonSliding(int from, int to, bool isGreater, bool isKing)
{
	set<int> s;
	int startingIndex = 0;
	if (isGreater) {
		startingIndex += GOING_UP;
	}
	if (isKing) {
		startingIndex += KING_INDEX;
	}
	while(knightAndKingIndexes[startingIndex] != 0) {
		int checkIndexAt = from + knightAndKingIndexes[startingIndex];

		if (chess_board[checkIndexAt].getType() == EMPTY 
			|| (!sameColor(from, checkIndexAt) 
				&& chess_board[checkIndexAt].getColor() != NONE)) {
			s.insert(checkIndexAt);
		}
		startingIndex++;
	}
	return (s.find(to) != s.end());
}

bool MoveGen::sameColor(int from, int to)
{
	color_p fromColor = chess_board[from].getColor();
	color_p toColor = chess_board[to].getColor();
	return fromColor == toColor;
}

int MoveGen::getRequiredKing(color_p color)
{
	int requiredKing;
	if (color == WHITE) {
		requiredKing = getWhiteKing();
	} else if (color == BLACK) {
		requiredKing = getBlackKing();
	}
	return requiredKing;
}



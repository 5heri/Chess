#include <iostream>
#include <stdlib.h>
#include <string>
#include "ChessBoard.hpp"
#include "MoveGen.h"

using namespace std;

	Piece* pieces;
  color_p currentColor;

ChessBoard::ChessBoard()
{
	pieces = new Piece[TOTAL_PIECES];
	resetBoard();
}

ChessBoard::~ChessBoard()
{
  delete []pieces;
}

Piece* ChessBoard::getBoard()
{
	return pieces;
}

void ChessBoard::printBoard()
{
	for (int i = 0; i < TOTAL_PIECES; i++) {

		if (pieces[i].getColor() == WHITE) {
			cout << "w";
		} else if (pieces[i].getColor() == BLACK) {
			cout << "b";
		}

		if (pieces[i].getType() == EMPTY) {
			cout << ".. ";
		} else if (pieces[i].getType() == OUT) {
			cout << "__ ";
		} else if (pieces[i].getType() == PAWN) {
			cout << "P ";
		} else if (pieces[i].getType() == KNIGHT) {
			cout << "H ";
		} else if (pieces[i].getType() == QUEEN) {
			cout << "Q ";
		} else if (pieces[i].getType() == BISHOP) {
			cout << "B ";
		} else if (pieces[i].getType() == ROOK) {
			cout << "R ";
		} else if (pieces[i].getType() == KING) {
			cout << "K ";
		}
		if ((i + 1) % 10 == 0) {
			cout << endl;
		}
	}
}

void ChessBoard::submitMove(const char* fromSquare, const char* toSquare)
{
 
  string from = fromSquare;
  string to = toSquare;
  int fromIndex = getIndex(from);
  int toIndex = getIndex(to);

  if (pieces[fromIndex].getColor() == currentColor) {
    MoveGen mg(pieces);
    bool validMove = mg.generateMoves(fromIndex, toIndex);

    if (validMove) {
      type_p fromType = pieces[fromIndex].getType();
      color_p fromColor = pieces[fromIndex].getColor();
      type_p toType = pieces[toIndex].getType();
      color_p toColor = pieces[toIndex].getColor();

      pieces[toIndex] = Piece(fromType, fromColor);
      pieces[fromIndex] = Piece(EMPTY, NONE);
      MoveGen mgChecker(pieces);
      bool willGoIntoCheck = mgChecker.isInCheck(currentColor);

      if (willGoIntoCheck) {
        pieces[fromIndex] = Piece(fromType, fromColor);
        pieces[toIndex] = Piece(toType, toColor);
        printCheckInfo(fromIndex, willGoIntoCheck, to, NONE);

      } else {
        printMessages(fromType, fromColor, toType, toColor, from, to);
        color_p otherColor = getDiffColor(currentColor);

        if (mgChecker.isInCheck(otherColor)) {
          if (mgChecker.isCheckMate(otherColor) && !mgChecker.canInterfere(otherColor)) {
            printCheckMateInfo(otherColor);
          } else {
            printCheckInfo(-1,false,to,otherColor);
          }
        } else if (mgChecker.isStaleMate(otherColor)) {
          printStaleMateInfo(otherColor);
          return;
        }

        changeTurn();
      }
    } else {
      printInvalidMsgs(fromIndex, toIndex, from, to, true);
    }
  } else {
    printInvalidMsgs(fromIndex, toIndex, from, to, false);
  }
}    

int ChessBoard::getIndex(string position)
{
	int file = position.at(0) - 44;
	int rank = abs(position.at(1) - 48 - 8);
	return file + 10 * rank;
}

void ChessBoard::printMessages(type_p fromType, color_p fromColor, 
  type_p toType, color_p toColor, string from, string to)
{
	string fromTypeStr = returnType(fromType);
	string fromColorStr = returnColor(fromColor);

	cout << fromColorStr << "'s " << fromTypeStr 
		<< " moves from " << from << " to " << to;

	if (toType != EMPTY) {
		string toTypeStr = returnType(toType);
		string toColorStr = returnColor(toColor);

		cout << " taking " << toColorStr << "'s " << toTypeStr;
	}
	cout << endl;
}

void ChessBoard::printCheckInfo(int position, bool willBeInCheck, string to, color_p checked)
{
  if (willBeInCheck) {
    cout << returnColor(position) << "'s " << returnType(position)
      << " cannot move to " << to << " because " << returnColor(position)
      << "'s King will be in check!" << endl;
  } else {
    cout << returnColor(checked) << " is in check" << endl;
  }
}

void ChessBoard::printCheckMateInfo(color_p color)
{
  cout << returnColor(color) << " is in checkmate" << endl;
}

void ChessBoard::printStaleMateInfo(color_p color)
{
  cout << returnColor(color) << " is in stalemate" << endl;
}

void ChessBoard::printInvalidMsgs(int fromIndex, int toIndex, 
  string from, string to, bool invalidTarget)
{
  if (invalidTarget) {
    cout << returnColor(fromIndex) << "'s " << returnType(fromIndex) 
      << " cannot move to " << to << "!" << endl;
  } else if (pieces[fromIndex].getType() == EMPTY) {
    cout << "There is no piece at position " << from << "!" << endl;
  } else {
    cout << "It is not " << returnColor(fromIndex) << "'s turn to move!" << endl; 
  }
}

string ChessBoard::returnType(int position) 
{
	type_p type = pieces[position].getType();
	switch(type)
	{
		case PAWN :
			return "Pawn";
		case KNIGHT :
			return "Knight";
		case QUEEN :
			return "Queen";
		case BISHOP :
			return "Bishop";
		case ROOK :
			return "Rook";
		case KING :
			return "King";
		default :
			return "EMPTY";
	}
}

string ChessBoard::returnColor(int position)
{
	color_p color = pieces[position].getColor();
	switch(color)
	{
		case WHITE :
			return "White";
		case BLACK :
			return "Black";
		default :
			return "NONE";
	}
}

string ChessBoard::returnType(type_p type) 
{
  switch(type)
  {
    case PAWN :
      return "Pawn";
    case KNIGHT :
      return "Knight";
    case QUEEN :
      return "Queen";
    case BISHOP :
      return "Bishop";
    case ROOK :
      return "Rook";
    case KING :
      return "King";
    default :
      return "EMPTY";
  }
}

string ChessBoard::returnColor(color_p color)
{
  switch(color)
  {
    case WHITE :
      return "White";
    case BLACK :
      return "Black";
    default :
      return "NONE";
  }
}

void ChessBoard::changeTurn()
{
  currentColor = (currentColor == WHITE) ? BLACK : WHITE;
}

color_p ChessBoard::getDiffColor(color_p currentColor)
{
  return (currentColor == WHITE) ? BLACK : WHITE;
}

void ChessBoard::resetBoard()
{
  cout << "A new chess game is started!" << endl;
  currentColor = WHITE;
  for (int i = 41; i <= 48; i++) {
    pieces[i] = Piece(EMPTY, NONE);
  }

  for (int i = 51; i <= 58; i++) {
    pieces[i] = Piece(EMPTY, NONE);
  }
  for (int i = 61; i <= 68; i++) {
  	pieces[i] = Piece(EMPTY, NONE);
  }
  for (int i = 71; i <= 78; i++) {
    pieces[i] = Piece(EMPTY, NONE);
  }

    //FOR BLACK
  pieces[21] = Piece(ROOK, BLACK);
  pieces[22] = Piece(KNIGHT, BLACK);
  pieces[23] = Piece(BISHOP, BLACK);
  pieces[24] = Piece(QUEEN, BLACK);
  pieces[25] = Piece(KING, BLACK);
  pieces[26] = Piece(BISHOP, BLACK);
  pieces[27] = Piece(KNIGHT, BLACK);
  pieces[28] = Piece(ROOK, BLACK);

  for (int i = 31; i <= 38; i++) {
    pieces[i] = Piece(PAWN, BLACK);
  }

    //FOR WHITE
  pieces[91] = Piece(ROOK, WHITE);
  pieces[92] = Piece(KNIGHT, WHITE);
  pieces[93] = Piece(BISHOP, WHITE);
  pieces[94] = Piece(QUEEN, WHITE);
  pieces[95] = Piece(KING, WHITE);
  pieces[96] = Piece(BISHOP, WHITE);
  pieces[97] = Piece(KNIGHT, WHITE);
  pieces[98] = Piece(ROOK, WHITE);

  for (int i = 81; i <= 88; i++) {
    pieces[i] = Piece(PAWN, WHITE);
  }
}


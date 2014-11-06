#define CHESSBOARD_H

#include "Piece.h"
#include "Parts.h"

class ChessBoard
{
  public:
    ChessBoard();
    ~ChessBoard();

    void resetBoard();
    Piece* getBoard();
    void printBoard();
    void submitMove(const char* fromSquare, const char* toSquare);

  private:
    Piece* pieces;
    color_p currentColor;

    void printMessages(type_p,color_p,type_p,color_p,std::string,std::string);
    void printCheckInfo(int,bool,std::string,color_p);
    void printInvalidMsgs(int,int,std::string,std::string,bool);
    void printCheckMateInfo(color_p);
    void printStaleMateInfo(color_p);
    std::string returnType(int);
    std::string returnColor(int);
    std::string returnType(type_p);
    std::string returnColor(color_p);
    void changeTurn();
    int getIndex(std::string);
    color_p getDiffColor(color_p);
};

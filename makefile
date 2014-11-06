all: Chess

Chess: ChessMain.o ChessBoard.o Piece.o MoveGen.o
	g++ -Wall -g ChessMain.o ChessBoard.o Piece.o MoveGen.o -o Chess

ChessMain: MoveGen.h ChessBoard.hpp Piece.h ChessMain.cpp
	g++ -Wall -g -c ChessMain.cpp -o ChessMain.o

ChessBoard: Parts.h MoveGen.h ChessBoard.hpp ChessBoard.cpp
	g++ -Wall -g -c ChessBoard.cpp -o ChessBoard.o
	
Piece: Parts.h Piece.h Piece.cpp
	g++ -Wall -g -c Piece.cpp -o Piece.o

MoveGen: Parts.h Piece.h MoveGen.h MoveGen.cpp
	g++ -Wall -g -c MoveGen.cpp -o MoveGen.o

clean:
	rm -f *.o Chess


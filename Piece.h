
#ifndef PIECE_H_
#define PIECE_H_

#include "Parts.h"

class Piece {
public:
	Piece();
	Piece(type_p, color_p);
	virtual ~Piece();
	type_p getType();
	color_p getColor();

private:
	type_p type_of_piece;
	color_p color_of_piece;
};

#endif /* PIECE_H_ */


#include "Piece.h"

	type_p type_of_piece;
	color_p color_of_piece;

Piece::Piece() {
	type_of_piece = OUT;
	color_of_piece = NONE;

}
Piece::Piece(type_p type, color_p color) {
	type_of_piece = type;
	color_of_piece = color;
}

Piece::~Piece() {

}

type_p Piece::getType()
{
	return type_of_piece;
}

color_p Piece::getColor()
{
	return color_of_piece;
}


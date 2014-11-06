
#ifndef PARTS_H_
#define PARTS_H_

enum type_p { OUT, EMPTY, PAWN, KNIGHT, QUEEN, BISHOP, ROOK, KING };
enum color_p {WHITE, BLACK, NONE};

const int TOTAL_PIECES = 120;
const int START = 21;
const int END = 99;
const int NOT_FOUND = -1;
const int KING_INDEX = 10;
const int GOING_UP = 5;

#endif /* PARTS_H_ */

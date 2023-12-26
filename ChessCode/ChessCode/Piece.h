#pragma once
#include "coord.h"
#include <tuple>

#define BOARD_ROWS 8
#define BOARD_COLS BOARD_ROWS

#define WHITE_PIECE 0
#define BLACK_PIECE 1

class Piece
{
protected:
	Coord _coord;
	int _color;
	char _sign;
	
	std::tuple<int, int> calcDelta(Coord coord1, Coord coord2);
	virtual bool arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS]) = 0;
	virtual bool isDstInPath(Coord dst) = 0;
	static Coord calcDst(Coord src, int numOfSteps, char direction);

public:
	Piece(Coord coord, int color);
	virtual char checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS]) = 0;
	Coord getCoord() const;
	int getColor() const;
	char getSign() const;
};


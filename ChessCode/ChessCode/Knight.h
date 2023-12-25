#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(Coord coord, int color);
	virtual char checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS]) override;

private:
	virtual bool arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS]) override;
	virtual bool isDstInPath(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS]) override;
};

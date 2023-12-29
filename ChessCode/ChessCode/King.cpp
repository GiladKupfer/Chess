#include "King.h"


King::King(Coord coord, Color color) : Piece(coord, color)
{
	if (this->_color == WHITE_PIECE) // if its a white piece
	{
		this->_sign = WhiteKing; // make it a white king
	}
	else // its a black piece
	{
		this->_sign = BlackKing; // make it a black king
	}
}

MoveResult King::checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS])
{

	auto dstInPathResult = isDstInPath(dst); // store the returned tuple
	// extract the values
	bool isInPath;
	Direction direction;
	std::tie(isInPath, direction) = dstInPathResult;

	if (!isInPath) // if the destination is not in path
	{
		return IllegalPieceMove; // return illegal piece move
	}

	// no need to check if pieces are in the way

	return Legal; // we got here meanign its a legal move
}

bool King::arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst)
{
	return false; // king has nothing in his way (as long as the piece is not his own but we checked it already)
}

std::tuple<bool, Direction> King::isDstInPath(Coord dst)
{
	auto delta = calcUnsignedDelta(this->_coord, dst); // store the returned tuple
	// extract the values
	int deltaRow;
	int deltaCol;
	std::tie(deltaRow, deltaCol) = delta;

	if (deltaRow > 1 || deltaCol > 1)
	{
		return std::make_tuple(false, None); // return false and garbage char
	}

	return std::make_tuple(true, getDirection(this->_coord, dst)); // return true and the direction

}

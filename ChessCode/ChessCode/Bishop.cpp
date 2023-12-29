#include "Bishop.h"

Bishop::Bishop(Coord coord, Color color) : Piece(coord, color)
{
	if (this->_color == WHITE_PIECE) // if its a white piece
	{
		this->_sign = WhiteBishop; // make the sign a white bishop
	}
	else // its a black piece
	{
		this->_sign = BlackKing; // make the sign a black bisop
	}
}

MoveResult Bishop::checkMove(Coord dst, Piece* board[BOARD_ROWS][BOARD_COLS])
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

	// check if there are pieces in the way that disallows the piece to move there
	if (arePiecesInWay(board, direction, dst))
	{
		return IllegalPieceMove; // return illegal piece move
	}

	return Legal; // we got here meanign its a legal move
}

bool Bishop::arePiecesInWay(Piece* board[BOARD_ROWS][BOARD_COLS], Direction direction, Coord dst)
{
	Coord currentCoord = calcDst(this->_coord, 1, direction); // save the next piece
	while (!currentCoord.isEqual(dst)) // while we havent reached the dest yet
	{
		if (board[currentCoord.Row][currentCoord.Col] != NULL)
		{
			return true; // piece ARE in the way
		}
		currentCoord = calcDst(currentCoord, 1, direction); // go to the next coord
	}
	return false; // we got here meaning there were no pieces in the way
}

std::tuple<bool, Direction> Bishop::isDstInPath(Coord dst)
{
	auto tupleRes = calcUnsignedDelta(this->_coord, dst); // store the returned tuple
	// extract the values
	int deltaRow;
	int deltaCol;
	std::tie(deltaRow, deltaCol) = tupleRes;

	if (deltaRow != deltaCol) // if the deltas match, they are in the diagonals of the bishop
	{
		return std::make_tuple(false, None); // return false and garbage char
	}

	return std::make_tuple(true, getDirection(this->_coord, dst)); // return true and the direction
}

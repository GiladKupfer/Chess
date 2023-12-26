#include "Pawn.h"

#define WHITE_PAWNS_STARTING_ROW 2
#define BLACK_PAWNS_STARTING_ROW 7

Pawn::Pawn(Coord coord, int color) : Piece(coord, color)
{
}

bool Pawn::isInStartingPosition()
{
    if (this->_color == WHITE_PIECE)
    {
        return this->_coord.Row == WHITE_PAWNS_STARTING_ROW; // return wether the piece is in its starting row
    }
    // we got here meaning the piece is black
    return this->_coord.Row == BLACK_PAWNS_STARTING_ROW; // return wether the piece is in its starting row
}

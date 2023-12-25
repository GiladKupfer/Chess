#include "Piece.h"
#include <math.h>

Piece::Piece(Coord coord, int color)
{
    this->_coord = coord; // set the coord
    this->_color = color; // set the color
}
std::tuple<int, int> Piece::calcDelta(Coord coord1, Coord coord2)
{
    int deltaRow = abs(coord1.Row - coord2.Row); // calc delta row
    int deltaCol = abs(coord1.Row - coord2.Row); // calc delta col
    return std::make_tuple(deltaRow, deltaCol); // return a tuple of the two
}

Coord Piece::getCoord() const
{
    return this->_coord; // return the coord
}

int Piece::getColor() const
{
    return this->_color; // return the color
}

int Piece::getType() const
{
    return this->_type; // return the type
}

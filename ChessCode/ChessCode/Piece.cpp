#include "Piece.h"
#include <math.h>
#include <exception>
#include <string>



Piece::Piece(Coord coord, Color color)
{
    this->_coord = coord; // set the coord
    this->_color = color; // set the color
}

bool Piece::isStraightLine(Coord coord1, Coord coord2)
{
    // either the row (or the col) of coord1 should be equal to row (or the col) of coord2
    if (coord1.Row != coord2.Row && coord1.Col != coord2.Col)
    {
        return false; // return false
    }
    return true; // return true
}

bool Piece::isDiagonalLine(Coord coord1, Coord coord2)
{
    auto tupleRes = calcUnsignedDelta(coord1, coord2); // store the returned tuple
    // extract the values
    int deltaRow;
    int deltaCol;
    std::tie(deltaRow, deltaCol) = tupleRes;

    if (deltaRow != deltaCol) // if the deltas match, they are a diagonal
    {
        return false; // return false
    }
    return true; // return true
}


std::tuple<int, int> Piece::calcUnsignedDelta(Coord coord1, Coord coord2)
{
    int deltaRow = abs(coord1.Row - coord2.Row); // calc delta row
    int deltaCol = abs(coord1.Col - coord2.Col); // calc delta col
    return std::make_tuple(deltaRow, deltaCol); // return a tuple of the two
}

std::tuple<int, int> Piece::calcSignedDelta(Coord coord1, Coord coord2)
{
    int deltaRow = coord1.Row - coord2.Row; // calc delta row
    int deltaCol = coord1.Col - coord2.Col; // calc delta col
    return std::make_tuple(deltaRow, deltaCol); // return a tuple of the two
}

Coord Piece::calcDst(Coord src, int numOfSteps, Direction direction)
{
    

    switch (direction)
    {
    case UP: // the direction is up
        return Coord(src.Row + numOfSteps, src.Col);
    case DOWN:// the direction is down
        return Coord(src.Row - numOfSteps, src.Col);
    case LEFT: // the direction is left
        return Coord(src.Row, src.Col - numOfSteps);
    case RIGHT: // the direction is right
        return Coord(src.Row, src.Col + numOfSteps);
    case UP_RIGHT: // the direction is up right
        return Coord(src.Row + numOfSteps, src.Col + numOfSteps);
    case UP_LEFT: // the direction is up left
        return Coord(src.Row + numOfSteps, src.Col - numOfSteps);
    case DOWN_RIGHT: // the direction is down right
        return Coord(src.Row - numOfSteps, src.Col + numOfSteps);
    case DOWN_LEFT: // the direction is down left
        return Coord(src.Row - numOfSteps, src.Col - numOfSteps);
    default: // got unexpected input
        throw std::exception("AINT NO WAY BOY YOU GAVE ME DIRECTIONS TO NARNIA (got unexpected direction)"); // if the direction is invalid throw an exception +""; // if the direction is invalid throw an exception
    }
}

Direction Piece::getDirection(Coord src, Coord dst)
{
    auto tupleRes = calcSignedDelta(src, dst); // store the returned tuple
    // extract the values
    int deltaRow;
    int deltaCol;
    std::tie(deltaRow, deltaCol) = tupleRes;

    if (deltaRow == 0 && deltaCol == 0) // same coord
    {
        return None;
    }

    if (deltaRow == 0) // right or left
    {

        if (deltaCol < 0) // right
        {
            return RIGHT; 
        }

        // we got here meaning its left
        return LEFT;
    }
    if (deltaCol == 0) // up or down
    {
        if (deltaRow < 0) // up
        {
            return UP;
        }

        // we got here menaing its down
        return DOWN;
    }

    if (deltaRow < 0) // up
    {
        if (deltaCol < 0) // right
        {
            return UP_RIGHT;
        }

        // we got here meaning its up left
        return UP_LEFT;
    }
    if (deltaRow > 0) // down
    {
        if (deltaCol < 0) // right
        {
            return DOWN_RIGHT;
        }

        // we got here meaning its down left
        return DOWN_LEFT;
    }
    
}

void Piece::setCoord(Coord coord)
{
    this->_coord = coord; // set the coord
}

Coord Piece::getCoord() const
{
    return this->_coord; // return the coord
}

Color Piece::getColor() const
{
    return this->_color; // return the color
}

Sign Piece::getSign() const
{
    return this->_sign;
}

#include "Piece.h"
#include <math.h>
#include <exception>
#include <string>

enum Directions
{
    UP = 'u',
    DOWN = 'd',
    LEFT = 'l',
    RIGHT = 'r',

    UP_RIGHT = 'ur',
    UP_LEFT = 'ul',
    DOWN_RIGHT = 'dr',
    DOWN_LEFT = 'dl',
};

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

Coord Piece::calcDst(Coord src, int numOfSteps, char direction)
{
    

    switch (direction)
    {
    case UP: // the direction is up
        return Coord(src.Row - numOfSteps, src.Col);
    case DOWN:// the direction is down
        return Coord(src.Row + numOfSteps, src.Col);
    case LEFT: // the direction is left
        return Coord(src.Row, src.Col - numOfSteps);
    case RIGHT: // the direction is right
        return Coord(src.Row, src.Col + numOfSteps);
    case UP_RIGHT: // the direction is up right
        return Coord(src.Row - numOfSteps, src.Col + numOfSteps);
    case UP_LEFT: // the direction is up left
        return Coord(src.Row - numOfSteps, src.Col - numOfSteps);
    case DOWN_RIGHT: // the direction is down right
        return Coord(src.Row + numOfSteps, src.Col + numOfSteps);
    case DOWN_LEFT: // the direction is down left
        return Coord(src.Row + numOfSteps, src.Col - numOfSteps);

    default: // got unexpected input
        throw std::exception("AINT NO WAY BOY YOU GAVE ME DIRECTIONS TO NARNIA (got unexpected direction)"); // if the direction is invalid throw an exception +""; // if the direction is invalid throw an exception
    }
}

Coord Piece::getCoord() const
{
    return this->_coord; // return the coord
}

int Piece::getColor() const
{
    return this->_color; // return the color
}

char Piece::getSign() const
{
    return this->_sign;
}

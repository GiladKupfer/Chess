#include "Coord.h"


#define MIN_COORD_VALUE 0
#define MAX_COORD_VALUE 7

Coord::Coord()
{
	this->Row = -1; // set row
	this->Col = -1; // set col
}

Coord::Coord(int row, int col)
{
	this->Row = row; // set row
	this->Col = col; // set col
}

Coord::Coord(const Coord &other) : Row(other.Row), Col(other.Col)
{
}

bool Coord::isValid()
{
	// check if either one of the coord values is valid (negative or over the limit)
	if (this->Row < MIN_COORD_VALUE || this->Row > MAX_COORD_VALUE || this->Col < MIN_COORD_VALUE || this->Col > MAX_COORD_VALUE)
	{
		return false; // return false
	}
	return true; // return true if we got here
}

bool Coord::isEqual(Coord other)
{
	return this->Row == other.Row && this->Col == other.Col; // return wether the values of the two coords are the same
}

#pragma once
class Coord
{
public:
	int Row;
	int Col;
	Coord(int row, int col);
	bool isValid();
	bool isEqual(Coord other);
};


#pragma once
class Coord
{
public:
	int Row;
	int Col;
	Coord();
	Coord(int row, int col);
	Coord(const Coord& other);
	bool isValid();
	bool isEqual(Coord other);
};


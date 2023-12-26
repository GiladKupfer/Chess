#pragma once
#include "Piece.h"
#include <string>


#define STARTING_PIECE_LAYOUT "ngololkante"

#define BOARD_ROWS 8
#define BOARD_COLS BOARD_ROWS

#define WHITE_PLAYER_TURN 0
#define BLACK_PLAYER_TURN 1


class GameBoard
{
public:
	Piece* board[BOARD_ROWS][BOARD_COLS];
	
	void init();
	char execMove(Coord src, Coord dest);

private:
	int _turn;
	std::string _startingPieceLayout = STARTING_PIECE_LAYOUT;

	Piece* createPiece(char sign, Coord coord);
	bool isExist(Coord coord);
	bool isPieceTurn(Coord coord);
	void switchTurn();
	char checkCheck();
	bool isPlayerKingInDanger();
	bool isOpponentKingInDanger();
	void move(Coord src, Coord dst);

};


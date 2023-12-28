#pragma once
#include "Piece.h"
#include <string>


//#define STARTING_PIECE_LAYOUT "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR" // printing blacks then whites

#define TURN_INDEX 64

#define BOARD_ROWS 8
#define BOARD_COLS BOARD_ROWS


class GameBoard
{
public:
	Piece* board[BOARD_ROWS][BOARD_COLS];
	std::string getCurrentPieceLayout();
	void init(std::string boardInput);
	char execMove(Coord src, Coord dst);
	Color getTurn();
	void setTurn(Color newColor);
private:
	Color _turn;

	Piece* createPiece(char sign, Coord coord);
	bool isExist(Coord coord);
	bool isPieceTurn(Coord coord);
	static Color alternativeTurn(Color currentTurn);
	void switchTurn();
	GameBoard getCopyOfBoard();
	MoveResult checkCheck(Coord src, Coord dst);
	Coord getKing(Color wantedColor);
	bool isPlayerKingInDanger();
	bool isOpponentKingInDanger();
	void move(Coord src, Coord dst);


};


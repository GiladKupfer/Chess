#pragma once
#include "Piece.h"
#include <string>


//#define STARTING_PIECE_LAYOUT "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR" // printing blacks then whites
#define STARTING_PIECE_LAYOUT "####################K##################################k########" // printing blacks then whites

#define BOARD_ROWS 8
#define BOARD_COLS BOARD_ROWS


class GameBoard
{
public:
	Piece* board[BOARD_ROWS][BOARD_COLS];
	std::string getStartingPieceLayout();
	std::string getCurrentPieceLayout();
	void init();
	char execMove(Coord src, Coord dst);

private:
	Color _turn;
	std::string _startingPieceLayout = STARTING_PIECE_LAYOUT;

	Piece* createPiece(char sign, Coord coord);
	bool isExist(Coord coord);
	bool isPieceTurn(Coord coord);
	static Color alternativeTurn(Color currentTurn);
	void switchTurn();
	GameBoard getCopyOfBoard();
	MoveResult checkCheck(Coord src, Coord dst);
	Coord getKing(Piece* board[BOARD_ROWS][BOARD_COLS], Color wantedColor);
	bool isPlayerKingInDanger(Piece* board[BOARD_ROWS][BOARD_COLS]);
	bool isOpponentKingInDanger(Piece* board[BOARD_ROWS][BOARD_COLS]);
	static void move(Piece* board[BOARD_ROWS][BOARD_COLS], Coord src, Coord dst);

};


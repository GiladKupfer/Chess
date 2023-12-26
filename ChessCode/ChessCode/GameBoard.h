#pragma once
#include "Piece.h"
#include <string>


#define STARTING_PIECE_LAYOUT "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR" // printing blacks then whites

#define BOARD_ROWS 8
#define BOARD_COLS BOARD_ROWS

#define WHITE_PLAYER_TURN 0
#define BLACK_PLAYER_TURN 1


class GameBoard
{
public:
	Piece* board[BOARD_ROWS][BOARD_COLS];
	std::string getStartingPieceLayout();
	std::string getCurrentPieceLayout();
	void init();
	char execMove(Coord src, Coord dst);

private:
	int _turn;
	std::string _startingPieceLayout = STARTING_PIECE_LAYOUT;

	Piece* createPiece(char sign, Coord coord);
	bool isExist(Coord coord);
	bool isPieceTurn(Coord coord);
	static int alternativeTurn(int currentTurn);
	void switchTurn();
	GameBoard getCopyOfBoard();
	char checkCheck(Coord src, Coord dst);
	Coord getKing(Piece* board[BOARD_ROWS][BOARD_COLS], int wantedColor);
	bool isPlayerKingInDanger(Piece* board[BOARD_ROWS][BOARD_COLS]);
	bool isOpponentKingInDanger(Piece* board[BOARD_ROWS][BOARD_COLS]);
	static void move(Piece* board[BOARD_ROWS][BOARD_COLS], Coord src, Coord dst);

};


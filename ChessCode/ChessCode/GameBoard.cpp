#include "GameBoard.h"
#include <exception>

enum PieceType {
	// Black Pieces
	BlackRook = 'r',
	BlackKnight = 'n',
	BlackBishop = 'b',
	BlackKing = 'k',
	BlackQueen = 'q',
	BlackPawn = 'p',

	// White Pieces
	WhiteRook = 'R',
	WhiteKnight = 'N',
	WhiteBishop = 'B',
	WhiteKing = 'K',
	WhiteQueen = 'Q',
	WhitePawn = 'P',

	EmptySquare = '#',
};


void GameBoard::init()
{
    this->_turn = WHITE_PLAYER_TURN; // set the default turn to white
	for (int Row = 0; Row < BOARD_ROWS; Row++)
	{
		for (int Col = 0; Col < BOARD_COLS; Col++)
		{
			// Calculate the index in the string based on Row and Col
			int stringIndex = Row * BOARD_COLS + Col;

            // get the piece char based on the starting piece layout
			char pieceChar = _startingPieceLayout[stringIndex];

            // create a new Piece based on the piece char
			this->board[Row][Col] = createPiece(pieceChar,  Coord(Row, Col));
		}
	};
}

Piece* GameBoard::createPiece(char sign, Coord coord)
{
	switch (sign)
    {
        case BlackRook: // it is a black rook
            return new Rook(coord, BLACK_PIECE);
        case BlackKnight: // it is a black knight 
            return new Knight(coord, BLACK_PIECE);
        case BlackBishop: // it is a black bishop
            return new Bishop(coord, BLACK_PIECE);
        case BlackKing: // it is a black king 
            return new King(coord, BLACK_PIECE);
        case BlackQueen: // it is a black queen
            return new Queen(coord, BLACK_PIECE);
        case BlackPawn: // it is a black pawn
            return new Pawn(coord, BLACK_PIECE);
		case WhiteRook: // it is a White rook
			return new Rook(coord, WHITE_PIECE);
		case WhiteKnight: // it is a White knight 
			return new Knight(coord, WHITE_PIECE);
		case WhiteBishop: // it is a White bishop
			return new Bishop(coord, WHITE_PIECE);
		case WhiteKing: // it is a White king 
			return new King(coord, WHITE_PIECE);
		case WhiteQueen: // it is a White queen
			return new Queen(coord, WHITE_PIECE);
		case WhitePawn: // it is a White pawn
			return new Pawn(coord, WHITE_PIECE);
        case EmptySquare: // it is an empty square
            return NULL;
		default: // something went wrong
			throw std::exception("WTF HOW DID YOU EVEN MANAGE TO FAIL"); 
    }
}

bool GameBoard::isExist(Coord coord)
{
    // check if the coord exists in the board
    return this->board[coord.Row][coord.Col] == NULL; 
}

bool GameBoard::isPieceTurn(Coord coord)
{
	// check if the piece color in the specified coordinate is the same as the curretn turn
	return board[coord.Row][coord.Col]->getColor() == this->_turn;
}

void GameBoard::switchTurn()
{
	if (this->_turn == WHITE_PLAYER_TURN) // if the current turn is white
	{
		this->_turn = BLACK_PLAYER_TURN; // switch to black
		return;
	}

	// we got here meaning the current turn is black
	this->_turn = WHITE_PLAYER_TURN // switch to white
}

void GameBoard::move(Coord src, Coord dst)
{
	Piece* originalPiece = board[src.Row][src.Col]; // save the original piece
	this->board[src.Row][src.Col] = NULL; // set the 'old' coord to null
	this->board[dst.Row][dst.Col] = originalPiece; // set the 'new' coord to the new piece (essentially moving it)
}

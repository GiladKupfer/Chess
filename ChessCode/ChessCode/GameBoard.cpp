#include "GameBoard.h"
#include "King.h"
#include "Rook.h"


std::string GameBoard::getStartingPieceLayout()
{
	return this->_startingPieceLayout;
}

std::string GameBoard::getCurrentPieceLayout()
{
	std::string retPieceLayout = "";
	for (int row = 0; row < BOARD_ROWS; row++)
	{
		for (int col = 0; col < BOARD_COLS; col++)
		{
			Piece* currentPiece = board[row][col]; // get the current piece
			try
			{
				retPieceLayout += currentPiece->getSign(); // add the sign we got from the func to the string
			}
			catch (...) // getSign() failed, meaning its an empty square
			{
				retPieceLayout += EmptySquare;
			}
		}
	}

	return retPieceLayout;
}

void GameBoard::init()
{
    this->_turn = WHITE_PIECE; // set the default turn to white
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

char GameBoard::execMove(Coord src, Coord dst)
{
	// invalid moves
	if (!src.isValid() || !dst.isValid()) // illegal coords (5)
	{
		return InvalidSquareIndexes;
	}
	if (!isExist(src) || !isPieceTurn(src)) // soucre piece non existent or not their turn (2)
	{
		return NoPieceOnSourceSquare;
	}
	if (src.isEqual(dst)) // source coord is dst coord (7)
	{
		return SourceAndTargetSquaresEqual; 
	}
	if (isExist(dst) && isPieceTurn(dst)) // dst coord is own player piece (3)
	{
		return OwnPieceOnTargetSquare;
	}	

	// check the move (6)
	MoveResult moveResult = board[src.Row][src.Col]->checkMove(dst, board);
	if (moveResult == IllegalPieceMove)
	{
		return moveResult;
	}


	// check check (1 / 4)
	MoveResult checkRes = checkCheck(src, dst); // get the code the func returns
	if (checkRes == SelfCheck || checkRes == LegalCheck) // if the function found a self check (illegal) or a normal check (legal)
	{
		return checkRes; // return the code
	}

	// move the piece in our board and return valid move
	move(this->board, src, dst);
	switchTurn();
	return Legal; // all the checks have been made so only code is 0
}

Piece* GameBoard::createPiece(char sign, Coord coord)
{
	switch (sign)
    {
        case BlackRook: // it is a black rook
            return new Rook(coord, BLACK_PIECE);
  //      case BlackKnight: // it is a black knight 
  //          return new Knight(coord, BLACK_PIECE);
  //      case BlackBishop: // it is a black bishop
  //          return new Bishop(coord, BLACK_PIECE);
        case BlackKing: // it is a black king 
            return new King(coord, BLACK_PIECE);
  //      case BlackQueen: // it is a black queen
  //          return new Queen(coord, BLACK_PIECE);
  //      case BlackPawn: // it is a black pawn
  //          return new Pawn(coord, BLACK_PIECE);
		case WhiteRook: // it is a White rook
			return new Rook(coord, WHITE_PIECE);
		//case WhiteKnight: // it is a White knight 
		//	return new Knight(coord, WHITE_PIECE);
		//case WhiteBishop: // it is a White bishop
		//	return new Bishop(coord, WHITE_PIECE);
		case WhiteKing: // it is a White king 
			return new King(coord, WHITE_PIECE);
		//case WhiteQueen: // it is a White queen
		//	return new Queen(coord, WHITE_PIECE);
		//case WhitePawn: // it is a White pawn
		//	return new Pawn(coord, WHITE_PIECE);
        case EmptySquare: // it is an empty square
            return NULL;
		default: // something went wrong
			throw std::exception("BRUH WTH YOU GAVE ME A LETTER IN GIBBERISH (got unexpected input)"); 
    }
}

bool GameBoard::isExist(Coord coord)
{
    // check if the coord exists in the board
    return this->board[coord.Row][coord.Col] != NULL; 
}

bool GameBoard::isPieceTurn(Coord coord)
{
	// check if the piece color in the specified coordinate is the same as the current turn
	if (isExist(coord))
	{
		return board[coord.Row][coord.Col]->getColor() == this->_turn;
	}
	throw std::exception("recieved null");
}

Color GameBoard::alternativeTurn(Color currentTurn)
{
	if (currentTurn == WHITE_PIECE) // if the current turn is white
	{
		return BLACK_PIECE; // switch to black
	}

	// we got here meaning the current turn is black
	return WHITE_PIECE; // switch to white
}

void GameBoard::switchTurn()
{
	// switch the turn (toggle of some sort)
	this->_turn = alternativeTurn(this->_turn);
}

GameBoard GameBoard::getCopyOfBoard()
{
	GameBoard newBoard; // create a new game board
	for (int row = 0; row < BOARD_ROWS; row++)
	{
		for (int col = 0; col < BOARD_COLS; col++)
		{
			newBoard.board[row][col] = this->board[row][col]; // copy the value from this board to the new board
		}
	}

	return newBoard; // return the new game board
}

MoveResult GameBoard::checkCheck(Coord src, Coord dst)
{
	GameBoard tempBoard = getCopyOfBoard(); // get a copy of the board
	move(tempBoard.board, src, dst); // simulate the move on the board

	// now that we simulated the move
	if (isPlayerKingInDanger(tempBoard.board)) // check if the player king is in danger
	{
		return SelfCheck; // return illegal move, self check
	}
	if (isOpponentKingInDanger(tempBoard.board)) // check if the opponent king is in danger
	{
		return LegalCheck; // NICE! the player put the enemy king in check
	}

	return Legal; // if nothing special happend, return a normal legal move
}


Coord GameBoard::getKing(Piece* board[BOARD_ROWS][BOARD_COLS], Color wantedColor)
{
	// iterate through the board
	for (int row = 0; row < BOARD_ROWS; row++)
	{
		for (int col = 0; col < BOARD_COLS; col++)
		{
			Piece* currentPiece = board[row][col]; // get the current piece
			if(currentPiece == NULL)
			{
				continue;
			}
			if (currentPiece->getSign() == WhiteKing ||
				currentPiece->getSign() == BlackKing
				) // check if its a king
			{
				if (currentPiece->getColor() == wantedColor ) // if its the player's king
				{
					return currentPiece->getCoord();; // return the coord of the piece
				}
				else
				{
					continue; // we found the wrong king, continue
				}
			}
		}
	}
	throw std::exception("no king found"); // somehow no king was found
}


bool GameBoard::isPlayerKingInDanger(Piece* board[BOARD_ROWS][BOARD_COLS])
{
	Coord wantedKingCoord = getKing(board, this->_turn); // get the coord of the king

	// iterate through the board
	for (int row = 0; row < BOARD_ROWS; row++)
	{
		for (int col = 0; col < BOARD_COLS; col++)
		{
			try
			{
				Piece* currentPiece = board[row][col]; // get the current piece
				if (currentPiece == NULL)
				{
					continue;
				}
				if (!isPieceTurn(currentPiece->getCoord())) // if the current piece is an enemy piece
				{
					if (currentPiece->checkMove(wantedKingCoord, board) == Legal) // check if the piece can eat the king
					{
						return true; // return true because the player king is in danger
					}
				}
			}
			catch (...) // isPieceTurn threw an empty piece exception, ignore
			{
				continue; // continue
			}
		}
	}
	return false; // we got here meaning our king is safe therefore the player king is NOT in danger
}

bool GameBoard::isOpponentKingInDanger(Piece* board[BOARD_ROWS][BOARD_COLS])
{
	Coord wantedKingCoord = getKing(board, alternativeTurn(this->_turn)); // get the coord of the king

	// iterate through the board
	for (int row = 0; row < BOARD_ROWS; row++)
	{
		for (int col = 0; col < BOARD_COLS; col++)
		{
			try
			{
				Piece* currentPiece = board[row][col]; // get the current piece
				if (currentPiece == NULL)
				{
					continue;
				}
				if (isPieceTurn(currentPiece->getCoord())) // if the current piece is an enemy piece
				{
					if (currentPiece->checkMove(wantedKingCoord, board) == Legal) // check if the piece can eat the king
					{
						return true; // return true because the player king is in danger
					}
				}
			}
			catch (...) // isPieceTurn threw an empty piece exception, ignore
			{
				continue; // continue
			}
		}
	}
	return false; // we got here meaning our king is safe therefore the player king is NOT in danger
}

void GameBoard::move(Piece* board[BOARD_ROWS][BOARD_COLS], Coord src, Coord dst)
{
	Piece* originalPiece = board[src.Row][src.Col]; // save the original piece
	board[src.Row][src.Col] = NULL; // set the 'old' coord to null
	board[dst.Row][dst.Col] = originalPiece; // set the 'new' coord to the new piece (essentially moving it)
}

/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "GameBoard.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Coord.h"
#include <tuple>
#include <string>
#include <exception>


using std::cout;
using std::endl;
using std::string;

#define COORD_CHAR_COUNT 2
#define FIRST_NOTATION_EXPECTED 'a'
#define LAST_NOTATION_EXPECTEED 'h'

std::tuple<Coord, Coord> parseInput(std::string input);
Coord parseToCoord(std::string move);
int NotationToNum(char notation);


void main()
{
	srand(time_t(NULL));


	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol

	// 1024 because they made msgToGraphics 1024 for some reason
	char frontendInitialInput[1024] = "r#b#kb####################################################B#KB#R1";

	// create a game board
	GameBoard board;
	board.init(frontendInitialInput);

	strcpy_s(msgToGraphics, frontendInitialInput);

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
  	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		
		// extract the source and dewst coords from the frontend 
		auto tupleRes = parseInput(msgFromGraphics);
		Coord coord1;
		Coord coord2;
		std::tie(coord1, coord2) = tupleRes;

		char result[1024];
		result[0] = board.execMove(coord1, coord2); // get the result of the move
		result[1] = '\0';

		strcpy_s(msgToGraphics, result); // msgToGraphics should contain the result of the operation


		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}



std::tuple<Coord, Coord> parseInput(std::string input)
{
	// seperate the first and second notation
	Coord firstMove = parseToCoord(input.substr(0, 2)); // get the first notation
	Coord secondMove = parseToCoord(input.substr(2)); // get the second notation
	return std::make_tuple(firstMove, secondMove); // return a tuple of the two

}

Coord parseToCoord(std::string move)
{
	if (move.length() > COORD_CHAR_COUNT) // got unexpected input
	{
		throw std::exception("My brother you gave me a string in MD5 (got unexpected input)");
	} 
	// translate the notation to a number and translate the number string to a notmal string
	return Coord(move[1] - '0' - 1, NotationToNum(move[0])); // -1 to not get memory access violation

}

int NotationToNum(char notation)
{
	if (notation < FIRST_NOTATION_EXPECTED || notation > LAST_NOTATION_EXPECTEED) // got unexpected input
	{
		throw std::exception("BROTHER IS PLAYING CHECKERS (wrong notation input)");
	}
	return notation - FIRST_NOTATION_EXPECTED; // use the power of math to return the notation as a number
}
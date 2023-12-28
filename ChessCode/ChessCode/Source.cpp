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
#include "Coord.h"
#include <tuple>
#include <string>
#include <exception>


using std::cout;
using std::endl;
using std::string;

#define COORD_CHAR_COUNT 2
#define FIRST_NOTATION_EXPECTED 'A'
#define LAST_NOTATION_EXPECTEED 'H'

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
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1");

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)

		// YOUR CODE
		strcpy_s(msgToGraphics, "YOUR CODE"); // msgToGraphics should contain the result of the operation

		/******* JUST FOR EREZ DEBUGGING ******/
		int r = rand() % 10; // just for debugging......
		msgToGraphics[0] = (char)(1 + '0');
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/


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
	return Coord(NotationToNum(move[0]), move[1] - '0'); // translate the notation to a number and translate the number string to a notmal string

}

int NotationToNum(char notation)
{
	if (notation < FIRST_NOTATION_EXPECTED || notation > LAST_NOTATION_EXPECTEED) // got unexpected input
	{
		throw std::exception("BROTHER PLAYING CHECKERS (wrong notation input)");
	}
	return notation - FIRST_NOTATION_EXPECTED; // use the power of math to return the notation as a number
}
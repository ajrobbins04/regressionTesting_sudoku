/*************************************************
 *  TEST CLASS
 *	Performs all regression testing on the Board and
 *	Coordinate classes.
***********************************************************************/
#ifndef test_h
#define test_h

#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "board.h"
#include "coordinate.h"

using namespace std;

class Test
{
public:
	Test() {}
	
	void run();
	
	// functions to be used in test cases
	bool  test_readFile(string fileName, int board[][9]);
	bool  test_writeFile(string fileName, int board[][9]);
	void  test_displayBoard(int board[][9]);
	string test_displayPossibleValues(int board[][9], string coordinates, int row, int col);
	string test_editSquare(int board[][9], string coordinates, int row, int col, int value); // For testing w/valid coord input
	string test_editSquare_invalidCoord(int board[][9], string coordinates, int row, int col); // For testing invalid coordinates
	bool test_interact(int board[][9], char input);           // for testing when input != 'E'
	bool test_interact_inputE(int board[][9], char input,     // for testing when input  = 'E'
							  string coordinates, int row,
							  int col, int value);



	
};

#endif

/*************************************************
 *  TEST BOARD CLASS
 *	Performs all regression testing on the Board class.
***********************************************************************/
#ifndef testBoard_h
#define testBoard_h

#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "board.h"
#include "coordinate.h"

using namespace std;

class TestBoard : public Board
{
public:
	TestBoard() {
		string fileName =
		"/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/sudoku.txt";
		
		initializeBoard(fileName);
	}
	
	TestBoard(string fileName){
		initializeBoard(fileName);
	}
	
	void run();
	
	// duplicate functions from Board class w/slight input or
	// attribute modifications to create automated test cases.
	void initializeTestBoard(string fileName);
	void test_displayBoard();
	bool readTestFile(string fileName);
	bool writeTestFile(string fileName);
	bool test_interact(char input);
	bool test_interact_inputE(char input, Coordinate &coordinate, int value); // use when input is 'E'to call test_editSquare
	bool test_interact_inputE_invalid(char input, Coordinate &coord);         // calls test_editSquare_invalidCoord
	string test_editSquare(Coordinate &coordinate, int value);                // For testing w/valid coord input
	string test_editSquare_invalidCoord(Coordinate &coordinate);              // For testing w/invalid coord input
	string test_displayPossibleValues(Coordinate &coordinate);
	
	void test_updateBoard();                                  // test case 1
	void test_correctLowercaseInput();                        // test case 2
	void test_updatePossValues();                             // test case 3
	void test_doubleNumInput();                               // test case 4
	void test_doubleLetterInput();                            // test case 5
	void test_reverseInputOrder();                            // test case 6
	void test_filledCoordinate();                             // test case 7
	void test_possValues_twoNumInput();                       // test case 8
	void test_possValues_twoLetterInput();                    // test case 9
	void test_possValues_coordinateFilled();                  // test case 10
	void test_possValues_incorrectOrder();                    // test case 11
	void test_saveSudokuBoard();                              // test case 12
	void test_readFile();                                     // test case 13
	
private:
	int tBoard[9][9];
	
};
#endif  

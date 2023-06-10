/*************************************************
 *  BOARD CLASS
 *	Represents the sudoku board that's created using any
 *	file containing 9 rows and 9 columns of values.
***********************************************************************/
#ifndef board_h
#define board_h
#define num_rows 8
#define num_cols 8

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "coordinate.h"

using namespace std;

class Board
{
public:
	Board() {
		string fileName =
		"/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/sudoku.txt";
		
		initializeBoard(fileName);
	}
	
	Board(string fileName){
		initializeBoard(fileName);
	}
	
	void initializeBoard(string fileName);
	void displayBoard();
	void computeValues(vector<int> &possible, int row, int col);
	int promptValue(string coord);

	string getPossibleValues(const Coordinate &coordinate);
	string editSquare(const Coordinate &coordinate);
	
	vector<vector<int>> getBoard() const { return board; }
	
	bool readFile(string fileName);

	
private:
	vector<vector<int>> board;
	
};

#endif

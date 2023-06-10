#include "board.h"
#include "testBoard.h"

/**********************************************************************
 * MAIN
 * Driver function for a program which runs a
 * game of Sudoku.
 **********************************************************************/
int main()
{
	// run test cases 1-13
	TestBoard test = TestBoard();
	test.run();
	
	// constructor contains a default filepath to
	// instantiate board obj quickly.
	Board board = Board();
	
	// start game by showing its command options
	// and the sudoku board
	board.displayBoard();
	cout << endl;
	board.displayOptions();
	cout << endl;
	
	// play sudoku until user enters 'Q'
	while (board.interact());
	
	 
	string fileName = board.promptFileName();
	
	// program closes after file is successfully written
	if (!board.writeFile(fileName))
		cout << "ERROR: unable to open " << fileName << endl;
	else
		cout << "Board written successfully\n";
	
	return 0;
}

#include "board.h"

/**********************************************************************
 * MAIN
 * Driver function for a program which runs a
 * game of Sudoku.
 **********************************************************************/
int main()
{
	
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
	
	// location that board will be saved in
	string fileName = board.promptFileName();
	
	// program closes after file is successfully written
	if (!board.writeFile(fileName))
		cout << "ERROR: unable to open " << fileName << endl;
	else
		cout << "Board written successfully\n";
	
	return 0;
}
	// run test cases 1 - 13
	/*test_updateBoard(board);
	test_correctLowercaseInput(board);
	test_updatePossValues(board);
	test_doubleNumInput(board);
	test_doubleLetterInput(board);
	test_reverseInputOrder(board);
	test_filledCoordinate(board);
	test_possValues_twoNumInput(board);
	test_possValues_twoLetterInput(board);
	test_possValues_coordinateFilled(board);
	test_possValues_incorrectOrder(board);
	test_saveSudokuBoard();
	test_readFile(board);*/
 

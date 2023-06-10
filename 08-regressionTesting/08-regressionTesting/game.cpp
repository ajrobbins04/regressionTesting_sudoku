#include "board.h"

/***********************************************************************
 * DISPLAY OPTIONS
 * Shows available options for playing the game.
 ***********************************************************************/
void displayOptions()
{
   cout << "Options:\n";
   cout << "   ?  Show these instructions\n";
   cout << "   D  Display the board\n";
   cout << "   E  Edit one square\n";
   cout << "   S  Show the possible values for a square\n";
   cout << "   Q  Save and Quit\n";

   return;
}

 
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
	displayOptions();
	cout << endl;
	displayBoard(board);
	cout << endl;
	
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

   return 0;
}


/***********************************************************************
* Program:
*    Project 13, Sudoku
*    Brother Ridges, CS124
* Author:
*    Amber Robbins
* Summary:
*    This program executes a sudoku game which originates
*    in a separate file. After the sudoku game is done, it
*    is then written to a new file.
************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

//bool readFile(int board[][9], string fileName);
//void displayOptions();
//void displayBoard(int board[][9]);
//string promptCoordinates();
//bool isCoordValid(int row, int col);
//bool isCoordFilled(int board[][9], int row, int col);
//void computeValues(int board[][9], int possible[], int row, int col);
//void displayPossibleValues(int board[][9]);
//int getRow(string coordinates);
//int getCol(string coordinates);
//void setRowCol(string &coordinates, int &row, int &col);
int promptValue(string coordinates);
void editSquare(int board[][9]);
bool interact(int board[][9]);
bool writeFile(int board[][9], string newFile);

string test_displayPossibleValues(int board[][9], string coordinates, int row, int col);
string test_editSquare(int board[][9], string coordinates, int row, int col, int value); // For testing w/valid coord input
string test_editSquare_invalidCoord(int board[][9], string coordinates, int row, int col); // For testing invalid coordinates

bool test_interact(int board[][9], char input);           // for testing when input != 'E'
bool test_interact_inputE(int board[][9], char input,     // for testing when input  = 'E'
						  string coordinates, int row,
						  int col, int value);

void test_updateBoard(int board[][9]);                    // test case 1
void test_correctLowercaseInput(int board[][9]);          // test case 2
void test_updatePossValues(int board[][9]);               // test case 3
void test_doubleNumInput(int board[][9]);                 // test case 4
void test_doubleLetterInput(int board[][9]);              // test case 5
void test_reverseInputOrder(int board[][9]);              // test case 6
void test_filledCoordinate(int board[][9]);               // test case 7
void test_possValues_twoNumInput(int board[][9]);         // test case 8
void test_possValues_twoLetterInput(int board[][9]);      // test case 9
void test_possValues_coordinateFilled(int board[][9]);    // test case 10
void test_possValues_incorrectOrder(int board[][9]);      // test case 11
void test_saveSudokuBoard();                              // test case 12
void test_readFile(int board[][9]);                       // test case 13


/**********************************************************************
 * MAIN
 * Driver function for a program which runs a
 * game of Sudoku.
 **********************************************************************/
int main()
{
    int board[9][9]; // stores sudoku board
   
	// serves 2 purposes: reads from and
	// writes to file
	string fileName = "/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/sudoku.txt";

	 // read the file
    if (!readFile(board, fileName))
    {
	   // handle possible errors
	   cout << "ERROR: Unable to open " << fileName << endl;
 	   return 0;
    }
 
    // start game by showing its command options
    // and the sudoku board
    displayOptions();
    cout << endl;
    displayBoard(board);
    cout << endl;
	
	// run test cases 1 - 13
	test_updateBoard(board);
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
	test_readFile(board);

   return 0;
}

/***********************************************************************
 * PROMPT VALUE
 * Returns the value that the user wants to place in a
 * given coordinate.
 ***********************************************************************/
int promptValue(string coordinates)
{
	// default value
	int value = -1;
	// get value at coordinate location
    cout << "What is the value at '" << coordinates << "': ";
    cin >> value;
	
	return value;
}

/***********************************************************************
 * EDIT SQUARE
 * Runs coordinates through a series of checks. If all are met,
 * value is added to the corresponding square on the board
 ***********************************************************************/
void editSquare(int board[][9])
{
   
    // get coordinates
    string coordinates = promptCoordinates();
	
	// -1 = default temporary value
	int row = -1;
	int col = -1;

	setRowCol(coordinates, row, col);
 
   // coordinates cannot be out of range
   if (!isCoordValid(row, col))
   {
	   cout << "ERROR: Square '" << coordinates << "' is invalid.\n";
	   cout << "Press 'E' to try again.\n";
	   return;
   }

   // check if square is filled
   if (isCoordFilled(board, row, col))
   {
	   cout << "ERROR: Square '" << coordinates << "' is filled.\n";
	   cout << "Press 'E' to try again.\n";
	   return;
   }
	  
	int value = promptValue(coordinates);

   // check if value is in range
   if (value < 0 || value > 9)
   {
	   cout << "ERROR: Value '" << value << "' in square '" << coordinates
		    << "' is invalid\n";
	   cout << "Press 'E' to try again.\n";
	  return;
   }

   int possible[9];
   computeValues(board, possible, row, col); // check if chosen value
											 // has already been used

   if (possible[value - 1] == 0) // index will be set to 0 if value is used
   {
	   cout << "ERROR: Value '" << value << "' in square '" << coordinates
		    << "' is invalid\n";
	   cout << "Press 'E' to try again.\n";
	  return;
   }

   // add value to its coordinate location
   board[row][col] = value;
	   
}

/***********************************************************************
 * INTERACT
 * User chooses their input from a series of options
 ***********************************************************************/
bool interact(int board[][9])
{
   char input;
   cout << "> ";
   cin >> input;
	  
   input = toupper(input);

   switch (input)
   {
	  case '?':
		 displayOptions(); // show list of options
		 cout << endl << endl;
		 return true;
	  case 'D':
		 displayBoard(board); // show sudoku board
		 cout << endl;
		 return true;
	  case 'E':
		 editSquare(board); // add new value onto board
		 cout << endl;
		 return true;
	  case 'S':
		 displayPossibleValues(board); // show possible values
		 cout << endl;
		 return true;
	  case 'Q': // Quit program
		 return false;
	  default:
		 cout << "ERROR: invalid value\n";
		 return true;
   }
}

/***********************************************************************
 * WRITE FILE
 * Write the sudoku board to its destination file.
 ***********************************************************************/
bool writeFile(int board[][9], string newFile)
{
   // open file
   ofstream fout(newFile);
   if (fout.fail())
   {
	  fout.close();
	  return false;
   }
   
   // write to file
   for (int row = 0; row < 9; row++)
   {
	  for (int col = 0; col < 9; col++)
	  {
		 
		 fout << board[row][col] << " ";
	  }
   }
   // close file
   fout.close();
   return true;
}

/***********************************************************************
 * TEST DISPLAY POSSIBLE VALUES
 * Runs coordinates through a series of checks before computing possible values.
 ***********************************************************************/
string test_displayPossibleValues(int board[][9], string coordinates, int row, int col)
{
 
	// coordinates cannot be out of range
	if (!isCoordValid(row, col))
	{
		string error = "ERROR: Square '" + coordinates + "' is invalid.";
		return error;
	}

	// check if square is filled
	if (isCoordFilled(board, row, col))
	{
		string error = "ERROR: Square '" + coordinates + "' is filled.";
		return error;
	}
	
	// array for storing possible values
	int possible[9];
	
	// populates possible array w/possible values
	computeValues(board, possible, row, col);
	string values;

	for (int i = 0; i < 9; i++)
	{
	   if (possible[i] != 0) //puts values in list form: 3, 5, 9
	   {
		  values += to_string(possible[i]) + ", ";
	   }
	}
	values.pop_back(); //removes ", " after last value
	values.pop_back();

	string msg = "The possible values at square '" + coordinates + "' are: " + values;

	
	return msg;
}

/***********************************************************************
 * TEST EDIT SQUARE
 * Runs coordinates through a series of checks. This version of
 * editSquare is used for testing purposes where a value is needed.
 ***********************************************************************/
string test_editSquare(int board[][9], string coordinates, int row, int col, int value)
{
   // coordinates cannot be out of range
   if (!isCoordValid(row, col))
   {
	   string error = "ERROR: Square '" + coordinates + "' is invalid.";
	   return error;
   }
	
	// check if square is filled
	if (isCoordFilled(board, row, col))
	{
		string error = "ERROR: Square '" + coordinates + "' is filled.";
		return error;
	}

   // check if value is in range
   if (value < 0 || value > 9)
   {
	   string error = "ERROR: Value '" + std::to_string(value) + "' in square '" + coordinates
	   + "' is invalid.";
	   return error;
   }

   int possible[9];
   computeValues(board, possible, row, col); // check if chosen value
											 // has already been used

   if (possible[value - 1] == 0) // index will be set to 0 if value is used
   {
	   string error = "ERROR: Value '" + std::to_string(value) + "' in square '" + coordinates
	   + "' is invalid.";
	   return error;
   }
	
	// add value to its coordinate location
	board[row][col] = value;
	
	string pass = "The square at '" + coordinates + "' was edited.";
	return pass;
}
 
/***********************************************************************
 * TEST EDIT SQUARE - INVALID COORDINATE
 * Runs coordinates through a series of checks. This version of
 * editSquare is used only when the provided coordinates are expected
 * to fail (so it doesn't try to check possible values).
 ***********************************************************************/
string test_editSquare_invalidCoord(int board[][9], string coordinates, int row, int col)
{
   // coordinates cannot be out of range
   if (!isCoordValid(row, col))
   {
	   string error = "ERROR: Square '" + coordinates + "' is invalid.";
	   return error;
   }
	
	// check if square is filled
	if (isCoordFilled(board, row, col))
	{
		string error = "ERROR: Square '" + coordinates + "' is filled.";
		return error;
    }

	string pass = "The square at '" + coordinates + "' can be edited.";
	return pass;
}
 
/***********************************************************************
* TEST INTERACT
* User chooses their input from a series of options. This version of interact is
* used for general testing purposes.
***********************************************************************/
bool test_interact(int board[][9], char input)
{
  char inputCaps = toupper(input);

  switch (inputCaps)
  {
	 case '?':
		displayOptions(); // show list of options
		cout << endl << endl;
		return true;
	 case 'D':
		displayBoard(board); // show sudoku board
		cout << endl;
		return true;
	 case 'E':
		editSquare(board); // add new value onto board
		cout << endl;
		return true;
	 case 'S':
		displayPossibleValues(board); // show possible values
		cout << endl;
		return true;
	 case 'Q': // Quit program
		return false;
	 default:
		cout << "ERROR: invalid value\n";
		return true;
  }
}


/***********************************************************************
* TEST INTERACT - INPUT 'E'
* User chooses their input from a series of options. This version of interact is
* used when the input must be 'E'
 ************************************************************************/
bool test_interact_inputE(int board[][9], char input, string coordinates,
						  int row, int col, int value)
{
  char inputCaps = toupper(input);

  switch (inputCaps)
  {
	 case '?':
		displayOptions(); // show list of options
		cout << endl << endl;
		return true;
	 case 'D':
		displayBoard(board); // show sudoku board
		cout << endl;
		return true;
	 case 'E':
		test_editSquare(board, coordinates, row, col, value);
		cout << endl;
		return true;
	 case 'S':
		test_displayPossibleValues(board, coordinates, row, col); // show possible values
		cout << endl;
		return true;
	 case 'Q': // Quit program
		return false;
	 default:
		cout << "ERROR: invalid value\n";
		return true;
  }
}

/***********************************************************************
 *  TEST CASE 1 - UPDATE BOARD
 *  Verify that the board registers and displays updated squares
 *  that have been filled in.
 ***********************************************************************/
void test_updateBoard(int board[][9])
{
	char input = 'E';
	string coordinates = "E1";
	
	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	int value = 4;
	test_interact_inputE(board, input, coordinates, row, col, value);
	
	input = 'D';
	test_interact(board, input);
	
	assert(board[row][col] == 4);
	
	if (board[row][col] == 4)
	{
		cout << "4 was added to square 'E1'.\nTest Case 1 has passed.\n\n";
	}
	else
		cout << "Test Case 1 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 2 - CORRECT LOWERCASE INPUT
 *  Ensure that lowercase coordinates are autocorrected and used successfully.
 ***********************************************************************/
void test_correctLowercaseInput(int board[][9])
{
	string coordinates = "i5";
	
	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	// must check if coord is valid before displaying possible values
	string msg = test_displayPossibleValues(board, coordinates, row, col);
	
	assert(coordinates == "I5");
	assert(msg == "The possible values at square 'I5' are: 1, 5");

	
	if (msg == "The possible values at square 'I5' are: 1, 5")
	{
		cout << "Possible values computed for 'I5'.\nTest Case 2 has passed.\n\n";
	}
	else
		cout << "Test Case 2 has Failed.\n\n";
}

 /***********************************************************************
 *  TEST CASE 3 - UPDATE POSSIBLE VALUES
 *  Check that the displayPossibleValues function doesn't compute values
 *  for  a square after it has been updated with a valid value.
 ***********************************************************************/
void test_updatePossValues(int board[][9])
{
	// valid coordinate w/one possible value left
	string coordinates = "E5";
	
	int row;
	int col;
	setRowCol(coordinates, row, col);

	// only possible value should be 8
	string msg = test_displayPossibleValues(board, coordinates, row, col);
	
	assert(msg == "The possible values at square 'E5' are: 8");
	
	if (msg == "The possible values at square 'E5' are: 8")
	{
		// edit the board at "E5" using 8
		char input = 'E';
		int value = 8;
		test_interact_inputE(board, input, coordinates, row, col, value);

		// check the possible values at "E5" again
		string msg = test_displayPossibleValues(board, coordinates, row, col);
		
		// cannot compute possible values b/c square is filled
		assert(msg == "ERROR: Square 'E5' is filled.");
		
		if (msg == "ERROR: Square 'E5' is filled.")
			cout << "Square 'E5' is now filled, so possible values aren't computed.\nTest Case 3 has Passed.\n\n";
		else
			cout << "Test Case 3 has Failed.\n\n";
	}
}

/***********************************************************************
 *  TEST CASE 4 - DOUBLE NUMBER INPUT
 *  Checks if the editSquare function handles invalid input where two numbers
 *  are added instead of valid coordinates.
 ***********************************************************************/
void test_doubleNumInput(int board[][9])
{
	string coordinates = "11";
 
	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	// must check if coord is valid before editing it
	string msg = test_editSquare_invalidCoord(board, coordinates, row, col);
	
	assert(msg == "ERROR: Square '11' is invalid.");
	
	if (msg == "ERROR: Square '11' is invalid.")
		cout << "Square '11' is invalid.\nTest Case 4 has Passed.\n\n";
	else
		cout << "Test Case 4 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 5 - DOUBLE LETTER INPUT
 *  Checks if the editSquare function handles invalid input
 *  where two letters are added.
 ***********************************************************************/
void test_doubleLetterInput(int board[][9])
{
	string coordinates = "BB";
 
	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	// must check if coord is valid before editing it
	string msg = test_editSquare_invalidCoord(board, coordinates, row, col);
	
	assert(msg == "ERROR: Square 'BB' is invalid.");
	
	if (msg == "ERROR: Square 'BB' is invalid.")
		cout << "Square 'BB' is invalid.\nTest Case 5 has Passed.\n\n";
	else
		cout << "Test Case 5 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 6 - REVERSE INPUT ORDER
 *  Checks if the editSquare function can correct and use
 *  coordinates written in reverse (number first, letter last).
 ***********************************************************************/
void test_reverseInputOrder(int board[][9])
{
	// given in reverse order
	string coordinates = "2B";

	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	int value = 1;

	// must check if coord is valid before editing it.
	// value is included in parameter b/c coord can be edited, so it needs a value.
	string msg = test_editSquare(board, coordinates, row, col, value);
	
	// check that coordinate order is fixed.
	assert(msg == "The square at 'B2' was edited.");
	
	if (msg == "The square at 'B2' was edited.")
		cout << msg << "\nTest Case 6 has Passed.\n\n";
	else
		cout << "Test Case 6 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 7 - FILLED COORDINATE
 *  Checks if the coordinate is already occupied from within
 *  the editSquare function.
 ***********************************************************************/
void test_filledCoordinate(int board[][9])
{
	// not valid b/c B1 is already filled
	string coordinates = "B1";
 
	int row;
	int col;
	setRowCol(coordinates, row, col);
 
	string msg = test_editSquare_invalidCoord(board, coordinates, row, col);
	
	// check that coordinate is already filled
	assert(msg == "ERROR: Square 'B1' is filled.");
	
	if (msg == "ERROR: Square 'B1' is filled.")
		cout << "Square 'B1' is filled.\nTest Case 7 has Passed.\n\n";
	else
		cout << "Test Case 7 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 8 - TWO NUMBER INPUT
 *  Checks if the displayPossibleValues function handles invalid
 *  input where two numbers are used.
 ***********************************************************************/
void test_possValues_twoNumInput(int board[][9])
{
	string coordinates = "22";
 
	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	// must check if coord is valid before displaying possible values
	string msg = test_displayPossibleValues(board, coordinates, row, col);
	
	assert(msg == "ERROR: Square '22' is invalid.");
	
	if (msg == "ERROR: Square '22' is invalid.")
		cout << "Square '22' is invalid.\nTest Case 8 has Passed.\n\n";
	else
		cout << "Test Case 8 has Failed.\n\n";
	
}

/***********************************************************************
 *  TEST CASE 9 - TWO LETTER INPUT
 *  Checks if the displayPossibleValues function handles invalid
 *  input where two letters are used.
 ***********************************************************************/
void test_possValues_twoLetterInput(int board[][9])
{
	string coordinates = "DD";
 
	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	// must check if coord is valid before editing it
	string msg = test_displayPossibleValues(board, coordinates, row, col);
	
	assert(msg == "ERROR: Square 'DD' is invalid.");
	
	if (msg == "ERROR: Square 'DD' is invalid.")
		cout << "Square 'DD' is invalid.\nTest Case 9 has Passed.\n\n";
	else
		cout << "Test Case 9 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 10 - COORDINATE FILLED
 *  Checks if the coordinate is already occupied from within
 *  the displayPossibleValues function.
 ***********************************************************************/
void test_possValues_coordinateFilled(int board[][9])
{
	// not valid b/c B1 is already filled
	string coordinates = "I9";
 
	int row;
	int col;
	setRowCol(coordinates, row, col);
  
	string msg = test_displayPossibleValues(board, coordinates, row, col);
	
	// check that coordinate is already filled
	assert(msg == "ERROR: Square 'I9' is filled.");
	
	if (msg == "ERROR: Square 'I9' is filled.")
		cout << "Square 'I9' is filled.\nTest Case 10 has Passed.\n\n";
	else
		cout << "Test Case 10 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 11 - INCORRECT ORDER
 *  Checks if the displayPossibleValues function can correct and use
 *  coordinates written in reverse (number first, letter last).
 ***********************************************************************/
void test_possValues_incorrectOrder(int board[][9])
{
	// given in reverse order
	string coordinates = "4A";

	int row;
	int col;
	setRowCol(coordinates, row, col);

	// must check if coord is valid before editing it.
	// value is included in parameter b/c coord can be edited, so it needs a value.
	string msg = test_displayPossibleValues(board, coordinates, row, col);
	
	// check that coordinate order is fixed.
	assert(msg == "The possible values at square 'A4' are: 1, 3");
	
	if (msg == "The possible values at square 'A4' are: 1, 3")
		cout << msg << ".\nTest Case 11 has Passed.\n\n";
	else
		cout << "Test Case 11 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 12 - SAVE SUDOKU BOARD
 *  Validates whether the writeFile function is able to successfully
 *  save the sudoku program.
 ***********************************************************************/
void test_saveSudokuBoard()
{
	int originalBoard[9][9];
	string fileName = "/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/sudoku.txt";
	
	// read original file's contents into an alternate board
	readFile(originalBoard, fileName);
	
	int newBoard[9][9];
	string newFileName = "/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/saveSudoku.txt";
	
	writeFile(newBoard, newFileName);
	
	assert(writeFile);
	assert(originalBoard[0][4] != newBoard[0][4]);
	
	if (writeFile(newBoard, newFileName) == true
		&& originalBoard[0][4] != newBoard[0][4])
		cout << "Sudoku successfully saved with changes to a new file.\nTest Case 12 has Passed.\n\n";
	else
		cout << "Test Case 12 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 13 - READ FILE
 *  Verifies that the sudoku board file containing 9 rows and 9 columns of numbers
 *  can be successfully read into the program and build as a sudoku game.
 ***********************************************************************/
void test_readFile(int board[][9])
{
	int altBoard[9][9];
	
	string fileName = "/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/altSudoku.txt";
	
	// read this file's contents into an alternate board
	readFile(altBoard, fileName);
	
	cout << "Original Board: \n\n";
	displayBoard(board);
	cout << endl;
	
	cout << "Test Case 13 Board: \n\n";
	displayBoard(altBoard);
	cout << endl;

	assert(readFile);
	
	if (readFile(altBoard, fileName) == true)
		cout << "File contents successfully read into the program.\nTest Case 13 has Passed.\n\n";
	else
		cout << "Test Case 13 has Failed.\n\n";

}

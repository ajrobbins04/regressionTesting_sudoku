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

bool readFile(int board[][9], string fileName);
void displayOptions();
void displayBoard(int board[][9]);
string promptCoordinates();
bool isCoordValid(int row, int col);
bool isCoordFilled(int board[][9], int row, int col);
void computeValues(int board[][9], int possible[], int row, int col);
void displayPossibleValues(int board[][9]);
int getRow(string coordinates);
int getCol(string coordinates);
void setRowCol(string &coordinates, int &row, int &col);
int promptValue(string coordinates);
void editSquare(int board[][9]);
bool interact(int board[][9]);
bool writeFile(int board[][9], string newFile);

string test_displayPossibleValues(int board[][9], string coordinates, int row, int col, int value);
string test_displayPossibleValues_invalidCoord(int board[][9], string coordinates, int row, int col);

string test_editSquare(int board[][9], string coordinates, int row, int col, int value); // For testing w/valid coord input
string test_editSquare_invalidCoord(int board[][9], string coordinates, int row, int col); // For testing invalid coordinates

bool test_interact(int board[][9], char input);           // for testing when input != 'E'
bool test_interact_inputE(int board[][9], char input,     // for testing when input  = 'E'
						  string coordinates, int row,
						  int col, int value);

void test_updateBoard(int board[][9]);                    // test case 2
void test_doubleNumInput(int board[][9]);                 // test case 3
void test_doubleLetterInput(int board[][9]);              // test case 4
void test_reverseInputOrder(int board[][9]);              // test case 5
void test_filledCoordinate(int board[][9]);               // test case 6
void test_possValues_twoNumInput(int board[][9]);         // test case 7
void test_possValues_twoLetterInput(int board[][9]);      // test case 8
void test_possValues_coordinateFilled(int board[][9]);    // test case 9
void test_possValues_incorrectOrder(int board[][9]);      // test case 10


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
	
	// run test cases 2 - 8
	test_updateBoard(board);
	test_doubleNumInput(board);
	test_doubleLetterInput(board);
	test_reverseInputOrder(board);
	test_filledCoordinate(board);
	test_possValues_twoNumInput(board);
	test_possValues_twoLetterInput(board);
   
   // play sudoku until user enters 'Q'
   while (interact(board));
 
   // program closes after file is successfully written
   if (!writeFile(board, fileName))
	  cout << "ERROR: unable to open " << fileName << endl;
   else
	  cout << "Board written successfully\n";

   return 0;
   
}

/***********************************************************************
 * READ FILE
 * Moves the sudoku data from its file to the
 * board array.
 ***********************************************************************/
bool readFile(int board[][9], string fileName)
{
   // open file
   ifstream fin(fileName);
   if (fin.fail())
	  return false;

   // read file into board
   for (int row = 0; row < 9; row++)
	  for (int col = 0; col < 9; col++)
	  {
		 fin >> board[row][col];
	  }

   // close file
   fin.close();
   return true;
}

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

/***********************************************************************
 * DISPLAY BOARD
 * Displays the sudoku board fully-formatted.
 ***********************************************************************/
void displayBoard(int board[][9])
{
   
   // create column header
   cout << "   A B C D E F G H I\n";
   
   for (int row = 0; row < 9; row++)
   {
	  cout << row + 1 << "  "; // two spaces between each square

	  for (int col = 0; col < 9; col++)
	  {
		 if (board[row][col] == 0) // 0 denotes empty square
			cout << " ";
		 else
			cout << board[row][col];

		 // separate board into 3 distinct columns
		 if (col == 2 || col == 5)
			cout << "|";
		 else if (col == 0 || col == 1 || col == 3
				  || col == 4 || col == 6 || col == 7)
			cout << " ";
	  }
	  // separate board into 3 distinct rows
	  if (row == 2 || row == 5)
		 cout << "\n   -----+-----+-----\n";
	  else
		 cout << endl;
   }
   return;
}

/***********************************************************************
 * PROMPT COORDINATES
 * Gets users coordinates corresponding to
 * squares on the sudoku board.
 ***********************************************************************/
string promptCoordinates()
{
   // for A1, A is the column and 1 is the row
   string coordinates;
   cout << "What are the coordinates of the square: ";
   cin >> coordinates;

   return coordinates;
}

/**********************************************************************
 * IS COORD VALID
 * Checks that the numerical part of the
 * coordinate is within the range 1 - 9.
 **********************************************************************/
bool isCoordValid(int row, int col)
{
   if (row >= 0 && row <= 8 && col >= 0 && col <= 8)
   {
	  return true;
   }
   return false;
}

/***********************************************************************
 * IS COORD FILLED
 * Checks that the coordinate hasn't already
 * been filled.
 ***********************************************************************/
bool isCoordFilled(int board[][9], int row, int col)
{
   if (board[row][col] != 0)
   {
	  return true;
   }
   return false;
}

/***********************************************************************
 * COMPUTE VALUES
 * Identifies possible values in each row, column,
 * and 3x3 square of the sudoku board.
 ***********************************************************************/
void computeValues(int board[][9], int possible[], int row, int col)
{
   // initialize possible values array
   int value = 0;

   for (int i = 0; i < 9; i++)
	  possible[i] = i + 1; // indexes 0-8 hold values 1-9
						   // index + 1 = the value it holds
						 
   // check row
   for (int c = 0; c < 9; c++)
   {
	  value = board[row][c];
	  if (value != 0)             // if a non-zero value is present,
		 possible[value - 1] = 0; // set index = 0
   }

   // check col
   for (int r = 0; r < 9; r++)
   {
	  value = board[r][col];
	  if (value != 0)           // index always set to 0 if value != 0
		 possible[value - 1] = 0; // bc its not a possible option anymore
   }
   
   // check 3 x 3 grid
   int startRow = (row / 3) * 3; // determines starting point of grid
   int startCol = (col / 3) * 3;

   int endRow = startRow + 3; // determines ending point of grid
   int endCol = startCol + 3;

   for (int r = startRow; r < endRow; r++)
	  for (int c = startCol; c < endCol; c++)
	  {
		 value = board[r][c];
		 if (value != 0)
			possible[value - 1] = 0;
	  }
}

/***********************************************************************
 * DISPLAY POSSIBLE VALUES
 * Runs through a series of checks. If all are met, displays the set
 * of possible values for the coordinates given by the user.
 ***********************************************************************/
void displayPossibleValues(int board[][9])
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
		cout << "Press 'S' to try again.\n";
		return;
	}

	// check if square is filled
	if (isCoordFilled(board, row, col))
	{
		cout << "ERROR: Square '" << coordinates << "' is filled.\n";
		cout << "Press 'S' to try again.\n";
		return;
	}
	
	// array for storing possible values
    int possible[9];
	
	// populates possible array w/possible values
    computeValues(board, possible, row, col);

    cout << "The possible values for '" << coordinates << "' are: ";
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

    cout << values << endl;
}

/***********************************************************************
 * SET ROW COLUMN
 * Sets the integer value of the row and the column that each
 * corresponds the given coordinates.
 ***********************************************************************/
void setRowCol(string &coordinates, int &row, int &col)
{
	char cRow;
	char cCol;

	if (isalpha(coordinates[0])) // if a1 or A1
	{
		cCol = toupper(coordinates[0]); // A
		cRow = coordinates[1]; // 1
	}
	else  // 1a or 1A
	{
		cCol = toupper(coordinates[1]); // A
		cRow = coordinates[0]; // 1
	}


	// convert characters cRow and cCol
	// to integer values row and col
	row = int(cRow) - 49;
	col = int(cCol) - 65;
	
	
	// correct coordinates order for otherwise valid coordinates.
	if (isCoordValid(row, col) && isalpha(coordinates[1]))
	{
		coordinates = "";
		coordinates += cCol;
		coordinates += cRow;
	}
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
 * This version is used for testing purposes where a value is needed.
 ***********************************************************************/
string test_displayPossibleValues(int board[][9], string coordinates, int row, int col, int value)
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

	cout << "The possible values for '" << coordinates << "' are: ";
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
	
	return values;
}

/***********************************************************************
 * TEST DISPLAY POSSIBLE VALUES - INVALID COORDINATE
 * Runs coordinates through a series of checks before computing possible values.
 * This version  is used only when the provided coordinates are expected
 * to fail (so it doesn't try to check possible values).
 ***********************************************************************/
string test_displayPossibleValues_invalidCoord(int board[][9], string coordinates, int row, int col)
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

	cout << "The possible values for '" << coordinates << "' are: ";
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
		
	return values;
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
 *  TEST CASE 1: DISPLAY BOARD
 ***********************************************************************/
void test_displayBoard()
{
	
}

/***********************************************************************
 *  TEST CASE 2
 *  UPDATE BOARD
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
		cout << "4 was added to square 'E1'.\nTest Case 2 has passed.\n\n";
	}
	else
		cout << "Test Case 2 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 3 - DOUBLE NUMBER INPUT
 *  Exercises the editSquare function.
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
		cout << "Square '11' is invalid.\nTest Case 3 has Passed.\n\n";
	else
		cout << "Test Case 3 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 4 - DOUBLE LETTER INPUT
 *  Exercises the editSquare function.
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
		cout << "Square 'BB' is invalid.\nTest Case 4 has Passed.\n\n";
	else
		cout << "Test Case 4 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 5 - REVERSE INPUT ORDER
 *  Exercises the editSquare function.
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
		cout << msg << "\nTest Case 5 has Passed.\n\n";
	else
		cout << "Test Case 5 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 6 - FILLED COORDINATE
 *  Exercises the editSquare function.
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
		cout << "Square 'B1' is filled.\nTest Case 6 has Passed.\n\n";
	else
		cout << "Test Case 6 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 7 - TWO NUMBER INPUT
 *  Exercises the displayPossibleValues function.
 ***********************************************************************/
void test_possValues_twoNumInput(int board[][9])
{
	string coordinates = "22";
 
	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	// must check if coord is valid before displaying possible values
	string msg = test_displayPossibleValues_invalidCoord(board, coordinates, row, col);
	
	assert(msg == "ERROR: Square '22' is invalid.");
	
	if (msg == "ERROR: Square '22' is invalid.")
		cout << "Square '22' is invalid.\nTest Case 7 has Passed.\n\n";
	else
		cout << "Test Case 7 has Failed.\n\n";
	
}

/***********************************************************************
 *  TEST CASE 8 - TWO LETTER INPUT
 *  Exercises the computeValues function.
 ***********************************************************************/
void test_possValues_twoLetterInput(int board[][9])
{
	string coordinates = "DD";
 
	int row;
	int col;
	setRowCol(coordinates, row, col);
	
	// must check if coord is valid before editing it
	string msg = test_displayPossibleValues_invalidCoord(board, coordinates, row, col);
	
	assert(msg == "ERROR: Square 'DD' is invalid.");
	
	if (msg == "ERROR: Square 'DD' is invalid.")
		cout << "Square 'DD' is invalid.\nTest Case 8 has Passed.\n\n";
	else
		cout << "Test Case 8 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 9 - COORDINATE FILLED
 *  Exercises the computeValues function.
 ***********************************************************************/
void test_possValues_coordinateFilled(int board[][9])
{
	
}

/***********************************************************************
 *  TEST CASE 10 - INCORRECT ORDER
 *  Exercises the computeValues function.
 ***********************************************************************/
void test_possValues_incorrectOrder(int board[][9])
{
	
}

/***********************************************************************
 *  TEST CASE 11 - SAVE SUDOKU BOARD
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 12
 ***********************************************************************/

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
bool isCoordFilled(int row, int col);
void computeValues(int board[][9], int possible[], int row, int col);
void displayPossibleValues(int board[][9]);
int getRow(string coordinates);
int getCol(string coordinates);
int promptValue(string coordinates);
void editSquare(int board[][9]);
string test_editSquare(int board[][9], string coordinates, int row, int col); // for general testing purposes
bool interact(int board[][9]);
bool test_interact(int board[][9], char input);           // for general testing purposes
bool writeFile(int board[][9], string newFile);
void test_doubleNumInput(int board[][9]);                 // test case 1

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
	
	// run test case 1
	test_doubleNumInput(board);
   
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
bool isCoordFilled(int row, int col)
{
   if (row > 0 || col > 0)
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
   char cRow;
   char cCol;
   int row;
   int col;
   
   // get coordinates
   string coordinates = getCoordinates();
   
   for (int i = 0; i < coordinates.length(); i++)
   {
	  if (isalpha(coordinates[0])) // if a1
	  {
		 cCol = toupper(coordinates[0]); // A
		 cRow = toupper(coordinates[1]); // 1
	  }
	  else  // 1a
	  {
		 cCol = toupper(coordinates[1]); // A
		 cRow = toupper(coordinates[0]); // 1
	  }
   }

   // convert characters cRow and cCol
   // to integer values row and col
   row = int(cRow) - 49;
   col = int(cCol) - 65;

   // coordinates cannot be out of range
   if (!isCoordValid(row, col))
   {
	  cout << "ERROR: Square '" << coordinates << "' is invalid\n";
	  getCoordinates();
   }

  
   int possible[9]; // array for storing possible values
   computeValues(board, possible, row, col); // gets possible values

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
 * GET ROW
 * Returns integer value of the row that corresponds to
 * the given coordinates.
 ***********************************************************************/
int getRow(string coordinates)
{
	// N stands for nothing - cRow uninitialized
	char cRow = 'N';
	
	// -1 stands for uninitialized int
	int row = -1;
	
	for (int i = 0; i < coordinates.length(); i++)
	{
		// the row should always correspond to the
		// coordinate number
	   if (isalpha(coordinates[0])) // if a1 or A1
	   {
		  cRow = coordinates[1];
	   }
	   else  // 1a or 1A
	   {
		  cRow = coordinates[0];
	   }
	}
	// convert cRow character to int using
	// ASCII table
	row = int(cRow) - 49;

	return row;
}

/***********************************************************************
 * GET COL
 * Returns integer value of the column that corresponds to
 * the given coordinates.
 ***********************************************************************/
int getCol(string coordinates)
{
	// N stands for nothing - cCol uninitialized
	char cCol = 'N';
	
	// -1 stands for uninitialized int
	int col = -1;
	
	// the column should always correspond to the
	// coordinate letter
	for (int i = 0; i < coordinates.length(); i++)
	{
	   if (isalpha(coordinates[0])) // if a1 or A1
	   {
		  cCol = toupper(coordinates[0]); // A
	   }
	   else  // 1a or 1A
	   {
		  cCol = toupper(coordinates[1]); // A
	   }
	}
	
	// convert cCol character to int using
	// ASCII table
	col = int(cCol) - 65;

	return col;

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
	
	int row = getRow(coordinates);
	int col = getCol(coordinates);
 
   // coordinates cannot be out of range
   if (!isCoordValid(row, col))
   {
	   cout << "ERROR: Square '" << coordinates << "' is invalid\n";
	   return;
   }

   // check if square is filled
   if (!isCoordFilled(row, col))
   {
	  cout << "ERROR: Square '" << coordinates << "' is filled\n";
	  return;
   }
	  
	int value = promptValue(coordinates);

   // check if value is in range
   if (value < 0 || value > 9)
   {
	  cout << "ERROR: Value '" << value << "' in square '" << coordinates
		   << "' is invalid\n";
	  return;
   }

   int possible[9];
   computeValues(board, possible, row, col); // check if chosen value
											 // has already been used

   if (possible[value - 1] == 0) // index will be set to 0 if value is used
   {
	  cout << "ERROR: Value '" << value << "' in square '" << coordinates
		   << "' is invalid\n";
	  return;
   }

   // add value to its coordinate location
   board[row][col] = value;
	   
}

/***********************************************************************
 * TEST EDIT SQUARE
 * Runs coordinates through a series of checks. This version of
 * editSquare is used for testing purposes.
 ***********************************************************************/
string test_editSquare(int board[][9], string coordinates, int row, int col)
{
   // coordinates cannot be out of range
   if (!isCoordValid(row, col))
   {
	   string error = "ERROR: Square '" + coordinates + "' is invalid\n";
	   return error;
   }
	
	// check if square is filled
	if (!isCoordFilled(row, col))
	{
		string error = "ERROR: Square '" + coordinates + "' is filled\n";
		return error;
    }
	  
	int value = promptValue(coordinates);

   // check if value is in range
   if (value < 0 || value > 9)
   {
	   string error = "ERROR: Value '" + std::to_string(value) + "' in square '" + coordinates
	   + "' is invalid\n";
	   return error;
   }

   int possible[9];
   computeValues(board, possible, row, col); // check if chosen value
											 // has already been used

   if (possible[value - 1] == 0) // index will be set to 0 if value is used
   {
	   string error = "ERROR: Value '" + std::to_string(value) + "' in square '" + coordinates
	   + "' is invalid\n";
	   return error;
   }
	
	// add value to its coordinate location
    board[row][col] = value;
	
	string pass = "The square can be edited\n";
	return pass;
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
* TEST INTERACT
* User chooses their input from a series of options. This version of interact is
* used for testing purposes.
***********************************************************************/
bool test_interact(int board[][9], char input, string coordinates,
				   int row, int col)
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
 * WRITE BOARD
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
 *  TEST CASE 1: DISPLAY BOARD
 ***********************************************************************/
void test_displayBoard()
{
	
}
/***********************************************************************
 *  TEST CASE 2: UPDATE BOARD
 ***********************************************************************/
void test_updateBoard()
{
	
}
/***********************************************************************
 *  TEST CASE 3: DOUBLE NUMBER INPUT
 ***********************************************************************/
void test_doubleNumInput(int board[][9])
{
	
	string coordinates = "11";
	int row = getRow(coordinates);
	int col = getCol(coordinates);
	
	// attempts to edit at coordinate 11 - which is invalid
	string msg = test_editSquare(board, coordinates, row, col);
	
	assert(msg == "ERROR: Square '11' is invalid");
	
	if (msg == "ERROR: Square '11' is invalid")
		cout << "Test Case 3 has Passed." << endl;
	else
		cout << "Test Case 3 has Failed." << endl;
  
}
/***********************************************************************
 *  TEST CASE 4: DOUBLE LETTER INPUT
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 5: REVERSE INPUT ORDER
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 6: FILLED COORDINATE
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 7
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 8
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 9
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 10
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 11
 ***********************************************************************/

/***********************************************************************
 *  TEST CASE 12
 ***********************************************************************/

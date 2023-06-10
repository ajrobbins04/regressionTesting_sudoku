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
	void displayPossibleValues();
	
	bool readFile(string fileName);
	bool isCoordFilled(int row, int col);

	
private:
	vector<vector<int>> board;
	
};

#endif

/*************************************************
 *  INITIALIZE BOARD
 *	Sets all attributes for the Board class.
***********************************************************************/
void Board::initializeBoard(string fileName)
{
	// read the file
    if (!readFile(fileName))
    {
	   // handle possible errors
	   cout << "ERROR: Unable to open " << fileName << endl;
	   return;
    }
	else
	{
		
	}
}

/***********************************************************************
 * READ FILE
 * Moves the sudoku data from its file to the
 * board array.
 ***********************************************************************/
bool Board::readFile(string fileName)
{
	// open file
	ifstream fin(fileName);
	if (fin.fail())
		return false;
 
	
	for ( string line; getline( fin, line ); )
	{
		stringstream ss(line);
		
		// holds row data
		vector <int> row;
		for ( int value; ss >> value; )
		{
			row.push_back(value);
			board.push_back(row);
		}
	}

   // close file
   fin.close();
   return true;

}

/***********************************************************************
 * DISPLAY BOARD
 * Displays the sudoku board fully-formatted.
 ***********************************************************************/
void Board::displayBoard()
{
   
   // create column header
   cout << "   A B C D E F G H I\n";
   
   for (int row = 0; row < num_rows; row++)
   {
	  cout << row + 1 << "  "; // two spaces between each square

	  for (int col = 0; col < num_cols; col++)
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
 * IS COORD FILLED
 * Checks that the coordinate hasn't already
 * been filled.
 ***********************************************************************/
bool Board::isCoordFilled(int row, int col)
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
void Board::computeValues(vector<int> &possible, int row, int col)
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
void Board::displayPossibleValues()
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

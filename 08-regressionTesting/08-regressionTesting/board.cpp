#include "board.h"

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
		cout << "Board successfully read from file\n";
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
 * Shows available options carried out by the board to
 * play sudoku.
 ***********************************************************************/
void Board::displayOptions()
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
 * INTERACT
 * User chooses their input from a series of options
 ***********************************************************************/
bool Board::interact()
{
   char input;
   cout << "> ";
   cin >> input;
	  
   input = toupper(input);

   switch (input)
   {
	  case '?':
		 displayOptions();       // show list of options
		 cout << endl << endl;
		 return true;
	  case 'D':
		 displayBoard();         // show sudoku board
		 cout << endl;
		 return true;
	  case 'E':
		 editSquare();           // add new value onto board
		 cout << endl;           // then return to main interface
		 displayBoard();
		 cout << endl;
		 displayOptions();
		 cout << endl;
		 return true;
	  case 'S':
		 displayPossibleValues(); // show possible values
		 cout << endl;            // then return to main interface
		 displayBoard();
		 cout << endl;
		 displayOptions();
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
 * COMPUTE VALUES
 * Identifies possible values in each row, column,
 * and 3x3 square of the sudoku board.
 ***********************************************************************/
void Board::computeValues(vector<int> &possible, int row, int col)
{
   // initialize possible values array
   int value = 0;

   for (int i = 0; i < 9; i++)
	   possible.push_back(i + 1); // indexes 0-8 hold values 1-9
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
 * PROMPT VALUE
 * Returns the value that the user wants to place in a
 * given coordinate on the board.
 ***********************************************************************/
int Board::promptValue(string coord)
{
	// default value
	int value = -1;
	// get value at coordinate location
	cout << "What is the value at '" << coord << "': ";
	cin >> value;
	
	return value;
}


/***********************************************************************
 * DISPLAY POSSIBLE VALUES
 * Displays a set of possible values for a given coordinate.
 * displayPossibleValues is currenlty its only caller function.
 ***********************************************************************/
string Board::displayPossibleValues()
{
	// create and initialize coordinate
	Coordinate coordinate = Coordinate();

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
 
	// coordinates cannot be out of range
	if (!coordinate.isCoordValid())
	{
		string errorMsg = "ERROR: Square '" + coord + "' is invalid.\nPress 'S' to try again.\n\n";
		return errorMsg;
	}

	// check if square is filled
	if (coordinate.isCoordFilled(board))
	{
		string errorMsg = "ERROR: Square '" + coord + "' is filled.\nPress 'S' to try again.\n\n";
		return errorMsg;
	}
	
	// vector to store possible values
	vector<int> possible;
	
	// populates possible array w/possible values
	computeValues(possible, row, col);

	string values;

	for (int i = 0; i < 9; i++)
	{
	   if (possible[i] != 0) // cannot be filled already
	   {
		   // add possible values to string of values
		  values += to_string(possible[i]) + ", ";
	   }
	}
	values.pop_back(); //removes ", " after last value
	values.pop_back();
	
	string valuesMsg = "The possible values for '" + coord + "' are: " + values + "\n\n";

	return valuesMsg;

}

/***********************************************************************
 * EDIT SQUARE
 * Runs coordinates through a series of checks. If all are met,
 * value is added to the corresponding square on the board
 ***********************************************************************/
string Board::editSquare()
{
	// create and initialize coordinate
	Coordinate coordinate = Coordinate();
	
	// will prompt for and set a coordinate
	coordinate.initialize();
	
	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
 
	// coordinates cannot be out of range
	if (!coordinate.isCoordValid())
	{
		string errorMsg = "ERROR: Square '" + coord + "' is invalid.\nPress 'S' to try again.\n\n";
		return errorMsg;
	}

	// check if square is filled
	if (coordinate.isCoordFilled(board))
	{
		string errorMsg = "ERROR: Square '" + coord + "' is filled.\nPress 'S' to try again.\n\n";
		return errorMsg;
	}
	
	int value = promptValue(coord);
	string strValue = std::to_string(value);
	
	// check if value is in range
	if (value < 0 || value > 9)
	{
		string errorMsg =
		"ERROR: Value '" + strValue + "' in square '" + coord + "' is invalid.\nPress 'E' to try again.\n\n";
		return errorMsg;
	}

	// vector to store possible values
	vector<int> possible;
	
	// populates possible vector w/possible values
	computeValues(possible, row, col);

	for (int i = 0; i < possible.size(); i++)
	{
	   if (possible[i] == value) // can edit the square
	   {
		   board[row][col] = value;
	   }
	}
	
	string editMsg = strValue + "successfully place in square '" + coord + "'.\n\n";
	
	return editMsg;

}

/**********************************************************************
 * GET FILE NAME
 * Gets the name of the file containing the sudoku game, or
 * it gets the name of the file that the game will be written to.
 ***********************************************************************/
string Board::promptFileName()
{
	string fileName;
	
	cout << "What file would you like to write your board to: ";
	cin >> fileName;
	
	return fileName;
}
/***********************************************************************
 * WRITE FILE
 * Write the sudoku board to its destination file.
 ***********************************************************************/
bool Board::writeFile(string fileName)
{
   // open file
   ofstream fout(fileName);
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


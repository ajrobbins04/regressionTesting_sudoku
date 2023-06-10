#include "testBoard.h"

/***********************************************************************
 * RUN
 * Runs all 13 test cases;
 ***********************************************************************/
void TestBoard::run()
{
	test_updateBoard();
	test_correctLowercaseInput();
	test_updatePossValues();
	test_doubleNumInput();
	test_doubleLetterInput();
	test_reverseInputOrder();
	test_filledCoordinate();
	test_possValues_twoNumInput();
	test_possValues_twoLetterInput();
	test_possValues_coordinateFilled();
	test_possValues_incorrectOrder();
	test_saveSudokuBoard();
	test_readFile();
}

/*************************************************
 *  INITIALIZE TEST BOARD
 *	Sets all attributes for the TestBoard class.
***********************************************************************/
void TestBoard::initializeTestBoard(string fileName)
{
	// read the file
	if (!readTestFile(fileName))
	{
	    // handle possible errors
	    cout << "ERROR: Unable to open " << fileName << endl;
	    return;
	}
	else
		return;
}

/***********************************************************************
 * TEST DISPLAY BOARD
 * Displays the sudoku board fully-formatted.
 ***********************************************************************/
void TestBoard::test_displayBoard()
{
   
   // create column header
   cout << "   A B C D E F G H I\n";
   
   for (int row = 0; row < num_rows; row++)
   {
	  cout << row + 1 << "  "; // two spaces between each square

	  for (int col = 0; col < num_cols; col++)
	  {
		 if (tBoard[row][col] == 0) // 0 denotes empty square
			cout << " ";
		 else
			cout << tBoard[row][col];

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
 * READ TEST FILE
 * Moves the sudoku data from its file to the
 * board array.
 ***********************************************************************/
bool TestBoard::readTestFile(string fileName)
{
	// open file
	ifstream fin(fileName);
	if (fin.fail())
	   return false;

	// read file into board
	for (int row = 0; row < 9; row++)
	   for (int col = 0; col < 9; col++)
	   {
		  fin >> tBoard[row][col];
	   }

	// close file
	fin.close();
	return true;
}

/***********************************************************************
 * WRITE TEST FILE
 * Write the sudoku board to its destination file.
 ***********************************************************************/
bool TestBoard::writeTestFile(string fileName)
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
		 
		 fout << tBoard[row][col] << " ";
	  }
   }
   // close file
   fout.close();
   return true;
}


/***********************************************************************
* TEST INTERACT
* User chooses their input from a series of options. This version of interact is
* used for general testing purposes.
***********************************************************************/
bool TestBoard::test_interact(char input)
{
	input = toupper(input);

	switch (input)
	{
	   case '?':
		  displayOptions();        // show list of options
		  cout << endl << endl;
		  return true;
	   case 'D':
		  test_displayBoard();     // show sudoku board
		  cout << endl;
		  return true;
	   case 'E':
		  editSquare();            // add new value onto board
		  return true;
	   case 'S':
		  displayPossibleValues(); // show possible values
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
 * TEST INTERACT - INPUT E
 * User chooses their input from a series of options
 ***********************************************************************/
bool TestBoard::test_interact_inputE(char input, Coordinate &coord, int value)
{
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
		 test_editSquare(coord, value);   // add new value onto board
		 cout << endl;
		 return true;
	  case 'S':
		 displayPossibleValues(); // show possible values
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
 * TEST INTERACT - INPUT E - INVALID
 * This version of interact will called test_editSquare_invalidCoord
 * instead of test_editSquare.
 * ***********************************************************************/
bool TestBoard::test_interact_inputE_invalid(char input, Coordinate &coord)
{
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
		 test_editSquare_invalidCoord(coord);
		 cout << endl;
		 test_displayBoard();
		 cout << endl;
		 displayOptions();
		 cout << endl;
		 return true;
	  case 'S':
		 displayPossibleValues(); // show possible values
		 cout << endl;            // then return to main interface
		 test_displayBoard();
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
 * TEST EDIT SQUARE
 * Runs coordinates through a series of checks. This version of
 * editSquare is used for testing purposes where a Coordinate object
 * and value are needed. The program would normally prompt the user.
 ***********************************************************************/
string TestBoard::test_editSquare(Coordinate &coordinate, int value)
{
	
	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
 
	// coordinates cannot be out of range
	if (!coordinate.isCoordValid())
	{
		string error = "ERROR: Square '" + coord + "' is invalid.";
		return error;
	}

	// check if square is filled
	if (coordinate.isCoordFilled(tBoard))
	{
		string error = "ERROR: Square '" + coord + "' is filled.";
		return error;
	}
	
	string strValue = std::to_string(value);
	
	// check if value is in range
	if (value < 0 || value > 9)
	{
		string error = "ERROR: Value '" + std::to_string(value) + "' in square '"
		+ coord + "' is invalid.";
		return error;
	}

	// vector to store possible values
	vector<int> possible;
	
	// populates possible vector w/possible values
	computeValues(possible, row, col);

	for (int i = 0; i < possible.size(); i++)
	{
	   if (possible[i] == value) // can edit the square
	   {
		   tBoard[row][col] = value;
	   }
	}
	
	string passMsg = "The square at '" + coord + "' was filled using " + strValue + ".";
	return passMsg;

}

/***********************************************************************
 * TEST EDIT SQUARE - INVALID COORD
 * Runs coordinates through a series of checks. This version of
 * editSquare is used for testing purposes where only a Coordinate object
 * is needed since the coordinate doesn't qualify to receive a value
 ***********************************************************************/
string TestBoard::test_editSquare_invalidCoord(Coordinate &coordinate)
{
	string coord = coordinate.getCoord();
 
	// coordinates cannot be out of range
	if (!coordinate.isCoordValid())
	{
		string error = "ERROR: Square '" + coord + "' is invalid.";
		return error;
	}

	// check if square is filled
	if (coordinate.isCoordFilled(tBoard))
	{
		string error = "ERROR: Square '" + coord + "' is filled.";
		return error;
	}
	

	string passMsg = "The square at '" + coord + "' can be edited.";
	return passMsg;

}

/***********************************************************************
 * TEST DISPLAY POSSIBLE VALUES
 * Runs coordinates through a series of checks before computing possible values.
 ***********************************************************************/
string TestBoard::test_displayPossibleValues(Coordinate &coordinate)
{
	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
 
	// coordinates cannot be out of range
	if (!coordinate.isCoordValid())
	{
		string error = "ERROR: Square '" + coord + "' is invalid.";
		return error;
	}

	// check if square is filled
	if (coordinate.isCoordFilled(tBoard))
	{
		string error = "ERROR: Square '" + coord + "' is filled.";
		return error;
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
	
	string valuesMsg = "The possible values at square '" + coord + "' are: " + values;

	return valuesMsg;
}

/***********************************************************************
 *  TEST CASE 1 - UPDATE BOARD
 *  Verify that the board registers and displays updated squares
 *  that have been filled in.
 ***********************************************************************/
void TestBoard::test_updateBoard()
{
	Coordinate coordinate = Coordinate("E1");

	// get coordinate's row and column values
	int row = coordinate.getRow();
	int col = coordinate.getCol();
	
	// E1 is currently empty
	assert(tBoard[row][col] == 0);

	// call editSquare from within its caller function
	test_interact_inputE('E', coordinate, 4);
	
	// display the new board
	test_interact('D');
	
	// E1 is now filled using 4
	assert(tBoard[row][col] == 4);
	
	if (tBoard[row][col] == 4)
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
void TestBoard::test_correctLowercaseInput()
{
	Coordinate coordinate = Coordinate("i5");
	
	string coord = coordinate.getCoord();
	
	// must check if coord is valid before displaying possible values
	string msg = test_displayPossibleValues(coordinate);
	
	assert(coord == "I5");
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
void TestBoard::test_updatePossValues()
{
	Coordinate coordinate = Coordinate("E5");

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();

	// only possible value should be 8
	string msg = test_displayPossibleValues(coordinate);
	
	assert(msg == "The possible values at square 'E5' are: 8");
	
	if (msg == "The possible values at square 'E5' are: 8")
	{
		// edit the board at "E5" using 8
		test_interact_inputE('E', coordinate, 8);

		// check the possible values at "E5" again
		string msg = test_displayPossibleValues(coordinate);
		
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
void TestBoard::test_doubleNumInput()
{
	Coordinate coordinate = Coordinate("11");

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
	
	// must check if coord is valid before editing it
	string msg = test_editSquare_invalidCoord(coordinate);
	
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
void TestBoard::test_doubleLetterInput()
{
	Coordinate coordinate = Coordinate("BB");

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
	
	// must check if coord is valid before editing it
	string msg = test_editSquare_invalidCoord(coordinate);
	
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
void TestBoard::test_reverseInputOrder()
{
	// given in reverse order
	Coordinate coordinate = Coordinate("2B");

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
 

	// must check if coord is valid before editing it.
	// 1 is included in parameter b/c coord can be edited, so it needs a value.
	string msg = test_editSquare(coordinate, 1);
	
	// check that coordinate order is fixed.
	assert(msg == "The square at 'B2' was filled using 1.");
	
	if (msg == "The square at 'B2' was filled using 1.")
		cout << msg << "\nTest Case 6 has Passed.\n\n";
	else
		cout << "Test Case 6 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 7 - FILLED COORDINATE
 *  Checks if the coordinate is already occupied from within
 *  the editSquare function.
 ***********************************************************************/
void TestBoard::test_filledCoordinate()
{
	// not valid b/c B1 is already filled
	Coordinate coordinate = Coordinate("B1");

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
 
 
	string msg = test_editSquare_invalidCoord(coordinate);
	
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
void TestBoard::test_possValues_twoNumInput()
{
	// not valid b/c B1 is already filled
	Coordinate coordinate = Coordinate("22");

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
	
	// must check if coord is valid before displaying possible values
	string msg = test_displayPossibleValues(coordinate);
	
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
void TestBoard::test_possValues_twoLetterInput()
{
	// not valid b/c B1 is already filled
	Coordinate coordinate = Coordinate("DD");

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();
	
	// must check if coord is valid before editing it
	string msg = test_displayPossibleValues(coordinate);
	
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
void TestBoard::test_possValues_coordinateFilled()
{
	// not valid b/c B1 is already filled
	Coordinate coordinate = Coordinate("I9");
	string coord = coordinate.getCoord();
  
	string msg = test_displayPossibleValues(coordinate);
	
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
void TestBoard::test_possValues_incorrectOrder()
{
	// given in reverse order
	Coordinate coordinate = Coordinate("4A");

	string coord = coordinate.getCoord();
	int row = coordinate.getRow();
	int col = coordinate.getCol();

	// must check if coord is valid before editing it.
	// value is included in parameter b/c coord can be edited, so it needs a value.
	string msg = test_displayPossibleValues(coordinate);
	
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
void TestBoard::test_saveSudokuBoard()
{
	
	string newFileName = "/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/saveSudoku.txt";
	
	// saves sudoku game changes in a new file
	writeTestFile(newFileName);
	
	string fileName = "/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/sudoku.txt";
	
	// read the orignal sudoku file into a new
	// TestBoard object
	TestBoard original = TestBoard();
	original.initializeTestBoard(fileName);
	
 
	// compare the values at 'D1'. If saved properly,
	// it should now be 4 instead of 0
	assert(writeTestFile(newFileName));
	assert(tBoard[0][4] != original.tBoard[0][4]);
	assert(tBoard[0][4] == 4);
	assert(original.tBoard[0][4] == 0);
	
	if (tBoard[0][4] != original.tBoard[0][4])
		cout << "Sudoku successfully saved with changes to a new file.\nTest Case 12 has Passed.\n\n";
	else
		cout << "Test Case 12 has Failed.\n\n";
}

/***********************************************************************
 *  TEST CASE 13 - READ FILE
 *  Verifies that the sudoku board file containing 9 rows and 9 columns of numbers
 *  can be successfully read into the program and build as a sudoku game.
 ***********************************************************************/
void TestBoard::test_readFile()
{
	
	string altFileName = "/Users/AmberRobbins/CSE-270_softwareTesting/regressionTesting_sudoku/08-regressionTesting/altSudoku.txt";
	TestBoard alternate = TestBoard();
	
	// initialize calls the readTestFile function
	alternate.initializeTestBoard(altFileName);
 
	cout << "Original Board: \n\n";
	displayBoard();
	cout << endl;
	
	cout << "Test Case 13 Board: \n\n";
	alternate.displayBoard();
	cout << endl;

	assert(readTestFile(altFileName));
	
	if (readFile(altFileName) == true)
		cout << "File contents successfully read into the program.\nTest Case 13 has Passed.\n\n";
	else
		cout << "Test Case 13 has Failed.\n\n";

}



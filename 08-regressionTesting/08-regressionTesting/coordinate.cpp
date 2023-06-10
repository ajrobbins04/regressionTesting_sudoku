#include "coordinate.h"

/***********************************************************************
 * INITIALIZE
 * Goes through a series of checks before setting the
 * integer values corresponding to a valid coordinate.
 ***********************************************************************/
void Coordinate::initialize()
{
	// if coordinate was A1, then A would be
	// the column and 1 would be the row.
	string coordinate = promptCoordinate();
	setCoordinate(coordinate);
	
}
/***********************************************************************
 * PROMPT COORDINATE
 * Gets user's chosen coordinate based on the
 * sudoku board.
 ***********************************************************************/
string Coordinate::promptCoordinate() const
{
   // for A1, A is the column and 1 is the row
   string coordinate;
   cout << "What are the coordinates of the square: ";
   cin >> coordinate;

   return coordinate;
}

/**********************************************************************
 * IS COORD VALID
 * Checks that the numerical part of the
 * coordinate is within the range 0 - 8.
 **********************************************************************/
bool Coordinate::isCoordValid() const
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
bool Coordinate::isCoordFilled(int board[][9]) const
{
   if (board[row][col] != 0)
   {
	  return true;
   }
   return false;
}

/***********************************************************************
 * SET COORDINATE
 * Sets the coordinate object's attributes: coord, row, and col.
 ***********************************************************************/
void Coordinate::setCoordinate(string coordinate)
{
	char cRow; // should be num
	char cCol; // should be letter

	if (isalpha(coordinate[0])) // if a1 or A1 format
	{
		cCol = toupper(coordinate[0]);
		cRow = coordinate[1];
		
		// ensure coordinate = A1 format only
		coordinate[0] = cCol;
	}
	else // 1a or 1A format
	{
		cCol = toupper(coordinate[1]);
		cRow = coordinate[0];
		
		// ensure coordinate = A1 format only
		coordinate[0] = cCol;
		coordinate[1] = cRow;
	}
	
	coord = coordinate;

	// convert and set the row and col attributes
	// using cRow and cCol's ascii values
	row = int(cRow) - 49;
	col = int(cCol) - 65;
}
 


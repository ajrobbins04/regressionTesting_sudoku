/***********************************************************************
 *  COORDINATE CLASS
 *  Deals with the coordinates used to specify locations on the
 *  sudoku board.
 ***********************************************************************/
#ifndef coordinate_h
#define coordinate_h

#include <string>

class Coordinate
{
public:
	string promptCoordinates();
	
private:
	int row;
	int col;
};

/***********************************************************************
 * PROMPT COORDINATES
 * Gets users coordinates corresponding to
 * squares on the sudoku board.
 ***********************************************************************/
string Coordinate::promptCoordinates()
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
 * coordinate is within the range 0 - 8.
 **********************************************************************/
bool Coordinate::isCoordValid(int row, int col)
{
   if (row >= 0 && row <= 8 && col >= 0 && col <= 8)
   {
	  return true;
   }
   return false;
}


#endif /* coordinate_h */

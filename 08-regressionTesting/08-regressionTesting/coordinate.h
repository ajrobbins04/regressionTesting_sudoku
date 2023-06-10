/***********************************************************************
 *  COORDINATE CLASS
 *  Deals with the coordinates used to specify locations on the
 *  sudoku board.
 ***********************************************************************/
#ifndef coordinate_h
#define coordinate_h

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Coordinate
{
public:
	Coordinate(): coord(""), row(-1), col(-1) {}
	
	Coordinate(string coord) {
		setCoordinate(coord);
	}
	
	void initialize();
	void setCoordinate(string coordinate);
	
	bool isCoordValid() const;
	bool isCoordFilled(int board[][9]) const;
	
	string promptCoordinate() const;
	string getCoord()         const { return coord; }
	
	int getRow() const { return row; }
	int getCol() const { return col; }
	
private:
	string coord;
	int row;
	int col;
};

#endif


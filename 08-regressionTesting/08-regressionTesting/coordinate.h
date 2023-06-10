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
	void initialize();
	void setCoordinate(string coordinate);
	string promptCoordinate();
	bool isCoordValid();
	
private:
	string coord;
	int row;
	int col;
};

#endif


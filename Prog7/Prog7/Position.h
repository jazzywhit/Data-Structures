#ifndef POSITION_H
#define POSITION_H
/*--------------- P o s i t i o n . h ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This is the interface to Position.cpp.

CHANGES
10-12-2011 gpc - Distributed to 16.322 class.

*/

#include <iostream>
#include <string>

//----- t y p e    d e f i n i t i o n s -----

// Define the 4 compass directions.
typedef enum  {E, S, W, N, NoDir} Direction;

//----- c l a s s    P o s i t i o n -----
class Position
{
public:
   // Constructors
   Position() {defined = false; }
   Position(const int theRow, const int theCol) {row = theRow; col=theCol; defined = true;}

   // Accessors
   int Row(void) const { return row; }
   int Col(void) const { return col; }
   bool Defined(void) { return defined; }

   // Overloaded operators
   Position operator+(const Position &b) const;
   Position operator+=(const Position &b);
   bool operator!=(const Position &b) const { return (row!=b.row) || (col!=b.col); }
   bool operator==(const Position &b) const { return (row==b.row) && (col==b.col); }

private:
   int	row;     // the row (y) location of a position
   int	col;     // the column (x) location of a position
   bool  defined; // True if the position has been defined
};

//----- c o n s t a n t    d e f i n i t i o n s -----

// Offsets to neighboring cells (relative positions)
const Position StepEast = Position(0, +1);   // One step east
const Position StepSouth = Position(+1, 0);  // One step south
const Position StepWest = Position(0, -1);   // One step west
const Position StepNorth = Position(-1, 0);  // One step north

#endif
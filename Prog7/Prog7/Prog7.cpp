/*--------------- P r o g  7. c p p ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
Find a path through a maze.

CHANGES
10-12-2011 gpc - Distributed to 16.322 class.

MODIFIED BY:
Jesse Whitworth 

DATE:
11-2-2011
*/

#include <stdlib.h>
#include <iostream>

using namespace std;

#include "Utility.h"
#include "Maze.h"


/*----- Y o u C a n G e t T h e r e F r o m (  ) -----

PURPOSE
Recursive maze solver.

RETURN VALUE
true  -- A path was found and marked.
false -- No path exists.
*/
bool YouCanGetThereFrom(Maze &maze, Position &curPos){

	Position tmpPos;
	/*
    Algorithm for recursive maze solving.
    1. If the current position is open
        a. Mark the current position Visited.
        b. If the current position is the goal
            i. Wait for the ENTER key to be pressed.
        c. If the current position is the goal or if you can get there from a
            neighbor of the current position
            i. Mark the current position as a Path Cell.
            ii. return true.
        d. Mark the current position Rejected.
    2. You can not get there from here, return false
    */

	if (maze.IsOpen(curPos)){
		maze.Visit(curPos);
		if (curPos == maze.Goal())
			cin.get();
		tmpPos = curPos + StepEast;
		if (curPos == maze.Goal() || YouCanGetThereFrom(maze, tmpPos)){
			maze.MarkPathCell(tmpPos);
			return true;
		}
		tmpPos = curPos + StepSouth;
		if (curPos == maze.Goal() || YouCanGetThereFrom(maze, tmpPos)){
			maze.MarkPathCell(tmpPos);
			return true;
		}
		tmpPos = curPos + StepWest;
		if (curPos == maze.Goal() || YouCanGetThereFrom(maze, tmpPos)){
			maze.MarkPathCell(tmpPos);
			return true;
		}
		tmpPos = curPos + StepNorth;
		if (curPos == maze.Goal() || YouCanGetThereFrom(maze, tmpPos)){
			maze.MarkPathCell(tmpPos);
			return true;
		}
		maze.Reject(curPos);
	}
	return false;
}


/*--------------- m a i n ( ) ---------------*/

void main(void)
{
	// Screen positions
	const unsigned XResult = 15;
	const unsigned YResult = 5;
	const unsigned XFinish = 0;
	const unsigned YFinish = 20;   

	for (;;)
		{
		// Construct a maze from a maze definition file.
		Maze maze;     
		
		Position curPos = maze.Start();     // The current position

		// Traverse the maze.
		bool success = YouCanGetThereFrom(maze, curPos);
		if(success)
			maze.MarkPathCell(curPos);        //Mark the start position as a path if a path was found.

		// Indicate success or failure.
		gotoxy(XResult, YResult);
		if (!success)
			cout << "Failed: No path from start to goal exists." << endl;
		else{
			cout << "Success: Found a path." << endl;
		}
		
		//DONE!!! :D D: D: D: D: :D
		gotoxy(XFinish, YFinish);
		}
}

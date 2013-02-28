/*--------------- P r o g 11 . c p p ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
Find the shortest path through a maze.

CHANGES
10-19-2011 gpc -- Created for 16.322 class.
*/



#include <stdlib.h>
#include <iostream>

using namespace std;

#include "Utility.h"
#include "Queue_T.h"
#include "Maze.h"

/*----- S o l v e M a z e (  ) -----

PURPOSE
Attempt to find the shortest path through the maze.

INPUT PARAMETERS
maze           -- the maze object to be traversed
positionQueue  -- the queue of current and future positions

RETURN VALUE
true  -- a path was found.
false -- failed to find a path.
*/
bool SolveMaze(Maze &maze, Queue<Position> &positionQueue)
{

// COMPLETE THIS FUNCTION.

   return false;
}

/*----- R e t r a c e P a t h (  ) -----

PURPOSE
Mark the path from the goal to the start cell.

INPUT PARAMETERS
maze           -- the maze object to be marked
*/
void RetracePath(Maze &maze)
{

// COMPLETE THIS FUNCTION.

}

/*--------------- m a i n ( ) ---------------*/

void main(void)
{
   // Screen positions
   const unsigned XResult = 35;
   const unsigned YResult = 5;
   const unsigned XFinish = 35;
   const unsigned YFinish = 10;

	for (;;)
		{
	   // Construct a maze from a maze definition file.
	   Maze  maze;

	   // Queue of future positions to visit
	   Queue<Position> positionQueue;

		// Solve the maze.
		bool success = SolveMaze(maze, positionQueue);

		// Indicate success or failure.
		gotoxy(XResult, YResult);

		if (!success)
			cout << "Failed: No path from start to goal exists." << endl;
		else
			{
			cout << "Success: Found the shortest path." << endl;
			gotoxy(XResult, YResult+2);
			cout << "Press ENTER to highlight the shortest path.";
			cin.get();

			RetracePath(maze);
			}

		// Done
		gotoxy(XFinish, YFinish);
		cout << "Press ENTER to continue...";
		cin.get();
		clrscr();
		}
}
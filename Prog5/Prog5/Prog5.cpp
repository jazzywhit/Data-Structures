/*--------------- P r o g 5 . c p p ---------------

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
*/

#include <stdlib.h>
#include <iostream>

using namespace std;

#include "Utility.h"
#include "Maze.h"


/*----- S o l v e M a z e (  ) -----

PURPOSE
Non-Naive maze traversal algorithm based on the provided pseudo code.

RETURN VALUE
true  -- a solution was found.
false -- failed to find a solution.
*/
bool SolveMaze(Maze &maze, Stack &stack)
{
   Position curPos = maze.Start();     // The current position
   stack.Push(curPos);
   maze.Visit(curPos);

   // Repeatedly find a next move until the goal is reached.
   for (;;){
	   if (curPos == maze.Goal()){
		   return true;
	   }else{
			if (maze.IsOpen(curPos + StepEast))
				curPos += StepEast;
			else if (maze.IsOpen(curPos + StepSouth))
				curPos = curPos + StepSouth;
			else if (maze.IsOpen(curPos + StepWest))
				curPos = curPos + StepWest;
			else if (maze.IsOpen(curPos + StepNorth))
				curPos = curPos + StepNorth;
			else{
				maze.Reject(curPos);
				curPos = stack.Pop();
				if (stack.Empty())
					return false;
				continue;
			}
			stack.Push(curPos);
			maze.Visit(curPos);
	   }
	}
}


/*--------------- m a i n ( ) ---------------*/

void main(void)
{
	// Screen positions
	const unsigned XResult = 15;
	const unsigned YResult = 5;
	const unsigned XFinish = 0;
	const unsigned YFinish = 20;

	// Position stack remembers visited positons.
	Stack posStack;   

	for (;;)
		{
		// Construct a maze from a maze definition file.
		Maze maze;     
   
		// Traverse the maze.
		bool success = SolveMaze(maze, posStack);
		// Indicate success or failure.
		gotoxy(XResult, YResult);
		if (!success)
			cout << "Failed: No path from start to goal exists." << endl;
		else
		   {
			cout << "Success: Found a path." << endl;
			
			cin.get();  // Wait for a key press.
			
      // Retrace the path back to the goal.
			while (!posStack.Empty())
			   maze.MarkPathCell(posStack.Pop());
			 }
		// Done
		gotoxy(XFinish, YFinish);
		}
}
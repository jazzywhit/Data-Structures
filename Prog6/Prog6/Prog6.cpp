/*--------------- P r o g 6 . c p p ---------------

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
#include "Maze.h"


/*----- n e x t O p e n P o s i t i o n (  ) -----

PURPOSE
Attempt to find the shortest path through the maze.

INPUT PARAMETERS
maze           -- the maze object to be traversed
positionQueue  -- the queue of current and future positions

RETURN VALUE
true  -- a path was found.
false -- failed to find a path.
*/
Position openPosition(Maze &maze, Position curPos){
	if (maze.State(curPos + StepEast) == Open)
		curPos = curPos + StepEast;
	else if (maze.State(curPos + StepSouth) == Open)
		curPos = curPos + StepSouth;
	else if (maze.State(curPos + StepWest) == Open)
		curPos = curPos + StepWest;
	else if (maze.State(curPos + StepNorth) == Open)
		curPos = curPos + StepNorth;
	return curPos;
}

/*----- n e x t O p e n P o s i t i o n (  ) -----

PURPOSE
Attempt to find the shortest path through the maze.

INPUT PARAMETERS
maze           -- the maze object to be traversed
positionQueue  -- the queue of current and future positions

RETURN VALUE
true  -- a path was found.
false -- failed to find a path.
*/
Position pathCheck(Maze &maze, Position curPos, const int &distance){
	Position tmpPos = curPos;
	int bestDistance = distance;

	int distanceCheck = maze.State(curPos + StepEast);
	if (distanceCheck > Open)
		if (distanceCheck < bestDistance){
			tmpPos = curPos + StepEast;
			bestDistance = distanceCheck;
		}

	distanceCheck = maze.State(curPos + StepSouth);
	if (distanceCheck > Open)
		if (distanceCheck < bestDistance){
			tmpPos = curPos + StepSouth;
			bestDistance = distanceCheck;
		}

	distanceCheck = maze.State(curPos + StepWest);
	if (distanceCheck > Open)
		if (distanceCheck < bestDistance){
			tmpPos = curPos + StepWest;
			bestDistance = distanceCheck;
		}

	distanceCheck = maze.State(curPos + StepNorth);
	if (distanceCheck > Open)
		if (distanceCheck < bestDistance){
			tmpPos = curPos + StepNorth;
			bestDistance = distanceCheck;
		}

	return tmpPos;
}

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
bool SolveMaze(Maze &maze, Queue &positionQueue)
{
/*
const int Open     = -1;	// Cell is open
const int Obstacle = -2;	// Cell is an obstacle
const int StartCell= -3;	// Cell is the start cell
const int GoalCell = -4;	// Cell is the goal cell
const int PathCell = -5;	// Cell is on the shortest path
*/ 
	Position curPos = maze.Start();
	Position neighbor;
	positionQueue.Enqueue(curPos);
	maze.Mark(curPos, 0);
	int distance;

	while(!positionQueue.Empty()){
		curPos = positionQueue.Dequeue();
		distance = maze.State(curPos);
		neighbor = openPosition(maze, curPos);
		while(curPos != neighbor){
			maze.Mark(neighbor, distance + 1);
			if(neighbor == maze.Goal())
				return true;
			positionQueue.Enqueue(neighbor);
			neighbor = openPosition(maze, curPos);
		}
	}
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
	Position curPos = maze.Goal();  //This function is used on complete mazes.
	Position neighbor;
	int distance;

	do{
		distance = maze.State(curPos);
		maze.Mark(curPos, PathCell);
		do{
			neighbor = pathCheck(maze, curPos,distance);
			if (maze.State(neighbor) < distance || distance == 0){
				curPos = neighbor;
				break;
			}		
		}while(curPos != neighbor);
	}while(distance > 0);
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
	   Queue positionQueue;

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
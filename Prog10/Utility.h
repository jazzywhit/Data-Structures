#ifndef CONSOLE_H
#define CONSOLE_H
/*--------------- U t i l i t y . h ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This is the interface to Utility.cpp.

CHANGES
11-11-2011 gpc - Distributed to 16.322 class.
*/

#define NoGraphics 0

#include <ctime>

//----- f u n c t i o n    p r o t o t y p e s

void getxy(int &x, int &y);
void gotoxy(int x, int y);
void clrscr (void);
void clreol (void);
void SaveXY(void);
void RestoreXY(void);
void Delay(int dt);
#endif
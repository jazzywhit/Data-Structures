/*--------------- U t i l i t y . c p p  ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Dept.
      UMASS Lowell

PURPOSE
This module defines a collection of useful utility routines
for the 16.322 class.

CHANGES
11-11-2011 gpc - Distributed to 16.322 class.
*/
#include "Utility.h"

#if NoGraphics


/*--------------- g e t x y ( ) --------------

PURPOSE
Obtain the cursor location from the screen.

OUTPUT PARAMETERS
x  -- the x (column) location of the cursor
y  -- the y (row) location of the cursor
*/

void getxy(int &x, int &y)
{
   x = 0;
   y = 0;
}

/*--------------- g o t o x y ( ) --------------

PURPOSE
Move the cursor to a specific screen position.

INPUT PARAMETERS
x  -- the x (column) location of the cursor
y  -- the y (row) location of the cursor
*/

void gotoxy(int x, int y)
{
}

/*--------------- c l r s c r ( ) --------------

PURPOSE
Erase the console window and move the cursor home.
*/

void clrscr (void) 
{ 
} 

/*--------------- c l r e o l ( ) --------------

PURPOSE
Erase from the cursor to the end of the line.
*/

void clreol (void) 
{ 
} 

/*--------------- S a v e C u r s o r ( ) --------------

PURPOSE
Save the current screen cursor location.
*/

void SaveXY(void)
{
}

/*--------------- R e s t o r e C u r s o r ( ) --------------

PURPOSE
Restore the screen cursor location
*/

void RestoreXY(void)
{
}

/*--------------- D e l a y ( ) --------------

PURPOSE
Delay execution for the specified number of milliseconds.

INPUT PARAMETERS
ms -- the number of ms. to delay.
*/

void Delay(int ms)
{
   const unsigned MsPerSec = 1000;
   const unsigned SecsPerTick = CLK_TCK;

   time_t tStart = clock();

   while ((clock()-tStart)*(MsPerSec/SecsPerTick) < ms)
      ;
}
#else
#include <windows.h>

/*--------------- g l o b a l s ---------------*/

// Console window colors

enum COLORS
{
   BLACK,
   BLUE,
   GREEN,
   CYAN,
   RED,
   MAGENTA,
   BROWN,
   LIGHTGRAY,
   DARKGRAY,
   LIGHTBLUE,
   LIGHTGREEN,
   LIGHTCYAN,
   LIGHTRED,
   LIGHTMAGENTA,
   YELLOW,
   WHITE
}; 

// Saved cursor location
static int   cursorSaveX;
static int   cursorSaveY;

// Background and foreground colors.
static int BACKGROUND = BLACK;
static int FOREGROUND = LIGHTGRAY; 

/*--------------- g e t x y ( ) --------------

PURPOSE
Obtain the cursor location from the screen.

OUTPUT PARAMETERS
x  -- the x (column) location of the cursor
y  -- the y (row) location of the cursor
*/

void getxy(int &x, int &y)
{
   CONSOLE_SCREEN_BUFFER_INFO screenBfr;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBfr);

   x = screenBfr.dwCursorPosition.X;
   y = screenBfr.dwCursorPosition.Y;
}

/*--------------- g o t o x y ( ) --------------

PURPOSE
Move the cursor to a specific screen position.

INPUT PARAMETERS
x  -- the x (column) location of the cursor
y  -- the y (row) location of the cursor
*/

void gotoxy(int x, int y)
{
    COORD point;
    point.X = x;
    point.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),point);
}

/*--------------- c l r s c r ( ) --------------

PURPOSE
Erase the console window and move the cursor home.
*/

void clrscr (void) 
{ 
   COORD home = {0, 0};
   DWORD written; 
   CONSOLE_SCREEN_BUFFER_INFO screenBfr;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBfr);

   int   screenChars = screenBfr.dwSize.X * screenBfr.dwSize.Y;

   FillConsoleOutputAttribute (  GetStdHandle (STD_OUTPUT_HANDLE),
                                 FOREGROUND + (BACKGROUND << 4),
                                 screenChars,
                                 home,
                                 &written); 
   FillConsoleOutputCharacter (  GetStdHandle (STD_OUTPUT_HANDLE),
                                 ' ',
                                 screenChars,
                                 home,
                                 &written); 
   gotoxy (0, 0); 
} 

/*--------------- c l r e o l ( ) --------------

PURPOSE
Erase from the cursor to the end of the line.
*/

void clreol (void) 
{ 
   COORD start;
   DWORD written; 
   CONSOLE_SCREEN_BUFFER_INFO screenBfr;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBfr);

   int   x;    // Current column
   int   y;    // Current row.

   // Find the cursor location
   getxy(x, y);
   
   start.X = x;
   start.Y = y;

   // How many characters from the cursor to the end of line?
   int   numChars = screenBfr.dwSize.X - start.X;
 
   // Erase
   FillConsoleOutputAttribute (  GetStdHandle (STD_OUTPUT_HANDLE),
                                 FOREGROUND + (BACKGROUND << 4),
                                 numChars,
                                 start,
                                 &written); 
   FillConsoleOutputCharacter (  GetStdHandle (STD_OUTPUT_HANDLE),
                                 ' ',
                                 numChars,
                                 start,
                                 &written); 
} 

/*--------------- S a v e C u r s o r ( ) --------------

PURPOSE
Save the current screen cursor location.
*/

void SaveXY(void)
{
   getxy(cursorSaveX, cursorSaveY);
}

/*--------------- R e s t o r e C u r s o r ( ) --------------

PURPOSE
Restore the screen cursor location
*/

void RestoreXY(void)
{
   gotoxy(cursorSaveX, cursorSaveY);
}

/*--------------- D e l a y ( ) --------------

PURPOSE
Delay execution for the specified number of milliseconds.

INPUT PARAMETERS
ms -- the number of ms. to delay.
*/

void Delay(int ms)
{
   const unsigned MsPerSec = 1000;
   const unsigned SecsPerTick = CLK_TCK;

   time_t tStart = clock();

   while ((clock()-tStart)*(MsPerSec/SecsPerTick) < ms)
      ;
}
#endif
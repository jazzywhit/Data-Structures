//
//  Prog4.cpp
//  Prog4
//
//  Created by JESSE WHITWORTH on 10/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*--------------- P r o g 4 . c p p ---------------
 
 by:   George Cheney
 16.322 Data Structures
 ECE Department
 UMASS Lowell
 
 PURPOSE
 This is an interactive polygon statistics program. A polygon may be entered from either the keyboard
 or from a text file. Then, upon command, the program will display the circumference and area of
 the polygon.
 
 DEMONSTRATES
 Singly Linked Lists
 Destructor
 Copy Constructor
 Overloaded Assignment
 
 CHANGES
 10-01-2011 gpc -  Created from Prog3.cpp
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

#include "Point.h"
#include "LinkedList.h"

//----- c o n s t a n t    d e f i n i t i o n s -----

// Command Letters
const char AreaCmd =    'A';  // Compute and display the area of the polygon
// and its triangles.
const char CircumCmd =  'C';  // Compute and display the circumference of the polygon.
const char DeleteCmd =  'D';  // Delete the current point from the polygon.
const char EraseCmd =   'E';  // Make the polygon empty
const char ForwardCmd = 'F';  // Move the current entry forward one step.
const char InsertCmd =  'I';  // Insert a new point in the polygon.
const char OpenCmd =    'O';  // Read in a polygon from a file.
const char PrintCmd =   'P';  // Show the polygon on the display.
const char QuitCmd =    'Q';  // Quit
const char RewindCmd =  'R';  // Rewind the polygon to the first point.
const char SaveAsCmd =  'S';  // Write the polygon to a file.
const char UpdateCmd =  'U';  // Update the current entry
const char ExecuteCmd = 'X';  // Execute command file.

const unsigned MinPolySides = 3;	// A polygon must have at least 3 sides.

//----- f u n c t i o n    p r o t o t y p e s -----

void DoExecute(const string cmdLine, LinkedList &polygon);
string GetCmd(istream &cmdStream, LinkedList &polygon);
void InsertPoint(const string cmdLine, LinkedList &polygon);
void ClearPolygon(LinkedList &polygon);
string GetFileName(string cmdLine);
void ReadPolygonFile(string cmdLine, LinkedList &polygon);
void WritePolygonFile(string cmdLine, LinkedList &polygon);
void DisplayPolygon(LinkedList &polygon);
void Execute(istream &cmdStream, LinkedList &polygon);
void ShowArea(LinkedList &polygon);
void ShowCircum(LinkedList &polygon);
double Dist(Point p1, Point p2);
bool ValidPoly(LinkedList &polygon);
void UpdateEntry(string cmdLine, LinkedList &polygon);

//--------------- m a i n ( ) ---------------

int main()
{
    LinkedList  polygon;            // The polygon list
    
    // Execute commands from the stream cin.
    Execute(cin, polygon);
    
    return 0;
}

/*--------------- E x e c u t e ( ) ---------------
 
 PURPOSE
 Execute a command stream, either from cin of
 from a command file
 
 INPUT PARAMETERS
 cmdStream		-- the stream from which commands are to be read
 polygon     -- the polygon list.
 */
void Execute(istream &cmdStream, LinkedList &polygon)
{
    string cmdLine; // The current command line
    
    // Repeatedly get a command from the keyboard and
    // execute it.
    do
    {
        cmdLine = GetCmd(cmdStream, polygon);
        
        if (cmdLine.length() != 0)
        {
            switch (toupper(cmdLine[0]))
            {
                case EraseCmd:      // Clear the polygon.
					// Test destructor function.
                    polygon.~LinkedList();
                    break;
                    // Display the areas.
                case AreaCmd:
                {
					LinkedList polyCopy;	// Duplicate polygon
                    
					//Test overloaded assignment.
					polyCopy = polygon;
                    
                    ShowArea(polyCopy);
                }
                    break;
                    // Display circumference
                case CircumCmd:
                {
					// Test copy constructor.
					LinkedList polyCopy(polygon);	// Dupicate the polygon
                    ShowCircum(polyCopy);
                }
                    break;
				case UpdateCmd:
					UpdateEntry(cmdLine, polygon);
					break;
                    // Execute a command file.
                case ExecuteCmd:
                    DoExecute(cmdLine, polygon);
                    break;
                    // Determine which command to execute.
                case InsertCmd:        // Insert a new point.
                    InsertPoint(cmdLine, polygon);
                    break;
                case DeleteCmd:     // Delete the current point.
                    if (!polygon.AtEnd())
                        polygon.Delete();
                    if (polygon.Empty())
                        cout << "The polygon is empty." << endl;
                    break;
                case PrintCmd:       // Display the polygon.
                    DisplayPolygon(polygon);
					break;
                case OpenCmd:       // Read in a polygon file.
                    ReadPolygonFile(cmdLine, polygon);
                    break;
                case SaveAsCmd:      // Write out a polygon file.
                    WritePolygonFile(cmdLine, polygon);
                    break;
                case ForwardCmd:       // Advance to the next point.
                    if (!polygon.AtEnd())
                        polygon.Skip();
                    if (polygon.AtEnd())
                        cout << "The polygon is at the end." << endl;
                    break;
                case RewindCmd:
                    polygon.Rewind();
                    break;
                case QuitCmd:       // Terminate execution.
                    break;
                case ' ':
                    break;
                default:            // Bad command
                    cout << "*** Error: Unknown Command" << endl;
                    break;
            }
        }
    }
    while (toupper(cmdLine[0]) != QuitCmd);
}

/*--------------- D o E x c u t e ( ) ---------------
 
 PURPOSE
 Get a command file name and execute the file.
 
 INPUT PARAMETERS
 cmdLine -- the execute command command line.
 polygon   -- the polygon list.
 */
void DoExecute(const string cmdLine, LinkedList & polygon)
{
    // Get the file name from the execute command.
    string cmdFileName = GetFileName(cmdLine);
    
    // If empty, cancel command.
    if (cmdFileName.length() == 0)
        return;
    
    // Associate a command stream with the command file.
    ifstream cmdStream(cmdFileName.c_str());
    
    // If the file exists, execute it; otherwise give
    // an error message.
    if (cmdStream.is_open())
        Execute(cmdStream, polygon);
    else
        cout << "***ERROR: No such file " << cmdFileName << endl;
}

/*--------------- G e t C m d ( ) ---------------
 
 PURPOSE
 Accept a command from the keyboard.
 
 INPUT PARAMETERS
 cmdStream   -- the stream from which commands are to be read
 polygon      -- the polygon list.
 
 RETURN VALUE
 The command letter.
 */
string GetCmd(istream &cmdStream, LinkedList &polygon)
{
    // Display the current point before accepting each command.
    if (!polygon.AtEnd() && cmdStream == cin)
    {
        // Display the current item.
        cout << "\nCURRENT ITEM" << endl;
        
        Point node = polygon.CurrentEntry();
        cout << node;
        
        cout << endl;
    }
    
    // Prompt for a new command.
    cout << "\n>";
    
    string cmdLine;    // Command line
    
    // Quit at end of a command file.
    if (cmdStream.peek() == EOF)
    {
        cmdLine = QuitCmd;
        
        return cmdLine;
    }
    
    // Get the next command and return it.
    getline(cmdStream, cmdLine);
    
    if (cmdStream != cin)
        cout << cmdLine << endl;
    
    cmdLine += " ";
    
    return cmdLine;
}

/*--------------- I n s e r t P o i n t ( ) ---------------
 
 PURPOSE
 Insert a new point in the polygon before the current point.
 
 INPUT PARAMETERS
 cmdLine -- the execute command command line.
 polygon  -- the polygon list.
 */
void InsertPoint(string cmdLine, LinkedList &polygon)
{
    const unsigned  MinCmdSize = 2; // To check for an empty insert command
    
    Point             point;                // New polygon point
    
    istringstream     cmdStream(cmdLine.erase(0,1));   // Command stream
    
    // Ignore if empty insert parameters.
    if (cmdLine.length() < MinCmdSize)
        return;
    
    // Read the new point and insert it into the polygon.
    cmdStream >> point;
    if (!cmdStream.fail())
        polygon.Insert(point);
    else
    {
		cout << "***Error: Invalid Point." << endl;
        cmdStream.clear();
        cmdStream.ignore(INT_MAX, '\n');
    }
}

/*--------------- U p d a t e E n t r y( ) ---------------
 
 PURPOSE
 Modify the current entry in the polygon.
 
 INPUT PARAMETERS
 cmdLine	 -- The command line string
 polygon  -- the polygon list.
 */
void UpdateEntry(string cmdLine, LinkedList &polygon)
{
    const unsigned  MinCmdSize = 2; // To check for an empty insert command
    
    Point             point;                // New point value
    
    istringstream     cmdStream(cmdLine.erase(0,1));   // Command stream
    
	if (polygon.AtEnd())
    {
		cout << "***Error: There is no current entry." << endl;
		return;
    }
    
    // Ignore if empty update parameters.
    if (cmdLine.length() < MinCmdSize)
        return;
    
    // Read the new point and insert it into the polygon.
    cmdStream >> point;
    if (!cmdStream.fail())
        polygon.Update(point);
    else
    {
		cout << "***Error: Invalid Point." << endl;
        cmdStream.clear();
        cmdStream.ignore(INT_MAX, '\n');
    }
}

/*--------------- G e t F i l e N a m e ( ) ---------------
 
 PURPOSE
 Read a file name from the keyboard.
 
 INPUT PARAMETERS
 cmdLine -- the execute command command line.
 
 RETURN VALUE
 the file name or empty string if cancelled.
 */
string GetFileName(string cmdLine)
{
    string        fileName;           // The file name
    istringstream cmdStream(cmdLine.erase(0,1)); // Make a command stream.
    
    // Ignore empty file name
    if (cmdLine.length() == 0)
        return "";
    
    // Advance over whitespace.
    while (isspace(cmdStream.peek()))
        cmdStream.get();
    
    // Get the file name and return it.
    getline(cmdStream, fileName);
    
    return fileName;
}

/*--------------- R e a d P o l y g o n F i l e ( ) ---------------
 
 PURPOSE
 Read in a polygon file.
 
 INPUT PARAMETERS
 cmdLine		-- the execute command command line.
 polygon		-- the polygon list.
 */
void ReadPolygonFile(string cmdLine, LinkedList &polygon)
{
    ifstream  polygonStream;  // The input stream
    string    polygonFile;    // The input file name
    
    // Ask for the file name and then open the file.
    polygonFile = GetFileName(cmdLine);
    if (polygonFile.length() == 0)
        return;
    
    polygonStream.open(polygonFile.c_str());
    if (!polygonStream.is_open())
    {
        cout << "*** ERROR: No such file " << polygonFile << endl;
        return;
    }
    
    // Read in the entire polygon file.
    while (polygonStream.peek() != EOF)
    {
        Point point; // Next input point
        
        polygonStream >> point;
        if (point.Defined())
            polygon.Insert(point);
    }
    polygonStream.close();
    
    polygon.Rewind();
}


/*--------------- W r i t e P o l y g o n F i l e ( ) ---------------
 
 PURPOSE
 Write out a polygon file.
 
 INPUT PARAMETERS
 cmdLine -- the execute command command line.
 polygon  -- the polygon list.
 */
void WritePolygonFile(string cmdLine, LinkedList &polygon)
{
    ofstream  polygonStream;  // The output stream
    string    polygonFile;    // The output file name
    
    // Ask for the file name and then open the file.
    polygonFile = GetFileName(cmdLine);
    
    if (polygonFile.length() == 0)
        return;
    
    polygonStream.open(polygonFile.c_str());
    
    if (!polygonStream.is_open())
    {
        cout << "*** ERROR: Failed to open file " << polygonFile << endl;
        return;
    }
    
    // Write out the entire polygon.
    polygon.Rewind();
    while (!polygon.AtEnd())
    {
        polygonStream << polygon.CurrentEntry().X() <<" " << polygon.CurrentEntry().Y() << endl;
        polygon.Skip();
    }
    
    polygonStream.close();
    
    polygon.Rewind();
}

/*--------------- D i s p l a y P o l y g o n ( ) ---------------
 
 PURPOSE
 Display a polygon from beginning to end.
 
 INPUT PARAMETERS
 polygon  -- the polygon to be displayed.
 */
void DisplayPolygon(LinkedList &polygon)
{
    // If the polygon is empty, say so.
    if (polygon.Empty())
        cout << "The polygon is empty." << endl;
    else
    {
        cout << "\nPOLYGON DEFINITION" << endl;
        
        polygon.Rewind();
        
        // Keep displaying until the end.
        while (!polygon.AtEnd())
        {
            // Display the current entry..
            NodeData node = polygon.CurrentEntry();
            cout <<  node << endl;
            
            // Move to the next entry.
            polygon.Skip();
        }
        
        cout << endl;
    }
    
    polygon.Rewind();
}

/*--------------- C l e a r P o l y g o n ( ) ---------------
 
 PURPOSE
 Make the polygon empty.
 
 INPUT PARAMETERS
 polygon  -- the polygon list.
 */
void ClearPolygon(LinkedList &polygon)
{
    // Delete vertexes until empty.
    polygon.Rewind();
    while (!polygon.Empty())
        polygon.Delete();
}

/*--------------- S q r ( ) ---------------
 
 PURPOSE
 Macro to compute the square of a number.
 
 INPUT PARAMETERS
 a	-- the number to square
 */
#define Sqr(a) ((a)*(a))

/*--------------- D i s t ( ) ---------------
 
 PURPOSE
 Compute the distance between a pair of points.
 
 INPUT PARAMETERS
 p1  -- the first point in a pair
 p2  -- the second point in a pair
 */
double Dist(Point p1, Point p2)
{
    double x1 = p1.X();	// x coordinate of point 1
    double y1 = p1.Y();	// y coordinate of point 1
    double x2 = p2.X();	// x coordinate of point 2
    double y2 = p2.Y();	// y coordinate of point 2
    
    // Compute the distance between p1 and p2.
    return sqrt(Sqr(x2 - x1) + Sqr(y2 - y1));
}

/*--------------- V a l i d P o l y ( ) ---------------
 
 PURPOSE
 Make sure that there at least 3 points.
 
 INPUT PARAMETERS
 polygon  -- the polygon list.
 
 RETURN VALUE
 true if there are at least 3 points,
 false otherwise
 */
bool ValidPoly(LinkedList &polygon)
{
	// Rewind to the first point.
	polygon.Rewind();
    
	// Make sure that there are at least 3 points.
	for (unsigned i=0; i<MinPolySides; i++)
    {
		if (polygon.AtEnd())
        {
			// If not valid, say so.
			cout << "*** ERROR: At least " << MinPolySides << " points are needed to define a polygon." << endl;
			return false;
        }
		polygon.Skip();
    }
    
	// Indicate valid.
	return true;
}

/*--------------- S h o w C i r c u m ( ) ---------------
 
 PURPOSE
 Show on the screen the the circumference of the polygon.
 
 INPUT PARAMETERS
 polygon  -- the polygon list.
 */
void ShowCircum(LinkedList &polygon)
{
	// Check for valid polygon.
	if (!ValidPoly(polygon))
		return;
    
	// Rewind the current entry.
    polygon.Rewind();
    
	// Save the first point for computing the length of the last side.
    Point p0 = polygon.CurrentEntry();
    
	// Prepare to accumulate the circumference.
    double circum = 0;
    
	// Point 1 of the first side
    Point p1 = p0;
    
	// Repeatedly add the lengths of the polygon sides.
    while (!polygon.AtEnd())
    {
		// Advance to the next point.
        polygon.Skip();
        
		// If no more points, done
        if (polygon.AtEnd())
			// Accumulate the length of the last side.
            circum += Dist(p1, p0);
        else
        {
			// Accumulate the length of the next side.
            Point p2 = polygon.CurrentEntry();
            
            circum += Dist(p1, p2);
            
			// Point 2 is the next point 1.
			p1 = p2;
        }
    }
    
	// Show the circumference.
    cout << "Circumference = " << circum << endl;
}

/*--------------- S h o w A r e a ( ) ---------------
 
 PURPOSE
 Show on the screen the areas of the triangles comprising the
 polygon followed by the area of the polygon.
 
 INPUT PARAMETERS
 polygon  -- the polygon list.
 */
void ShowArea(LinkedList &polygon)
{
    if (ValidPoly(polygon)){
        
        polygon.Rewind();
        //Does not change, as the first point is the origin for all other triangles.
        Point firstPoint = polygon.CurrentEntry(); 
        polygon.Skip();
        Point currPoint;
        Point nextPoint;
        bool currPointAssigned = false;
        
        double a,b,c,s;
        double totalArea = 0;
        double triArea = 0;
        unsigned triCount = 0;
        
        do{
            if (!currPointAssigned){
                currPoint = polygon.CurrentEntry();
                currPointAssigned = true;
                polygon.Skip();
                continue;
            }
            triCount+=1;
            nextPoint = polygon.CurrentEntry();
            a = Dist(currPoint, firstPoint);
            b = Dist(nextPoint, currPoint); 
            c = Dist(nextPoint, firstPoint);
            s = (a + b + c)/2;
            triArea = sqrt(s*((s-a)*(s-b)*(s-c)));
            cout << "Triangle " << triCount << " area = " << triArea << endl; 
            totalArea += triArea;
            currPoint = nextPoint;
            polygon.Skip();
        }while (!polygon.AtEnd());
        cout << "Polygon Area = " << totalArea << endl;
        polygon.Rewind();
    }
}

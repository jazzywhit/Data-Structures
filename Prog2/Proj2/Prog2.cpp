/*=============== P r o g 2 . c p p ===============
 
 by: George Cheney
 ECE Dept.
 UMASS Lowell
 
 PURPOSE
 Read in the definition of an arbitrary polygon, and then
 compute both the circumference and the area of the polygon.
 
 CHANGES
 09-19-2011 Distribute to 16.322 class.
 
 **** REQUIRED FOR SUBMISSION. DO NOT MODIFY *****
 */

#include <iostream>

using namespace std;

#include "Point.h"
#include "Polygon.h"

//----- f u n c t i o n    p r o t o t y p e s -----

void DisplayPolyStats(Polygon &thePoly);

//--------------- m a i n ( ) ---------------

int main()
{
    Polygon aPolygon;   // The polygon definition
    
    // Read in a polygon definition. If a valid polygon was entered,
    // display its circumference and area; otherwise terminate
    // execution.
    
    cout << "ENTER A POLYGON DEFINITION:" << endl;
    cin >> aPolygon;
    
    // Unless it is empty, show the polygon statistics.
    if (aPolygon.IsDefined())
    {
        DisplayPolyStats(aPolygon);
        
        // Now add one more vertex to the polygon.
        cout << "Enter one more point: ";
        
        Point extraPt;  // The extra vertex
        
        cin >> extraPt;
        
        // If new point is valid, add it to the polygon and display the new
        // circumference and area.
        if (extraPt.IsDefined())
        {
            // Add the new point.
            aPolygon = aPolygon + extraPt;
            
            DisplayPolyStats(aPolygon);
            
        }
    }
    return 0;
}

/*---------- D i s p l a y P o l y S t a t s ( ) -----
 
 PURPOSE
 Display a polygon by showing:
 1. The list of points describing the vertexes,
 2. the circumference of the polygon,
 3. the area of the polygon, and
 4. the areas of the triangles comprising the polygon.
 
 INPUT PARAMETERS
 thePoly -- the polygon whose statistics are to be displayed.
 */
void DisplayPolyStats(Polygon &thePoly)
{
    // Show the polygon definition.
    cout << endl << "Here is the polygon definition:" << endl;
    cout << thePoly;
    
    // Compute and display the circumference.
    cout << "\nCircumference = " << thePoly.Circumference() << endl;
    
    // Compute the areas.
    double area[MaxSides+1];
    
    // Display the polygon area.
    thePoly.Area(area);
    cout << "\nPolygon Area = " << area[0] << endl << endl;
    
    //Display the triangle areas.
    for (unsigned i=1; i <= thePoly.numSides-2; ++i)
        cout << "Triangle " << i << ": Area = " << area[i] << endl;
    
    cout << endl;
    
}
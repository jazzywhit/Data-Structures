//
//  Polygon.h
//  Data Structures
//
//  Created by JESSE WHITWORTH on 9/12/11.
//  
//   This header file defines the data type “Polygon,” and also supplies the function
//   prototypes for the functions exported from the module Polygon.c. Prog1.c includes this
//   file.

#include "Point.h"

#ifndef Data_Structures_Polygon_h
#define Data_Structures_Polygon_h

const unsigned MaxSides=10; // Maximum number of Sides in a polygon

struct Polygon
{
    unsigned numSides; // -- Number of sides in the polygon
    Point vert[MaxSides]; // -- List of points defining the polygon vertices
};

//-------------------  Function Prototypes -------------------
bool GetPoly(char *prompt, Polygon &thePoly);
void ShowPoly(Polygon &thePoly);
double PolyCircumference(Polygon &thePoly);
void PolyArea(Polygon &thePoly, double *area);

#endif

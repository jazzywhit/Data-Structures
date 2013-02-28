//
//  Polygon.h
//  Data Structures
//
//  Created by JESSE WHITWORTH on 9/26/11.
//  
//   This header file defines the data type “Polygon,” and also supplies the function
//   prototypes for the functions exported from the module Polygon.cpp. Prog2.cpp includes this
//   file.

#ifndef Data_Structures_Polygon_h
#define Data_Structures_Polygon_h
using namespace std;

#include "Point.h"
const unsigned MaxSides=10; // Maximum number of Sides in a polygon

class Polygon{
public:
    Polygon(){isPolygon = false;};
    Polygon(Point *data, unsigned sides);
    bool IsDefined() {return isPolygon;};
    void Get(istream &is);
    void Show(ostream &os);
    double Circumference();
    void Area(double *area);
    
    Polygon operator+(Point point);
    
//priv®ate:
    unsigned numSides; // -- Number of sides in the polygon
    Point vert[MaxSides]; // -- List of points defining the polygon vertices
    bool isPolygon;  // Whether the polygon has been defined yet (numSides > 2)
};


// Non-member function prototypes
ostream & operator<<(ostream &os, Polygon &poly);
istream & operator>>(istream &is, Polygon &poly);


#endif

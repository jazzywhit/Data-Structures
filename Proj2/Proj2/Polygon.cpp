//
//  Polygon.cpp
//  Data Structures
//
//  Created by JESSE WHITWORTH on 9/26/11.
//
//  The functions Get(), Show(), Circumference(), and Area() as well as operator<<(), operator>>(),
//  and operator+() overloading, along with any helper functions are stored in this file

#include <iostream>
#include <cmath>
#include "Polygon.h"
#include "Point.h"

//-------------------  Polygon::Polygon() -------------------
// Purpose: Used for instances when you want to create a new Polygon object from
// an old one.
// Inputs: 
//      *data -- A pointer to a Point[] array.
//      sides -- The number of sides in the original polygon.
// Return: A newly populated Polygon
//
Polygon::Polygon(Point *data, unsigned sides){
    for (unsigned i=0; i < sides; i++){
        vert[i] = data[i];
    }
    numSides = sides;
}
    
//-------------------  Polygon::Get() -------------------
//PURPOSE
//To get a polygon from the user through an istream.
void Polygon::Get(istream &is){
    numSides = 0;
    
    cout << "\nEnter the first point: ";
    cin >> vert[0];
    
    if (vert[0].IsDefined()){
        for(unsigned i = 1; i < MaxSides; i++){
            cout << "\nEnter the next point: ";
            cin >> vert[i];
            
            if (vert[i].IsDefined()){
                numSides = i+1;
            }else{
                if (numSides > 2) isPolygon = true;
                break;
            }
        }
    } else {
        cout << "That is not a valid first point";
    }
    cout << endl;
}

//-------------------  Polygon::Show() -------------------
//PURPOSE
//Show the polygon through an ostream
void Polygon::Show(ostream &os){
    
    for (unsigned i = 0; i < numSides; i++){
        vert[i].Show(os);
    }
}

//-------------------  Polygon::Cirumference() -------------------
//PURPOSE
//Calculate the circumference of the polygon and return as double
double Polygon::Circumference(){
    
    Point firstPoint = vert[0];
    double circumference = 0;
    
    for (unsigned i = 0; i < numSides-1; i++){
        circumference += sqrt((vert[i].X() - vert[i+1].X())*(vert[i].X() - vert[i+1].X()) + (vert[i].Y() - vert[i+1].Y())*(vert[i].Y() - vert[i+1].Y()));
    }
    circumference += sqrt((vert[numSides-1].X() - firstPoint.X())*(vert[numSides-1].X() - firstPoint.X()) + (vert[numSides-1].Y() - firstPoint.Y())*(vert[numSides-1].Y() - firstPoint.Y()));
    return circumference;
}

//-------------------  Polygon::Area() -------------------
//PURPOSE
//Calculate the area of the polygon by segmenting it into triangles.
//Place the total area in [0] and the triangle areas inside the area array [i].
void Polygon::Area(double *area){
    
    Point firstPoint = vert[0]; //Does not change, as the first point is the origin for all other triangles.
    Point currPoint;
    Point nextPoint;
    bool currPointAssigned = false;
    
    double a,b,c,s;
    double totalArea = 0;
    
    for (unsigned i = 1; i < numSides; i++){
        if (!currPointAssigned){
            currPoint = vert[i];
            currPointAssigned = true;
            continue;
        }else{
            nextPoint = vert[i];
            a = sqrt((currPoint.X() - firstPoint.X())*(currPoint.X() - firstPoint.X()) + (currPoint.Y() - firstPoint.Y())*(currPoint.Y() - firstPoint.Y()));
            b = sqrt((nextPoint.X() - currPoint.X())*(nextPoint.X() - currPoint.X()) + (nextPoint.Y() - currPoint.Y())*(nextPoint.Y() - currPoint.Y()));
            c = sqrt((nextPoint.X() - firstPoint.X())*(nextPoint.X() - firstPoint.X()) + (nextPoint.Y() - firstPoint.Y())*(nextPoint.Y() - firstPoint.Y()));
            s = (a + b + c)/2;
            area[i-1] = sqrt(s*((s-a)*(s-b)*(s-c)));
            
            totalArea += area[i-1];
            currPoint = nextPoint;
        }
    }
    area[0] = totalArea;
}


//--------------- Point::operator+() ----------------
// Purpose: Add a Point to a Polygon.
// Input:
// point -- The point you want to add to the Polygon.
// Return: A new Polygon with the extra point added on.
//
Polygon Polygon::operator+(Point point){
    
    if (numSides < MaxSides){
        vert[numSides] = point;
        if (vert[numSides].IsDefined())
            numSides = numSides + 1;
    }
    return Polygon(vert,numSides);
}

//--------------- Point::operator<<() ----------------
// Purpose: Output a Polygon to an ostream.
// Input:
// os -- the ostream to which the Polygon is written
// poly -- the Polygon
// Return: a reference to the ostream

ostream & operator<<(ostream &os, Polygon &poly){
    
    poly.Show(os);
    return os;
}

/*--------------- Point::operator>>() ----------------
 PURPOSE
 Get input from an istream in order to create a new Point.
 INPUT PARAMETERS
 is -- the ostream to which the Time is written
 poly -- the Polygon
 RETURN VALUE
 a reference to the ostream
 */

istream & operator>>(istream &is, Polygon &poly){
    poly.Get(is);
    return is;
}

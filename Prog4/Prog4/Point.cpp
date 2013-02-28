//
//  Point.cpp
//  Prog4
//
//  Created by JESSE WHITWORTH on 10/10/11.
//  Copyright 2011 Jesse Whitworth. All rights reserved.
//
//  The functions Get() and Show() are defined in this module as well 
//  as operator<<() and operator>>() overloading.

#include <iostream>
using namespace std;
#include "Point.h"

// Non-member function prototypes
ostream & operator<<(ostream &os, Point &p);
istream & operator>>(istream &is, Point &p);

//-------------------  Point::Point() -------------------
// Copy Constructor
Point::Point(const Point &source){
    x = source.X();
    y = source.Y();
    isPoint = source.Defined();
}

//-------------------  Point::Operator=() -------------------
// Overloaded assignment operator
Point Point::operator=(const Point &right){
    
    if (this != &right){
        x = right.X();
        y = right.Y();
        isPoint = right.Defined(); 
    }
    return *this;
}

//-------------------  Point::Get() -------------------
//Purpose: Get a point from the user with a supplied prompt.
void Point::Get(istream &is){
    
    if(is.peek() != '\n'){
        is >> x >> y;
        isPoint = true;
    }else{
        isPoint = false;
    }
    is.ignore(INT_MAX, '\n');
}

//-------------------  Point::Show() -------------------
//Purpose: Show a particular point (x,y)
void Point::Show(ostream &os) const{
    
    os << "(" << x << ", " << y << ")";
}

//--------------- Point::operator<<() ----------------
// Purpose: Output a Point to an ostream.
// Input:
//      os -- the ostream to which the Point is written
//      point -- the Point
// Return: a reference to the ostream
ostream & operator<<(ostream &os, Point &point){
    
    point.Show(os);
    return os;
}

//--------------- Point::operator>>() ----------------
// Purpose: Get input from an istream in order to create a new Point.
// Input:
//      is -- the ostream to which the Point is written 
//      point -- the Point
// Return: a reference to the ostream
istream & operator>>(istream &is, Point &point){
    
    point.Get(is);
    return is;
}


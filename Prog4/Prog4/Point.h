//
//  Point.h
//  Prog4
//
//  Created by JESSE WHITWORTH on 10/10/11.
//  Copyright 2011 Jesse Whitworth. All rights reserved.
//

#ifndef Prog4_Point_h
#define Prog4_Point_h

//  This header file defines the data type “Point,” and also supplies the function
//  prototypes for the functions exported from the module Point.cpp. Both Prog3.cpp and
//  Polygon.cpp include this file

using namespace std;

class Point
{
public:
    Point(){ isPoint = false;};
    Point(const Point &source);
    Point operator=(const Point &right);
    
    void Get(istream &is);
    void Show(ostream &os) const;
    bool Defined() const {return isPoint;};
    double X() const {return x;};
    double Y() const {return y;};
    
private:
    double x; // -- x coordinate of a point
    double y; // -- y coordinate of a point
    bool isPoint; // -- has the point been defined
};

// Non-member function prototypes
ostream & operator<<(ostream &os, Point &point);
istream & operator>>(istream &is, Point &point);

#endif

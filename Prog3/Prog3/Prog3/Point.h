//
//  Point.h
//  Prog3
//
//  Created by JESSE WHITWORTH on 10/1/11.
//
//  This header file defines the data type “Point,” and also supplies the function
//  prototypes for the functions exported from the module Point.cpp. Both Prog3.cpp and
//  Polygon.cpp include this file

#ifndef Prog3_Point_h
#define Prog3_Point_h

using namespace std;

class Point
{
public:
    Point(){isPoint = false;};
    void Get(istream &is);
    void Show(ostream &os);
    bool Defined(){return isPoint;};
    double X(){return x;};
    double Y(){return y;};
    
private:
    double x; // -- x coordinate of a point
    double y; // -- y coordinate of a point
    bool isPoint; // -- has the point been defined
};

// Non-member function prototypes
ostream & operator<<(ostream &os, Point &point);
istream & operator>>(istream &is, Point &point);

#endif

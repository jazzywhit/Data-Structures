//
//  Point.h
//  Data Structures
//
//  Created by JESSE WHITWORTH on 9/26/11.
//
//  This header file defines the data type “Point,” and also supplies the function
//  prototypes for the functions exported from the module Point.cpp. Both Prog2.cpp and
//  Polygon.cpp include this file

#ifndef Data_Structures_Point_h
#define Data_Structures_Point_h
using namespace std;

class Point
{
public:
    Point(){isPoint = false;};
    void Get(istream &is);
    void Show(ostream &os);
    bool IsDefined(){return isPoint;};
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

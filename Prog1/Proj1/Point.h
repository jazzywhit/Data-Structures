//
//  Point.h
//  Data Structures
//
//  Created by JESSE WHITWORTH on 9/12/11.
//
//  This header file defines the data type “Point,” and also supplies the function
//  prototypes for the functions exported from the module Point.cpp. Both Prog1.cpp and
//  Polygon.cpp include this file

#ifndef Data_Structures_Point_h
#define Data_Structures_Point_h

struct Point
{
    double x; // -- x coordinate of a point
    double y; // -- y coordinate of a point
};

//-------------------  Function Prototypes -------------------
bool GetPoint(char *prompt, Point &pt);
void ShowPoint(Point pt);

#endif

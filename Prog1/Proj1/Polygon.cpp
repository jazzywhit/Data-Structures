//
//  Polygon.cpp
//  Data Structures
//
//  Created by JESSE WHITWORTH on 9/12/11.
//
//  The functions GetPoly(), ShowPoly(), PolyCircumference(), and PolyArea() along
//  with any helper functions are stored in this file

#include <iostream>
#include "Polygon.h"
#include "Point.h"
#include <cmath>

//-------------------  GetPoly() -------------------
//PURPOSE
//To get a polygon from the user
 bool GetPoly(char *prompt, Polygon &thePoly){
    
    std::cout << prompt << std::endl;
    thePoly.numSides = 0;
    bool polygonCreated = false;
    
    if (GetPoint((char *)"\nEnter the first point: ", thePoly.vert[0])){
        for(unsigned i = 1; i < MaxSides; i++){
            thePoly.numSides = i;
            if (!polygonCreated && i > 2)
                polygonCreated = true;
            if (!(GetPoint((char *)"Enter next point: ", thePoly.vert[i])))
                break;
        }
    } else {
        std::cout << "That is not a valid first point" << std::endl;
    }
    return polygonCreated;
}

//-------------------  ShowPoly() -------------------
//PURPOSE
//Show the polygon
void ShowPoly(Polygon &thePoly){
    
    std::cout << "\nHere is the polygon definition:" << std::endl;
    for (unsigned i = 0; i < thePoly.numSides; i++){
        ShowPoint(thePoly.vert[i]);
    }
}

//-------------------  PolyCirumference() -------------------
//PURPOSE
//Calculate the circumference of the polygon and return as double
double PolyCircumference(Polygon &thePoly){
    
    Point firstPoint = thePoly.vert[0];
    double circumference = 0;
    
    for (unsigned i = 0; i < thePoly.numSides-1; i++){
        circumference += sqrt(pow((thePoly.vert[i].x - thePoly.vert[i+1].x),2) + pow((thePoly.vert[i].y - thePoly.vert[i+1].y),2));
    }
    circumference += sqrt(pow((thePoly.vert[thePoly.numSides-1].x - firstPoint.x),2) + pow((thePoly.vert[thePoly.numSides-1].y - firstPoint.y),2));
    return circumference;
}

//-------------------  PolyArea() -------------------
//PURPOSE
//Calculate the area of the polygon by segmenting it into triangles.
//Place the total area in [0] and the triangle areas inside the area array [i].
void PolyArea(Polygon &thePoly, double *area){
    
    Point firstPoint = thePoly.vert[0]; //Does not change, as the first point is the origin for all other triangles.
    Point currPoint;
    Point nextPoint;
    bool currPointAssigned = false;
    
    double a,b,c,s;
    double totalArea = 0;
    
    for (unsigned i = 1; i < thePoly.numSides; i++){
        if (!currPointAssigned){
            currPoint = thePoly.vert[i];
            currPointAssigned = true;
            continue;
        }else{
            nextPoint = thePoly.vert[i];
            a = sqrt(pow((currPoint.x - firstPoint.x),2) + pow((currPoint.y - firstPoint.y),2));
            b = sqrt(pow((nextPoint.x - currPoint.x),2) + pow((nextPoint.y - currPoint.y),2));
            c = sqrt(pow((nextPoint.x - firstPoint.x),2) + pow((nextPoint.y - firstPoint.y),2));
            s = (a + b + c)/2;
            area[i-1] = sqrt(s*((s-a)*(s-b)*(s-c)));
            
            totalArea += area[i-1];
            currPoint = nextPoint;
        }
    }
    area[0] = totalArea;
}

//
//  Point.cpp
//  Data Structures
//
//  Created by JESSE WHITWORTH on 9/12/11.
//  
//  The functions GetPoint() and ShowPoint() are defined in this module

#include <iostream>
#include "Point.h"

//-------------------  GetPoint() -------------------
//PURPOSE
//Get a point from the user with a supplied prompt.
bool GetPoint(char *prompt, Point &pt){
    
    std::cout << prompt;
    
    if(std::cin.peek() != '\n'){
        std::cin >> pt.x >> pt.y;
        std::cin.ignore(INT_MAX, '\n');
        return true;
    }
    
    return false;
}

//-------------------  ShowPoint() -------------------
//PURPOSE
//Show a particular point (x,y)
void ShowPoint(Point pt){
    
    std::cout << "(" << pt.x << ", " << pt.y << ")" << std::endl;
    
}

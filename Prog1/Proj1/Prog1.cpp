//
//  Prog1.cpp
//  Data Structures
//
//  Created by JESSE WHITWORTH on 9/12/11.
//

#include <iostream>
#include "Point.h"
#include "Polygon.h"

//-------------------  main() -------------------
int main (int argc, const char * argv[])
{

    Polygon firstPoly;
    double firstPolyAreas[MaxSides];
    
    if (!GetPoly((char *)"ENTER A POLYGON DEFINITION:", firstPoly)){
        std::cout << "A polygon could not be created from your input. Exiting" << std::endl;
        return 0;
    }
    ShowPoly(firstPoly);
    PolyArea(firstPoly, firstPolyAreas);
        
    std::cout << "\nCircumference = " << PolyCircumference(firstPoly) << std::endl;
    std::cout << "\nPolygon Area = " << firstPolyAreas[0] << "\n\n";
    for (unsigned j=1; j < firstPoly.numSides - 1; j++){
        std::cout << "Triangle "<< j << ": Area = " << firstPolyAreas[j] << std::endl;
    }
    return 0;
}

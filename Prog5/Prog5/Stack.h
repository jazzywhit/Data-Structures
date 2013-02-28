//
//  Stack.h
//  Prog5
//
//  by:   George Cheney
//  16.322 Data Structures
//  ECE Department
//  UMASS Lowell
//
//  Used by JESSE WHITWORTH on 10/22/11.
//
//  This header file defines the data type “Stack” and also supplies 
//  the function prototypes for the functions exported from the module 
//  Stack.cpp. Prog5.cpp includes this file.
//

#ifndef Prog5_Stack_h
#define Prog5_Stack_h

using namespace std;

/*--------------- S T A C K . H ---------------
 PURPOSE
 This header file is the interface to the module "Stack.cpp."
 */

#include "Position.h"
#include "LinkedList.h"

typedef Position StackElement;

//----- C l a s s L i n k e d L i s t -----
class Stack
{
public:
	Stack(){size=0;};
	// Return true if the stack is empty.
	bool Empty() const { return stack.Empty(); }
	
	// Push a new element onto the stack.
	void Push(const StackElement &p);

	// Pop the top element from the stack.
	StackElement Pop();

	// Return the value of the top element on the stack.
	StackElement Top() const;

	void FindEnd();
private:
	LinkedList stack;
	int size;
};

#endif
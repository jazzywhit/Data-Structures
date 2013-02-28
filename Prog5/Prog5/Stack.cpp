//
//  Stack.cpp
//  Prog5
//
//  Created by JESSE WHITWORTH on 10/22/11.
//  Copyright 2011 Jesse Whitworth. All rights reserved.
//
//  A linked list stack class.
//

#include<iostream>
using namespace std;
#include "Stack.h"

// -------------------- P U S H () ------------------------
// Push a new element onto the top of the stack.
void Stack::Push(const StackElement &p){
	stack.Rewind();
	stack.Insert(p);
}

// -------------------- P O P () ------------------------
// Pop off the top of the stack.
StackElement Stack::Pop(){
	stack.Delete();
	return Top();
}

// -------------------- T O P () ------------------------
// Return the top element of the stack.
StackElement Stack::Top() const{
	return stack.CurrentEntry();
}
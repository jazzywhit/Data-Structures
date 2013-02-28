//
//  Queue.cpp
//  Prog6
//
//  Created by JESSE WHITWORTH on 10/27/11.
//  Copyright 2011 Jesse Whitworth. All rights reserved.
//
//  Generic Queue class to be used for multiple projects. 
//  NodeData -- the generic object type that will allow for this generalized class.
//  The default functions Enqueue(), Dequeue are defined in this file.

#include<iostream>
#include<cassert>
using namespace std;
#include "Queue.h"

/////////////////////////////////////// Guidelines /////////////////////////////////////
// Use assert() to verify successful memory allocation whenever you use the “new” operator.
// Use assert() to validate the any queue operations that may fail if misused


//----------------------- Q u e u e :: E n q u e u e ( ) ----------------------------
// Add a new tail element
void Queue::Enqueue(const QueueElem &p){            
	Node *newNode;
	if (Empty()){        
		assert(newNode = new(nothrow) Node(p));
		this->head = newNode;
	}else{
		assert(newNode = new(nothrow) Node(p, this->tail));
		this->tail->succ = newNode;
	}
	this->tail = newNode;
}

//------------------------ Q u e u e :: D e q u e u e ( ) ---------------------------
// Remove and return head element
QueueElem Queue::Dequeue(){                        
	QueueElem data = this->head->data;      // store the data from the head Node

	if (this->head->succ == 0){             // Only one node left in the queue
		delete this->head;
		this->head = 0;
		this->tail = 0;
	}else{
		Node *tmpNode = head;               // Create a pointer to the current head for deletion
		this->head = this->head->succ;      // Head's successor becomes new Head
		this->head->pred = 0;               // New Head has no predecessor
		delete tmpNode;             
	}
	return data;
}







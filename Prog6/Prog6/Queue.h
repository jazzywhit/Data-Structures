//
//  Queue.h
//  Prog6
//
//  by:   George Cheney
//  16.322 Data Structures
//  ECE Department
//  UMASS Lowell
//
//  Used by JESSE WHITWORTH on 10/27/11.
//
//  This header file defines the data type “Queue” and also supplies the function
//  prototypes for the functions exported from the module Queue.cpp. Prog6.cpp includes
//  this file.
//

#ifndef Prog5_Queue_h
#define Prog5_Queue_h

using namespace std;

/*--------------- Q u e u e . h ---------------
 PURPOSE
 This header file is the interface to the module "Queue.cpp."
 */

#include <cassert>
#include "Position.h"

// Make the list data generic.
typedef Position QueueElem;

//----- C l a s s L i n k e d L i s t -----
class Queue
{
private:
    // List node class definition
    struct Node
    {
        QueueElem data; // The "contents" of the node
        Node *pred; // Link to the predecessor node
		Node *succ; // Link to the successor node

        // Node Constructor Functions
		Node() : pred(0), succ(0) {}
        Node(const QueueElem &theData, const Node *prd = 0, const Node *suc = 0)
        : data((QueueElem) theData), pred((Node *)prd), succ((Node *) suc) { }
    };
public:
	Queue() : tail(0), head(0) { } //Default Constructor
	bool Empty() const {return head == 0;};   //Returns true if empty
	void Enqueue(const QueueElem &p);            //Add a new tail element
	QueueElem Dequeue();                         //Remove and return head element
    
private:
    // Make this list a copy of source.
    //void DeepCopy(Queue &source);
    Node *tail;    // Points to tail node
	Node *head;    // Points to head node
};

#endif

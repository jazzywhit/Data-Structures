//
//  LinkedList.h
//  Prog4
//
//  by:   George Cheney
//  16.322 Data Structures
//  ECE Department
//  UMASS Lowell
//
//  Used by JESSE WHITWORTH on 10/10/11.
//
//  This header file defines the data type “LinkedList” and also supplies the function
//  prototypes for the functions exported from the module LinkedList.cpp. Prog3.cpp includes
//  this file.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Prog4_LinkedList_h
#define Prog4_LinkedList_h

using namespace std;

/*--------------- L i n k e d L i s t . h ---------------
 PURPOSE
 This header file is the interface to the module "LinkedList.cpp."
 */

#include <cassert>
#include "Point.h"

// Make the list data generic.
typedef Point NodeData;

//----- C l a s s L i n k e d L i s t -----
class LinkedList
{
private:
    // List node class definition
    struct Node
    {
        NodeData data; // The "contents" of the node
        Node *next; // Link to the next node
        // Node Constructor Functions
        Node(){}
        Node(const NodeData &theData, const Node *theNext = 0)
        : data(theData), next((Node *)theNext) { }
    };
public:
    // Constructors
    LinkedList();
    //Copy Constructor
    LinkedList(LinkedList &source);  
    // Destructor
    ~LinkedList();        
    // Overloaded assignment operator
    LinkedList operator=(LinkedList &right);
    // True if the list is empty
    bool Empty() const;
    // True if the current position is beyond the last entry.
    bool AtEnd() const;
    // Rewind the current entry to the beginning of the list.
    void Rewind() { current = first; pred = 0; }
    // Skip to the next entry in the list.
    void Skip();
    // Get the contents of the current list entry.
    NodeData CurrentEntry() const;
    // Insert a new list entry before the current entry.
    void Insert(const NodeData &d);
    // Update the current entry.
    void Update(const NodeData &d) { assert(!AtEnd()); assert(current != 0); current->data = d; }
    //Delete the current entry.
    //The new current entry is the successor of the deleted node.
    void Delete();
private:
    // Make this list a copy of source.
    void DeepCopy(LinkedList &source);
    Node *first; // Points to the first node in the list
    Node *current; // Points to the current node
    Node *pred; // Points to the node preceding the current entry.
};

#endif

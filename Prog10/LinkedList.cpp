/////////////////////////////////////////////////////////
//File Name: LinkedList.cpp
//Author: Matthew Cook
//Description:
/*	Assignment 3 - Convex Polygons Linked List
		LinkedList.cpp
			Contains the function definitions for:
					LinkedList();
					bool Empty() const;
					bool AtEnd() const;
					void Skip();
					NodeData CurrentEntry() const;
					void Insert(const NodeData &d);
					void Delete();
*/
//Date: 09/28/11 
//Record of Changes: 
/*
	10/3/11 - bool Empty() const
	10/3/11 - bool AtEnd() const
	10/3/11 - NodeData CurrentEntry() const
	10/4/11 - void Skip()
	10/4/11 - void Insert(const NodeData &d);
	10/4/11 - void Delete();
	10/6/11 - void Skip()
	10/6/11 - void Insert(const NodeData &d);
	10/6/11 - void Delete();
	10/8/11 - void Skip()
	10/8/11 - void Insert(const NodeData &d);
	10/8/11 - void Delete();
	10/10/11 - void Skip()
	10/10/11 - void Insert(const NodeData &d);
	10/10/11 - void Delete();
*/
//
/////////////////////////////////////////////////////////

#include "LinkedList.h"
#include <iostream>
#include <sstream>
#include <climits>
#include <cassert>

using namespace std;


//-------------------  LinkedList::LinkedList() -------------------
// Copy Constructor
LinkedList::LinkedList(LinkedList &source){
    
    first = 0;
    current = 0;
    pred = 0;
   
    DeepCopy(source);
}

//-------------------  LinkedList::LinkedList() -------------------
// Make new nodes for all the source nodes. Set current/pred/first based on position of source
// Ensure that the destination is empty before starting a copy.
void LinkedList::DeepCopy(LinkedList &source){
    
    Node *tmpCurrent = source.current;
    source.Rewind();
    
    //First Node
    Insert(source.current->data);
    current = first;
    
    do{
        Skip();
        source.Skip();
        
        //All other Nodes
        Insert(source.current->data);
        if (source.current == tmpCurrent){
            tmpCurrent = current;
        }
    }while(!source.AtEnd());
    current = tmpCurrent;
}

//-------------------  LinkedList::LinkedList() -------------------
// Destructor
LinkedList::~LinkedList(){
    Rewind();
    while(!AtEnd())
        Delete();
    
}

//-------------------  LinkedList::LinkedList() -------------------
// Overloaded assignment operator
LinkedList LinkedList::operator=(LinkedList &right){
    
    if (this != &right){
        this->~LinkedList();
        DeepCopy(right);
    }
    return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//
//bool LinkedList::Empty() const
/*
Purpose: Used to find if the list is empty.
Input Parameters: N/A
Reference Parameter: N/A
Return Value: 
	true - empty
	false - not empty
*/
//
////////////////////////////////////////////////////////////////////////////////////////////////

bool LinkedList::Empty() const
{
	if(first == 0) // At start of list first is null.
	{
		return true;
	}
	else
	{
		return false;
	}	
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//bool LinkedList::AtEnd() const
/*
Purpose: Used to find if the end of the list has been reached.
Input Parameters: N/A
Reference Parameter: N/A
Return Value: 
	true - end of list
	false - not at end of list
*/
//
////////////////////////////////////////////////////////////////////////////////////////////////

bool LinkedList::AtEnd() const
{
	if( current == 0 ) // At end of list the current entry is null.
	{
		return true; // End of list
	}
	else
	{
		return false; // Not end of list
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//void LinkedList::Skip()
/*
Purpose: Used to skip an entry in the list.
Input Parameters: N/A
Reference Parameter: N/A
Return Value: N/A
*/
//
////////////////////////////////////////////////////////////////////////////////////////////////

void LinkedList::Skip()
{
	assert(!AtEnd()); // Cannot skip if you are at the end of the list.
	pred = current; // Previous entry is now the current entry
	current = current->next; // Current entry is now the next entry.
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//NodeData LinkedList::CurrentEntry() const
/*
Purpose: 
Input Parameters:
Reference Parameter: 
Return Value: 
*/
//
////////////////////////////////////////////////////////////////////////////////////////////////

NodeData &LinkedList::CurrentEntry() const
{
	assert(current != 0); // Cannot return an entry if it is null.
	return current->data; // Return the current entries data.
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//void LinkedList::Insert(const NodeData &d)
/*
Purpose: 
Input Parameters:
Reference Parameter: 
Return Value: 
*/
//
////////////////////////////////////////////////////////////////////////////////////////////////

void LinkedList::Insert(const NodeData &d)
{
	Node *temp = new(nothrow) Node(); // Create a temporary node.
	assert(temp != 0); // Cannot continue if node fail to be created.
	temp->data = d; // Insert data into node.
	if( pred == 0 ) // Beginning of the list 
	{
		temp->next = first; // Temp node points to what first node pointed to.
		first = temp; // First points to the temp node.
		pred = temp; // The previous node is now the temp node because inserted at beginning.
	}
	else // Not beginning of list.
	{
		temp->next = current; // Temp now points to what current pointed to.
		pred->next = temp; // The previous entry now points to temp. 
		pred = temp; // The previous entry is now the temp entry before the current entry.
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//void LinkedList::Delete()
/*
Purpose: Used to delete the current entry.
Input Parameters: N/A
Reference Parameter: N/A
Return Value: N/A
*/
//
////////////////////////////////////////////////////////////////////////////////////////////////

void LinkedList::Delete()
{
	assert( current != 0); // Cannot be at the end of the list.
	if( pred == 0 ) // At the beginning of the list
	{
		first = current->next; // First now points to what the current entry points to.
		delete current; //delete the current entry
		current = first; // Make the current entry the first entry.
	}
	else // Not at beginning of list
	{
		pred->next = current->next; // The previous node now points the what the current node points to.
		delete current; // Delete the current node.
		current = pred->next; // Make the current node what the previous node points to.
	}
}




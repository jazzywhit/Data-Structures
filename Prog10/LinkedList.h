#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/////////////////////////////////////////////////////////
//File Name: LinkedList.h
//Author: Matthew Cook
//Description:
/*	Assignment 3 - Convex Polygons Linked List
		LinkedList.h
			Contains Linked list function prototypes.
			Used to create a singly linked list of points each containing the 
			x and y data as well as a pointer to the next point node.
*/
//Date: 09/28/11
//Record of Changes: 
/*
	N/A
*/
//
/////////////////////////////////////////////////////////

#include <cassert>
#include "WordCount.h"

typedef WordCount NodeData; // Make the list data generic.

class LinkedList // List node class definition
{
private:

	struct Node
		{
			NodeData data; // The "contents" of the node
			Node *next; // Link to the next node
			Node(){} // Node Constructor Functions
			Node(const NodeData &theData, const Node *theNext = 0) 
				: data(theData), next((Node *)theNext) { }
		};
		
public:

	LinkedList () : first(0), current(0), pred(0) {}; // Constructor
	LinkedList (LinkedList &source);
	~LinkedList();
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
	NodeData &CurrentEntry() const; 
	// Insert a new list entry before the current entry.
	void Insert(const NodeData &d); 
	// Update the current entry.
	void Update(NodeData &d) { assert(!AtEnd()); current->data = d; } 
	//Delete the current entry. The new current entry is the successor of the deleted node.
	void Delete(); 

private:
	void DeepCopy(LinkedList &source);

	Node *first; // Points to the first node in the list
	Node *current; // Points to the current node
	Node *pred; // Points to the node preceding the current entry.

};

#endif
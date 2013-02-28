//
//  LinkedList.cpp
//  Prog3
//
//  Created by JESSE WHITWORTH on 10/1/11.
//
//  Generic LinkList class to be used for multiple projects. 
//  NodeData -- the generic object type that will allow for this generalized class.
//  The default constructor LinkedList() is defined in this file as well as the functions Empty(), AtEnd(),
//  Rewind(), Skip(), CurrentEntry(), Insert(), Update(), and Delete().

#include<iostream>
#include<cassert>
using namespace std;
#include "LinkedList.h"
typedef Point NodeData;


//-------------------  LinkedList::LinkedList() -------------------
//  Basic Constructor
LinkedList::LinkedList(){
    Node *newNode;
    assert(newNode = new(nothrow) Node(Point(),0));
    
    first = newNode;
    newNode->next = 0;
    current = newNode;
    pred = 0;
}

//-------------------  LinkedList::Empty() -------------------
// True if the list is empty
bool LinkedList::Empty() const{
    return (first->next == 0);
}

//-------------------  LinkedList::AtEnd() -------------------
// True if the current position is beyond the last defined entry.
bool LinkedList::AtEnd() const{
    return (current->next == 0);
}

//-------------------  LinkedList::Skip() -------------------
// Skip to the next entry in the list.
void LinkedList::Skip(){
    if (!AtEnd()){
        pred = current;
        current = current->next;
    }
}

//-------------------  LinkedList::CurrentEntry() -------------------
// Return the contents of the current list entry in whatever type NodeData has been defined.
NodeData LinkedList::CurrentEntry() const{
    return current->data;
}

//-------------------  LinkedList::Insert() -------------------
// Insert a new list entry before the current entry.
//
//  INPUT
//  d -- The new Node that will be inserted BEFORE the current node.
void LinkedList::Insert(const NodeData &d){
    Node *newNode;
    assert(newNode = new(nothrow) Node(d, current));
    if (current == first || Empty())    
        first = newNode; //Insert at the beginning/empty
    else                                
        pred->next = newNode; //Insert in the middle/end
    pred = newNode;
}

//-------------------  LinkedList::Delete() -------------------
//Delete the current entry.
//The new current entry is the successor of the deleted node.
//Do not have to check for Empty() as Prog3.cpp already does this.
void LinkedList::Delete(){
    if(current == first){               //Delete the first node
        first = current->next;
        delete current;
        current = first;
    }else{                              //Delete in middle/end
        pred->next = current->next;
        delete current;
        current = pred->next;
    }
}






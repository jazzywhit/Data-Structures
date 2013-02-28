//
//  LinkedList.cpp
//  Prog4
//
//  Created by JESSE WHITWORTH on 10/10/11.
//  Copyright 2011 Jesse Whitworth. All rights reserved.
//
//  Generic LinkList class to be used for multiple projects. 
//  NodeData -- the generic object type that will allow for this generalized class.
//  The default constructor LinkedList() is defined in this file as well as the functions Empty(), AtEnd(),
//  Rewind(), Skip(), CurrentEntry(), Insert(), Update(), and Delete().

#include<iostream>
#include<cassert>
using namespace std;
#include "LinkedList.h"

/*
 
 Use assert() to validate the following list operations:
 a) CurrentItem() – Make sure that the current item exists.
 b) DeleteItem() – Make sure that the current item exists
 c) Forward() – Make sure that the list position is not at the end.
 d) Update() - Make sure that the current item exists.
 e) Skip() - Make sure that the list is not at the end
 
*/


//-------------------  LinkedList::LinkedList() -------------------
//  Basic Constructor
LinkedList::LinkedList(){
    Node *newNode;
    assert(newNode = new(nothrow) Node(NodeData(),0));
    
    first = newNode;
    current = first;
    pred = 0;
}

//-------------------  LinkedList::LinkedList() -------------------
// Copy Constructor
LinkedList::LinkedList(LinkedList &source){
    
    Node *newNode;
    assert(newNode = new(nothrow) Node(NodeData(),0));
    
    first = newNode;
    current = first;
    pred = 0;
    
    DeepCopy(source);
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

//-------------------  LinkedList::Empty() -------------------
// True if the list is empty
bool LinkedList::Empty() const{
    return (first->next == 0);
}

//-------------------  LinkedList::AtEnd() -------------------
// True if the current position is beyond the last defined entry.
bool LinkedList::AtEnd() const{
    return (!current->data.Defined());
}

//-------------------  LinkedList::Skip() -------------------
// Skip to the next entry in the list.
void LinkedList::Skip(){
    assert(!AtEnd());  
    pred = current;
    current = current->next;
}

//-------------------  LinkedList::CurrentEntry() -------------------
// Return the contents of the current list entry in whatever type NodeData has been defined.
NodeData LinkedList::CurrentEntry() const{
    assert(current->data.Defined());
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
    
    assert(current->data.Defined());
    
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








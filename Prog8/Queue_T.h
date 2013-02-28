//
//  Queue_T.h
//  Prog8
//
//  Created by JESSE WHITWORTH on 11/20/11.
//  Copyright 2011 Jesse Whitworth. All rights reserved.
//
//  Queue Template to be used for multiple projects. 
//  NodeData -- the generic object type that will allow for this generalized class.
//  The functions Enqueue(), Dequeue(), Head(), and Empty() are defined in this file.

#ifndef QUEUE_H
#define QUEUE_H


#include <cassert>
#include <new>
#include <iostream>
using namespace std;


template <typename NodeData>


class Queue
{
	class Node
	{
		public:
			Node() : pred(0),succ(0){} 
			Node(const  NodeData &theData, const Node *prd = 0, const Node *suc = 0) { data = theData; pred = (Node *)prd; succ = (Node *)suc; }
			NodeData data; 
			Node *pred; 
			Node *succ; 
	};		
	public:
		Queue() :tail(0),head(0) {} 
		bool Empty() const; 
		void Enqueue(const NodeData &p); 
		NodeData Dequeue(); 
        NodeData Head(); 
	private: 
		Node *tail; 
		Node *head; 
};

//----------------------- Q u e u e :: E m p t y ( ) ----------------------------
// Returns a boolean true-empty false-not_empty.

template <typename NodeData>

bool Queue<NodeData>::Empty() const
{
	if(head == 0 || tail == 0){
		return true; 
	}else{
		return false; 
	}
}

//----------------------- Q u e u e :: E n q u e u e ( ) ----------------------------
// Add a new tail element

template <typename NodeData>

void Queue<NodeData>::Enqueue(const NodeData &p)
{
	if(Empty())     //If the queue is empty
	{
		Node *newNode = new(nothrow) Node(p); 
		assert(newNode != 0);  
		head = newNode; 
		tail = newNode; 
	}
	else            //If the queue is not empty
	{
		Node *newNode = new(nothrow) Node(p,tail); 
		assert(newNode != 0);  
		tail->succ = newNode; 
		tail = newNode; 	}
}

//------------------------ Q u e u e :: D e q u e u e ( ) ---------------------------
// Remove and return head element
template <typename NodeData>

NodeData Queue<NodeData>::Dequeue()
{
	NodeData tmpData = head->data;
	if (head -> succ == 0 || tail -> pred == 0)     //If the last node
	{
		delete head; 
		head = 0;
		tail = 0;
	}
	else                                            //If not the last node
	{
		Node *tmpNode = head; 
		head = head->succ; 
		head->pred = 0; 
		delete tmpNode; 
	}
	return tmpData;
}

//------------------------ Q u e u e :: H e a d ( ) ---------------------------
// Remove and return head element
template <typename NodeData>

NodeData Queue<NodeData>::Head()
{
	assert(!Empty()); 
	return head->data;
}

#endif
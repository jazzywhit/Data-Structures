//
// Heap_T.h 
// Prog9 
// 
// Created by JESSE WHITWORTH on 11/29/11. 
// Copyright 2011 Jesse Whitworth. All rights reserved. 
//

#ifndef HEAP_T_H
#define HEAP_T_H

#include <iostream>
#include <cassert>
#include "Utility.h"

template <typename ElemData, unsigned Capacity>
class Heap
{
public:
      // Constructor
      Heap() : size(0), current(0) { }
      // Return the number of elements in the array.
      unsigned Size() { return size; }
      // Return true if the array is empty.
      bool Empty() { return size == 0; }
      // Return true if the array is full.
      bool Full() { return size >= Capacity; }
      // Insert a new element into the array properly stored in ascending order.
      void Insert(ElemData &data);
      // Perform Heap Sort to sort the array into ascending order.
      void Sort();
      // Call "BinSearch()" to search the sorted array for the entry "data".
      // If found, make this the current entry and return true;
      // otherwise, return false.
      bool Search(ElemData &data);
      // Output the array to the stream "os".
      void Output(ostream &os);
      // Show the heap on the right side of the screen as a tree.
      void ShowTree() const;
      // Return the current entry.
      ElemData &CurrentEntry() { return heap[current]; }
      
	  // Standard heap operations
      void PercolateUp();
      void DeleteMax();
      void PercolateDown(unsigned r, unsigned n);
      void Heapify();

private:
      unsigned size; // The number of items in the heap
      unsigned current; // The index of the entry found by the last search
      ElemData heap[Capacity+1]; // The heap array
      // Perform a binary search for "data". Search the index range from
      // "start" to "end".
      bool BinSearch(unsigned start, unsigned end, ElemData &data);
      // Recursive function to show the tree as a heap.
      void RShowTree(unsigned r, int x, int y) const;
};

const unsigned XLeft = 60;        // Column number for start of dictionary display
const unsigned XRoot = 40;        // Column number for root node

//--------------- I n s e r t ( ) ---------------
//PURPOSE
//Insert a new element in ascending order.
//
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::Insert(ElemData &data){

     size++; // Increase size by one.
     heap[size] = data; // Insert data as least new node.
     PercolateUp();
}

//--------------- S e a r c h ( ) ---------------
//PURPOSE
//Search the sorted array for the data. If found, make this the current entry and return.
//
template <typename ElemData, unsigned Capacity>
bool Heap<ElemData, Capacity>::Search(ElemData &data){

     if( BinSearch(0, size, data) )
         return true;
     return false;
}

//--------------- D e l e t e M a x ( ) ---------------
//PURPOSE
//Delete the top entry (max) in the heap.
//
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::DeleteMax(){

     heap[1] = heap[size];
     size--;
     PercolateDown(1,size);   
}

//--------------- S o r t ( ) ---------------
//PURPOSE
//Perform Heap Sort to sort the array into ascending order.
//
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::Sort(){

    unsigned i = size;
    Heapify();
    while(i != 0){
        ElemData temp = heap[1];
        heap[1] = heap[i];
        heap[i] = temp;
		PercolateDown(1,--i);
	}
}

//--------------- O u t p u t ( ) ---------------
//PURPOSE
//Output the array to the stream "os".
//
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::Output(ostream &os){

	for(unsigned i = 1; i <= size; i++)
		os << heap[i] << endl;
}

//--------------- P e r c o l a t e D o w n ( ) ---------------
//PURPOSE
//Swap down to maintain heap property
//
//INPUT PARAMETERS
//root -- The index of the Root node.
//subSize -- Subtree size.
//
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::PercolateDown(unsigned root, unsigned subSize){

     unsigned leftChild = 2 * root; // leftChild
     while(leftChild <= subSize){
		if(leftChild < subSize && heap[leftChild] < heap[leftChild+1]){ // Find a larger child
			leftChild++;
        }        
		if(heap[root] < heap[leftChild]){ // If Larger, switch.
            ElemData temp = heap[root];
            heap[root] = heap[leftChild];
            heap[leftChild] = temp;  
            root = leftChild;
            leftChild = 2 * leftChild ; // Next leftChild.
        }else{
		return; // Child not bigger, done. 
		}
     } 
}

//--------------- H e a p i f y ( ) ---------------
//PURPOSE
//Turn heap array into a heap.
//Do this by percolating until heap property is achieved.
//
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::Heapify(){

     unsigned i = size;
     for(unsigned j = i / 2 ; j >= 1; j-- ){
          PercolateDown(j , i); 
     }
}

//--------------- P e r c o l a t e U p ( ) ---------------
//PURPOSE
//Swap up to maintain heap property.
//
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::PercolateUp(){

	unsigned lastNode = size;
    unsigned parent = lastNode/2;
    while(parent >= 1 && heap[lastNode] > heap[parent]){

		ElemData tempElement = heap[lastNode];
        heap[lastNode] = heap[parent];
        heap[parent] = tempElement;
        lastNode = parent;
        parent = lastNode/2;
    }
}

//--------------- B i n S e a r c h ( ) ---------------
//PURPOSE
//A binary search through the heap
//
template <typename ElemData, unsigned Capacity>
bool Heap<ElemData, Capacity>:: BinSearch(unsigned begin, unsigned end, ElemData &data){

    if (begin <= end){ 
          unsigned center = (begin + end)/2; //Locate the center
		  if (data == heap[center]){
			  current = center;
              return true;
		  }else if (data < heap[center]){  
               return BinSearch(begin, center-1, data); //Lower half
		  }else{
               return BinSearch(center+1, end, data);  //Upper half
		  }
    }else{
		return false;
	}
}

//-------------------------- Provided Functions ---------------------------------

/*--------------- R S h o w T r e e ( ) ---------------

PURPOSE
Recursive function to display a tree on the right half of the screen
using (crude) character graphics.

INPUT PARAMETERS
r         -- the root of the sub-tree to display
x         -- the cursor x coordinate index
y         -- the cursor y coordinate
*/
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::RShowTree(unsigned r, int x, int y) const
{
  const unsigned VertSpacing = 7;   // Vertical spacing constant
  const unsigned HorizSpacing = 10; // Horizontal spacing of tree nodes
  const unsigned MaxLevels = 4;     // The number of levels that fit on the screen

  // If the tree is not empty display it..
  if (r <= size && x < MaxLevels)
    {
    // Show the left sub-tree.
    RShowTree(2*r, x+1, y+VertSpacing/(1<<x));

    // Show the root.
    gotoxy(XRoot+HorizSpacing*x, y);
    cout << heap[r];

    // Show the right subtree.
    RShowTree(2*r+1, x+1, y-VertSpacing/(1<<x));
    }
}

/*--------------- S h o w T r e e ( ) ---------------

PURPOSE
Display a tree on the right half of the screen using (crude)
character graphics.This function calls RShowTree() which does
the work.
*/
template <typename ElemData, unsigned Capacity>
void Heap<ElemData, Capacity>::ShowTree() const
{
	  const unsigned YRoot = 12;      // Line number of root node
	  const unsigned ScrollsAt = 24;  // Screen scrolls after line 24

#if !NoGraphics    
	  int xOld;                       // Old cursor x coordinate
	  int yOld;                       // Old cursor y coordinate

	  // Save cursor position
	  getxy(xOld, yOld);

	  // Has the screen scrolled yet?
	  int deltaY = 0;

	  if (yOld > ScrollsAt)
		deltaY = yOld - ScrollsAt+1;

	  // Clear the right half of the screen.
	  for (int y=0; y<ScrollsAt+1; y++)
		{
		gotoxy(XRoot,y+deltaY);
		clreol();
		}

	  // Show the tree and offset if scrolled.
	  RShowTree(1, 0, YRoot+deltaY);   

	  // Restore old cursor position.
	  gotoxy(xOld,yOld);      
#endif
}

#endif

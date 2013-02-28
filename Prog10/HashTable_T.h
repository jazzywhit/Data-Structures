#ifndef HASH_TABLE
#define HASH_TABLE
//
//  HashTable_T.h
//  Prog10
//
//  Created by JESSE WHITWORTH on 12/7/11.
//  Copyright 2011 Jesse Whitworth. All rights reserved.
//
//  Hash Table Template to be used for multiple projects. 
//
#include "LinkedList.h"

//----- c l a s s H a s h T a b l e

template <typename ItemData, unsigned NumBuckets>
class HashTable
{
public:
	//Constructor: Make all buckets empty.
	HashTable();

	// Search the table for entry "d."
	// If "d" is found, return true,make "d"
	// the current entry for this bucket,
	// and make this the current bucket.
	// If "d" is not found, return false.
	bool Search(ItemData &d);										
	// Add an entry to the table.
	void Insert(ItemData &d);									
	// Delete the current entry.
	void Delete();											 
	// Return true if the table is empty.
	bool Empty() { return size == 0; }
	// Return the number of entries in the table.
	unsigned Size() { return size; }
	// Return the current entry.
	ItemData &CurrentEntry();
	// Remove the first entry from the table.
	ItemData Remove();							
	// Output the entire table to the stream "os", 1 entry per line.
	void Show();													

private:
	unsigned size; // The number of entries in the table.
	unsigned curBucket; // The index of the current bucket
	LinkedList *bucket[NumBuckets]; // Array of pointers to linked lists
	// The hashing function
	unsigned long Hash(ItemData &d);
};

/*----------------H a s h T a b l e ( ) ----------------
Default Constructor
// Empty all buckets
*/
template <typename ItemData, unsigned NumBuckets>
HashTable<ItemData, NumBuckets>::HashTable(){
	size = 0;
	curBucket = 0;
	for (unsigned i = 0; i < NumBuckets; i++){
		assert(bucket[i] = new(nothrow) LinkedList());
	}
}

//---------------- C u r r e n t E n t r y ( ) ----------------
template <typename ItemData, unsigned NumBuckets>
ItemData &HashTable<ItemData, NumBuckets>::CurrentEntry(){
	return bucket[curBucket]->CurrentEntry();
}

/*---------------- S e a r c h ( ) ----------------
PURPOSE
Search the table for an entry and set the found entry as the current entry

Pseudo Code
-Search the table for entry "d."
-If "d" is found, return true,make "d"
	the current entry for this bucket,
	and make this the current bucket.
-If "d" is not found, return false.
*/
template <typename ItemData, unsigned NumBuckets>
bool HashTable<ItemData, NumBuckets>::Search(ItemData &d){
	long hIndex = Hash(d);
	bucket[hIndex]->Rewind();
	while(!bucket[hIndex]->AtEnd()){
		if (bucket[hIndex]->CurrentEntry() == d){
			curBucket = hIndex;
			return true;
		}
		bucket[hIndex]->Skip();
	}	
	return false;
}

/*---------------- I n s e r t ( ) ----------------
// Add an entry to the table.
*/
template <typename ItemData, unsigned NumBuckets>
void HashTable<ItemData, NumBuckets>::Insert(ItemData &d){
	long hIndex = Hash(d);
	if (Search(d)){			//Check whether the word is already recorded
		ItemData tmpData = bucket[hIndex]->CurrentEntry();
		tmpData.Update();
		bucket[hIndex]->Update(tmpData);
	}else{					//If there isn't, insert it.
		bucket[hIndex]->Insert(d);
		size++;
	}
}

/*---------------- D e l e t e ( ) ----------------
// Delete the current entry.
*/
template <typename ItemData, unsigned NumBuckets>
void HashTable<ItemData, NumBuckets>::Delete(){
	bucket[curBucket]->Delete();
	size--;
}

/*---------------- R e m o v e ( ) ----------------
// Remove the first entry from the table.
*/
template <typename ItemData, unsigned NumBuckets>
ItemData HashTable<ItemData, NumBuckets>::Remove(){
	ItemData tmpData;
	for (unsigned i=0; i < NumBuckets; i++){
		if (!bucket[i]->Empty()){
			bucket[i]->Rewind();
			tmpData = bucket[i]->CurrentEntry();
			curBucket = i;
			Delete();
			break;	
		}
	}
	return tmpData;
}

///-----------------------------------------------------------------------
/// Provided Functions
///-----------------------------------------------------------------------

/*----------------H a s h ( ) ----------------
PURPOSE
Obtain a hash key from the ItemData object 'd' and then generate 
a random table index such that 0 <= index <= Num Buckets-1.

INPUT PARAMETERS
d -- the ItemData object from which to obtain a hash key
*/
template <typename ItemData, unsigned NumBuckets>
unsigned long HashTable<ItemData, NumBuckets>::Hash(ItemData &d)
{
	// Ask ItemData 'd' for it's hash key.
	unsigned x = d.HashKey();

	// Now, generate a random table index such that
	// 0 <= index <= NumBuckets-1
	const unsigned C1 = 25173;
	const unsigned C2 = 13849;
	const unsigned C3 = 65536;

	return ((C1*x + C2) % C3) % NumBuckets;
}

/*--------------- S h o w ( ) ---------------

PURPOSE
Display the hash table on the right half of the screen.
*/
template <typename ItemData, unsigned NumBuckets>
void HashTable<ItemData, NumBuckets>::Show()
{
#if !NoGraphics
  const unsigned XLeft = 40;          // Column number for start of dictionary display
  const unsigned XHeading = XLeft - 3;// Column location of heading
  const unsigned ScrollsAt = 24;      // Screen scrolls after line 24
  const unsigned XMax = 79;           // Don't show words after this column
  const unsigned YSpacing = NumBuckets < 22 ? 22/NumBuckets : 1;  // Vertical spacing
  const unsigned DisplayLines = NumBuckets < 22 ? NumBuckets : 22;// Number of buckets to display
    
  int xOld;                       // Old cursor position x coordinate
  int yOld;                       // Old cursor position y coordinate

  // Save cursor position
  getxy(xOld, yOld);

  // Has the screen scrolled yet?
  int deltaY = 0;

  if (yOld > ScrollsAt)
    deltaY = yOld - ScrollsAt+1;

  // Clear the right half of the screen.
  for (int y=0; y<ScrollsAt+1; y++)
    {
    gotoxy(XLeft,y+deltaY);
    clreol();
    }

  // Display heading.
  gotoxy(XHeading, deltaY);
  cout << "BUCKET";

  // Show the array and offset if scrolled.
  for(unsigned index=0; index<DisplayLines; index++)
    {
    // Display the bucket number.
    gotoxy(XLeft, YSpacing*index+deltaY+2);
    cout << setw(2) << right << index << ": ";

    // If the bucket is not empty, display it.
    if (bucket[index] != 0)
       {
       // Traverse the linked list bucket,
       // displaying each entry.
       bucket[index]->Rewind();
       while (!bucket[index]->AtEnd())
          {
          int xCursor;  // cursor x position
          int yCursor;  // cursor y position

          // Don't go off the right side of the screen
          getxy(xCursor, yCursor);
          if (xCursor + bucket[index]->CurrentEntry().Word().length() >= XMax)
            break;

          // Display the next entry from the bucket. 
          cout << left << bucket[index]->CurrentEntry() << " ";
          bucket[index]->Skip();
          }
       }
    }

  // Restore old cursor position.
  gotoxy(xOld,yOld);      
#endif  
}
#endif
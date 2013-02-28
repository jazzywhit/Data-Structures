#ifndef LINKEDLIST_T_H
#define LINKEDLIST_T_H

#include <cassert>

//----- C l a s s L i n k e d L i s t -----
template <typename NodeData>
class LinkedList
{ 
	protected:
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
		LinkedList() : first(0), current(0), pred(0) {}; // Constructor
		//Copy Constructor
		LinkedList(LinkedList &source);
		// Destructor
		~LinkedList();
		void Clear(); //Clear the list of all nodes.
		// Overloaded assignment operator
		LinkedList operator=(LinkedList &right);// True if the list is empty
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
		void Update(const NodeData &d) { assert(!AtEnd()); current->data = d; }
		//Delete the current entry.
		//The new current entry is the successor of the deleted node.
		void Delete();
	private:
		// Make this list a copy of source.
		void DeepCopy(LinkedList &source);
	protected:
		Node *first; // Points to the first node in the list
		Node *current; // Points to the current node
		Node *pred; // Points to the node preceding the current entry.
};

/*---------------------- C o p y C o n s t r u c t o r ------------------------

Purpose: Used to construct a linked list from the source linked list.

Preconditions: N/A

Input Parameters:  
	&source - The source list.

Return Value: N/A

*/

template <typename NodeData>
LinkedList<typename NodeData>::LinkedList( LinkedList &source )
{
	DeepCopy(source);	//Initialize copy of list with source list.
}

/*---------------- ~ L i n k e d L i s t ( ) ----------------------- 
Purpose: Used to dealocate the dynamically allocated memory associated to Linked List.

Precondition: N/A

Input Parameters: N/A

Return Value: N/A
*/

template <typename NodeData>
LinkedList<typename NodeData>::~LinkedList()
{
	Rewind(); // Send List Back to beginning
	Clear();
}

/*---------------- C l e a r ( ) ----------------------- 
Purpose: Used to clear a list of all nodes.

Precondition: N/A

Input Parameters: N/A

Return Value: N/A
*/

template <typename NodeData>
void LinkedList<typename NodeData>::Clear()
{
	while (!Empty()) // While the list is not empty
	{
		Delete(); // Kill Nodes.
	}
}

/*---------------o p e r a t o  r = ( ) ---------------------
 
Purpose: Used to assign the source list the the copy list.
Input Parameters: 
	&right - The Souce List.
Return Value: 
	LinkedList - The Copy list.
*/

template <typename NodeData>
LinkedList<typename NodeData> LinkedList<typename NodeData>::operator=(LinkedList &right)
{
	if( this != &right) //Check is input is the same as the copy list.
	{
		Rewind(); // Send copy list back to beginning.
		Clear(); // Clear the copy list of all nodes.
		DeepCopy(right); //Copy the source the the copy list.
	}
	return *this; // Return the copy list. 
}

/*------------------- E m p t y ( ) ----------------------------------------

Purpose: Used to find if the list is empty.
Input Parameters: N/A
Reference Parameter: N/A
Return Value: 
	true - empty
	false - not empty
*/

template <typename NodeData>
bool LinkedList<typename NodeData>::Empty() const
{
	if(pred == 0) // At start of list first is null.
		return true;
	else
		return false;
}


/*------------------- A t E n d ( ) ----------------------------

Purpose: Used to find if the end of the list has been reached.
Input Parameters: N/A
Reference Parameter: N/A
Return Value: 
	true - end of list
	false - not at end of list
*/

template <typename NodeData>
bool LinkedList<typename NodeData>::AtEnd() const
{
	if( current == 0 ) // At end of list the current entry is null.
		return true; // End of list
	else
		return false; // Not end of list
}

/*--------------- S k i p ( ) ---------------------------------

Purpose: Used to skip an entry in the list.
Input Parameters: N/A
Reference Parameter: N/A
Return Value: N/A
*/

template <typename NodeData>
void LinkedList<typename NodeData>::Skip()
{
	assert(!AtEnd()); // Cannot skip if you are at the end of the list.
	pred = current; // Previous entry is now the current entry
	current = current->next; // Current entry is now the next entry.
}

/*------------------ C u r r e n t E n t r y ( ) ----------------------------

Purpose: Returns the Current Entry. 
Input Parameters: N/A
Reference Parameter: N/A
Return Value: 
	NodeData -- The current entry.
*/

template <typename NodeData>
NodeData LinkedList<typename NodeData>::CurrentEntry() const
{
	assert(current != 0); // Cannot return an entry if it is null.
	return current->data; // Return the current entries data.
}

//Insert
template <typename NodeData>
void LinkedList<typename NodeData>::Insert(const NodeData &d)
{
	Node *temp = new(nothrow) Node(); // Create a temporary node.
	assert(temp != 0); // Cannot continue if node fail to be created.
	temp->data = d; // Insert data into node.
	if( pred == 0 ) // Beginning of the list 
	{
		current = first;
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

//Delete
template <typename NodeData>
void LinkedList<typename NodeData>::Delete()
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




#endif
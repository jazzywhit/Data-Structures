#ifndef QUEUE
#define QUEUE

//----- c l a s s q u e u e -----
// Derived from class "LinkedList"

#include "LinkedList_T.h"

template <typename ElemData>
class Queue : public LinkedList<ElemData>
{
	public:
		// Construct an empty queue.
		Queue() : last(0) { }
		// Add "elem" at the tail of the queue.
		void Enqueue(const ElemData &elem);
		// Remove and return the head element.
		ElemData Dequeue();
		// Return, but do not remove the head element.
		ElemData Head();
	private:
		// Points to the last (tail) node of the queue
		Node *last;
};

//Enqueue
template <typename ElemData>
void Queue<typename ElemData>::Enqueue(const ElemData &data)
{
	current = last;
	if(!Empty())
	{
		Skip();	
	}
	Insert(data);
}

//Dequeue
template <typename ElemData>
ElemData Queue<typename ElemData>::Dequeue()
{
	return Head();
	Delete();
}

//Enqueue
template <typename ElemData>
ElemData Queue<typename ElemData>::Head()
{
	Rewind();
	return CurrentEntry();
}


#endif
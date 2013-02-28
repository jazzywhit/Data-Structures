//
//  BST_T.h
//  Prog8
//
//  Created by JESSE WHITWORTH on 11/20/11.
//  Copyright 2011 Jesse Whitworth. All rights reserved.
//
//  Binary Search Tree Template to be used for multiple projects. 
//

#ifndef BST_H
#define BST_H

#include "Queue_T.h"

const unsigned XRoot = 40;      //Root node column number for visualization
template <typename NodeData>

class BST
{
	private:
	// Tree node class definition
		struct Node
		{
			// Constructors
			Node() : left(0), right(0) {}
			Node(const NodeData &d) : data(d), left(0), right(0) { }
			// Data Members
			NodeData data; // The "contents" of the node
			Node *left; // Link to the left successor node
			Node *right; // Link to the right successor node
		};
	public:
		// Constructor
		BST() : root(0), current(0) { }
		// True if the tree is empty
		bool Empty() { return root == 0;}
		// Search for an entry in the tree. If the entry is found,
		// make it the "current" entry. If not, make the current entry
		// NULL. Return true if the entry is found; otherwise return false.
		bool Search(NodeData &d);
		// Add a new node to the tree.
		void Insert(NodeData &d);
		// Delete the current node.
		void Delete();
		// Output the tree to the "os" in the indicated sequence.
		void OutputInOrder(ostream &os) const; // Output inorder
		void OutputPreOrder(ostream &os) const; // Output preorder
		void OutputPostOrder(ostream &os) const; // Output postorder
		void OutputByLevel(ostream &os) const; // Output by level
		// Retrieve the data part of the current node.
		NodeData Current() { return current->data; }
		// Show the binary tree on the screen.
		void ShowTree() const;
	private:
		Node *root; // Points to the root node
		Node *current; // Points to the current node
		Node *parent; // Points to current node's parent
		// Recursive Search
		bool RSearch(Node *subTree, NodeData &d);
		// Recursive Insert
		void RInsert(Node *&subTree, NodeData &d);
		// Recursive Traversal Functions
		void ROutputInOrder(Node *subTree, ostream &os) const;
		void ROutputPreOrder(Node *subTree, ostream &os) const;
		void ROutputPostOrder(Node *subTree, ostream &os) const;
		// Find the parent of leftmost right successor of the current node.
		typename BST<NodeData>::Node *BST<NodeData>::ParentOfLeftMostRightSucc(Node* node, Node *parent) const;
		// Show the binary tree on the screen.
		void RShowTree(Node *subTree, int x, int y) const;
};


//----------------------- B S T :: S e a r c h ( ) ----------------------------
/*
Purpose: Search for an entry in the tree. If the entry is found,
		 make it the "current" entry. If not, make the current entry
		 NULL. Return true if the entry is found; otherwise return false.
*/
template <typename NodeData>

bool BST<NodeData>::Search(NodeData &d)
{
	parent = 0;
	return RSearch(root, d);
}

//----------------------- B S T :: I n s e r t ( ) ----------------------------
//
// Purpose: Add a new node to the tree.
//
template <typename NodeData>

void BST<NodeData>::Insert(NodeData &d)
{
	RInsert(current, d);
	if (root == 0){
		root = current;
        parent = current;
    }
}

//----------------------- B S T :: D e l e t e ( ) ----------------------------
//
// Purpose: Add a new node to the tree.
//
template <typename NodeData>

void BST<NodeData>::Delete()
{
	Node* currNode = current;   // X
	Node* p = 0;

	if(parent == 0 && root != 0)
		parent = root;

	////Case 3
	if( (currNode->left != 0) && (currNode->right != 0) )
	{
		Node* inOrderParent = ParentOfLeftMostRightSucc(currNode->right,currNode);
		if(currNode == inOrderParent){
			currNode = inOrderParent->right;  //3a
			inOrderParent->right = currNode->right;
		}else{
			currNode = inOrderParent->left;  //3b
			inOrderParent-> left = currNode->left;
		}
		current->data = currNode->data;
	}else{
		if (currNode->left != 0)
			p = currNode->left;
		else if (currNode->right != 0)
			p = currNode->right;
	
		///Case 1/2
		if (currNode == root)
			root = p;
		else if (currNode == parent->left)
			parent->left = p;
		else
			parent->right = p;
	}
	delete currNode;
	current = root;
	parent = root;
}


//----------------------- B S T :: OutputInOrder ( ) ----------------------------
//
//Purpose: Output the tree in alphabetical order.
//
template <typename NodeData>

void BST<NodeData>::OutputInOrder(ostream &os) const
{
	if (root != 0){
		ROutputInOrder(root, os);
	}
}

//----------------------- B S T :: OutputPreOrder ( ) ----------------------------
//
// Purpose: Output the tree in Preorder form.
//
	
template <typename NodeData>

void BST<NodeData>::OutputPreOrder(ostream &os) const
{
	if (root != 0){
		ROutputPreOrder(root, os);
	}
}

//----------------------- B S T :: OutputPostOrder ( ) ----------------------------
//
// Purpose: Output the tree in Postorder form.
//
template <typename NodeData>

void BST<NodeData>::OutputPostOrder(ostream &os) const
{
	if (root != 0){
		ROutputPostOrder(root, os);
	}
}
		
//----------------------- B S T :: OutputByLevel ( ) ----------------------------
//
// Purpose: Output the tree level by level.
//

template <typename NodeData>

void BST<NodeData>::OutputByLevel(ostream &os) const
{
	Queue<Node*> nodeQueue;

	nodeQueue.Enqueue(root);
	while(!nodeQueue.Empty()){
		Node* tmp = nodeQueue.Dequeue();
		os << tmp->data << endl;
		if(tmp->left != 0){
			nodeQueue.Enqueue(tmp->left);
		}
		if(tmp->right != 0){
			nodeQueue.Enqueue(tmp->right);
		}
	}
}

/*--------------- S h o w T r e e ( ) ---------------

PURPOSE
Display a tree on the right half of the screen using (crude)
character graphics.This function calls RShowTree() which does
the work.
*/
template <typename NodeData>

void BST<NodeData>::ShowTree() const
{
  const unsigned YRoot = 11;      // Line number of root node
  const unsigned ScrollsAt = 24;  // Screen scrolls after line 24
    
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
  RShowTree(root, 0, YRoot+deltaY);   

  // Restore old cursor position.
  gotoxy(xOld,yOld);      
}


//----------------------- B S T :: R S e a r c h ( ) ----------------------------
/*
 Purpose: Search for an entry in the tree. If the entry is found,
 make it the "current" entry. If not, make the current entry
 NULL. Return true if the entry is found; otherwise return false.
 */

template <typename NodeData>

bool BST<NodeData>::RSearch(Node *subTree, NodeData &d)
{
	if( subTree == 0 ){
		return false;
	}else if( subTree->data == d ){
		current = subTree;
		return true;
	}else if( d < subTree->data){
		parent = subTree;
		return RSearch( subTree->left, d);
	}else{
		parent = subTree;
		return RSearch( subTree->right, d);
	}
}


//----------------------- B S T :: I n s e r t ( ) ----------------------------
//
// Purpose: Add a new node to the tree.
//
template <typename NodeData>

void BST<NodeData>::RInsert(Node *&subTree, NodeData &d)
{
	if( subTree == 0 )
		subTree = new Node(d);
	else if( d < subTree->data )
		RInsert(subTree->left,d);
	else if( d > subTree->data )
		RInsert(subTree->right,d);
	else
		subTree->data.Update();
}

//----------------------- B S T :: ROutputInOrder ( ) ----------------------------
//
//Purpose: Output the tree in alphabetical order through recursion.
//
template <typename NodeData>

void BST<NodeData>::ROutputInOrder(Node *subTree, ostream &os) const
{
	if(subTree != 0){
		ROutputInOrder(subTree->left,os);
		os << subTree->data << endl;
		ROutputInOrder(subTree->right,os);	
	}
}

//----------------------- B S T :: OutputPreOrder ( ) ----------------------------
//
// Purpose: Output the tree in Preorder form.
//

template <typename NodeData>

void BST<NodeData>::ROutputPreOrder(Node *subTree, ostream &os) const
{
	if( subTree != 0 ){
		os << subTree->data << endl;
		ROutputPreOrder(subTree->left,os);
		ROutputPreOrder(subTree->right,os);
	}

}

//----------------------- B S T :: ROutputPostOrder ( ) ----------------------------
//
// Purpose: Output the tree in Postorder form.
//

template <typename NodeData>

void BST<NodeData>::ROutputPostOrder(Node *subTree, ostream &os) const
{
	if( subTree != 0 ){
		ROutputPostOrder(subTree->left,os);
		ROutputPostOrder(subTree->right,os);
		os << subTree->data << endl;
	}
}


//----------------------- B S T :: ParentofLeftMostRightSucc ( ) ----------------------------
/*
 Purpose: Find the left most successor of the node to the right of 'node'. This value will be used
          during delete.
 */
template <typename NodeData>

typename BST<NodeData>::Node *BST<NodeData>::ParentOfLeftMostRightSucc(Node* node, Node *parent) const 
{
	if(node->left != 0)
		return ParentOfLeftMostRightSucc(node->left,node);
	return parent;
}

/*--------------- R S h o w T r e e ( ) ---------------

PURPOSE
Recursive function to display a tree on the right half of the screen
using (crude) character graphics.

INPUT PARAMETERS
subTree   -- the root of the sub-tree to display
x         -- the cursor x coordinate index
y         -- the cursor y coordinate
*/
template <typename NodeData>

void BST<NodeData>::RShowTree(Node *subTree, int x, int y) const
{
  const unsigned VertSpacing = 7;   // Vertical spacing constant
  const unsigned HorizSpacing = 10; // Horizontal spacing of tree nodes
  const unsigned MaxLevels = 4;     // The number of levels that fit on the screen

  // If the tree is not empty display it..
  if (subTree != 0 && x < MaxLevels){
      
    // Show the left sub-tree.
    RShowTree(subTree->left, x+1, y+VertSpacing/(1<<x));

    // Show the root.
    gotoxy(XRoot+HorizSpacing*x, y);
    cout << subTree->data;

    // Show the right subtree.
    RShowTree(subTree->right, x+1, y-VertSpacing/(1<<x));
    }
}


#endif
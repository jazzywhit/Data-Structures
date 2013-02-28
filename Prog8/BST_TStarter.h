const unsigned XRoot = 40;        // Column number for root node

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
  if (subTree != 0 && x < MaxLevels)
    {
    // Show the left sub-tree.
    RShowTree(subTree->left, x+1, y+VertSpacing/(1<<x));

    // Show the root.
    gotoxy(XRoot+HorizSpacing*x, y);
    cout << subTree->data;

    // Show the right subtree.
    RShowTree(subTree->right, x+1, y-VertSpacing/(1<<x));
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

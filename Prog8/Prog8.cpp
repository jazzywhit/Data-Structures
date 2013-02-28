/*--------------- P r o g 8 . c p p ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Department
      UMASS Lowell

PURPOSE
Count the number of occurrences of each word in a file

DEMONSTRATES
Binary Search Trees
Class Templates

CHANGES
11-02-2011 gpc - Distributed to 16.322 class.
*/
#include <Windows.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include<cassert>

using namespace std;

#include "Utility.h"

#include "WordCount.h"
#include "BST_T.h"

//----- c o n s t a n t    d e f i n i t i o n s -----

// Command Letters
const char ShowCmd =        'A';  // Show the tree inorder.
const char PreOrderCmd =    'B';  // Show the tree in preorder.
const char DeleteCmd =      'D';  // Delete the current entry from the tree.
const char InsertCmd =      'I';  // Add a new word to the tree.
const char ByLevelCmd =     'L';  // Show the tree level-by-level.
const char OpenCmd =        'O';  // Read in a tree from a file.
const char PostOrderCmd =   'P';  // Show the tree in postorder
const char QuitCmd =        'Q';  // Quit
const char ExecuteCmd =     'X';  // Execute command file.

// File mode characters
const char ReadMode =       'R';  // Open for reading
const char WriteMode =      'W';  // Open for Writing

//----- f u n c t i o n    p r o t o t y p e s -----

void DoExecute(string cmdLine, BST<WordCount> &wordTree);
string GetCmd(istream &cmdStream, BST<WordCount> &wordTree);
string GetFileName(string cmdLine);
bool OpenFile(string cmdLine, fstream &stream, char mode);
void AddWord(string cmdLine, BST<WordCount> &wordTree);
void DeleteWord(string cmdLine, BST<WordCount> &wordTree);
void ReadFile(string cmdLine, BST<WordCount> &wordTree);
void DisplayTree(BST<WordCount> wordTree);
void Execute(istream &cmdStream, BST<WordCount> &wordTree);
string UnCapitalize(string word);

/*--------------- U n C a p i t a l i z e ( ) ---------------

PURPOSE
Convert letters to lower case and delete non-alphabetic
characters from a string.

INPUT PARAMETERS
word  -- the word to uncapitialize
*/
string UnCapitalize(string word)
{
  string result = "";

  for(unsigned i=0; i<word.length(); ++i)
    if (isalpha(word[i]))
      result += tolower(word[i]);

  return result;
}

/*--------------- A d d W o r d ( ) ---------------

PURPOSE
Add a new word to the tree.

INPUT PARAMETERS
cmdLine     --  the command line
wordTree    --  the tree
*/
void AddWord(string cmdLine, BST<WordCount> &wordTree)
{
  const unsigned  MinCmdSize = 2;     // To check for an empty add command

  string word;                        // New word
  istringstream   cmdStream(cmdLine); // Command stream

  // Ignore if empty add parameters.
  if (cmdLine.length() < MinCmdSize)
    return;
      
  // Read the new word and insert it into the tree.
  cmdStream.get();   // Discard command character.
  cmdStream >> word;

  wordTree.Insert(WordCount(UnCapitalize(word)));
}

/*--------------- D e l e t e W o r d ( ) ---------------

PURPOSE
Delete the current node from the tree.

INPUT PARAMETERS
cmdLine     --  the command line
wordTree    --  the tree
*/
void DeleteWord(string cmdLine, BST<WordCount> &wordTree)
{
  const unsigned  MinCmdSize = 2;     // To check for an empty delete command

  string word;                        // Word to delete
  istringstream   cmdStream(cmdLine); // Command stream

  // Ignore if no command parameters.
  if (cmdLine.length() < MinCmdSize)
    return;
      
  // Read the word to delete.
  cmdStream.get();   // Discard command character.
  cmdStream >> word;

  // If the word is in the tree, delete it.
  if (wordTree.Search(WordCount(UnCapitalize(word))))
    wordTree.Delete();
  else
    cout << "\"" << word << "\"" << " is not in the tree." << endl;
}

/*--------------- R e a d F i l e ( ) ---------------

PURPOSE
Read in a text file, adding words to the tree.

INPUT PARAMETERS
cmdLine     --  the command line.
wordTree    --  the tree.
*/
void ReadFile(string cmdLine, BST<WordCount> &wordTree)
{
  fstream  wordStream;  // The input stream

  if (!OpenFile(cmdLine, wordStream, ReadMode))
    return;

  // Read in the entire file and build
  // the tree.
  while (wordStream.peek() != EOF)
    {
    string word;

    wordStream >> word;
    if (word.length() > 0)
      wordTree.Insert(WordCount(UnCapitalize(word)));
    }

  wordStream.close();
}


//--------------- m a i n ( ) ---------------

int main()
{
  BST<WordCount>  wordTree; // The word tree

//	MaxConsoleWin();

	// Execute commands from the stream cin.

	Execute(cin, wordTree);

  return 0;
}

/*--------------- E x e c u t e ( ) ---------------

PURPOSE
Execute a command stream, either from cin of
from a command file

INPUT PARAMETERS
cmdStream -- the stream from which commands are to be read
route     -- the route list.
*/
void Execute(istream &cmdStream, BST<WordCount> &wordTree)
{
  string cmdLine; // The current command line

  // Repeatedly get a command from the keyboard and
  // execute it.
  do
    {
#if !NoGraphics    
    wordTree.ShowTree();
#endif
    cmdLine = GetCmd(cmdStream, wordTree);

    if (cmdLine.length() != 0)
      {
      // Determine which command to execute.
      switch (toupper(cmdLine[0]))
        {
        case ExecuteCmd:    // Execute a command file.
          DoExecute(cmdLine, wordTree);
          break;
       case InsertCmd:      // Add a new word to the tree.
          AddWord(cmdLine, wordTree);
          break;
        case DeleteCmd:     // Delete the current entry.
          DeleteWord(cmdLine, wordTree);
          break;
        case ShowCmd:       // Show the word tree on the display inorder.
          wordTree.OutputInOrder(cout);
          break;
        case OpenCmd:       // Read in a file.
          ReadFile(cmdLine, wordTree);
          break;
        case QuitCmd:       // Terminate execution.
          break;
        case PreOrderCmd:   // Show the tree in preorder.
          wordTree.OutputPreOrder(cout);
          break;
        case PostOrderCmd:  // Show the tree in postorder.
          wordTree.OutputPostOrder(cout);
          break;
        case ByLevelCmd:    // Show the tree one level at a time.
		  wordTree.OutputByLevel(cout);
          break;
        default:            // Bad command
          cout << "*** Error: Unknown Command" << endl;
          break;
        }
      }
    }
  while (toupper(cmdLine[0]) != QuitCmd);
}

/*--------------- D o E x c u t e ( ) ---------------

PURPOSE
Get a command file name and execute the file.

INPUT PARAMETERS
cmdLine  -- the execute command command line.
wordTree -- the alphabetized word tree.
*/
void DoExecute(string cmdLine, BST<WordCount> &wordTree)
{
  fstream  cmdStream;  // The input stream

  if (!OpenFile(cmdLine, cmdStream, ReadMode))
    return;

  Execute(cmdStream, wordTree);
}

/*--------------- G e t C m d ( ) ---------------

PURPOSE
Accept a command from the keyboard.

INPUT PARAMETERS
wordTree -- the alphabetized word tree.

RETURN VALUE
The command string
*/
string GetCmd(istream &cmdStream, BST<WordCount> &wordTree)
{
  string cmdLine;

  // Prompt for a new command.
  cout << ">";

  // If empty command, force a Quit command.
  if (cmdStream.peek() == EOF)
    {
    cmdLine = QuitCmd;

    return cmdLine;
    }

  // Read the command line.
  getline(cmdStream, cmdLine);

  // If not from the keyboard, echo the command on the screen.
  if (cmdStream != cin)
    cout << cmdLine << endl;

  return cmdLine;
}

/*--------------- O p e n F i l e ( ) ---------------

PURPOSE
Associate an fstream with a file

INPUT PARAMETERS
cmdLime -- the command line containing the file name
mode    -- 'R' for reading, 'W' for writing

OUTPUT PARAMETERS
stream  - the opened stream

RETURN VALUE
true if the file was opened successfully,
false otherwise
*/
bool OpenFile(string cmdLine, fstream &stream, char mode)
{
  string    fileName;    // The input file name

  // Ask for the file name and then open the file.
  fileName = GetFileName(cmdLine);
  if (fileName.length() == 0)
    return false;

  //Validate the file open mode.
  mode = toupper(mode);
  assert (mode == ReadMode || mode == WriteMode);

  // Open the file in read or write mode.
  if (mode == ReadMode)
    stream.open(fileName.c_str(), fstream::in);
  else
    stream.open(fileName.c_str(), fstream::out);

  // Verify that the file exists and was opened successfully.
  if (!stream.is_open())
    {
    cout << "*** ERROR: No such file " << fileName << endl;
    return false;
    }
    
  return true;
}

/*--------------- G e t F i l e N a m e ( ) ---------------

PURPOSE
Get a file name from the command line.

RETURN VALUE
the file name or empty string if none.
*/
string GetFileName(string cmdLine)
{
  string        fileName;           // The file name
  istringstream cmdStream(cmdLine); // The command stream

  // If empty, return an empty string.
  if (cmdLine.length() == 0)
    return "";

  // Skip over whitespace.
  do
    {
    cmdStream.get();
    }
  while (isspace(cmdStream.peek()));

  // Get the file name from the command line.
  getline(cmdStream, fileName);

  return fileName;
}



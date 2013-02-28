/*--------------- P r o g 9 . c p p ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Department
      UMASS Lowell

PURPOSE
Count the number of occurrences of each word in a file

DEMONSTRATES
Heaps and Heap Sort
Static Data Member

CHANGES
11-19-2009  gpc - Created for 16.322 
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include <cassert>

using namespace std;

#include "WordCount.h"
#include "Heap_T.h"

//----- c o n s t a n t    d e f i n i t i o n s -----

// Command Letters
const char AlphaCmd =       'A';  // Show the word list in alphabetical order.
const char ClearCmd =       'C';  // Erase the entire list.
const char DeleteCmd =      'D';  // Delete the maximum entry from the heap.
const char InsertCmd =      'I';  // Insert a new word into the word list
const char NumericCmd =     'N';  // Show the word list in numerical order.
const char OpenCmd =        'O';  // Read in a word list from a file.
const char QuitCmd =        'Q';  // Quit
const char ExecuteCmd =     'X';  // Execute command file.

// File mode characters
const char ReadMode =       'R';  // Open for reading
const char WriteMode =      'W';  // Open for Writing

const unsigned MaxWords = 100;		// Heap capacity

//----- f u n c t i o n    p r o t o t y p e s -----

void DoExecute(string cmdLine, Heap <WordCount, MaxWords>  &wordHeap);
string GetCmd(istream &cmdStream, Heap <WordCount, MaxWords>  &wordHeap);
string GetFileName(string cmdLine);
bool OpenFile(string cmdLine, fstream &stream, char mode);
void InsertWord(string word, Heap <WordCount, MaxWords>  &wordHeap);
void AddWord(string cmdLine, Heap <WordCount, MaxWords>  &wordHeap);
void Delete(Heap <WordCount, MaxWords>  &wordHeap);
void ReadFile(string cmdLine, Heap <WordCount, MaxWords>  &wordHeap);
void Execute(istream &cmdStream, Heap <WordCount, MaxWords>  &wordHeap);
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

/*--------------- I n s e r t W o r d ( ) ---------------

PURPOSE
Insert a word into the word list.

INPUT PARAMETERS
word        --  the word to insert
wordHeap    --  the heap
*/
void InsertWord(string word, Heap <WordCount, MaxWords>  &wordHeap)
{
  // Set alphabetic sort order.
  WordCount::alpha = true;

	// Check that the heap is not full.
	if (wordHeap.Full())
    {
    cout << "The list is full." << endl;
    return;
    }

	// Force lower case.
  word = UnCapitalize(word);
  
  // If the word is already listed, increment the count; otherwise,
  // insert it into the list.
	wordHeap.Sort();
  if (wordHeap.Search(WordCount(word)))
		{
    wordHeap.CurrentEntry().Update();
		wordHeap.Heapify();
		}
  else
    {
    wordHeap.Heapify();
    wordHeap.Insert(WordCount(word));
    }    
}

/*--------------- A d d W o r d ( ) ---------------

PURPOSE
Add a new word to the heap.

INPUT PARAMETERS
cmdLine     --  the command line
wordHeap    --  the heap
*/
void AddWord(string cmdLine, Heap <WordCount, MaxWords>  &wordHeap)
{
  const unsigned  MinCmdSize = 2;     // To check for an empty add command

  string word;                        // New word
  istringstream   cmdStream(cmdLine); // Command stream

  // Ignore if empty add parameters.
  if (cmdLine.length() < MinCmdSize)
    return;
      
  // Read the new word and insert it into the heap.
  cmdStream.get();   // Discard command character.
  cmdStream >> word;
  
  InsertWord(word, wordHeap);
}

/*--------------- D e l e t e ( ) ---------------

PURPOSE
Delete the current node from the heap.

INPUT PARAMETERS
cmdLine     --  the command line
wordHeap    --  the heap
*/
void Delete(Heap <WordCount, MaxWords>  &wordHeap)
{
  if (wordHeap.Empty())
    {
    cout << "The list is empty." << endl;
    
    return;
    }
  wordHeap.DeleteMax();
}

/*--------------- R e a d F i l e ( ) ---------------

PURPOSE
Read in a text file, adding words to the heap.

INPUT PARAMETERS
cmdLine     --  the command line.
wordHeap    --  the heap.
*/
void ReadFile(string cmdLine, Heap <WordCount, MaxWords>  &wordHeap)
{
  fstream  wordStream;  // The input stream

  if (!OpenFile(cmdLine, wordStream, ReadMode))
    return;

  // Read in the entire file and build
  // the heap.
  for (;;)
    {
    string word;

    wordStream >> word;

    if (wordStream.eof())
      break;
      
    InsertWord(word, wordHeap);      
    }

  wordStream.close();
}


//--------------- m a i n ( ) ---------------

// Instantiate WordCount static member.
bool WordCount::alpha;

int main()
{
  
  WordCount::alpha = true;
  
  Heap<WordCount, MaxWords>  wordHeap; // The word heap

  // Execute commands from the stream cin.
  Execute(cin, wordHeap);

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
void Execute(istream &cmdStream, Heap <WordCount, MaxWords>  &wordHeap)
{
  string cmdLine; // The current command line

  // Repeatedly get a command from the keyboard and
  // execute it.
  do
    {
#if !NoGraphics    
    wordHeap.ShowTree();
#endif
    cmdLine = GetCmd(cmdStream, wordHeap);

    if (cmdLine.length() != 0)
      {
      // Determine which command to execute.
      switch (toupper(cmdLine[0]))
        {
        case ExecuteCmd:    // Execute a command file.
          DoExecute(cmdLine, wordHeap);
          break;
       case InsertCmd:      // Add a new word to the heap.
          AddWord(cmdLine, wordHeap);
          break;
        case DeleteCmd:     // Delete the current entry.
          Delete(wordHeap);
          break;
        case ClearCmd:
          while (!wordHeap.Empty())
            Delete(wordHeap);
          break;
        case AlphaCmd:       // Show the word heap on the display inorder.
          WordCount::alpha = true;
          wordHeap.Sort();
          wordHeap.Output(cout);
					wordHeap.Heapify();
          break;
        case NumericCmd:       // Show the word heap on the display inorder.
          WordCount::alpha = false;
          wordHeap.Sort();
          wordHeap.Output(cout);
					wordHeap.Heapify();
          break;
        case OpenCmd:       // Read in a file.
          ReadFile(cmdLine, wordHeap);
          break;
        case QuitCmd:       // Terminate execution.
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
wordHeap -- the alphabetized word heap.
*/
void DoExecute(string cmdLine, Heap <WordCount, MaxWords>  &wordHeap)
{
  fstream  cmdStream;  // The input stream

  if (!OpenFile(cmdLine, cmdStream, ReadMode))
    return;

  Execute(cmdStream, wordHeap);
}

/*--------------- G e t C m d ( ) ---------------

PURPOSE
Accept a command from the keyboard.

INPUT PARAMETERS
wordHeap -- the alphabetized word heap.

RETURN VALUE
The command string
*/
string GetCmd(istream &cmdStream, Heap <WordCount, MaxWords>  &wordHeap)
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



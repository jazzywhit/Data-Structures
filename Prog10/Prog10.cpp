/*--------------- P r o g 1 0 . c p p ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Department
      UMASS Lowell

PURPOSE
Count the number of occurrences of each word in a file

DEMONSTRATES
Hash Tables

CHANGES
11-23-2011  gpc - Created for 16.322 
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include <cassert>

using namespace std;

#include "Utility.h"

#include "WordCount.h"
#include "HashTable_T.h"
#include "BST_T.h"

//----- c o n s t a n t    d e f i n i t i o n s -----
// Number of buckets in the hash table dictionary.
// If not defined already, define it here.
#ifndef NumBucks
#define NumBucks 11 // Default number of buckets if not overridden externally
#endif

// Make sure that the number of buckets is at least 1,
#if NumBucks < 1
#error Number of buckets must be a whole number no less than 1.
#endif

const unsigned NumBuckets = NumBucks;

// Command Letters
const char AlphaCmd =       'A';  // Show the word list in alphabetical order.
const char ClearCmd =       'C';  // Erase the entire list.
const char DeleteCmd =      'D';  // Delete a word from the hash table.
const char InsertCmd =      'I';  // Insert a new word into the word list
const char OpenCmd =        'O';  // Read in a word list from a file.
const char QuitCmd =        'Q';  // Quit
const char ExecuteCmd =     'X';  // Execute command file.

// File mode characters
const char ReadMode =       'R';  // Open for reading
const char WriteMode =      'W';  // Open for Writing

//----- f u n c t i o n    p r o t o t y p e s -----

void DoExecute(string cmdLine, HashTable <WordCount, NumBuckets>  &wordTable);
string GetCmd(istream &cmdStream, HashTable <WordCount, NumBuckets>  &wordTable);
string GetFileName(string cmdLine);
bool OpenFile(string cmdLine, fstream &stream, char mode);
void InsertWord(string word, HashTable <WordCount, NumBuckets>  &wordTable);
void AddWord(string cmdLine, HashTable <WordCount, NumBuckets>  &wordTable);
void DeleteWord(string cmdLine, HashTable <WordCount, NumBuckets>  &wordTable);
void ReadFile(string cmdLine, HashTable <WordCount, NumBuckets>  &wordTable);
void Execute(istream &cmdStream, HashTable <WordCount, NumBuckets>  &wordTable);
void ShowTable(HashTable <WordCount, NumBuckets>  &wordTable);
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
wordTable   --  the hash table
*/
void InsertWord(string word, HashTable <WordCount, NumBuckets>  &wordTable)
{
  // Force lower case.
  word = UnCapitalize(word);
  
  // If the word is already listed, increment the count; otherwise,
  // insert it into the list.
  if (wordTable.Search(WordCount(word)))
    wordTable.CurrentEntry().Update();
  else
    wordTable.Insert(WordCount(word));
}

/*--------------- A d d W o r d ( ) ---------------

PURPOSE
Add a new word to the hash table.

INPUT PARAMETERS
cmdLine     --  the command line
wordTable   --  the hash table
*/
void AddWord(string cmdLine, HashTable <WordCount, NumBuckets>  &wordTable)
{
  const unsigned  MinCmdSize = 2;     // To check for an empty add command

  string word;                        // New word
  istringstream   cmdStream(cmdLine); // Command stream

  // Ignore if empty add parameters.
  if (cmdLine.length() < MinCmdSize)
    return;
      
  // Read the new word and insert it into the hash table.
  cmdStream.get();   // Discard command character.
  cmdStream >> word;
  
  InsertWord(word, wordTable);
}

/*--------------- D e l e t e W o r d ( ) ---------------

PURPOSE
Delete the current node from the hash table.

INPUT PARAMETERS
cmdLine     --  the command line
wordTable   --  the hash table
*/
void DeleteWord(string cmdLine, HashTable <WordCount, NumBuckets>  &wordTable)
{
  if (wordTable.Size() == 0)
    {
    cout << "The list is empty." << endl;
    
    return;
    }
    
  const unsigned  MinCmdSize = 2;     // To check for an empty delete command

  string word;                        // Word to delete
  istringstream   cmdStream(cmdLine); // Command stream

  // Ignore if no command parameters.
  if (cmdLine.length() < MinCmdSize)
    return;
      
  // Read the word to delete.
  cmdStream.get();   // Discard command character.
  cmdStream >> word;

  // If the word is in the table, delete it.
  if (wordTable.Search(WordCount(UnCapitalize(word))))
    wordTable.Delete();
  else
    cout << "\"" << word << "\"" << " is not in the table." << endl;
}

/*--------------- R e a d F i l e ( ) ---------------

PURPOSE
Read in a text file, adding words to the hash table.

INPUT PARAMETERS
cmdLine     --  the command line.
wordTable   --  the hash table.
*/
void ReadFile(string cmdLine, HashTable <WordCount, NumBuckets>  &wordTable)
{
  fstream  wordStream;  // The input stream

  if (!OpenFile(cmdLine, wordStream, ReadMode))
    return;

  // Read in the entire file and build
  // the hash table.
  for (;;)
    {
    string word;

    wordStream >> word;

    if (wordStream.eof())
      break;
      
    InsertWord(word, wordTable);      
    }

  wordStream.close();
}


//--------------- m a i n ( ) ---------------

int main()
{
  HashTable<WordCount, NumBuckets>  wordTable; // The word hash table

  // Execute commands from the stream cin.
  Execute(cin, wordTable);

  return 0;
}

/*--------------- E x e c u t e ( ) ---------------

PURPOSE
Execute a command stream, either from cin of
from a command file

INPUT PARAMETERS
cmdStream -- the stream from which commands are to be read
wordTable -- the word hash table
*/
void Execute(istream &cmdStream, HashTable <WordCount, NumBuckets>  &wordTable)
{
  string cmdLine; // The current command line

  // Repeatedly get a command from the keyboard and
  // execute it.
  do
    {
#if !NoGraphics    
    wordTable.Show();
#endif
    cmdLine = GetCmd(cmdStream, wordTable);

    if (cmdLine.length() != 0)
      {
      // Determine which command to execute.
      switch (toupper(cmdLine[0]))
        {
        case ExecuteCmd:    // Execute a command file.
          DoExecute(cmdLine, wordTable);
          break;
       case InsertCmd:      // Add a new word to the hash table.
          AddWord(cmdLine, wordTable);
          break;
        case DeleteCmd:     // Delete the current entry.
          DeleteWord(cmdLine, wordTable);
          break;
        case ClearCmd:
          while (!wordTable.Empty())
            wordTable.Remove();
          break;
        case AlphaCmd:       // Show the word table on the display in alphabetical order.
          ShowTable(wordTable);
          break;
        case OpenCmd:       // Read in a file.
          ReadFile(cmdLine, wordTable);
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
cmdLine   -- the execute command command line.
wordTable -- the word hash table.
*/
void DoExecute(string cmdLine, HashTable <WordCount, NumBuckets>  &wordTable)
{
  fstream  cmdStream;  // The input stream

  if (!OpenFile(cmdLine, cmdStream, ReadMode))
    return;

  Execute(cmdStream, wordTable);
}

/*--------------- G e t C m d ( ) ---------------

PURPOSE
Accept a command from the keyboard.

INPUT PARAMETERS
wordTable -- the word hash table.

RETURN VALUE
The command string
*/
string GetCmd(istream &cmdStream, HashTable <WordCount, NumBuckets>  &wordTable)
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


/*--------------- S h o w T a b l e ( ) ---------------

PURPOSE
Show the word list in alphabetical order .

INPUT PARAMETERS
wordTable   -  the word hash table
*/
void ShowTable(HashTable <WordCount, NumBuckets>  &wordTable)
{
   // Remove one word at a time from the hash table and
   // insert the word into a heap.
   const unsigned HeapCapacity = 20;
   
   BST<WordCount>  wordTree;
   
   while (wordTable.Size() > 0)
      {
      WordCount   w = wordTable.Remove();
      
      wordTree.Insert(w);
      }
 
   // Dispaly the word list in order.  
   wordTree.OutputInOrder(cout);
 
   // Remove one word at a time from the heap and
   // insert the word into the hash table.
   while (!wordTree.Empty())
		{
    WordCount wc = wordTree.RemoveLeaf();
    wordTable.Insert(wc);
		}
}
/*--------------- W o r d C o u n t . h ---------------

by:   George Cheney
      16.322 Data Structures
      ECE Department
      UMASS Lowell

PURPOSE
Defines class WordCount to count the number of occurrences of words.

CHANGES
11-11-2009  gpc - Created for 16.322 
11-20-2009  gpc - Added static data member to facilitate both alphabetic
                  as well as numeric sort order
*/

#include <iostream>
#include <string>

using namespace std;

//------ C l a s s    D e f i n i t i o n -----

//----- C l a s s    W o r d C o u n t -----

//Records one word and a count of the number of occurences of that word.

class WordCount
{
public:
   static bool alpha;    // Determine sort order, true = alphabetic, false = numeric
   // Constructors
   WordCount() : word(""), count(0) { }
   WordCount(string theWord, unsigned theCount = 1) : word(theWord), count(theCount) { }
   // Accessors
   string Word() const { return word; }
   unsigned Count() const { return count; }
   // Mutator
   void Update() { ++count; }
   // Output a Word to a stream.
   void Show(ostream &os)  { if (alpha) os << word << "=" << count; else os << count << "=" << word; }
   // Overloaded relational operators
	bool operator<(WordCount &rhs) { return alpha ? word < rhs.word : count < rhs.count;}
	bool operator<=(WordCount &rhs) { return alpha ? word <= rhs.word : count <= rhs.count;}
	bool operator>(WordCount &rhs) { return alpha ? word > rhs.word : count > rhs.count;}
	bool operator>=(WordCount &rhs) { return alpha ? word >= rhs.word : count >= rhs.count;}
	bool operator==(WordCount &rhs) { return alpha ? word == rhs.word : count == rhs.count;}
	bool operator!=(WordCount &rhs) { return alpha ? word != rhs.word : count != rhs.count;}
private:
   string   word;    // The word to be counted
   unsigned count;   // The number of occurrences
};


/*--------------- o p e r a t o r < < ( ) ---------------

PURPOSE
Defines overloaded output operator for WordCount objects

INPUT PARAMETERS
os    -- The stream to which the WordCount is to be output
w     -- the WordCount

RETURN VALUE
the stream
*/
ostream &operator<<(ostream &os, WordCount w)
{
   w.Show(os);
   
   return os;
}   
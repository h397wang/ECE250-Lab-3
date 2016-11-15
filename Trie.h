
/*
 1
ECE250: Lab Project 3
Due Date: Saturday, November 19, 2016 – 11:00PM
1 Project Description
In this project you will implement a trie data structure using recursive programming. A trie is a 26-ary
tree where the root node represents an empty string “” and if the kth (k going from 0 to 25) sub-tree is not
a null sub-tree, it represents a string that is the concatenation of string represented by the parent and the
kth letter of the alphabet (where a is the 0th letter, b is the 1st letter, and so on). Each node may or may not
indicate that it is a terminal entry for a word. While a trie could be used to store hyphenated and
capitalized words together with those with apostrophes, we will restrict ourselves to words made up of the
twenty-six letters of the English alphabet.
For example, consider the sentence “The fable then faded from my thoughts and memory”. If we wanted
to put these nine words into a Trie, it would look like Figure 1. Only the root node explicitly shows its 26
sub-trees, each sub-tree being associated with a letter of the alphabet. In this example, 22 of the sub-trees
of the root node are null, as there are no words that begin with, for example, ‘b’. Four of the children of
the root are not null: those representing the letters ‘a’, ‘f’, ‘m’, and‘t’. For the other nodes, only the nonnull
sub-trees are shown. These sub-trees represent words starting with these letters, respectively.
Terminal nodes are represented as red circles.
Figure 1. A trie containing the words in the sentence “The fable then
faded from my thoughts and memory”
 2
2 Characters and Strings
In this project you need to work with characters and strings. A string is a list of characters. In C, a string
of n characters is an array of type char of size n + 1 or greater where the (n + 1)th character is the null
character '\0'. Fortunately, in C++, there is a string class in the standard library. You can include this
library with: #include <string.h>. As this is in the standard template library, the class is defined within
the std namespace: std::string. To access the kth character, use the index (similar to arrays). You can also
use the cctype library to work with characters.
3 How to Test Your Program
We use drivers and tester classes for automated marking, and provide them for you to use while you build
your solution. We also provide you with basic test cases, which can serve as a sample for you to create
more comprehensive test cases. You can find the testing files on the course website.
4 How to Submit Your Program
Once you have completed your solution, and tested it comprehensively, you need to build a compressed
file, in tar.gz format, which should contain the file:
• Trie.h
• Trie_node.h
Build your tar file using the UNIX tar command as given below:
• tar –cvzf xxxxxxxx_pn.tar.gz Trie.h Trie_node.h
where xxxxxxxx is your UW user id (i.e., jsmith), and n is the project number which is 3 for this project.
All characters in the file name must be lowercase. Submit your tar.gz file using LEARN, in the drop box
corresponding to this project
5 Class Specifications
In this project, you will implement two classes: Trie.h that contains the root node, from where every other
node in the tree can be reached, and Trie_node.h that represents each node in the tree.
5.1 Trie.h
This is the class that implements a trie. In the following, the variable n represents length of a string; that
is, the number of characters making up the string. This trie tree is not case sensitive; that is, the words
“Hello”, “hello” and “HELLO” all represent the same word. In these examples, we converted all letters
into lower-case; however, you may chose to convert all letters into upper-case—it works either way. The
expected running time of each member function is specified in parentheses at the end of the function
description (? indicates the number of characters in the string and ? indicates the number of strings).
Member Variables
The Trie class has two member variables:
• A pointer to the root node, and
• An integer variable storing the number of words in the tree (that is, the size).
Accessors
This class has four accessors:
• bool empty() const - Return true if the trie is empty (the size is 0). (O(1))
• int size() const - Returns the number of words in the trie. (O(1))
• Trie_node *root() const - Returns a pointer to the root node. (O(1))
• bool member( std::String str ) const - Return true if the word represented by the string is in the
Trie and false otherwise. If the string contains any characters other than those of the English
alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw an illegal_argument exception. (O(n))
 3
Mutators
This class has three mutators:
• bool insert( std::string str) - Insert the word represented by str into the tree. If the string contains
any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw
an illegal_argument exception; otherwise if the string is already in the tree, return false;
otherwise, return true (the insertion was successful). This is done by calling insert on the root, and
if the root node is null, it will be necessary create an instance of the Trie_node class and assign it
to the root first. (O(n))
• bool erase( std::string str) - Erase the word represented by str from the tree. If the string contains
any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw
an illegal_argument exception; otherwise if the string is not in the tree, return false; otherwise,
return true (the erase was successful). If the tree is empty, return false, otherwise this function
calls erase on the root. If the word erased is the last one in the tree, delete the root node. (O(n))
• void clear() - Delete all the nodes in the tree. Again, if the tree is not empty, it should just call
clear on the root and set the appropriate member variables. (O(N) where N is the number of
words in the tree)
Please note, you are allowed to any additional member functions you wish; however, they should be
private to the Trie class as they are not specified in this interface.
5.2 Trie_node.h
This class implements the nodes of trie. The expected running time of each member function is specified
in parentheses at the end of the function description.
Member Variables
This Trie_node has two member variables:
• A pointer to an array of pointers to trie nodes, and
• A Boolean flag indicating whether a node represents a terminal node for a word.
There is also a constant static member variable CHARACTERS that is assigned the value 26.
Constructor
The constructor sets the pointer to children to null and sets the Boolean flag to false.
Accessors
This Trie_node class has two accessors:
• Trie_node *child( int n ) const - Return a pointer to the n-th child. If the children array is empty,
return NULL; otherwise, just return children[i]. This member function will never be called with a
value outside 0 to 25. (O(1))
• bool member( std::string const &str, int depth ) const - The string being searched for is being
passed recursively; however, as we go deeper into the tree, we must have access to the character
corresponding to the depth. You can assume that the characters are all alphabetical, as the
Trie class should have checked for invalid characters. The trie tree is not case sensitive, so you
must map letters to the range 0 to 25. If we are at the end of the word, the is_terminal member
variable will determine the appropriate return value; otherwise, we need to call member
recursively or return false, as appropriate. You must return the appropriate values in all cases,
including: when children are null, when the appropriate child pointer is assigned null, and
otherwise. (O(n)).
 4
Mutators
This class has three mutators:
• bool insert( std::string const &str, int depth ) - Like member accessor function, we need to
recurse into the tree. If we reach a node and we are at the end of the word we are attempting to
insert, we need only check and possibly modify the member variable is_terminal to determine the
appropriate return value. If we are not yet at the end of the word, we must recurse through the
appropriate sub-tree. This may require first assigning an array of 26 pointers to Trie nodes to
children in some cases, and it may require assigning a new Trie node to the kth sub-tree of this
array. (O(n))
• bool erase( std::string const &, int depth, B, Trie_node *&ptr_to_this ) - Like member accessor
function, we need to recurse into the tree. If we reach the end of branch of the tree before we get
to the end of the word, it is clear the word is not stored in this tree and thus cannot be erased. If
we get to a node when we are the end of the word, we must choose the appropriate course of
action and the appropriate return value based on the value of is_terminal. If this node is a leaf
node (children is assigned null), we should delete this node. While we are recursing back, if the
children array became entirely unassigned as a result of our erase, the current node must also be
erased. For example, in Figure 1, if the word "thoughts" was erased, then the nodes containing
“o”, “u”, “g”, “h”, ”t”, and “s” must be deleted and the appropriate sub-child of the node
containing “h” must be set to null. (O(n))
• void clear() - Calls clear on all sub-trees and deletes this node.

*/


/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef TRIE_H
#define TRIE_H


#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		bool illegalArgument(std::string const &) const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():root_node( NULL ), trie_size( 0 ) {
	// empty constructor
}


Trie::~Trie() {
	cout << "Destructor called" << endl;
	clear();
	// clear already deletes the root node
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	if (size() == 0){
		return true;
	}else{
		return false;
	}
}

Trie_node *Trie::root() const {
	return root_node;
}

// check if the string is valid
bool Trie::illegalArgument(std::string const &str) const{
	
	// check for illegal arguments
	for (int i = 0; i < str.size(); i++){
		if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z'){
			return true;
		}
	}
	return false;
	
}


/*
Return true if the word represented by the string is in the
Trie and false otherwise. If the string contains any characters other than those of the English
alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw an illegal_argument exception. (O(n))
*/
bool Trie::member( std::string const &str ) const {
	
	if (illegalArgument(str)){
		throw illegal_argument();
	}
	
	// first check if its empty
	if (empty()){
		return false;
	}
	
	// call the recursive member function. root node garanteed to be not NULL pointer
	return root_node->member(str, 0);
	
}

/*
Insert the word represented by str into the tree. If the string contains
any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw
an illegal_argument exception; otherwise if the string is already in the tree, return false;
otherwise, return true (the insertion was successful). This is done by calling insert on the root, and
if the root node is null, it will be necessary create an instance of the Trie_node class and assign it
to the root first. (O(n))
*/
bool Trie::insert( std::string const &str ) {
	
	if (illegalArgument(str)){
		throw illegal_argument();
	}
	
	// if the string is already in the tree, return false
	if (member(str)){
		return false;
	}
	
	//cout << "member function returned " << endl;
	
	if (root_node == NULL){
		root_node = new Trie_node();
	}
	
	//cout << "Before root-insert " << endl;
	root_node->insert(str, 0);
	//cout << "After root-insert " << endl;
	
	trie_size++;
	
	return true;
	
}

/*
Erase the word represented by str from the tree. If the string contains
any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw
an illegal_argument exception; otherwise if the string is not in the tree, return false; otherwise,
return true (the erase was successful). If the tree is empty, return false, otherwise this function
calls erase on the root. If the word erased is the last one in the tree, delete the root node. (O(n))
*/

bool Trie::erase( std::string const &str ) {
	
	if (illegalArgument(str)){
		throw illegal_argument();
	}
	
	// implies is empty...
	if (root_node == NULL){
		return false;
	}
	
	if (!member(str)) {
		return false;
	}
	
	// if size == 1 then delete the root ptr
	Trie_node * inPtr = NULL;
	root_node->erase(str, 0, inPtr);
	// was passing in root_node but memory was not being deallocated properly
		
	trie_size--;
		
	if (trie_size == 0){ // last word was deleted, delete root
		// clear function would automatically call delete on root_node
		root_node = NULL;
	}
	
	return true;

}

/*
Delete all the nodes in the tree. Again, if the tree is not empty, it should just call
clear on the root and set the appropriate member variables. (O(N) where N is the number of
words in the tree)
*/
void Trie::clear() {
	
	// recursive
	if (!empty() && root_node != NULL){ // being empty implies that root_node is null
		root_node->clear();	
		delete root_node; 
		root_node = NULL;
	}
	
	trie_size = 0;
	
}

// You can modify this function however you want:  it will not be tested
std::ostream &operator<<( std::ostream &out, Trie const &trie ) {
	
	
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif



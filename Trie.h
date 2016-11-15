/*
Build your tar file using the UNIX tar command as given below:
• tar –cvzf xxxxxxxx_pn.tar.gz Trie.h Trie_node.h
where xxxxxxxx is your UW user id (i.e., jsmith), and n is the project number which is 3 for this project.
All characters in the file name must be lowercase. Submit your tar.gz file using LEARN, in the drop box
corresponding to this project
*/


/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  h397wang@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall 2016)
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
	clear(); 
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

// check if the string is valid, it should have only alphabet characters
bool Trie::illegalArgument(std::string const &str) const{
	
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
	
	if (empty()){
		return false;
	}
	
	// call the recursive member() function, root_node is already garanteed to be not NULL
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
	
	// instantiate root_node if neccesary
	if (root_node == NULL){
		root_node = new Trie_node();
	}
	
	// call the recursive insert() function
	root_node->insert(str, 0);
	
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
	
	// check if it's empty first
	if (root_node == NULL){
		return false;
	}
	
	if (!member(str)) {
		return false;
	}
	
	
	// see the explanation of the recursive function for why inPtr = NULL 
	Trie_node * inPtr = NULL;	
	root_node->erase(str, 0, inPtr);
		
	trie_size--;
		
	// if the last word was deleted	
	if (trie_size == 0){ 
		
		// erase function would already delete root_node, but we have to set NULL here
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



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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string.h>
#include <cctype>
#include "ece250.h"

using namespace std;


class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;
	

	public:
		Trie_node();
		Trie_node *child( int ) const;
	
		bool member( std::string const &, int ) const;
	
		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};


Trie_node::Trie_node():children( nullptr ), is_terminal( false ) {
	// empty constructor
}

/*
Return a pointer to the n-th child. If the children array is empty,
return nullptr; otherwise, just return children[i]. This member function will never be called with a
value outside 0 to 25. (O(1))
*/

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}


/*
The string being searched for is being
passed recursively; however, as we go deeper into the tree, we must have access to the character
corresponding to the depth. You can assume that the characters are all alphabetical, as the
Trie class should have checked for invalid characters. The trie tree is not case sensitive, so you
must map letters to the range 0 to 25. If we are at the end of the word, the is_terminal member
variable will determine the appropriate return value; otherwise, we need to call member
recursively or return false, as appropriate. You must return the appropriate values in all cases,
including: when children are null, when the appropriate child pointer is assigned null, and
otherwise. (O(n)).
*/
bool Trie_node::member( std::string const &str, int depth ) const {
	
	// check for base recursive case
	if (depth == str.size()){
		if (is_Terminal){
			return true; 
	}
	
	// check if the char at the specified "depth" is stored here
	
	char c = str[depth];
	
	// first convert it to lower case
	if (c < 97){ // ascii for "a"
		c = c + 32; // offset between "A" and "a"
	}
	
	// map it to an integer by subtracting the ASCII value of "a"
	int index = c - 97; 
	
	// check for the char within the children array
	if (children == nullptr){
		return false;
	}
	
	if (children[index] == nullptr){ // then the word is obviously not stored
		return false;	
	}
	
	// recursively search for it 
	return children[index]->member(str, depth+1); 
	

}

/*
Like member accessor function, we need to
recurse into the tree. If we reach a node and we are at the end of the word we are attempting to
insert, we need only check and possibly modify the member variable is_terminal to determine the
appropriate return value. If we are not yet at the end of the word, we must recurse through the
appropriate sub-tree. This may require first assigning an array of 26 pointers to Trie nodes to
children in some cases, and it may require assigning a new Trie node to the kth sub-tree of this
array. (O(n))
this can't actually return false...
*/

bool Trie_node::insert( std::string const &str, int depth ) {
	
	// base case for recursion
	if (depth == str.size()){
		is_terminal = true;
		return true;
	}
	
	char c = str[depth];
	
	// first convert it to lower case
	if (c < 97){ // ascii for "a"
		c = c + 32; // offset between "A" and "a"
	}
	
	// map it to an integer by subtracting the ASCII value of "a"
	int index = c - 97; 
	
	if (children == nullptr){
		children = new Trie_node[26];
	}
	
	if (chilren[index] == nullptr){
		children[index] = new Trie_node();
	}
	
	return children[index]->insert(str, depth+1);
	
}

/*
- Like member accessor
function, we need to recurse into the tree. If we reach the end of branch of the tree before we get
to the end of the word, it is clear the word is not stored in this tree and thus cannot be erased. If
we get to a node when we are the end of the word, we must choose the appropriate course of
action and the appropriate return value based on the value of is_terminal. If this node is a leaf
node (children is assigned null), we should delete this node. While we are recursing back, if the
children array became entirely unassigned as a result of our erase, the current node must also be
erased. For example, in Figure 1, if the word "thoughts" was erased, then the nodes containing
“o”, “u”, “g”, “h”, ”t”, and “s” must be deleted and the appropriate sub-child of the node
containing “h” must be set to null. (O(n))
*/

// currently not sure how to traverse back up the tree....parent pointers would not be helpful at all...


// already checked to garantee the existence of the word in the tree...
bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	
	
	// base case of recursion
	if (depth == str.size()){ 
		delete this;
		
		// traverse up the tree
		Trie_node * currentPtr = ptr_to_this;
		while(currentPtr != root_node){
			
		
			currentPtr = 	
		}
		
		bool hasChildren = false;
		// check if ptr_to_this has any children left
		for (int i = 0; i < CHARACTERS; i++){
			if (ptr_to_this->children[i] != nullptr){
				hasChildren = true;
				break;
			}
		}
		
		if (!hasChildren){
			
			
	}
	
	char c = str[depth];
	
	// first convert it to lower case
	if (c < 97){ // ascii for "a"
		c = c + 32; // offset between "A" and "a"
	}
	
	// map it to an integer by subtracting the ASCII value of "a"
	int index = c - 97; 
	
	// i already know that its in the tree
	children[index]->erase(str, depth+1, this);
	
	return false;
}

void Trie_node::clear() {
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif

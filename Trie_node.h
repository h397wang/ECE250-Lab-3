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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

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
		Trie_node * parent;
	

	public:
		Trie_node();
		Trie_node *child( int ) const;
	
		bool member( std::string const &, int ) const;
	
		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;
		
		int countChildren() const;
		
		Trie_node * getParent() const;
		void setParent(Trie_node *);
		
		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};


Trie_node::Trie_node():children( NULL ), is_terminal( false ), parent(NULL) {
	// empty constructor
}

/*
Return a pointer to the n-th child. If the children array is empty,
return NULL; otherwise, just return children[i]. This member function will never be called with a
value outside 0 to 25. (O(1))
*/

Trie_node *Trie_node::child( int n ) const {
	if ( children == NULL ) {
		return NULL;
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

Input
string str: is guaranteed to be valid since error checks are done in the Trie.h
int depth: recursion goes through each char in the str, depth describes the index of the char within the string 
*/
bool Trie_node::member( std::string const &str, int depth ) const {
	
	// check for the recursion's base case
	if (depth == str.size()){
		if (is_terminal){
			return true; 
		}else{
			return false;
		}
	}
	
	
	// check if the char at the specified "depth" is stored here
	
	char c = str[depth];
	int index = 0;
	
	// first convert it to lower case
	if (c < 97){ // ascii for "a"
		index = c + 32; // offset between "A" and "a"
	}
	
	// map it to an integer by subtracting the ASCII value of "a"
	index = c - 97; 
	
	// check whether or not there are even any children nodes
	if (children == NULL){
		return false;
	}
	
	// check the particular child node that corresponds to the letter
	if (children[index] == NULL){ 
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
		
	if (children == NULL){
		children = new Trie_node*[26];
		// make them all null pointers
		for (int i = 0; i < CHARACTERS; i++){
			children[i] = NULL;
		}
	}
	
	if (children[index] == NULL){
		children[index] = new Trie_node();
	}
	
	children[index]->setParent(this);	
		
	return children[index]->insert(str, depth+1);
	
}


/*
Counts the number of children this node has.
Called by the erase function
*/
int Trie_node::countChildren() const{
	
	if (children == NULL){
		return 0;
	}
	
	int counter = 0;
	
	for (int i = 0; i < CHARACTERS; i++){
		if (children[i] != NULL){
			counter++;
		}
	}
	
	return counter;
}


// Required to traverse back up the tree
Trie_node * Trie_node::getParent() const {
	if (parent == NULL){
		return NULL;
	}else{
		return parent;
	}
}

void Trie_node::setParent(Trie_node * p ){
	parent = p;
}

/*
- Like member accessor
function, we need to recurse into the tree. If we reach the end of branch of the tree before we get
to the end of the word, it is clear the word is not stored in this tree and thus cannot be erased. 

If we get to a node when we are the end of the word, we must choose the appropriate course of
action and the appropriate return value based on the value of is_terminal. 

If this node is a leaf
node (children is assigned null), we should delete this node. While we are recursing back, if the
children array became entirely unassigned as a result of our erase, the current node must also be
erased. For example, in Figure 1, if the word "thoughts" was erased, then the nodes containing
“o”, “u”, “g”, “h”, ”t”, and “s” must be deleted and the appropriate sub-child of the node
containing “h” must be set to null. (O(n))

Input: 
string str: is garuanteed to exist in the tree based on prior checks
int depth: same as others
ptr_to_this: pointer to a node along the path towards the terminal node. This node
is updated (see conditions below) as we traverse down the tree. Upon reaching the terminal node, if the terminal node is 
a leaf, then we traverse up the tree and delete every node until we reach this ptr_to_this.
the node pointed to by ptr_to_this would NOT be deleted..   

Output: garuanteed to return true from this point because the membership was already determined
*/

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	
	// We've reached the base of the recursion
	if (depth == str.size()){ 
			
		// first clear the terminal flag
		is_terminal = false;
		
		if (children != NULL){ // if it's not a leaf node, then we're done
			
			return true;
		
		}else{  	
			
			// Delete every node in the path from ptr_to_this (exclusive) to this node (inclusive) 	
					
			Trie_node * currentPtr = getParent();
			
			// basically the depth as a traverse back up it lol
			int d = depth-1; 
			
			// I need a pointer to the root_node eventually...too lazy to learn friend shit
			Trie_node * root; 
			while (currentPtr != ptr_to_this){
				
				for (int i = 0; i < CHARACTERS; i++){
					if (currentPtr->child(i) != NULL){
						delete currentPtr->child(i);
					}
				}
				
				delete [] currentPtr->children;				
				// um dont do this here, it messes things up lol i dunno why
				//currentPtr->children = NULL;
				root = currentPtr;
				currentPtr = currentPtr->getParent();
				
				d = d-1;
			}
			
			
			if (currentPtr != NULL){
				char c = str[d];
				
				if (c < 97){ // ascii for "a"
					c = c + 32; // offset between "A" and "a"
				}
	
				// map it to an integer by subtracting the ASCII value of "a"
				int index = c - 97; 
				
				delete currentPtr->children[index];
				currentPtr->children[index] = NULL; // dont forget sigh
				
				// 12 bytes are not being deallocated
				if (currentPtr->countChildren() == 0){
					delete [] currentPtr->children;
					currentPtr->children = NULL; // dont forget holyfuck
					
				}
				
			}else{ // currentPtr is NULL, aka the whole thing must have been deleted, 
			// so delete the root_node
				delete root;
			}
			
			return true;
		}
		
	}
	
	char c = str[depth];
	int index = c;
	
	// first convert it to lower case
	if (c < 97){ // ascii for "a"
		index = c + 32; // offset between "A" and "a"
	}
	
	// map it to an integer by subtracting the ASCII value of "a"
	index = index - 97; 
	
//	cout << "determined index " << index << endl;
	// if this node is a terminal node, then update the input pointer
	// check how many children this node has to determine the input pointer
	Trie_node *inPtr = ptr_to_this;
	
	if (is_terminal){
		inPtr = this;
	}
	
	// I know it has at least 1 child
	if (countChildren() > 1){
		inPtr = this;	
	}
	
	//cout << "Calling recursion " << endl;
	
	children[index]->erase(str, depth+1, inPtr);
	
	return true; // garanteed to return true in my implementation
}

/*
- Calls clear on all sub-trees 
*/
// Recursively delete everything 
void Trie_node::clear() {
	
	
	// base case recursion 
	if (children == NULL){
		
		return;	
	}else{
		//cout << "children != NULL " << endl;
		
		
		for (int i = 0; i < CHARACTERS; i++){
			
			
			if (child(i) != NULL){
				//cout << "children[" << i << " != NULL" << endl;
				
				child(i)->clear();

				delete child(i);
				children[i] = NULL;
			}
			
		}
		
		//cout << "Clear about to delete [] children " << endl;
		delete [] children;
		children = NULL;
	}
		
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif

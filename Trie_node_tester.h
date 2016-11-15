/*************************************************
 * Trie_node_tester
 * A class for testing nodes used in singly linked lists.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2014 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef TRIE_NODE_TESTER_H
#define TRIE_NODE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Trie_node.h"

#include <iostream>

class Trie_node_tester:public Tester< Trie_node > {
	using Tester< Trie_node >::object;
	using Tester< Trie_node >::command;

	public:
		Trie_node_tester( Trie_node *obj = nullptr ):Tester< Trie_node >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For single nodes, these include:
 *
 *                 Member
 *   Flag         Function         Tests if ...
 *
 *  Accessors
 *
 *   child n          child( n )          the nth child pointer can be followed
 *   child0 n         child( n )          the nth child pointer is 'nullptr'
 ****************************************************/

void Trie_node_tester::process() {
	if ( command == "child" ) {
		int index;

		std::cin >> index;

		Trie_node *actual_child = Trie_node_tester::object->child( index );

		if ( actual_child != nullptr ) {
			object = actual_child;
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in child( " << index << " ): expecting to follow a non-null child pointer" << std::endl;
		}
	} else if ( command == "child0" ) {
		int index;

		std::cin >> index;

		if ( object->child( index ) == nullptr ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << ": Failure in child( " << index << " ): expecting a null (nullptr) child pointer" << std::endl;
		}
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif

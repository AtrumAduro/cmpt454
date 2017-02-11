/*BpTree.h
 * Authors: Dave Gill, Jackie Lang
 */

#ifndef BPTREE_H
#define BPTREE_H

#include <string>
#include "Node.h"
 class BpTree{
 	public:

 		/*
 		 *Default constructor. Creates an empty B+Tree with nodeSize n
 		 */
 		BpTree(int n);

 		BpTree(BpTree& other);

 		~BpTree();

 		/*
 		 *Inserts value into B+ Tree, sorted on key value
 		 *All key values must be unique, or insertion will fail
 		 *Returns true if insertion was successful, otherwise false
 		 */
 		bool insert(int key, std::string value);

 		/*
 		 *Removes the entry from the B+ Tree that corresponds to the key value
 		 *Returns true if the value was successfully removed, false if the value is not in the tree
 		 */
 		bool remove(int key);

 		/*
 		 *Returns the string value corresponding to the key
		 *If the key is not in the B+Tree, will return the empty string ""
 		 */
 		std::string find(int key) const;

 		/*
 		 *Prints all keys in the B+ Tree to standard output to match Tree's structure
 		 */
 		void printKeys() const;

 		/*
 		 *Prints all values in the B+ Tree to standard output
 		 */
 		void printValues() const;

 	private:
 		int nodeSize;
 		void* root;
 };
 #endif
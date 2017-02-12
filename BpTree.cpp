/*
 *BpTree.cp
 *Authors: Dave Gill, Jackie Lang
 */

#include "BpTree.h"
#include "Node.h"
#include <string>
#include <iostream>

BpTree::BpTree(int n){
	nodeSize = n;
	root = nullptr;
}

BpTree::BpTree(BpTree& other){
	nodeSize = other.nodeSize;
	root = other.root; //temporary just to compile. Needs to be made proper
}

BpTree::~BpTree(){
	delete root; //temporary just to compile. Needs to be made proper
}

/*
 *Inserts value into B+ Tree, sorted on key value
 *All key values must be unique, or insertion will fail
 *Returns true if insertion was successful, otherwise false
 */
bool BpTree::insert(int key, std::string value){
	return true;
}

/*
*Removes the entry from the B+ Tree that corresponds to the key value
*Returns true if the value was successfully removed, false if the value is not in the tree
*/
bool BpTree::remove(int key){
	return true;
}

/*
 *Returns the string value corresponding to the key
*If the key is not in the B+Tree, will return the empty string ""
 */
std::string BpTree::find(int key) const{
	return "";
}

/*
 *Prints all keys in the B+ Tree to standard output to match Tree's structure
 */
void BpTree::printKeys() const{
	std::cout << "printKeys\n";
}

/*
 *Prints all values in the B+ Tree to standard output
 */
void BpTree::printValues() const{
	std::cout << "printValues\n";
}
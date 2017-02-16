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

BpTree::BpTree(BpTree& other){ //need to make copy
	nodeSize = other.nodeSize;
	root = other.root; //temporary just to compile. Needs to be made proper
}

BpTree::~BpTree(){
	if(root != nullptr){
		((Node*)root)->fullDeletion();
		delete (Node*)root;
	}
}

/*
 *Inserts value into B+ Tree, sorted on key value
 *All key values must be unique, or insertion will fail
 *Returns true if insertion was successful, otherwise false
 */
bool BpTree::insert(int key, std::string value){
	if(root == nullptr){
		root = new LeafNode(nodeSize);
	}

	void* insertionNode = ((Node*)root)->findLeaf(key);
	if( ((LeafNode*)insertionNode)->contains(key)){
		return false; //duplicates are not allowed
	}

	root = ((Node*)root)->insert(key, value);
	return true;
}

/*
*Removes the entry from the B+ Tree that corresponds to the key value
*Returns true if the value was successfully removed, false if the value is not in the tree
*/
bool BpTree::remove(int key){
	if(root == nullptr){
		return false;
	}

	void* deletionNode = ((Node*)root)->findLeaf(key);
	if( !((LeafNode*)deletionNode)->contains(key)){
		return false; //duplicates are not allowed
	}

	((Node*)root)->remove(key);

	if( ((Node*)root)->  isEmpty()){ //only returns true with InnerNodes that have empty pointer vectors
		void* temp = root;
		root = ((InnerNode*)root)->extra;
		((Node*)root)->parent = nullptr;
		delete (Node*)temp;
	}
	return true;
}

/*
 *Returns the string value corresponding to the key
*If the key is not in the B+Tree, will return the empty string ""
 */
std::string BpTree::find(int key) const{
	if(root == nullptr){
		return "";
	}
	return ((Node*)root)->find(key);
}

/*
 *Prints all keys in the B+ Tree to standard output to match Tree's structure
 */
void BpTree::printKeys() const{
	if(root == nullptr){
		return;
	}
	((Node*)root)->printNode();
}

/*
 *Prints all values in the B+ Tree to standard output
 */
void BpTree::printValues() const{
	if(root == nullptr){
		return;
	}
	((Node*)root)->printValues();
}